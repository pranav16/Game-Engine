#pragma once
#ifndef MESSAGING_SYSTEM_H
#define MESSAGING_SYSTEM_H
#include "HashString.h"
#include <map>
#include <vector>
#include "MessageHandler.h"
#include "MutexLock.h"
#include "HashString.h"
namespace Engine
{

namespace MessagingSystem
{
	class MessageHandlerSystem
	{
	public:
		static MessageHandlerSystem* getInstance();
		~MessageHandlerSystem();
		
		void RegisterHandler(const char* message, IMessageHandler* handler);
		void DeRegisterHandler(const char* message, IMessageHandler* handler);
		void sendMessage(const char* message, void* payLoad);
		void shutDown();
	private:
		MessageHandlerSystem();
		static MessageHandlerSystem* instance;
		std::map<const char*, std::vector<IMessageHandler*>>registeredHandler;
		MutexLock messageMapLock;
	};
} //namespace MessagingSystem
} //namespace Engine
#endif