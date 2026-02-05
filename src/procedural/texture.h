/**
 * @file
 * Textures for surface mapping on 3D models and sprites.
 * Textures can be created, loaded from files, or created from pixmaps.
 */
#pragma once

#include "common.h"

struct Pixmap;
struct Texture;

extern "C"
{
	/**
	 * Creates an empty texture with specified dimensions.
	 *
	 * @param width The width in pixels.
	 * @param height The height in pixels.
	 * @return A new texture.
	 */
	EXPORT Texture *CALL CreateTexture(int width, int height);

	/**
	 * Creates a texture from a pixmap.
	 *
	 * @param pixmap The pixmap containing the texture data.
	 * @return A new texture, or NULL if creation fails.
	 */
	EXPORT Texture *CALL CreateTextureFromPixmap(Pixmap *pixmap);

	/**
	 * Loads a texture from an image file.
	 *
	 * @param filename The path to the image file.
	 * @return A new texture, or NULL if loading fails.
	 */
	EXPORT Texture *CALL LoadTexture(const char *filename);

	/**
	 * Frees a texture and releases its resources.
	 *
	 * @param tex The texture to free.
	 */
	EXPORT void CALL FreeTexture(Texture *tex);

	/**
	 * Clears the texture cache of all unreferenced textures.
	 */
	EXPORT void CALL ClearTextureCache();

	/**
	 * Gets the width of a texture in pixels.
	 *
	 * @param tex The texture.
	 * @return The width in pixels.
	 */
	EXPORT int CALL GetTextureWidth(const Texture *tex);

	/**
	 * Gets the height of a texture in pixels.
	 *
	 * @param tex The texture.
	 * @return The height in pixels.
	 */
	EXPORT int CALL GetTextureHeight(const Texture *tex);

	/**
	 * Gets the filename of a loaded texture.
	 *
	 * @param tex The texture.
	 * @return The filename used to load the texture.
	 */
	EXPORT const char *CALL GetTextureFilename(const Texture *tex);
}
