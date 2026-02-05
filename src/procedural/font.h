/**
 * @file
 * Font loading and text metrics for 2D text rendering.
 */
#pragma once

#include "common.h"

struct Font;

extern "C"
{
	/**
	 * Loads a font from a file.
	 *
	 * @param filename The path to the font file.
	 * @param height The desired font height in pixels.
	 * @return A new font, or NULL if loading fails.
	 */
	EXPORT Font *CALL LoadFont(const char *filename, int height);

	/**
	 * Frees a font and releases its resources.
	 *
	 * @param font The font to free.
	 */
	EXPORT void CALL FreeFont(Font *font);

	/**
	 * Gets the pixel width of a text string when rendered with a font.
	 *
	 * @param font The font to use for measurement.
	 * @param text The text string to measure.
	 * @return The width in pixels.
	 */
	EXPORT int CALL GetTextWidth(Font *font, const char *text);

	/**
	 * Gets the pixel height of a text string when rendered with a font.
	 *
	 * @param font The font to use for measurement.
	 * @param text The text string to measure.
	 * @return The height in pixels.
	 */
	EXPORT int CALL GetTextHeight(Font *font, const char *text);
}
