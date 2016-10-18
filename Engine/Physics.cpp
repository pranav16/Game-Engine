#include "Physics.h"
#include "GameObject.h"
#include "Vector.h"
#include "Assert.h"


namespace Engine
{

	Physics* Physics::myInstance = nullptr;


	void Physics::removeObject(SmartPointer<GameObject>& object)
	{
		std::vector<PhysicsInfo*>::iterator physicsInfoIterator = Physics::physicObjects.begin();
		while (physicsInfoIterator != Physics::physicObjects.end())
		{
			if ((*physicsInfoIterator)->object == object)
			{
				delete (*physicsInfoIterator);
				Physics::physicObjects.erase(physicsInfoIterator);
				return;
			}
			physicsInfoIterator++;
		}
	}


	void Physics::addForce(SmartPointer<GameObject>& object, Engine::Vector force)
	{
		std::vector<PhysicsInfo*>::iterator physicsInfoIterator = Physics::physicObjects.begin();
		while (physicsInfoIterator != Physics::physicObjects.end())
		{
			if ((*physicsInfoIterator)->object == object)
			{
				operator+=((*physicsInfoIterator)->forces, force);
				return;
			}
			physicsInfoIterator++;
		}
	}
	void Physics::update(double dt)
	{
		std::vector<PhysicsInfo*>::iterator physicsInfoIterator = Physics::physicObjects.begin();
		while (physicsInfoIterator != Physics::physicObjects.end())
		{
			Vector currentVelocity = (*physicsInfoIterator)->object->getVelocity();
			Vector forces = (*physicsInfoIterator)->forces;
			Vector drag = currentVelocity  * (*physicsInfoIterator)->coefficientOfDrag;
			forces -= drag;
			(*physicsInfoIterator)->forces = forces;
			Vector accelaration = forces / (*physicsInfoIterator)->mass;
			Vector updatedVelocity = currentVelocity + (accelaration* dt);
			Vector averageVelocity = (currentVelocity + updatedVelocity) / 2;
			Vector updatedPostion = (*physicsInfoIterator)->object->getPosition()+ (averageVelocity * dt);
			(*physicsInfoIterator)->object->setPosition(updatedPostion);
			(*physicsInfoIterator)->object->setVelocity(updatedVelocity);
			physicsInfoIterator++;
		}
	}
	void Physics::update(PhysicsInfo * object1, PhysicsInfo * object2,double dt)
	{

		Vector currentVelocityObj1 = object1->object->getVelocity();
		Vector forcesObject1 = object1->forces;
		Vector dragObject1 = currentVelocityObj1  * object1->coefficientOfDrag;
		forcesObject1 -= dragObject1;
		object1->forces = forcesObject1;
		Vector accelarationObject1 = forcesObject1 / object1->mass;
		Vector updatedVelocityObject1 = currentVelocityObj1 + (accelarationObject1* dt);
		Vector averageVelocityObject1 = (currentVelocityObj1 + updatedVelocityObject1) / 2;
		Vector updatedPostionObject1 = object1->object->getPosition() + (averageVelocityObject1 * dt);
		object1->object->setPosition(updatedPostionObject1);
		object1->object->setVelocity(updatedVelocityObject1);

		Vector currentVelocityObj2 = object2->object->getVelocity();
		Vector forcesObject2 = object2->forces;
		Vector dragObject2 = currentVelocityObj2  * object2->coefficientOfDrag;
		forcesObject2 -= dragObject2;
		object2->forces = forcesObject2;
		Vector accelarationObject2 = forcesObject2 / object2->mass;
		Vector updatedVelocityObject2 = currentVelocityObj2 + (accelarationObject2* dt);
		Vector averageVelocityObject2 = (currentVelocityObj2 + updatedVelocityObject2) / 2;
		Vector updatedPostionObject2 = object2->object->getPosition() + (averageVelocityObject2 * dt);
		object2->object->setPosition(updatedPostionObject2);
		object2->object->setVelocity(updatedVelocityObject2);
	}


	bool Physics::init()
	{
		return true;
	}
	void Physics::shutDown()
	{
		std::vector<PhysicsInfo*>::iterator physicsInfoIterator = Physics::physicObjects.begin();
		while (physicsInfoIterator != Physics::physicObjects.end())
		{

			delete (*physicsInfoIterator);
			physicsInfoIterator = Physics::physicObjects.erase(physicsInfoIterator);
		}
		delete myInstance;
	}
}
