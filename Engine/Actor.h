#pragma once
#ifndef __ACTOR__H___
#define  __ACTOR__H___
#include "GameObject.h"
#include "Physics.h"
#include <inttypes.h>
#include "CollisionData.h"
namespace Engine
{
class Actor
{
public:
	inline Actor(struct SpriteRenderInfo* sinfo,  PhysicsInfo* pinfo,  SmartPointer<GameObject> obj) :renderInfo(sinfo), physicsInfo(pinfo), gameObj(obj) {};
	inline Actor();
	inline ~Actor();
	inline  struct SpriteRenderInfo* getRenderer() const;
	inline   PhysicsInfo* getPhysics() const;
	inline   SmartPointer<GameObject> getGameObject() const;
	inline void  setRenderer(struct SpriteRenderInfo* info);
	inline void setPhysics( PhysicsInfo* info);
	inline void setGameObject(SmartPointer<GameObject> obj) ;
	inline void setActorController(class IActorController* controller);
	inline void setBoundingBox(BoundingBox* bondingBox);
	inline BoundingBox* getBoundingBox();
	inline int getCollisionType()const;
	inline void setCollisionType(int type);
	inline class IActorController* getController()const;
	static Actor* loadActorFromFile(const char* filePath);
	static Actor*loadActorFromData(uint8_t* data,size_t sizeFile);

private:
	 struct SpriteRenderInfo* renderInfo;
	 PhysicsInfo* physicsInfo;
	
	 SmartPointer<GameObject> gameObj;
	 class IActorController* m_controller;
	 int collisionType;
	 BoundingBox* m_boundingBox;
};

}//namespace Engine
#include "ActorIni.h"
#endif // !