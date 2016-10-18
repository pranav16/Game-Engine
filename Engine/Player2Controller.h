#pragma once
#ifndef PLAYER2_CONTROLLER_H
#define PLAYER2_CONTROLLER_H
#include "IActorController.h"
#include "MessageHandler.h"
namespace Engine
{

	class Player2Controller : public IActorController, public MessagingSystem::IMessageHandler
	{
		class Actor* actorControlled;
		double speed;
	public:
		Player2Controller();
		~Player2Controller();
		void setActor(class Actor* actor);
		class Actor* getActor() const;
		void keyPressed();
		void safeCast(IActorController & controller);
		void roatateImage(double dt);
		static const HashString ClassType;
		virtual void update(double dt);
		virtual void HandleMessage(const HashString message, void* payLoad);
	};


}
#endif