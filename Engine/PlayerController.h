#pragma once
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "IActorController.h"
#include "MessageHandler.h"
namespace Engine
{

	class PlayerController : public IActorController,public MessagingSystem::IMessageHandler
	{
		class Actor* actorControlled;
		double speed;
	public:
		PlayerController();
		~PlayerController();
		void setActor(class Actor* actor);
		class Actor* getActor() const;
		void keyPressed();
		void roatateImage(double dt);
		void safeCast(IActorController & controller) ;
		static const HashString ClassType;
		virtual void update(double dt);
		virtual void HandleMessage(const HashString message, void* payLoad);
	};


}
#endif