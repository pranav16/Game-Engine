#include "GameObject.h"

namespace Engine
{
	
	GameObject::GameObject()
	{
		name = NULL;
		controller = NULL;
	}

	 GameObject::GameObject(const GameObject& object)
	{
		controller = object.controller;
		position = object.position;
		if (object.name)
		{
			size_t length = strlen(object.name) + 1;
			name = new char[length];
			strncpy_s(name,length, object.name, length);
		}
	}
	 GameObject& GameObject::operator=(const GameObject& object)
	{
		if (&object == this)
			return *this;
		if (this->name)
			delete[] name;

		this->controller = object.controller;
		this->position = object.position;
		if (object.name)
		{
			size_t length = strlen(object.name) + 1;
			name = new char[length];
			strncpy_s(name,length, object.name, length);
		}
		return *this;
	}
	
	 GameObject::~GameObject()
	 {
		 if (name)
			 free(name);
	 }

}
