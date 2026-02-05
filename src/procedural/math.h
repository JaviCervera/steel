/**
 * @file
 * Mathematical utility functions for common operations including trigonometry, rounding, and utilities.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Rounds a value down to the nearest integer.
	 *
	 * @param val The value to floor.
	 * @return The floored value.
	 */
	EXPORT float CALL Floor(float val);

	/**
	 * Rounds a value up to the nearest integer.
	 *
	 * @param val The value to ceil.
	 * @return The ceiled value.
	 */
	EXPORT float CALL Ceil(float val);

	/**
	 * Gets the absolute value of a number.
	 *
	 * @param val The value.
	 * @return The absolute value.
	 */
	EXPORT float CALL Abs(float val);

	/**
	 * Squares a value.
	 *
	 * @param val The value to square.
	 * @return The squared value.
	 */
	EXPORT float CALL Sqr(float val);

	/**
	 * Calculates the sine of an angle in radians.
	 *
	 * @param val The angle in radians.
	 * @return The sine value.
	 */
	EXPORT float CALL Sin(float val);

	/**
	 * Calculates the cosine of an angle in radians.
	 *
	 * @param val The angle in radians.
	 * @return The cosine value.
	 */
	EXPORT float CALL Cos(float val);

	/**
	 * Calculates the tangent of an angle in radians.
	 *
	 * @param val The angle in radians.
	 * @return The tangent value.
	 */
	EXPORT float CALL Tan(float val);

	/**
	 * Calculates the arc sine (inverse sine) of a value.
	 *
	 * @param val The value (-1 to 1).
	 * @return The angle in radians.
	 */
	EXPORT float CALL ASin(float val);

	/**
	 * Calculates the arc cosine (inverse cosine) of a value.
	 *
	 * @param val The value (-1 to 1).
	 * @return The angle in radians.
	 */
	EXPORT float CALL ACos(float val);

	/**
	 * Calculates the arc tangent (inverse tangent) of a value.
	 *
	 * @param val The value.
	 * @return The angle in radians.
	 */
	EXPORT float CALL ATan(float val);

	/**
	 * Calculates the arc tangent of y/x, accounting for quadrant.
	 *
	 * @param x The x value.
	 * @param y The y value.
	 * @return The angle in radians.
	 */
	EXPORT float CALL ATan2(float x, float y);

	/**
	 * Calculates e raised to the power of a value.
	 *
	 * @param val The exponent.
	 * @return The result.
	 */
	EXPORT float CALL Exp(float val);

	/**
	 * Raises a base to a power.
	 *
	 * @param base The base value.
	 * @param exp The exponent.
	 * @return The result.
	 */
	EXPORT float CALL Pow(float base, float exp);

	/**
	 * Calculates the natural logarithm (base e) of a value.
	 *
	 * @param val The value.
	 * @return The logarithm.
	 */
	EXPORT float CALL Log(float val);

	/**
	 * Calculates the base-10 logarithm of a value.
	 *
	 * @param val The value.
	 * @return The logarithm.
	 */
	EXPORT float CALL Log10(float val);

	/**
	 * Returns the smaller of two values.
	 *
	 * @param a The first value.
	 * @param b The second value.
	 * @return The minimum value.
	 */
	EXPORT float CALL Min(float a, float b);

	/**
	 * Returns the larger of two values.
	 *
	 * @param a The first value.
	 * @param b The second value.
	 * @return The maximum value.
	 */
	EXPORT float CALL Max(float a, float b);

	/**
	 * Clamps a value between a minimum and maximum.
	 *
	 * @param val The value to clamp.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @return The clamped value.
	 */
	EXPORT float CALL Clamp(float val, float min, float max);

	/**
	 * Converts a boolean to an integer (0 or 1).
	 *
	 * @param val The boolean value.
	 * @return 0 if false, 1 if true.
	 */
	EXPORT int CALL BoolToInt(bool_t val);

	/**
	 * Converts a float to an integer (truncates decimal part).
	 *
	 * @param val The value to convert.
	 * @return The integer value.
	 */
	EXPORT int CALL Int(float val);

	/**
	 * Generates a random integer between min and max (inclusive).
	 *
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @return A random integer.
	 */
	EXPORT int CALL Rand(int min, int max);

	/**
	 * Seeds the random number generator.
	 *
	 * @param seed The seed value.
	 */
	EXPORT void CALL RandSeed(int seed);

	/**
	 * Converts degrees to radians.
	 *
	 * @param deg The angle in degrees.
	 * @return The angle in radians.
	 */
	EXPORT float CALL Deg(float rad);

	/**
	 * Converts radians to degrees.
	 *
	 * @param rad The angle in radians.
	 * @return The angle in degrees.
	 */
	EXPORT float CALL Rad(float deg);

	/**
	 * Wraps a value around a modulus.
	 *
	 * @param val The value to wrap.
	 * @param mod The modulus.
	 * @return The wrapped value.
	 */
	EXPORT float CALL Wrap(float val, float mod);
}
