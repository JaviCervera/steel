#pragma once

#include "entity_manager.h"

struct Sprite : public Entity
{
};

struct Texture;

struct SpriteManager
{
	virtual ~SpriteManager() {}
	virtual Sprite *createSprite(Texture *texture) = 0;
	virtual void spriteSize(Sprite *sprite, float width, float height) = 0;
	virtual float spriteWidth(const Sprite *sprite) = 0;
	virtual float spriteHeight(const Sprite *sprite) = 0;
};
