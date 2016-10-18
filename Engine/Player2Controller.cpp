#include "Player2Controller.h"
#include "MessagingSystem.h"
#include "Vector.h"

#include "Actor.h"
namespace Engine
{


	const HashString Player2Controller::ClassType = "Player2Controller";
	void Player2Controller::keyPressed()
	{

	}
	void Player2Controller::safeCast(IActorController & controller)
	{
		if (controller.m_type == ClassType)
		{
			Player2Controller* controller = reinterpret_cast<Player2Controller*>(&controller);
			controller->keyPressed();
		}
	}
	Player2Controller::Player2Controller() :IActorController(ClassType),speed(0.0)
	{

	}
	void 	Player2Controller::setActor(Actor* actor)
	{
		actorControlled = actor;
	}
	Actor* Player2Controller::getActor() const
	{
		return actorControlled;
	}
	Player2Controller::~Player2Controller()
	{

	}
	void Player2Controller::roatateImage(double dt)
	{
		double roatation = actorControlled->getGameObject()->getZRotation();
		roatation += speed * dt;
		actorControlled->getGameObject()->setZRoation(roatation);
	}
	 void Player2Controller::update(double dt)
	{
		roatateImage(dt);
	}
	void Player2Controller::HandleMessage(const HashString message, void* payLoad)
	{
		unsigned long keyId = *static_cast<unsigned int*>(payLoad);
		switch (keyId)
		{
		case 87: {
			Engine::Vector force(0.0f, 0.5f, 0.0f);
			SmartPointer<GameObject> obj = actorControlled->getGameObject();
			Engine::Physics::getInstance()->addForce(obj, force);

			break;
		}
		case 83: {
			Engine::Vector force(0.0f, -0.5f, 0.0f);
			SmartPointer<GameObject> obj = actorControlled->getGameObject();
			Engine::Physics::getInstance()->addForce(obj, force);

			break;
		}
		case 65: {
			Engine::Vector force(-0.5f, 0.0f, 0.0f);
			SmartPointer<GameObject> obj = actorControlled->getGameObject();
			Engine::Physics::getInstance()->addForce(obj, force);
			break;
		}
		case 68: {
			Engine::Vector force(0.5f, 0.0f, 0.0f);
			SmartPointer<GameObject> obj = actorControlled->getGameObject();
			Engine::Physics::getInstance()->addForce(obj, force);
			break;
		}
		}
	}
}