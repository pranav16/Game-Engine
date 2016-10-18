#ifndef __ACTORINI__H___
#define  __ACTORINI__H___
#include "IActorController.h"
#include "Actor.h"
namespace Engine
{
	inline  Actor::Actor()
	{

	}

	inline  Actor::~Actor()
	{
		

	}
	inline SpriteRenderInfo * Actor::getRenderer() const
	{
		return renderInfo;
	}
	inline  PhysicsInfo*  Actor::getPhysics() const
	{
		return physicsInfo;
	}
	inline   SmartPointer<GameObject> Actor::getGameObject() const
	{
		return gameObj;
	}

	inline void Actor::setRenderer(SpriteRenderInfo * info)
	{
		renderInfo = info;
	}

	inline void  Actor::setPhysics(PhysicsInfo* info)
	{
		 physicsInfo = info;
	}
	inline void  Actor::setGameObject(SmartPointer<GameObject> obj)
	{
		gameObj = obj;
	}
	inline void  Actor::setActorController(IActorController* controller)
	{
		m_controller = controller;
	}

	inline void Actor::setBoundingBox(BoundingBox * bondingBox)
	{
		m_boundingBox = bondingBox;
	}
	inline BoundingBox * Actor::getBoundingBox()
	{
		return m_boundingBox;
	}
	inline IActorController* Actor::getController()const
	{
		return m_controller;
	}
	inline int Actor::getCollisionType()const
	{
		return collisionType;
	}
	inline void Actor::setCollisionType(int type)
	{
		collisionType = type;
	}


}// Engine
#endif

