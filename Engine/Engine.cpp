#include "Engine.h"
#include "HeapManager.h"
#include "Assert.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "FixedSizeAllocator.h"
#include "Physics.h"
#include "Actor.h"
#include "FileProcessor.h"
#include "MessagingSystem.h"
#include "CollisionCheck.h"
#include "Serializer.h"
#include "ScoringSystem.h"
namespace Engine
{
EngineMain* EngineMain::myInstance;
bool EngineMain::init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	const size_t 		sizeHeap = 1024 * 1024;
	const size_t blockSize = 16;
	// Allocate memory for my test heap.
	void * alignedBlockMem = _aligned_malloc(sizeHeap, 4);
	MessagedAssert(alignedBlockMem != nullptr, "out of memory");
	FixedSizeAllocator::getInstance()->create(alignedBlockMem, sizeHeap, blockSize);
	Engine::SpriteRenderer::getInstance()->init(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);
	Engine::Serializer::getInstance()->initialize(1024 * 1024);

	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\wall4.lua"));
	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\wall3.lua"));
	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\Wall1.lua"));
	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\wall2.lua"));
	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\Player.lua"));
	Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\Enemy.lua"));

	//Engine::FileProcessor::getInstance().AddFileDataLoadQueue(*new Engine::FileData(nullptr, 0, "data\\Bg.lua"));
	GLib::SetKeyStateChangeCallback(keyBackCallBack);
	return true;
}


void EngineMain::run(double dt)
{

	Engine::FileProcessor::getInstance().updateGameActors();
	if (worldActors.size() >= 6)
	{
		Engine::Physics::getInstance()->update(dt);
		Engine::CollisionCheck::getInstance()->update((float)dt);
		Engine::SpriteRenderer::getInstance()->run();
		for (size_t i = 0; i < worldActors.size(); i++)
		{
			if (worldActors[i]->getController())worldActors[i]->getController()->update(dt);
				
		}
	}
}
EngineMain::~EngineMain()
{

}
void EngineMain::shutDown()
{
	Engine::FileProcessor::shutdown();
	Engine::SpriteRenderer::getInstance()->shutDown();
	Physics::getInstance()->shutDown();
	MessagingSystem::MessageHandlerSystem::getInstance()->shutDown();
	removeActorsFromPool();
	myInstance->~EngineMain();
	Engine::Serializer::getInstance()->shutDown();
	free(myInstance);
	HeapManager::getHeapManager()->deleteHeap();
	FixedSizeAllocator::getInstance()->deleteHeap();
	
}
void  EngineMain::addActorToPool(Actor* actor)
{
	worldActors.push_back(actor);
	if (worldActors.size() >= 6)
		Engine::EngineMain::getInstance()->saveInitState();
	
}
void  EngineMain::removeActorFromPool(Actor* actor)
{
	std::vector<Actor*>::iterator Iterator = worldActors.begin();
	while (Iterator != worldActors.end())
	{
		if ((*Iterator) == actor)
		{
		SpriteRenderer::getInstance()->removeSpriteObject((*Iterator)->getGameObject());
		Physics::getInstance()->removeObject((*Iterator)->getGameObject());
		Iterator = worldActors.erase(Iterator);
		continue;
		}
		Iterator++;
	}

}
void EngineMain::removeActorsFromPool()
{
	std::vector<Actor*>::iterator Iterator = worldActors.begin();
	while (Iterator != worldActors.end())
	{
		if ((*Iterator) !=nullptr)
		{
			SpriteRenderer::getInstance()->removeSpriteObject((*Iterator)->getGameObject());
			Physics::getInstance()->removeObject((*Iterator)->getGameObject());
			CollisionCheck::getInstance()->removeActor((*Iterator));
			//delete (*Iterator)->getGameObject();
			delete(*Iterator)->getBoundingBox();
			delete (*Iterator);
			Iterator = worldActors.erase(Iterator);
			continue;
		}
		Iterator++;
	}
}

void EngineMain::saveInitState()
{
	for (size_t i = 0; i < worldActors.size(); i++)
	{
		initialPositions.push_back(worldActors[i]->getGameObject()->getPosition());
	}
}
void EngineMain::resetGame()
{
	for (size_t i = 0; i < worldActors.size(); i++)
	{
		worldActors[i]->getGameObject()->setPosition(initialPositions[i]);
		worldActors[i]->getPhysics()->forces = Vector::VectorZero;
	}
}

void EngineMain::keyBackCallBack(unsigned int i_VKeyID, bool bWentDown)
{
	
	MessagingSystem::MessageHandlerSystem::getInstance()->sendMessage("ButtonPressed",&i_VKeyID);
	switch (i_VKeyID)
	{
	case 9: {
		Engine::Serializer::getInstance()->serializeObjects();
		break;
	}
	case 16: {
		Engine::Serializer::getInstance()->deSerializeObjects();
		break;
	}
	case 82: {
		Engine::EngineMain::getInstance()->resetGame();
		break;
	}
	default:
		break;
	}

}


}