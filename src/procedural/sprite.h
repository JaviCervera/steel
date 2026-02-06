/**
 * @file
 * Sprites for 2D graphics rendering within the 3D world.
 * Sprites are texture-based 2D objects that can be positioned, scaled, and rotated in 3D space.
 * Sprites are entities, so any entity function can be used on them, such as setting their
 * position, rotation, scale, etc.
 */
#pragma once

#include "common.h"

struct Sprite;
struct Texture;

extern "C"
{
	/**
	 * Creates a new sprite from a texture.
	 *
	 * @param texture The texture to display on the sprite.
	 * @return A new sprite entity.
	 */
	EXPORT Sprite *CALL CreateSprite(Texture *texture);

	/**
	 * Sets the size (width and height) of a sprite.
	 *
	 * @param sprite The sprite.
	 * @param width The width in world units.
	 * @param height The height in world units.
	 */
	EXPORT void CALL SetSpriteSize(Sprite *sprite, float width, float height);

	/**
	 * Gets the width of a sprite.
	 *
	 * @param sprite The sprite.
	 * @return The width in world units.
	 */
	EXPORT float CALL GetSpriteWidth(const Sprite *sprite);

	/**
	 * Gets the height of a sprite.
	 *
	 * @param sprite The sprite.
	 * @return The height in world units.
	 */
	EXPORT float CALL GetSpriteHeight(const Sprite *sprite);
}
