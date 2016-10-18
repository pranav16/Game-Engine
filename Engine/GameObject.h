#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Vector.h"
#include "GameObjectController.h"
#include "Serializable.h"
#include <iostream>

namespace Engine 
{ 
class GameObjectController;
class  GameObject : public Serializable 
{
	
public:
	GameObject();
	inline GameObject(Vector position,Vector velocity,char* namev) : position(position),velocity(velocity),name(_strdup(namev)){};
	inline Vector getPosition() const;
	inline Vector getVelocity() const;
	inline void setVelocity(const Vector vector);
	inline void setPosition(const Vector a);
	inline void setController(GameObjectController * controller);
	inline GameObjectController* getController() const;
	inline void setName(const char* name);
	inline std::string getName()const;
	inline float getZRotation();
	inline void setZRoation(float rot);
	inline HashString getSerializableType();
    inline HashString getSerializableId();

	inline size_t serialize(uint8_t* buffer);
	inline size_t deserialize(uint8_t* buffer);
	GameObject(const GameObject& Object);
	GameObject& operator= (const GameObject& object);
	~GameObject();

	
private:
	Vector position;
	Vector velocity;
	float rotation;
	char* name;
	GameObjectController * controller;
	
};



}

#include "GameObject_Inline.h"
#endif // GAME_OBJECT_H