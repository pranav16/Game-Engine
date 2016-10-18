#pragma once
#ifndef  COLLISIONDATA_H
#define COLLISIONDATA_H
#include "Vector4.h"

namespace Engine
{
	struct BoundingBox
	{
		Vector4 Center;
		Vector4 BoxEntents;

	};

	struct Collision
	{
	
		class Actor* pActor;
		class Actor* pOther;
		float timeOfCollision;
		Vector4 collisionNormal;
	};
}
#endif // ! COLLISIONDATA