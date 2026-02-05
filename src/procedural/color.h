/**
 * @file
 * Color utilities for creating and manipulating RGBA colors.
 * Colors are represented as 32-bit integers with separate channels for red, green, blue, and alpha.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Creates a color from red, green, and blue components.
	 *
	 * @param r The red component (0-255).
	 * @param g The green component (0-255).
	 * @param b The blue component (0-255).
	 * @return The resulting color with alpha set to 255.
	 */
	EXPORT int CALL RGB(int r, int g, int b);

	/**
	 * Creates a color from red, green, blue, and alpha components.
	 *
	 * @param r The red component (0-255).
	 * @param g The green component (0-255).
	 * @param b The blue component (0-255).
	 * @param a The alpha component (0-255).
	 * @return The resulting color.
	 */
	EXPORT int CALL RGBA(int r, int g, int b, int a);

	/**
	 * Extracts the red component from a color.
	 *
	 * @param color The color.
	 * @return The red component (0-255).
	 */
	EXPORT int CALL GetRed(int color);

	/**
	 * Extracts the green component from a color.
	 *
	 * @param color The color.
	 * @return The green component (0-255).
	 */
	EXPORT int CALL GetGreen(int color);

	/**
	 * Extracts the blue component from a color.
	 *
	 * @param color The color.
	 * @return The blue component (0-255).
	 */
	EXPORT int CALL GetBlue(int color);

	/**
	 * Extracts the alpha component from a color.
	 *
	 * @param color The color.
	 * @return The alpha component (0-255).
	 */
	EXPORT int CALL GetAlpha(int color);

	/**
	 * Modifies the alpha component of a color.
	 *
	 * @param color The original color.
	 * @param new_alpha The new alpha value (0-255).
	 * @return The color with the new alpha.
	 */
	EXPORT int CALL FadeColor(int color, int new_alpha);

	/**
	 * Multiplies all RGB components of a color by a factor.
	 *
	 * @param color The color to multiply.
	 * @param factor The multiplication factor.
	 * @return The resulting color.
	 */
	EXPORT int CALL MultiplyColor(int color, float factor);

	/**
	 * Swaps the red and blue components of a color.
	 *
	 * @param color The color.
	 * @return The color with red and blue components swapped.
	 */
	EXPORT int CALL SwapColor(int color);
}
