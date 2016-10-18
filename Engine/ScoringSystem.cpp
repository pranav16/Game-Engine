#include "ScoringSystem.h"
#include "CollisionData.h"
#include  "Serializer.h"
#include "Actor.h"
#include "MessagingSystem.h"
namespace Engine
{

	ScoringSystem* ScoringSystem::instance = nullptr;

	HashString LeaderBoardNode::getSerializableType()
	{
		return "ScoreNode";
	}
	HashString LeaderBoardNode::getSerializableId()
	{
		return "SerialiazableId";
	}

	size_t LeaderBoardNode::serialize(uint8_t* buffer)
	{
		MessagedAssert(buffer != nullptr, "buffer passed to gameobject for serialization is null");

		memcpy(buffer, &score, sizeof(score));
		return sizeof(score);
	}
	size_t LeaderBoardNode::deserialize(uint8_t* buffer)
	{
		MessagedAssert(buffer != nullptr, "buffer passed to gameobject for serialization is null");
		memcpy(&score, buffer, sizeof(score));
		return sizeof(score);
	}

	void ScoringSystem::HandleMessage(const HashString message, void* payLoad)
	{
		Collision data = *static_cast<Collision*>(payLoad);
		for (size_t i = 0; i < leaderBoard.size();i++)
		{
		
			if (leaderBoard[i]->playerName == data.pActor->getGameObject()->getName() || leaderBoard[i]->playerName == data.pOther->getGameObject()->getName()	&& data.timeOfCollision - lastUpdate > 0.1)
			{
				lastUpdate = data.timeOfCollision;
				leaderBoard[i]->score = leaderBoard[i]->score++;
			}
			else
			{
				lastUpdate = 0;
			}

		}
	

	}
	void ScoringSystem::addActorToLeaderBoard(LeaderBoardNode* node)
	{
		leaderBoard.push_back(node);
		Serializer::getInstance()->addSerializableObject(node);
	}
	
	ScoringSystem* ScoringSystem::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new ScoringSystem();
			MessagingSystem::MessageHandlerSystem::getInstance()->RegisterHandler("TriggerCollision",instance);
		}
		return instance;
	}

	
	ScoringSystem::ScoringSystem()
	{
		lastUpdate = 0;
	}


}