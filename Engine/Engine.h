#ifndef _ENGINE_H
#define _ENGINE_H
#include <Windows.h>
#include "SmartPointer.h"
#include "GameObject.h"
#include "Actor.h"
#include <vector>
namespace Engine
{

	class EngineMain
	{
	public:
		inline static EngineMain* getInstance();
		bool init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
		void run(double dt);
		void shutDown();
		void addActorToPool(Actor* actor);
		void removeActorFromPool(Actor* actor);
		void removeActorsFromPool();
		~EngineMain();
		void saveInitState();
	
	private:

		static EngineMain* myInstance;
		inline EngineMain();
		EngineMain(const EngineMain& engine) {};
		static void keyBackCallBack(unsigned int i_VKeyID, bool bWentDown);
		const EngineMain& operator=(const EngineMain& engine) {};
	
		void resetGame();
		std::vector<Vector>initialPositions;
		std::vector<Actor*>worldActors;

	};
	

}
#include "EngineInit.h"

#endif