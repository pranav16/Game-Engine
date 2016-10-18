#include "Actor.h"
#include "LauHandler.h"
#include "SpriteRenderer.h"
#include "Physics.h"
#include "Assert.h"
#include "PlayerController.h"
#include "Player2Controller.h"
#include "Serializer.h"
#include "MessagingSystem.h"
#include "CollisionCheck.h"
#include "ScoringSystem.h"
#define ROOTKEY "Player"
#define NAMETAG "name"
#define SPRITEINFO "SpriteInfo"
#define SPRITEPATH "SpritePath"
#define INITIALPOSITION	"initial_position"
#define PHYSICINFO "PhysicsInfo"
#define MASS "mass"
#define COEFFINTDRAG "coefficientOfDrag"
#define VELOCITY "velocity"
#define BOUNDING_BOX "BoxExtents"
#define CENTER "Center"
#define ROTATION "Roation"
#define CONTROLLER "Controller"
#define COLLISION "Trigger"
#define SERIALIZEABLE "Serializable"

namespace Engine
{
	
	 Actor* Actor::loadActorFromFile(const char* filePath)
	{
		lua_State * pLuaState = luaL_newstate();
		MessagedAssert(pLuaState != nullptr,"could not create lau state at load actor from file");
		luaL_openlibs(pLuaState);
		size_t			sizeFile = 0;
		uint8_t *pFileContents = LauHandler::LoadFile(filePath, sizeFile);

		if (pFileContents  && sizeFile)
		{
			int			result = 0;
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			MessagedAssert(result == 0,"loadbuffer was not sucessful");
			lua_pcall(pLuaState, 0, 0, 0);
			MessagedAssert(result == 0,"function processing call failed");
			int			type = LUA_TNIL;
			result = lua_getglobal(pLuaState, ROOTKEY);
			MessagedAssert(result == LUA_TTABLE,"could not retrive player table from the lau file");
			lua_pushstring(pLuaState, NAMETAG);
		
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TSTRING,"name must be of type string");
			 const char * pName = lua_tostring(pLuaState, -1);
			 if (pName)
				 pName = _strdup(pName);
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState, CONTROLLER);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TSTRING, "name must be of type string");
			const char * controller = lua_tostring(pLuaState, -1);
			if (controller)
				controller = _strdup(controller);
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState,SPRITEINFO);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "spriteinfo must be of type table");
			lua_pushstring(pLuaState, SPRITEPATH);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TSTRING, "spritepath must be of type string");
			const char * pSpriteFilePath = lua_tostring(pLuaState, -1);
			if (pSpriteFilePath)
				pSpriteFilePath = _strdup(pSpriteFilePath);
			lua_pop(pLuaState, 2);
			size_t stackSize = lua_gettop(pLuaState);
			lua_pushstring(pLuaState, INITIALPOSITION);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			Vector initialPosition = LauHandler::GetVector3(pLuaState,-1);
			lua_pop(pLuaState, 1);
			stackSize = lua_gettop(pLuaState);
			lua_pushstring(pLuaState, VELOCITY);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			Vector velocity = LauHandler::GetVector3(pLuaState, -1);
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState, PHYSICINFO);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "physics info must be of type table");
			lua_pushstring(pLuaState, MASS);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			double mass = float (lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 2);
			stackSize = lua_gettop(pLuaState);
			lua_pushstring(pLuaState, PHYSICINFO);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "physics info must be of type table");
			lua_pushstring(pLuaState, COEFFINTDRAG);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TNUMBER, "coint should be must be of type number");
			double cofficient = double (lua_tonumber(pLuaState, -1));
			stackSize = lua_gettop(pLuaState);
			lua_pop(pLuaState, 2);
			lua_pushstring(pLuaState, BOUNDING_BOX);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			Vector4 boundingBox(LauHandler::GetVector3(pLuaState, -1),0);
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState, CENTER);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			Vector4 Center(LauHandler::GetVector3(pLuaState, -1), 1);
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState, ROTATION);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			double roatation = float(lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 1);
			lua_pushstring(pLuaState, SERIALIZEABLE);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			double isSerializeable = float(lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 2);
			lua_pushstring(pLuaState, COLLISION);
			type = lua_gettable(pLuaState, -2);
			MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			double isTrigger = float(lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 2);
			stackSize = lua_gettop(pLuaState);
			SmartPointer<GameObject>obj(new GameObject(initialPosition, velocity, const_cast<char*>(pName)));
			obj->setZRoation((float)roatation);
			SpriteRenderInfo* sinfo = SpriteRenderer::getInstance()->createSprite(obj, pSpriteFilePath);
			PhysicsInfo* pInfo = Physics::getInstance()->addObjectToPhysicSystem(obj, mass, cofficient);
			IActorController* aiController;
			BoundingBox * bounding = new BoundingBox();
			bounding->Center = Center;
			bounding->BoxEntents = boundingBox;
			Actor* actor = new Actor(sinfo, pInfo, obj);
			actor->setBoundingBox(bounding);
			if (strcmp(controller, "PlayerController") == 0)
			{
				aiController = new PlayerController();
				static_cast<PlayerController*> (aiController)->setActor(actor);
				actor->setActorController(aiController);
			}
			else
			{
				aiController = new Player2Controller();
				static_cast<Player2Controller*> (aiController)->setActor(actor);
				actor->setActorController(aiController);
			}
			if (isSerializeable == 1)
			{
		
				Engine::Serializer::getInstance()->addSerializableObject(obj.getObject());	
			}
			if (isTrigger == 1)
			{
				Engine::CollisionCheck::getInstance()->addCollidable(actor);
		
			}
			free((void*)pSpriteFilePath);
			free((void*)pName);
			free((void*)controller);
			lua_close(pLuaState);
			delete[] pFileContents;
			return actor;
		}
		lua_close(pLuaState);
		return nullptr;
	}

	 Actor* Actor::loadActorFromData(uint8_t* data,size_t sizeFile)
	 {
		 lua_State * pLuaState = luaL_newstate();
		 MessagedAssert(pLuaState != nullptr, "could not create lau state at load actor from file");
		 luaL_openlibs(pLuaState);
		 if (data  && sizeFile)
		 {
			 int			result = 0;
			 result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(data), sizeFile, nullptr);
			 MessagedAssert(result == 0, "loadbuffer was not sucessful");
			 lua_pcall(pLuaState, 0, 0, 0);
			 MessagedAssert(result == 0, "function processing call failed");
			 int			type = LUA_TNIL;
			 result = lua_getglobal(pLuaState, ROOTKEY);
			 MessagedAssert(result == LUA_TTABLE, "could not retrive player table from the lau file");
			 lua_pushstring(pLuaState, NAMETAG);

			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TSTRING, "name must be of type string");
			 const char * pName = lua_tostring(pLuaState, -1);
			 if (pName)
				 pName = _strdup(pName);
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, CONTROLLER);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TSTRING, "name must be of type string");
			 const char * controller = lua_tostring(pLuaState, -1);
			 if (controller)
				 controller = _strdup(controller);
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, SPRITEINFO);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "spriteinfo must be of type table");
			 lua_pushstring(pLuaState, SPRITEPATH);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TSTRING, "spritepath must be of type string");
			 const char * pSpriteFilePath = lua_tostring(pLuaState, -1);
			 if (pSpriteFilePath)
				 pSpriteFilePath = _strdup(pSpriteFilePath);
			 lua_pop(pLuaState, 2);
			 size_t stackSize = lua_gettop(pLuaState);
			 lua_pushstring(pLuaState, INITIALPOSITION);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			 Vector initialPosition = LauHandler::GetVector3(pLuaState, -1);
			 lua_pop(pLuaState, 1);
			 stackSize = lua_gettop(pLuaState);
			 lua_pushstring(pLuaState, VELOCITY);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			 Vector velocity = LauHandler::GetVector3(pLuaState, -1);
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, PHYSICINFO);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "physics info must be of type table");
			 lua_pushstring(pLuaState, MASS);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			 double mass = (float)lua_tonumber(pLuaState, -1);
			 lua_pop(pLuaState, 2);
			 stackSize = lua_gettop(pLuaState);
			 lua_pushstring(pLuaState, PHYSICINFO);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "physics info must be of type table");
			 lua_pushstring(pLuaState, COEFFINTDRAG);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TNUMBER, "coint should be must be of type number");
			 double cofficient = double(lua_tonumber(pLuaState, -1));
			 stackSize = lua_gettop(pLuaState);
			 lua_pop(pLuaState, 2);
			 lua_pushstring(pLuaState, BOUNDING_BOX);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			 Vector4 boundingBox(LauHandler::GetVector3(pLuaState, -1), 0);
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, CENTER);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TTABLE, "intial position must be of type table");
			 Vector4 Center(LauHandler::GetVector3(pLuaState, -1), 1);
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, ROTATION);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			 double roatation = float(lua_tonumber(pLuaState, -1));
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, SERIALIZEABLE);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			 double isSerializeable = float(lua_tonumber(pLuaState, -1));
			 lua_pop(pLuaState, 1);
			 lua_pushstring(pLuaState, COLLISION);
			 type = lua_gettable(pLuaState, -2);
			 MessagedAssert(type == LUA_TNUMBER, "mass must be of type integer");
			 double isTrigger = float(lua_tonumber(pLuaState, -1));
			 lua_pop(pLuaState, 2);
			 stackSize = lua_gettop(pLuaState);
			 SmartPointer<GameObject>obj(new GameObject(initialPosition, velocity, const_cast<char*>(pName)));
			 obj->setZRoation((float)roatation);
			 SpriteRenderInfo* sinfo = nullptr;
			 if(strcmp(pSpriteFilePath,"") != 0)
			 sinfo = SpriteRenderer::getInstance()->createDelayedSprite(obj, pSpriteFilePath);
			 PhysicsInfo* pInfo = Physics::getInstance()->createDelayedPhysicObject(obj, mass, cofficient);
			 IActorController* aiController;
			 BoundingBox * bounding = new BoundingBox();
			 bounding->Center = Center;
			 bounding->BoxEntents = boundingBox;
			 Actor* actor = new Actor(sinfo, pInfo, obj);
			 actor->setBoundingBox(bounding);
			
			 if (strcmp(controller, "PlayerController") == 0)
			 {
				 aiController = new PlayerController();
				 static_cast<PlayerController*> (aiController)->setActor(actor);
				 actor->setActorController(aiController);
				 LeaderBoardNode* node = new LeaderBoardNode;
				 node->playerName = obj->getName();
				 node->score = 0;
				 ScoringSystem::getInstance()->addActorToLeaderBoard(node);
				 MessagingSystem::MessageHandlerSystem::getInstance()->RegisterHandler("ButtonPressed", static_cast<PlayerController*> (aiController));
			 }
			 else if(strcmp(controller, "Player2Controller") == 0)
			 {
				 aiController = new Player2Controller();
				 static_cast<Player2Controller*> (aiController)->setActor(actor);
				 actor->setActorController(aiController);
				 LeaderBoardNode* node = new LeaderBoardNode;
				 node->playerName = obj->getName();
				 node->score = 0;
				 ScoringSystem::getInstance()->addActorToLeaderBoard(node);
				 MessagingSystem::MessageHandlerSystem::getInstance()->RegisterHandler("ButtonPressed", static_cast<Player2Controller*> (aiController));
			 }
			 if (isSerializeable == 1)
			 {

				 Engine::Serializer::getInstance()->addSerializableObject(obj.getObject());
			 }
			 if (isTrigger > 0)
			 {
				 Engine::CollisionCheck::getInstance()->addCollidable(actor);
				 actor->setCollisionType((int)isTrigger);
			 }
			 free((void*)pSpriteFilePath);
			 free((void*)pName);
			 free((void*)controller);
			 lua_close(pLuaState);
			 
			 return actor;
		 }
		 lua_close(pLuaState);
		 return nullptr;
	 }


}