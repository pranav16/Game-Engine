#include "FileRead.h"
#include "FileProcessor.h"
#include "Assert.h"
namespace Engine
{
	FileRead* FileRead::fileReadInstance = nullptr;
	FileRead::FileRead()
	{
	}

	FileRead * FileRead::getInstance()
	{
		if (fileReadInstance == nullptr)
			fileReadInstance = new FileRead();
		return fileReadInstance;
	}

	FileRead::~FileRead()
	{
	}

	HANDLE FileRead::createThread()
	{
		DWORD ThreadID = 0;
		readThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FileRead::LoadThreadFunction, NULL, CREATE_SUSPENDED, &ThreadID);
		return readThreadHandle;
	}

	void FileRead::Resume()
	{
		ResumeThread(readThreadHandle);
	}

	DWORD FileRead::LoadThreadFunction(void * i_pThreadData)
	{
		FileProcessor & Me = FileProcessor::getInstance();

		OVERLAPPED FileOverlapped;

		FileOverlapped.Offset = FileOverlapped.OffsetHigh = 0;
		FileOverlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		HANDLE LoadHandles[] = { Me.m_ShutdownRequestEvent.GetHandle(), Me.m_LoadQueueSemaphore.GetHandle() };
		HANDLE ReadHandles[] = { Me.m_ShutdownRequestEvent.GetHandle(), FileOverlapped.hEvent };

		bool bDone = false;

		while (!bDone)
		{
			// Me.m_LoadQueueSemaphore.WaitAndDecrement();
			DWORD LQResult = WaitForMultipleObjects(sizeof(LoadHandles) / sizeof(LoadHandles[0]), LoadHandles, FALSE, INFINITE);

			if (LQResult == WAIT_OBJECT_0)
			{
				bDone = true;
			}
			else if (LQResult == WAIT_OBJECT_0 + 1)
			{
				FileData * pLoadTask = Me.getFileDataLoadQueue();

				if (pLoadTask)
				{
					const char * pFileName = pLoadTask->m_fileName;
					MessagedAssert(pFileName != NULL,"filename is null");
					size_t fileNameSize = strlen(pFileName) + 1;
					LPWSTR fileName = new wchar_t[fileNameSize];
					size_t size;
					mbstowcs_s(&size,fileName,fileNameSize,pFileName, fileNameSize-1);
			
					HANDLE FileHandle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
					delete fileName;
					if (FileHandle == INVALID_HANDLE_VALUE)
					{
						free((void*)pLoadTask->m_fileName);
						delete pLoadTask;
					}
					else
					{
						DWORD FileSize = GetFileSize(FileHandle, NULL);
						MessagedAssert(FileSize != INVALID_FILE_SIZE,"file size is not correct");

						uint8_t * pFileBuffer = new uint8_t[FileSize];
						MessagedAssert(pFileBuffer != NULL,"could not create a buffer of required size");

						BOOL RFResult = ReadFile(FileHandle, pFileBuffer, FileSize, NULL, &FileOverlapped);
						if ((RFResult != TRUE) && (GetLastError() != ERROR_IO_PENDING))
						{
							free((void*)pLoadTask->m_fileName);
							delete pLoadTask;
						}
						else
						{
							DWORD RResult = WaitForMultipleObjects(sizeof(ReadHandles) / sizeof(ReadHandles[0]), ReadHandles, FALSE, INFINITE);
							if (RResult == WAIT_OBJECT_0)
							{
								CancelIo(FileHandle);
								free((void*)pLoadTask->m_fileName);
								delete pLoadTask;
								bDone = true;
							}
							else if (RResult == WAIT_OBJECT_0 + 1)
							{
								DWORD BytesRead = 0;
								BOOL GORResult = GetOverlappedResult(FileHandle, &FileOverlapped, &BytesRead, FALSE);
								MessagedAssert(GORResult == TRUE,"gorresult is false");
								FileData * pNewLoadTaskData = new FileData(pFileBuffer, BytesRead, pLoadTask->m_fileName);
								Me.AddFileDataProcessQueue(*pNewLoadTaskData);
								free((void*)pLoadTask->m_fileName);
								delete pLoadTask;
							}
							else
							{
								free((void*)pLoadTask->m_fileName);
								delete pLoadTask;
							}
						}
					}
				}
			}
			else
			{
				MessagedAssert(false,"something went wrong!!");
			}
		}

		CloseHandle(FileOverlapped.hEvent);
		return 0;
	}
}