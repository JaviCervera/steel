/**
 * @file
 * Pixel maps for reading and writing image data in memory.
 * Pixmaps can be created, loaded from files, or captured from the screen.
 */
#pragma once

#include "common.h"

struct Pixmap;
struct Texture;

extern "C"
{
	/**
	 * Creates an empty pixmap with specified dimensions.
	 *
	 * @param width The width in pixels.
	 * @param height The height in pixels.
	 * @return A new pixmap.
	 */
	EXPORT Pixmap *CALL CreatePixmap(int width, int height);

	/**
	 * Creates a pixmap from a texture, copying its contents.
	 *
	 * @param texture The texture to copy from.
	 * @return A new pixmap containing the texture data.
	 */
	EXPORT Pixmap *CALL CreatePixmapFromTexture(Texture *texture);

	/**
	 * Creates a pixmap from the current screen contents.
	 *
	 * @return A new pixmap containing the screen image.
	 */
	EXPORT Pixmap *CALL CreatePixmapFromScreen();

	/**
	 * Loads a pixmap from an image file.
	 *
	 * @param filename The path to the image file.
	 * @return A new pixmap, or NULL if loading fails.
	 */
	EXPORT Pixmap *CALL LoadPixmap(const char *filename);

	/**
	 * Frees a pixmap and releases its resources.
	 *
	 * @param pixmap The pixmap to free.
	 */
	EXPORT void CALL FreePixmap(Pixmap *pixmap);

	/**
	 * Saves a pixmap to an image file.
	 *
	 * @param pixmap The pixmap to save.
	 * @param filename The path to save to.
	 */
	EXPORT void CALL SavePixmap(const Pixmap *pixmap, const char *filename);

	/**
	 * Reads a pixel color from a pixmap at the specified coordinates.
	 *
	 * @param pixmap The pixmap.
	 * @param x The x-coordinate.
	 * @param y The y-coordinate.
	 * @return The color value at that pixel.
	 */
	EXPORT int CALL ReadPixel(const Pixmap *pixmap, int x, int y);

	/**
	 * Writes a pixel color to a pixmap at the specified coordinates.
	 *
	 * @param pixmap The pixmap.
	 * @param x The x-coordinate.
	 * @param y The y-coordinate.
	 * @param color The color to write.
	 */
	EXPORT void CALL WritePixel(Pixmap *pixmap, int x, int y, int color);

	/**
	 * Gets the width of a pixmap in pixels.
	 *
	 * @param pixmap The pixmap.
	 * @return The width in pixels.
	 */
	EXPORT int CALL GetPixmapWidth(const Pixmap *pixmap);

	/**
	 * Gets the height of a pixmap in pixels.
	 *
	 * @param pixmap The pixmap.
	 * @return The height in pixels.
	 */
	EXPORT int CALL GetPixmapHeight(const Pixmap *pixmap);
}
