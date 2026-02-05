/**
 * @file
 * 3D models for use in the 3D world.
 * Models can be loaded from files or programmatically created (cube, sphere).
 */
#pragma once

#include "common.h"
#include "memblock.h"

struct Model;

extern "C"
{
	/**
	 * Creates a model from memblock data.
	 *
	 * @param data The memblock containing the model geometry data.
	 * @return A new model, or NULL if creation fails.
	 */
	EXPORT Model *CALL CreateModel(const Memblock *data);

	/**
	 * Creates a cube-shaped model.
	 *
	 * @return A new cube model.
	 */
	EXPORT Model *CALL CreateCubeModel();

	/**
	 * Creates a sphere-shaped model.
	 *
	 * @return A new sphere model.
	 */
	EXPORT Model *CALL CreateSphereModel();
}
