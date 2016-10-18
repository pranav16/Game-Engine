#include "CollisionCheck.h"
#include "MessagingSystem.h"
namespace Engine
{
	CollisionCheck* CollisionCheck::instance = nullptr;

	CollisionCheck* CollisionCheck::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new CollisionCheck();
		}

		return instance;
	}
	CollisionCheck::~CollisionCheck()
	{

	}
	CollisionCheck::CollisionCheck()
	{

	}
	void CollisionCheck::update(float dt)
	{
		size_t index = 0;
		while (index < collidables.size())
		{
			checkForcollision(index, dt);
			index++;
		}



	}

	void CollisionCheck::checkForcollision(int index, float dt)
	{
		Actor* actorToCheck = collidables[index];
		for (size_t i = index + 1; i < collidables.size(); i++)
		{
			Collision info;
			if (checkCollisions(actorToCheck, collidables[i], dt, info))
			{
				if (info.pActor->getCollisionType() == 1 && info.pOther->getCollisionType() != 1)
				{
					MessagingSystem::MessageHandlerSystem::getInstance()->sendMessage("TriggerCollision",&info);
				}
				else if (info.pActor->getCollisionType() != 1 && info.pOther->getCollisionType() == 1)
				{
					MessagingSystem::MessageHandlerSystem::getInstance()->sendMessage("TriggerCollision", &info);
				}
				else if(info.pActor->getCollisionType() != 1 || info.pOther->getCollisionType() != 1)
     			updatePhysicsPropertiesAfterCollision(info,dt);
			}


		}
	}
	void CollisionCheck::updatePhysicsPropertiesAfterCollision(Collision& data,double dt)
	{
		PhysicsInfo* object1 = data.pActor->getPhysics();
		PhysicsInfo* object2 = data.pOther->getPhysics();
	    //if collision is detected reset velocity 
		Physics::getInstance()->update(object1, object2, -dt);
		//advance till the time of collision
		Physics::getInstance()->update(object1, object2, data.timeOfCollision);
	
		Vector direction(data.collisionNormal.getX(),data.collisionNormal.getY(),data.collisionNormal.getZ());
		object1->object->setVelocity(Vector::VectorZero);
		object2->object->setVelocity(Vector::VectorZero);
		object1->forces = direction * object1->mass/5;
		object2->forces = direction * -object2->mass/5;
		//update physics with new velocities
		Physics::getInstance()->update(object1, object2,dt - data.timeOfCollision);

	}
	void CollisionCheck::addCollidable(Actor* actor)
	{
		collidables.push_back(actor);
	}
	void CollisionCheck::removeActor(Actor* actor)
	{
		std::vector<Actor*>::iterator itr = collidables.begin();
		while (itr != collidables.end())
		{
			if (*itr == actor)
			{
				collidables.erase(itr);
				break;
			}
			itr++;
		}


	}

	bool CollisionCheck::checkCollisions(Actor* A, Actor* B, float dt, Collision & collisionInfo)
	{
		
		// will be used to check earliest open and latest close
		float actorClose = 0.0f;
		float actorOpen = 1.0f;

		// will be used to check sepration close and open for a perticular axis
		float axisClose = 0.0f;
		float axisOpen = 1.0f;

		// transfroms from actors to world
		Matrix4 actorAToWorld = Matrix4::CreateTranslationCV(A->getGameObject()->getPosition())* Matrix4::CreateZRotationCV(A->getGameObject()->getZRotation());
		Matrix4 actorBToWorld = Matrix4::CreateTranslationCV(B->getGameObject()->getPosition()) *Matrix4::CreateZRotationCV(B->getGameObject()->getZRotation());
		
		//transfroms to and from A and B
		Matrix4 AToB = actorBToWorld.GetInverse() * actorAToWorld;
		Matrix4 BToA = actorAToWorld.GetInverse() * actorBToWorld;
		
		//calculating centers in each others coordinate systems
		Vector4 ACenterInB = AToB  * A->getBoundingBox()->Center;
		Vector4 BCenterInA = BToA * B->getBoundingBox()->Center;

		//calculating relative velocity atob in b coordinate system
		Vector relativeAVelocityInWorld = A->getGameObject()->getVelocity() - B->getGameObject()->getVelocity();
		Vector4 relativeVeloctityAInB(relativeAVelocityInWorld, 0.0f);
		relativeVeloctityAInB = AToB * relativeVeloctityAInB;
		
		//calculating the extents of A in B coordinate system
		Vector4 BoxExtentsXAInB = AToB *  Vector4(A->getBoundingBox()->BoxEntents.getX(), 0.0f, 0.0f, 0.0f);
		Vector4 BoxExtentsYAInB = AToB * Vector4(0.0f, A->getBoundingBox()->BoxEntents.getY(), 0.0f, 0.0f);
		float projectionExtendsAOnB_x = fabs(BoxExtentsXAInB.getX()) + fabs(BoxExtentsYAInB.getX());
		float projectionExtendsAOnB_Y = fabs(BoxExtentsXAInB.getY()) + fabs(BoxExtentsYAInB.getY());
		
		// combining the extents of A withs B to get a line to point check
		float CombinedExtentsX = projectionExtendsAOnB_x +  B->getBoundingBox()->BoxEntents.getY();
		float CombinedExtentsY = projectionExtendsAOnB_Y + B->getBoundingBox()->BoxEntents.getY();
		
		//start and end for x axis
		float start = B->getBoundingBox()->Center.getX() -  CombinedExtentsX;
		float end = B->getBoundingBox()->Center.getX() +  CombinedExtentsX;
	
		Vector4 collisionAxis = Matrix4::CreateZRotationCV(A->getGameObject()->getZRotation()).Col(0).getUnitVector();
	
		if (!checkForAxisCollisions(start,end, ACenterInB.getX(), relativeVeloctityAInB.getX(),axisClose, axisOpen))
		{
			return false;
		}

		if (axisClose > actorClose)
		{
			actorClose = axisClose;
			collisionAxis;
		}
		if (axisOpen < actorOpen)
		{
			actorOpen = axisOpen;
		}


	
		//start and end for y axis
		 start = B->getBoundingBox()->Center.getY() - CombinedExtentsY;
		 end = B->getBoundingBox()->Center.getY() + CombinedExtentsY;
		collisionAxis = Matrix4::CreateZRotationCV(A->getGameObject()->getZRotation()).Col(1).getUnitVector();
    if (!checkForAxisCollisions(start, end, ACenterInB.getY(), relativeVeloctityAInB.getY(), axisClose, axisOpen))
		{
			return false;
		}
		if (axisClose > actorClose)
		{
			actorClose = axisClose;
			collisionAxis;
		}
		if (axisOpen < actorOpen)
		{
			actorOpen = axisOpen;
		}

		//calculating the extents of B in A coordinate system
		Vector4 BoxExtentsXBInA = BToA *  Vector4(B->getBoundingBox()->BoxEntents.getX(), 0.0f, 0.0f, 0.0f);
		Vector4 BoxExtentsYBInA = BToA * Vector4(0.0f, B->getBoundingBox()->BoxEntents.getY(), 0.0f, 0.0f);
		float projectionExtendsBOnA_X = fabs(BoxExtentsXBInA.getX()) + fabs(BoxExtentsYBInA.getX());
		float projectionExtendsBOnA_Y = fabs(BoxExtentsXBInA.getY()) + fabs(BoxExtentsYBInA.getY());

		// combining the extents of A withs B to get a line to point check
		 CombinedExtentsX = projectionExtendsBOnA_X + A->getBoundingBox()->BoxEntents.getX();
		 CombinedExtentsY = projectionExtendsBOnA_Y +A->getBoundingBox()->BoxEntents.getY();
		
		start = A->getBoundingBox()->Center.getX() - CombinedExtentsX;
		end = A->getBoundingBox()->Center.getX() + CombinedExtentsX;

		//calculating relative velocity BtoA in B coordinate system
		Vector relativeBVelocityInWorld = B->getGameObject()->getVelocity() - A->getGameObject()->getVelocity();
		Vector4 relativeVeloctityBInA(relativeBVelocityInWorld, 0.0f);
		relativeVeloctityBInA = BToA * relativeVeloctityAInB;
		collisionAxis = Matrix4::CreateZRotationCV(B->getGameObject()->getZRotation()).Col(0).getUnitVector();
		if (!checkForAxisCollisions(start, end, BCenterInA.getX(), relativeVeloctityBInA.getX(), axisClose, axisOpen))
		{
			return false;
		}

		if (axisClose > actorClose)
		{
			actorClose = axisClose;
			collisionAxis ;
		}
		if (axisOpen < actorOpen)
		{
			actorOpen = axisOpen;
		}

		collisionAxis = Matrix4::CreateZRotationCV(B->getGameObject()->getZRotation()).Col(1).getUnitVector();
		start = A->getBoundingBox()->Center.getY() - CombinedExtentsY;
		end = A->getBoundingBox()->Center.getY() + CombinedExtentsY;
		//Check for separation parallel to obj2 X-axis
		if (!checkForAxisCollisions(start, end, BCenterInA.getY(), relativeVeloctityBInA.getY(), axisClose, axisOpen))
		{
			return false;
		}

		if (axisClose > actorClose)
		{
			actorClose = axisClose;
			collisionAxis;
		}
		if (axisOpen < actorOpen)
		{
			actorOpen = axisOpen;
		}



		//if a new seperation was opened before a seperation closing
		if (actorOpen > actorClose)
		{

		
				collisionInfo.pActor = A;
				collisionInfo.pOther = B;
				collisionInfo.timeOfCollision = actorClose;
				collisionInfo.collisionNormal = collisionAxis;
		
		}

		return actorOpen > actorClose;


	}

	bool CollisionCheck::checkForAxisCollisions(float start, float end,float center, float realativevelocity, float& axisClose, float& axisOpen)
	{

		if (start > end)
		{
			float swap = end;
			end = start;
			start = swap;
		}

		if (realativevelocity == 0.0f)
		{
			if (start < center && end > center)
				return true;
			else
			{
				axisClose = 0.0f;
				axisOpen = 1.0f;
				return false;
			}

		}
	
		axisClose = (start - center) / realativevelocity;
		axisOpen = (end - center) / realativevelocity;
		if (axisOpen < axisClose)
		{
			float swap = axisOpen;
			axisOpen = axisClose;
			axisClose = swap;
		}


		return !((axisClose >= 1.0f) || (axisOpen <= 0.0f));


	}
}


