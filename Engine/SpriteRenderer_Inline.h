#pragma once
#ifndef SPRITERENDERINI
#define SPRITERENDERINI

namespace Engine
{

	inline  SpriteRenderer* SpriteRenderer::getInstance()
	{
		if (SpriteRenderer::instance == nullptr)
			SpriteRenderer::instance = new SpriteRenderer();
	
		return SpriteRenderer::instance;
	}

	inline void SpriteRenderer::addSpritesToRender(SpriteRenderInfo* i_sprite)
	{
		SpriteRenderer::spritesToRender.push_back(i_sprite);
	}

}

#endif // !SPRITERENDERINI