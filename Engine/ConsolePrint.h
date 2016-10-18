#ifndef __CONSOLE_PRINT_H
#define __CONSOLE_PRINT_H
#include "Target.h"
namespace Engine
{
enum Verbosity
{
		Warnings ,Error
};
void ConsolePrint( const char * i_fmt, ... );
void ConsolePrintCustom(const char* lineInfo,const char* verbosity,const char * i_fmt, ...);

} // Namespace Engine

// This is how we handle variable argument pre-processor macros
// This is only supported by compilers that support the C99 standard
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(lineinfo,verbosity,fmt,...) Engine::ConsolePrintCustom(lineinfo,#verbosity,(fmt),__VA_ARGS__)
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define DEBUG_PRINT(fmt,...) void(0)
#endif


#endif // __CONSOLE_PRINT_H