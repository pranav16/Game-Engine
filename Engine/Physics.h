#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>
#include "Vector.h"
#include "GameObject.h"
#include "SmartPointer.h"

namespace Engine
{
	

	struct PhysicsInfo
	{
		double mass;
		double coefficientOfDrag;
		Engine::Vector forces;
		SmartPointer<GameObject> object;
	};


	class Physics
	{
	public:
		
		inline  static Physics* getInstance();
		inline PhysicsInfo* addObjectToPhysicSystem(SmartPointer<GameObject>& obj,double mass, double coefficientOfDrag,Engine::Vector force = Engine::Vector::VectorZero);
		inline PhysicsInfo* createDelayedPhysicObject(SmartPointer<GameObject>& obj, double mass, double coefficientOfDrag, Engine::Vector force = Engine::Vector::VectorZero);
		inline void addPhysicsInfo(PhysicsInfo* info);
		
		void removeObject(SmartPointer<GameObject>& object );
		void update(double dt);
		void update(PhysicsInfo * object1,PhysicsInfo * object2,double dt);
		bool init();
	    void shutDown();
		void addForce(SmartPointer<GameObject>& object, Engine::Vector force);

	private:
		std::vector<PhysicsInfo*>physicObjects;
		static Physics* myInstance;
		Physics() {};
		Physics(const Physics& physics) {};
		Physics& operator=(const Physics& physics) {};
			   


	};
}
#include "Physics_Ini.h"
#endif