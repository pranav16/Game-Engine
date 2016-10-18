#pragma once
#ifndef  COLLISION_CHECK_H
#define COLLISION_CHECK_H
#include "Matrix4.h"
#include "Actor.h"
namespace Engine
{

	class  CollisionCheck
	{
		
	public:	

		static CollisionCheck* getInstance();
		void update(float dt);
		void addCollidable(Actor* actor);
		void removeActor(Actor* actor);
		~CollisionCheck();
	private:
		CollisionCheck();
		static CollisionCheck* instance;
		void checkForcollision(int index,float dt);
		void updatePhysicsPropertiesAfterCollision(Collision& data,double dt);
		bool checkCollisions(Actor* A, Actor* B, float dt, Collision & collisionInfo);
		bool checkForAxisCollisions(float start, float end,float center, float realativevelocity,float& axisClose, float& axisOpen);
		std::vector<Actor*>collidables;
	
	};

}



#endif // ! COLLISION_CHECK_H
