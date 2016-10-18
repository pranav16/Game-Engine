#include "SpriteRenderer.h"
#include "Assert.h"
#include "../GLib/GLib.h"
#include "Vector.h"
namespace Engine
{
	
	SpriteRenderer* SpriteRenderer::instance = nullptr;

	void SpriteRenderer::run()
	{
		MessagedAssert(isInitiliazed == true, "calling SpriteRenderer::run when not initialized");
		GLib::BeginRendering();
		GLib::Sprites::BeginRendering();
		std::vector<SpriteRenderInfo*>::iterator spriteRendererIterator = SpriteRenderer::spritesToRender.begin();
		while (spriteRendererIterator != SpriteRenderer::spritesToRender.end())
		{
			SpriteRenderInfo* spriteInfo = *spriteRendererIterator;
			static GLib::Point2D	Offset;
			Offset.x = static_cast<float> (spriteInfo->object->getPosition().getPositionX());
			Offset.y = static_cast<float> (spriteInfo->object->getPosition().getPositionY());
			GLib::Sprites::RenderSprite(*(spriteInfo->sprite), Offset,spriteInfo->object->getZRotation() * 3.14f / 180.0f);
			spriteRendererIterator++;
		}
		GLib::Sprites::EndRendering();
		GLib::EndRendering();
	}
	bool SpriteRenderer::init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
	{
		isInitiliazed = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
		return isInitiliazed;
	}

	SpriteRenderInfo* SpriteRenderer::createSprite(SmartPointer<GameObject>& i_object, const char* spritePath)
	{
		MessagedAssert(i_object != nullptr,"gameobject to create sprite is null");
		MessagedAssert(spritePath != nullptr, "spritepath to create sprite is null");
		SpriteRenderInfo* spriteInfo = new SpriteRenderInfo;
		MessagedAssert(spriteInfo != nullptr,"could not create spriteinfo entry");
		spriteInfo->object = i_object;
		GLib::Sprites::Sprite* sprite = CreateGlibSprite(spritePath);
		MessagedAssert(sprite != nullptr, "sprite returned by glib is null");
		spriteInfo->sprite = sprite;
		addSpritesToRender(spriteInfo);
		return spriteInfo;
	}
	SpriteRenderInfo* SpriteRenderer::createDelayedSprite(SmartPointer<GameObject>& i_object, const char* spritePath)
	{
		MessagedAssert(i_object != nullptr, "gameobject to create sprite is null");
		MessagedAssert(spritePath != nullptr, "spritepath to create sprite is null");
		SpriteRenderInfo* spriteInfo = new SpriteRenderInfo;
		MessagedAssert(spriteInfo != nullptr, "could not create spriteinfo entry");
		spriteInfo->object = i_object;
		GLib::Sprites::Sprite* sprite = CreateGlibSprite(spritePath);
		MessagedAssert(sprite != nullptr, "sprite returned by glib is null");
		spriteInfo->sprite = sprite;
		return spriteInfo;
	}
	void SpriteRenderer::removeSpriteObject(SmartPointer<GameObject>& i_object)
	{
		std::vector<SpriteRenderInfo*>::iterator spriteRendererIterator = SpriteRenderer::spritesToRender.begin();
		while (spriteRendererIterator != SpriteRenderer::spritesToRender.end())
		{
			if ((*spriteRendererIterator)->object == nullptr)
			{
				GLib::Sprites::Release((*spriteRendererIterator)->sprite);
				delete (*spriteRendererIterator);
				SpriteRenderer::spritesToRender.erase(spriteRendererIterator);
				return;
			}
			spriteRendererIterator++;
		}

	}
	void  SpriteRenderer::addSpriteInfo(SpriteRenderInfo* info)
	{
		MessagedAssert(info != nullptr, "adding null to spritesToRender list!!");
		SpriteRenderer::spritesToRender.push_back(info);
	}

	GLib::Sprites::Sprite *  SpriteRenderer::CreateGlibSprite(const char * i_pFilename)
	{
		MessagedAssert(i_pFilename != nullptr ,"FileName for spite creation can not be nullptr");
		size_t sizeTextureFile = 0;
		void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);
		GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;
		if (pTextureFile)
			delete[] pTextureFile;
		if (pTexture == nullptr)
			return NULL;
		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;
		bool result = GLib::GetDimensions(pTexture, width, height, depth);
		MessagedAssert(result == true,"GetDimensions resulted in false");
		MessagedAssert((width > 0) && (height > 0), "width or height cannot be less than zero");
		GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
		GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
		GLib::RGBA							Color = { 255, 255, 255, 255 };
		GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
		if (pSprite == nullptr)
		{
			GLib::Release(pTexture);
			return nullptr;
		}
		GLib::Sprites::SetTexture(*pSprite, *pTexture);
		return pSprite;
	}

	void * SpriteRenderer::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		MessagedAssert(i_pFilename != nullptr,"filepath cannot be null" );
		FILE * pFile = NULL;
		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;
		MessagedAssert(pFile != NULL,"file could not be opened");
		int FileIOError = fseek(pFile, 0, SEEK_END);
		MessagedAssert(FileIOError == 0,"FileIOError");
		long FileSize = ftell(pFile);
		MessagedAssert(FileSize >= 0,"Filesize is less that zero");
		FileIOError = fseek(pFile, 0, SEEK_SET);
		MessagedAssert(FileIOError == 0,"FileIOError");
		uint8_t * pBuffer = new uint8_t[FileSize];
		MessagedAssert(pBuffer != nullptr,"buffer could not be created");
		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		MessagedAssert(FileRead == FileSize,"Filesize read is not equal to filesize");
		fclose(pFile);
		o_sizeFile = FileSize;
		return pBuffer;
	}

	void SpriteRenderer::shutDown()
	{
		MessagedAssert(isInitiliazed == true, "calling SpriteRenderer::shutDown when not initialized");
		MessagedAssert(instance != nullptr, "calling SpriteRenderer::shutDown with null instance ");
		std::vector<SpriteRenderInfo*>::iterator spriteRendererIterator = SpriteRenderer::spritesToRender.begin();
		while (  spriteRendererIterator != SpriteRenderer::spritesToRender.end())
		{
			
			GLib::Sprites::Release((*spriteRendererIterator)->sprite);
			delete (*spriteRendererIterator);
			spriteRendererIterator = SpriteRenderer::spritesToRender.erase(spriteRendererIterator);
			
		}
		delete instance;
		GLib::Shutdown();
	}

}