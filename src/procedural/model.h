/**
 * @file
 * 3D models for use in the 3D world.
 * Models can be loaded from files or programmatically created (cube, sphere).
 * Models are entities, so any entity function can be used on them, such as
 * setting their position, rotation, scale, etc.
 */
#pragma once

#include "common.h"
#include "memblock.h"

struct Model;

extern "C"
{
	/**
	 * Creates a model from memblock data. The memblock can contain multiple buffers.
	 * A buffer is a collection of vertices and indices that will have one material.
	 * The memblock format is as follows:
	 * Short: Number of buffers.
	 * For each buffer:
	 * Byte: 1 if the buffer has 2 UV sets, 0 otherwise.
	 * Short: Number of vertices.
	 * Short: Number of indices.
	 * For each vertex:
	 * Float x 3: Position XYZ.
	 * Float x 3: Normal XYZ.
	 * Int: Color ARGB.
	 * Float x 2: UV1.
	 * Float x 2: UV2 (only if the buffer has 2 UV sets).
	 * For each index:
	 * Short: Vertex index.
	 * Every 3 indices form a triangle.
	 * The model will be rendered with one material per buffer, so if you want
	 * different materials on different parts of the model, you should use multiple buffers.
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
