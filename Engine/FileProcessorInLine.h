#pragma once
#ifndef FILEPROCESORINLINE
#define FILEPROCESORINLINE
#include "FileProcessor.h"
#include "Assert.h"
#include "FileRead.h"
#include "FileProcessDataToActor.h"
namespace Engine
{

	FileProcessor::~FileProcessor()
	{

	}
	FileData* FileProcessor::getFileDataLoadQueue() 
	{
		FileData * pLoadTask = NULL;
		m_LoadQueueMutex.Lock();
		if (!m_LoadQueue.empty())
		{
			pLoadTask = m_LoadQueue.front();
			m_LoadQueue.pop();
		}

		m_LoadQueueMutex.Release();
		return pLoadTask;
	}
	FileData* FileProcessor::getFileDataProcessQueue() 
	{
		FileData *  pLoadTaskData = NULL;

		m_ProcessQueueMutex.Lock();

		if (!m_ProcessQueue.empty())
		{
			pLoadTaskData = m_ProcessQueue.front();
			m_ProcessQueue.pop();
		}

		m_ProcessQueueMutex.Release();

		return pLoadTaskData;
	
	}
	inline Actor*  FileProcessor::getActorFromPool()
	{
		Actor* actor = nullptr;
		m_ActorPoolMutex.Lock();
		if (!m_ActorsPool.empty())
		{
			actor = m_ActorsPool.front();
			m_ActorsPool.pop();
		}
		m_ActorPoolMutex.Release();
		return actor;
	}
	inline void FileProcessor::AddActorToPool(Actor* actor)
	{
		m_ActorPoolMutex.Lock();
		m_ActorsPool.push(actor);
		m_ActorPoolMutex.Release();
	}
	void FileProcessor::FileProcessor::AddFileDataLoadQueue(FileData& fileData)
	{
		m_LoadQueueMutex.Lock();

		m_LoadQueue.push(&fileData);

		m_LoadQueueMutex.Release();

		m_LoadQueueSemaphore.Increment();
	}
	void FileProcessor::AddFileDataProcessQueue(FileData& fileData)
	{
		m_ProcessQueueMutex.Lock();

		m_ProcessQueue.push(&fileData);

		m_ProcessQueueMutex.Release();
		m_ProcessQueueSemaphore.Increment();
	}
	 FileProcessor& FileProcessor::getInstance()
	{
		if (Instance == NULL)
		{
			DWORD ThreadID = 0;

			HANDLE LoadThreadHandle = FileRead::getInstance()->createThread();
			HANDLE ProessThreadHandle = FileDataToActor::getInstance()->createThread();
			Instance = new FileProcessor(LoadThreadHandle, ProessThreadHandle);
		}

		MessagedAssert(Instance != NULL,"could not create singleton");

		return *Instance;
	}

	
	 FileProcessor::FileProcessor(HANDLE readthreadHandle, HANDLE loadthreadHandle) :
		 m_ShutdownRequestEvent(L"ShutdownRequestEvent", false),
		 m_LoadThreadHandle(readthreadHandle),
		 m_ProcessThreadHandle(loadthreadHandle),
		 m_LoadQueueSemaphore(L"LoadQueueSemaphore", 100, 0),
		 m_LoadQueueMutex(L"LoadQueueMutex"),
		 m_ProcessQueueSemaphore(L"ProcessQueueSemaphore", 100, 0),
		 m_ProcessQueueMutex(L"ProcessQueueMutex"), 
		 m_ActorPoolMutex(L"ActorPoolMutex")
	 {
		 FileRead::getInstance()->Resume();
		 FileDataToActor::getInstance()->Resume();
	 }
}



#endif // !FILEPROCESORINLINE
