#pragma once



#include "Physics.h"
#include "SmartPointer.h"
namespace Engine
{

	inline Physics* Physics::getInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new Physics();
		}

		return myInstance;
	}
	inline PhysicsInfo* Physics::addObjectToPhysicSystem(SmartPointer<GameObject>& object, double mass, double coefficientOfDrag, Engine::Vector forces)
	{
		PhysicsInfo* info = new PhysicsInfo;
		info->object = object;
		MessagedAssert(object != nullptr, "game object cannot be null");
		info->mass = mass;
		MessagedAssert(object != nullptr, "game object mass  cannot be zero");
		info->coefficientOfDrag = coefficientOfDrag;
		MessagedAssert(object != nullptr, "game object force  cannot be zero");
		info->forces = forces;
		physicObjects.push_back(info);
		return info;
	}
	inline void Physics::addPhysicsInfo(PhysicsInfo* info)
	{
		MessagedAssert(info != nullptr, "adding null to physics objects list!!");
		physicObjects.push_back(info);
	}

	inline PhysicsInfo* Physics::createDelayedPhysicObject(SmartPointer<GameObject>& obj, double mass, double coefficientOfDrag, Engine::Vector force)
	{
		PhysicsInfo* info = new PhysicsInfo;
		info->object = obj;
		MessagedAssert(obj != nullptr, "game object cannot be null");
		info->mass = mass;
		info->coefficientOfDrag = coefficientOfDrag;
		info->forces = force;
		return info;
	}

}
