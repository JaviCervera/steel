#include "../interface/sprite_manager.h"
#include "engine_internal.h"
#include "sprite.h"

extern "C"
{
	EXPORT Sprite *CALL CreateSprite(Texture *texture)
	{
		return GetEngine().spriteManager().createSprite(texture);
	}

	EXPORT void CALL SetSpriteSize(Sprite *sprite, float width, float height)
	{
		GetEngine().spriteManager().spriteSize(sprite, width, height);
	}

	EXPORT float CALL GetSpriteWidth(const Sprite *sprite)
	{
		return GetEngine().spriteManager().spriteWidth(sprite);
	}

	EXPORT float CALL GetSpriteHeight(const Sprite *sprite)
	{
		return GetEngine().spriteManager().spriteHeight(sprite);
	}
}
