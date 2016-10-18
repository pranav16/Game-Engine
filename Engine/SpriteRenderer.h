#ifndef _SpriteRenderer_H
#define __SpriteRenderer_H
#include <vector>
#include "../GLib/GLib.h"
#include "SmartPointer.h"
#include "GameObject.h"
namespace Engine
{

	struct SpriteRenderInfo
	{
		SmartPointer<GameObject> object;
		GLib::Sprites::Sprite* sprite;

	};

	class SpriteRenderer
	{

	public:
		inline static SpriteRenderer* getInstance();
		void shutDown();
		void run();
		bool init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
		SpriteRenderInfo* createSprite(SmartPointer<GameObject>& i_object, const char* spritePath);
		SpriteRenderInfo* createDelayedSprite(SmartPointer<GameObject>& i_object, const char* spritePath);
		void addSpriteInfo(SpriteRenderInfo* info);
		void removeSpriteObject(SmartPointer<GameObject>& i_object);
	private:
		bool isInitiliazed;
		std::vector<SpriteRenderInfo*>spritesToRender;
		inline void addSpritesToRender(SpriteRenderInfo* i_sprite);
		void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		GLib::Sprites::Sprite * CreateGlibSprite(const char * i_pFilename);
		static SpriteRenderer* instance;
		SpriteRenderer(const SpriteRenderer& ref){};
		SpriteRenderer& operator=(const SpriteRenderer& ref) {};
		SpriteRenderer() :isInitiliazed(false){};

	};

}

#include "SpriteRenderer_Inline.h"

#endif