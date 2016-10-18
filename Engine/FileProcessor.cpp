#include "FileProcessor.h"
#include "SpriteRenderer.h"
#include "Physics.h"
#include "Engine.h"
Engine::FileProcessor* Engine::FileProcessor::Instance = nullptr;

void  Engine::FileProcessor::shutdown()
{
	if (Instance)
	{
		FileProcessor & Me = getInstance();

		Me.m_ShutdownRequestEvent.Signal();

		HANDLE ThreadHandles[] = { Me.m_LoadThreadHandle, Me.m_ProcessThreadHandle };

		DWORD Result = WaitForMultipleObjects(sizeof(ThreadHandles) / sizeof(ThreadHandles[0]), ThreadHandles, TRUE, INFINITE);

		delete Instance;
		Instance = NULL;
	}

}

void Engine::FileProcessor::updateGameActors()
{
	m_ActorPoolMutex.Lock();
	size_t numberOfElements = m_ActorsPool.size();
	for (size_t i = 0; i < numberOfElements; i++)
	{
		Actor* actor = getActorFromPool();
	    Physics::getInstance()->addPhysicsInfo(actor->getPhysics());
		if(actor->getRenderer())
		SpriteRenderer::getInstance()->addSpriteInfo(actor->getRenderer());
		Engine::EngineMain::getInstance()->addActorToPool(actor);
	}

	m_ActorPoolMutex.Release();
}
