#pragma once
#ifndef SCORING_SYSTEM_H
#define SCORING_SYSTEM_H
#include "MessageHandler.h"
#include "Serializable.h"
namespace Engine
{
	struct LeaderBoardNode : public Serializable
	{
		std::string playerName;
		int score;
		virtual HashString getSerializableType();
		virtual HashString getSerializableId();

		virtual size_t serialize(uint8_t* buffer);
		virtual size_t deserialize(uint8_t* buffer);

	};

	class ScoringSystem: public MessagingSystem::IMessageHandler
	{
	public:
	virtual void HandleMessage(const HashString message, void* payLoad);
	static ScoringSystem* getInstance();
	void addActorToLeaderBoard(LeaderBoardNode* node);
	private:
		static ScoringSystem* instance;
		ScoringSystem();
		std::vector<LeaderBoardNode*>leaderBoard;
		float lastUpdate;
	};

}


#endif