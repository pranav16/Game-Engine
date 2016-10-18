#include "MessagingSystem.h"
#include "Assert.h"

Engine::MessagingSystem::MessageHandlerSystem* Engine::MessagingSystem::MessageHandlerSystem::instance = nullptr;
void Engine::MessagingSystem::MessageHandlerSystem::RegisterHandler(const char* message, IMessageHandler * handler)
{
	messageMapLock.Lock();
	MessagedAssert(handler != nullptr,"handler cannot be null")
	if (registeredHandler.find(message) != registeredHandler.end())
	{
		registeredHandler[message].push_back(handler);
	}
	else
	{
		registeredHandler[message].push_back(handler);
	}
	messageMapLock.Release();
}

void Engine::MessagingSystem::MessageHandlerSystem::DeRegisterHandler(const char* message, IMessageHandler * handler)
{
	messageMapLock.Lock();
	//MessagedAssert(registeredHandler.find(message) == registeredHandler.end(), "not registred event")
	std::vector<IMessageHandler*>handlers = registeredHandler[message];
	std::vector<IMessageHandler*>::iterator handlerItr = handlers.begin();
	while (handlerItr != handlers.end())
	{
		if ((*handlerItr) == handler)
		{
			handlers.erase(handlerItr);
			break;
		}
	}
	registeredHandler[message] = handlers;
	handlers = registeredHandler[message];
	messageMapLock.Release();
}

void Engine::MessagingSystem::MessageHandlerSystem::sendMessage(const char* message, void * payLoad)
{
	messageMapLock.Lock();
	MessagedAssert(payLoad !=nullptr,"payload is null!");
	std::vector<IMessageHandler*>handlers = registeredHandler[message];
	std::vector<IMessageHandler*>::iterator handlerItr = handlers.begin();
	while (handlerItr != handlers.end())
	{
		HashString msg(message);
		(*handlerItr)->HandleMessage(msg,payLoad);
		handlerItr++;
	}
	messageMapLock.Release();

}
Engine::MessagingSystem::MessageHandlerSystem* Engine::MessagingSystem::MessageHandlerSystem::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MessageHandlerSystem();
	}
	return instance;
}
void Engine::MessagingSystem::MessageHandlerSystem::shutDown()
{
	if (instance)
		delete instance;
}
Engine::MessagingSystem::MessageHandlerSystem::~MessageHandlerSystem()
{

}
Engine::MessagingSystem::MessageHandlerSystem::MessageHandlerSystem():messageMapLock(L"MESSAGEMAPLOCk")
{

}
