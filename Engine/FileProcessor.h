#pragma once
#ifndef FILE_PROCESSOR_H
#define	FILE_PROCESSOR_H
#include <stdint.h>
#include <queue>
#include <Windows.h>
#include "ManualRestEvent.h"
#include "AutoResetEvents.h"
#include "MutexLock.h"
#include "Semaphores.h"
#include "FileRead.h"
#include "Actor.h"
namespace Engine
{
struct FileData
{
	uint8_t *				m_pFileContents;
	uint32_t 				m_FileContentsSize;
	const char*				 m_fileName;
	FileData(uint8_t * data, uint32_t contentSize, const char * pFileName) : m_pFileContents(data), m_FileContentsSize(contentSize) { m_fileName = _strdup(pFileName); };
};


	class FileProcessor
	{
	public:
		
		inline ~FileProcessor();
		inline FileData* getFileDataLoadQueue();
		inline FileData* getFileDataProcessQueue();
		inline void AddFileDataLoadQueue(FileData& fileData);
		inline void AddFileDataProcessQueue(FileData& fileData);
		inline Actor*  getActorFromPool();
		inline void AddActorToPool(Actor* fileData);
		static inline FileProcessor & getInstance();
		static void shutdown();
		void updateGameActors();

		MutalResetEvents		m_ShutdownRequestEvent;
		Semaphore				m_LoadQueueSemaphore;
		MutexLock				m_LoadQueueMutex;
		Semaphore				m_ProcessQueueSemaphore;
		MutexLock				m_ProcessQueueMutex;
		MutexLock				m_ActorPoolMutex;

	private:
		static FileProcessor* Instance;
		inline FileProcessor(HANDLE readthreadHandle, HANDLE loadthreadHandle);
		std::queue<FileData*>	m_LoadQueue;
		std::queue<FileData*>	m_ProcessQueue;
		std::queue<Actor*>		m_ActorsPool;
		HANDLE					m_LoadThreadHandle;
		HANDLE					m_ProcessThreadHandle;

		
	};

}

#include "FileProcessorInLine.h"

#endif // !FILE_PROCESSOR_H

