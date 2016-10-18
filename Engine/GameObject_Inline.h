#include "GameObject.h"
#include "assert.h"

namespace Engine
{
	inline Vector GameObject::getPosition() const
	{
		return position;
	}

	inline void GameObject::setPosition(const Vector a)
	{
		position = a;
	}
	inline Vector GameObject::getVelocity() const
	{
		return velocity;
	}
	inline void GameObject::setVelocity(const Vector vector)
	{
		velocity = vector;
	}
	inline void GameObject::setController(GameObjectController * controller)
	{
		MessagedAssert(controller != NULL, "player cannot be null!");
		this->controller = controller;
	}
	inline GameObjectController* GameObject::getController() const
	{
		return controller;
	}
	inline void GameObject::setName(const char* name)
	{
		MessagedAssert(name != nullptr, "Name is being set to null");
		if (this->name)
			delete[]this->name;
		this->name =const_cast<char*>(name);
	}
	inline void Engine::GameObject::setZRoation(float rot)
	{
		rotation = rot;
	}
	inline float Engine::GameObject::getZRotation()
	{
		return rotation;
	}

	inline std::string GameObject::getName() const
	{
		return name;
	}
	inline HashString GameObject::getSerializableType()
	{
		return "GameObject";
	}
	inline HashString GameObject::getSerializableId()
	{
		return name;
	}

	inline size_t GameObject::serialize(uint8_t* buffer)
	{
		MessagedAssert(buffer != nullptr,"buffer passed to gameobject for serialization is null");

		memcpy(buffer, &position, sizeof(position));

		return sizeof(position);
	}
	inline size_t GameObject::deserialize(uint8_t* buffer)
	{
		
		memcpy(&(position),buffer, sizeof(position));
		return sizeof(position);
	}


}//closing namspace engine