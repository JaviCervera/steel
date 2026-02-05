/**
 * @file
 * Drawing functions for rendering 2D graphics directly to the screen.
 * This includes primitives like lines and rectangles, as well as text and texture rendering.
 */
#pragma once

#include "common.h"

struct Font;
struct Texture;

extern "C"
{
	/**
	 * Clears the screen with a solid color.
	 *
	 * @param color The color to fill the screen with.
	 */
	EXPORT void CALL Cls(int color);

	/**
	 * Sets the drawing color for subsequent drawing operations.
	 *
	 * @param color The color to use for drawing.
	 */
	EXPORT void CALL SetColor(int color);

	/**
	 * Sets the viewport for drawing operations.
	 *
	 * @param x The left edge of the viewport in screen coordinates.
	 * @param y The top edge of the viewport in screen coordinates.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 */
	EXPORT void CALL SetViewport(int x, int y, int width, int height);

	/**
	 * Draws a single pixel at the specified screen coordinates.
	 *
	 * @param x The x-coordinate in screen space.
	 * @param y The y-coordinate in screen space.
	 */
	EXPORT void CALL DrawPlot(float x, float y);

	/**
	 * Draws a line between two points on the screen.
	 *
	 * @param x1 The x-coordinate of the starting point.
	 * @param y1 The y-coordinate of the starting point.
	 * @param x2 The x-coordinate of the ending point.
	 * @param y2 The y-coordinate of the ending point.
	 */
	EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2);

	/**
	 * Draws a filled rectangle on the screen.
	 *
	 * @param x The left edge of the rectangle.
	 * @param y The top edge of the rectangle.
	 * @param width The width of the rectangle.
	 * @param height The height of the rectangle.
	 */
	EXPORT void CALL DrawRect(float x, float y, float width, float height);

	/**
	 * Draws text on the screen using a font.
	 *
	 * @param font The font to use for rendering.
	 * @param text The text string to draw.
	 * @param x The x-coordinate for the text.
	 * @param y The y-coordinate for the text.
	 */
	EXPORT void CALL DrawText(Font *font, const char *text, int x, int y);

	/**
	 * Draws a texture at specified screen coordinates.
	 *
	 * @param tex The texture to draw.
	 * @param x The x-coordinate for drawing.
	 * @param y The y-coordinate for drawing.
	 */
	EXPORT void CALL DrawTexture(Texture *tex, float x, float y);

	/**
	 * Draws a texture at specified screen coordinates with custom width and height.
	 *
	 * @param tex The texture to draw.
	 * @param x The x-coordinate for drawing.
	 * @param y The y-coordinate for drawing.
	 * @param width The width to draw the texture at.
	 * @param height The height to draw the texture at.
	 */
	EXPORT void CALL DrawTextureEx(Texture *tex, float x, float y, float width, float height);

	/**
	 * Draws a portion of a texture to a different portion of the screen.
	 *
	 * @param tex The texture to draw.
	 * @param src_x The source texture x-coordinate.
	 * @param src_y The source texture y-coordinate.
	 * @param src_width The width of the source region.
	 * @param src_height The height of the source region.
	 * @param dst_x The destination screen x-coordinate.
	 * @param dst_y The destination screen y-coordinate.
	 * @param dst_width The destination width on screen.
	 * @param dst_height The destination height on screen.
	 */
	EXPORT void CALL DrawTextureRect(Texture *tex, float src_x, float src_y, float src_width, float src_height, float dst_x, float dst_y, float dst_width, float dst_height);
}
