/**
 * @file
 * Scene rendering and coordinate conversion functions.
 * Controls rendering, ambient light, fog, and conversion between world and screen coordinates.
 */
#pragma once

#include "common.h"

struct Camera;

extern "C"
{
	/**
	 * Sets the ambient light color for the entire scene.
	 *
	 * @param color The ambient light color.
	 */
	EXPORT void CALL SetAmbient(int color);

	/**
	 * Sets up fog effect for the scene.
	 *
	 * @param color The fog color.
	 * @param start The distance where fog begins.
	 * @param end The distance where fog is fully opaque.
	 */
	EXPORT void CALL SetFog(int color, float start, float end);

	/**
	 * Renders the scene from a camera's perspective.
	 *
	 * @param camera The camera to render from.
	 */
	EXPORT void CALL DrawScene(const Camera *camera);

	/**
	 * Converts a 3D world position to 2D screen coordinates.
	 * The result is stored internally and retrieved with GetCoordX/Y/Z.
	 *
	 * @param camera The camera for the conversion.
	 * @param x The world x-coordinate.
	 * @param y The world y-coordinate.
	 * @param z The world z-coordinate.
	 */
	EXPORT void CALL GetScreenCoords(const Camera *camera, float x, float y, float z);

	/**
	 * Converts a 2D screen position to a 3D world position at a specified depth.
	 * The result is stored internally and retrieved with GetCoordX/Y/Z.
	 *
	 * @param camera The camera for the conversion.
	 * @param x The screen x-coordinate.
	 * @param y The screen y-coordinate.
	 * @param depth The depth (z-distance from camera) for the result.
	 */
	EXPORT void CALL GetSceneCoords(const Camera *camera, float x, float y, float depth);

	/**
	 * Gets the x-coordinate of the last coordinate conversion result.
	 *
	 * @return The x-coordinate.
	 */
	EXPORT float CALL GetCoordX();

	/**
	 * Gets the y-coordinate of the last coordinate conversion result.
	 *
	 * @return The y-coordinate.
	 */
	EXPORT float CALL GetCoordY();

	/**
	 * Gets the z-coordinate of the last coordinate conversion result.
	 *
	 * @return The z-coordinate.
	 */
	EXPORT float CALL GetCoordZ();
}
