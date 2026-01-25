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

	EXPORT void CALL SetCameraRange(Camera *cam, float near_range, float far_range);
	EXPORT float CALL GetCameraNearRange(Camera *cam);
	EXPORT float CALL GetCameraFarRange(Camera *cam);
	EXPORT void CALL SetCameraAspectRatio(Camera *cam, float ratio);
	EXPORT float CALL GetCameraAspectRatio(Camera *cam);
	EXPORT void CALL SetCameraFOV(Camera *cam, float fov);
	EXPORT float CALL GetCameraFOV(Camera *cam);
}
