/**
 * @file
 * Audio listener positioning for 3D spatial sound.
 * The listener position and orientation define the point from which 3D sounds are calculated.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Sets the position and orientation of the audio listener.
	 * This is typically synchronized with the camera position for proper spatial audio.
	 *
	 * @param x The listener x-coordinate in world space.
	 * @param y The listener y-coordinate in world space.
	 * @param z The listener z-coordinate in world space.
	 * @param yaw The listener orientation (yaw angle in degrees).
	 */
	EXPORT void CALL SetListener(float x, float y, float z, float yaw);
}
