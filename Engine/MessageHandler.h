#pragma once
#ifndef  MESSAGE_HANDLER_H
#define	 MESSAGE_HANDLER_H
#include "HashString.h"
#include <map>
#include <vector>
namespace Engine
{
	namespace MessagingSystem
	{

		class IMessageHandler
		{
		public:
			IMessageHandler() {};
			virtual void HandleMessage(const HashString message, void* payLoad) = 0;
		};
	    



	}
}

#endif // ! MESSAGE_HANDLER_H
