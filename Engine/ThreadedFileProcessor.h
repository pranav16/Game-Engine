#ifndef _THREADEDFILEREAD_
#define _THREADEDFILEREAD_
#include "WaitableObject.h"
#include <inttypes.h>
namespace Engine
{
class ThreadedFileRead 
{
public:
	static void create(char* pFileName, DWORD & threadId) {
		m_filePath = _strdup(pFileName); 
		ThreadId = threadId;
		m_handle = INVALID_HANDLE_VALUE;
	};
	~ThreadedFileRead();
	static bool run();
	static bool resume();
	static bool suspend();

private:
	static DWORD WINAPI entry(void * i_pThreadParameters);
	static uint8_t* LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	static const char* m_filePath;
	static DWORD ThreadId;
	static HANDLE m_handle;
};

}





#endif //_THREADEDFILEREAD_
