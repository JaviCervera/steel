#pragma once

#include "common.h"

struct Sprite;
struct Texture;

extern "C"
{
	EXPORT Sprite *CALL CreateSprite(Texture *texture);
	EXPORT void CALL SetSpriteSize(Sprite *sprite, float width, float height);
	EXPORT float CALL GetSpriteWidth(const Sprite *sprite);
	EXPORT float CALL GetSpriteHeight(const Sprite *sprite);
}
