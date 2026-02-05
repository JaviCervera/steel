/**
 * @file
 * Collision detection and physics are handled through colliders attached to entities.
 * Supported collision types include box colliders and mesh colliders from models and animated models.
 */
#pragma once

#include "common.h"

struct AnimModel;
struct Camera;
struct Entity;
struct Model;

extern "C"
{
	/**
	 * Attaches a box collider to an entity.
	 *
	 * @param entity The entity to attach the collider to.
	 */
	EXPORT void CALL SetBoxCollider(Entity *entity);

	/**
	 * Attaches a mesh collider based on a model to an entity.
	 *
	 * @param model The model to use for collision geometry.
	 */
	EXPORT void CALL SetModelCollider(Model *model);

	/**
	 * Attaches a mesh collider based on an animated model to an entity.
	 *
	 * @param model The animated model to use for collision geometry.
	 */
	EXPORT void CALL SetAnimModelCollider(AnimModel *model);

	/**
	 * Removes the collider from an entity.
	 *
	 * @param entity The entity to remove the collider from.
	 */
	EXPORT void CALL RemoveCollider(Entity *entity);

	/**
	 * Checks if an entity has a collider attached.
	 *
	 * @param entity The entity to check.
	 * @return True if the entity has a collider, false otherwise.
	 */
	EXPORT bool_t CALL HasCollider(Entity *entity);

	/**
	 * Sets the collision group mask for an entity.
	 *
	 * @param entity The entity.
	 * @param mask The collision mask value.
	 */
	EXPORT void CALL SetEntityCollisionMask(Entity *entity, int mask);

	/**
	 * Gets the collision group mask of an entity.
	 *
	 * @param entity The entity.
	 * @return The collision mask value.
	 */
	EXPORT int CALL GetEntityCollisionMask(const Entity *entity);

	/**
	 * Slides an entity along collision geometry.
	 *
	 * @param entity The entity to move.
	 * @param x The desired x translation.
	 * @param y The desired y translation.
	 * @param z The desired z translation.
	 * @param rad_x The radius for collision detection in the x direction.
	 * @param rad_y The radius for collision detection in the y direction.
	 * @param rad_z The radius for collision detection in the z direction.
	 * @param mask The collision mask to test against.
	 * @return The entity that was collided with, or NULL if no collision.
	 */
	EXPORT Entity *CALL SlideEntity(
			Entity *entity,
			float x,
			float y,
			float z,
			float rad_x,
			float rad_y,
			float rad_z,
			int mask);

	/**
	 * Casts a ray through the world and returns the first entity hit.
	 *
	 * @param x1 The starting x-coordinate of the ray.
	 * @param y1 The starting y-coordinate of the ray.
	 * @param z1 The starting z-coordinate of the ray.
	 * @param x2 The ending x-coordinate of the ray.
	 * @param y2 The ending y-coordinate of the ray.
	 * @param z2 The ending z-coordinate of the ray.
	 * @param mask The collision mask to test against.
	 * @return The entity hit by the ray, or NULL if no collision.
	 */
	EXPORT Entity *CALL Raycast(float x1, float y1, float z1, float x2, float y2, float z2, int mask);

	/**
	 * Picks an entity at a screen position using a ray from the camera.
	 *
	 * @param camera The camera to cast the ray from.
	 * @param x The screen x-coordinate.
	 * @param y The screen y-coordinate.
	 * @param mask The collision mask to test against.
	 * @return The entity under the cursor, or NULL if none.
	 */
	EXPORT Entity *CALL PickEntity(Camera *camera, float x, float y, int mask);

	/**
	 * Gets the x-coordinate of the last collision point.
	 *
	 * @return The x-coordinate of the last collision.
	 */
	EXPORT float CALL GetCollisionPointX();

	/**
	 * Gets the y-coordinate of the last collision point.
	 *
	 * @return The y-coordinate of the last collision.
	 */
	EXPORT float CALL GetCollisionPointY();

	/**
	 * Gets the z-coordinate of the last collision point.
	 *
	 * @return The z-coordinate of the last collision.
	 */
	EXPORT float CALL GetCollisionPointZ();
}
