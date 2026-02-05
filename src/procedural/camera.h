/**
 * @file
 * A camera is a special type of Entity which is not visible in the world, but defines how the world
 * will be rendered. It can be positioned and rotated in the world using the Entity functions.
 * */
#pragma once

#include "common.h"

struct Camera;

extern "C"
{
	/**
	 * Creates a new camera.
	 *
	 * @return A new camera entity.
	 */
	EXPORT Camera *CALL CreateCamera();

	/**
	 * Sets the near and far clipping planes for the camera.
	 *
	 * @param cam The camera entity.
	 * @param near_range The distance to the near clipping plane.
	 * @param far_range The distance to the far clipping plane.
	 */
	EXPORT void CALL SetCameraRange(Camera *cam, float near_range, float far_range);

	/**
	 * Gets the near clipping plane distance of the camera.
	 *
	 * @param cam The camera entity.
	 * @return The distance to the near clipping plane.
	 */
	EXPORT float CALL GetCameraNearRange(Camera *cam);

	/**
	 * Gets the far clipping plane distance of the camera.
	 *
	 * @param cam The camera entity.
	 * @return The distance to the far clipping plane.
	 */
	EXPORT float CALL GetCameraFarRange(Camera *cam);

	/**
	 * Sets the aspect ratio of the camera.
	 *
	 * @param cam The camera entity.
	 * @param ratio The aspect ratio (width / height).
	 */
	EXPORT void CALL SetCameraAspectRatio(Camera *cam, float ratio);

	/**
	 * Gets the aspect ratio of the camera.
	 *
	 * @param cam The camera entity.
	 * @return The aspect ratio (width / height).
	 */
	EXPORT float CALL GetCameraAspectRatio(Camera *cam);

	/**
	 * Sets the field of view (FOV) of the camera.
	 *
	 * @param cam The camera entity.
	 * @param fov The field of view in degrees.
	 */
	EXPORT void CALL SetCameraFOV(Camera *cam, float fov);

	/**
	 * Gets the field of view (FOV) of the camera.
	 *
	 * @param cam The camera entity.
	 * @return The field of view in degrees.
	 */
	EXPORT float CALL GetCameraFOV(Camera *cam);
}
