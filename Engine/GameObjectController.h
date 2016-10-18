#ifndef GAME_OBJECT_CONTROLLER_H
#define GAME_OBJECT_CONTROLLER_H
#include "GameObject.h"
namespace Engine
{
	class GameObject;
	class GameObjectController
	{

	public:
	 virtual void moveGameObject(GameObject & object,const char direction) = 0;
	

	};

}//namespace

#endif //GAME_OBJECT_CONTROLLER_H