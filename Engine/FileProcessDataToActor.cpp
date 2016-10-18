#include "FileProcessDataToActor.h"
#include "FileProcessor.h"
#include "Assert.h"
#include "Actor.h"
namespace Engine
{

	FileDataToActor* Engine::FileDataToActor::fileProcessInstance = nullptr;
	FileDataToActor * Engine::FileDataToActor::getInstance()
	{
		if (fileProcessInstance == nullptr)
		{
			fileProcessInstance = new FileDataToActor();
		}
		return fileProcessInstance;
	}

	Engine::FileDataToActor::~FileDataToActor()
	{
	}

	HANDLE Engine::FileDataToActor::createThread()
	{
		DWORD ThreadID = 0;
		processThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FileDataToActor::ProcessThreadFunction, NULL, CREATE_SUSPENDED, &ThreadID);
		return processThreadHandle;
		
	}

	void Engine::FileDataToActor::Resume()
	{
		ResumeThread(processThreadHandle);
	}

	DWORD Engine::FileDataToActor::ProcessThreadFunction(void * i_pThreadData)
	{
		FileProcessor & Me = FileProcessor::getInstance();

		HANDLE WaitHandles[] = { Me.m_ShutdownRequestEvent.GetHandle(), Me.m_ProcessQueueSemaphore.GetHandle() };

		bool bDone = false;

		while (!bDone)
		{
			//Me.m_ProcessQueueSemaphore.WaitAndDecrement();
			DWORD result = WaitForMultipleObjects(sizeof(WaitHandles) / sizeof(WaitHandles[0]), WaitHandles, FALSE, INFINITE);

			if (result == WAIT_OBJECT_0)
			{
				bDone = true;
			}
			else if (result == (WAIT_OBJECT_0 + 1))
			{
			 FileData * pLoadData = Me.getFileDataProcessQueue();

				if (pLoadData)
				{
					Actor* actor = Actor::loadActorFromData(pLoadData->m_pFileContents, pLoadData->m_FileContentsSize);
					FileProcessor::getInstance().AddActorToPool(actor);
					delete[] pLoadData->m_pFileContents;
					free((void*) pLoadData->m_fileName);
					delete pLoadData;
				}
			}
			else
			{
				MessagedAssert(false,"something went wrong");
				
			}
		}

		return 0;
		
	}

	FileDataToActor::FileDataToActor()
	{


	}
}