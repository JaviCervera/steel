/**
 * @file
 * Entities are the fundamental objects in the 3D world. They can be positioned, rotated, scaled,
 * and parented to form hierarchies. Entities serve as containers for various components like models
 * and materials.
 */
#pragma once

#include "common.h"

struct Entity;
struct Material;

extern "C"
{
	/**
	 * Creates a new empty entity.
	 *
	 * @return A new entity.
	 */
	EXPORT Entity *CALL CreateEntity();

	/**
	 * Frees an entity and releases its resources.
	 *
	 * @param entity The entity to free.
	 */
	EXPORT void CALL FreeEntity(Entity *entity);

	/**
	 * Gets the type name of an entity (e.g., "Model", "Camera").
	 *
	 * @param entity The entity.
	 * @return A string describing the entity type.
	 */
	EXPORT const char *CALL GetEntityType(Entity *entity);

	/**
	 * Sets a custom name for an entity.
	 *
	 * @param entity The entity.
	 * @param name The name to assign.
	 */
	EXPORT void CALL SetEntityName(Entity *entity, const char *name);

	/**
	 * Gets the name of an entity.
	 *
	 * @param entity The entity.
	 * @return The entity's name.
	 */
	EXPORT const char *CALL GetEntityName(Entity *entity);

	/**
	 * Sets whether an entity is visible.
	 *
	 * @param entity The entity.
	 * @param visible True to show the entity, false to hide it.
	 */
	EXPORT void CALL SetEntityVisible(Entity *entity, bool_t visible);

	/**
	 * Checks if an entity is visible.
	 *
	 * @param entity The entity.
	 * @return True if the entity is visible, false otherwise.
	 */
	EXPORT bool_t CALL IsEntityVisible(Entity *entity);

	/**
	 * Sets the parent entity for hierarchical transformation.
	 *
	 * @param entity The entity to set the parent for.
	 * @param parent The parent entity, or NULL to remove parent.
	 */
	EXPORT void CALL SetEntityParent(Entity *entity, Entity *parent);

	/**
	 * Gets the parent entity.
	 *
	 * @param entity The entity.
	 * @return The parent entity, or NULL if none.
	 */
	EXPORT Entity *CALL GetEntityParent(Entity *entity);

	/**
	 * Gets the number of child entities.
	 *
	 * @param entity The entity.
	 * @return The number of children.
	 */
	EXPORT int CALL GetEntityNumChildren(Entity *entity);

	/**
	 * Gets a child entity by index.
	 *
	 * @param entity The entity.
	 * @param index The child index (0-based).
	 * @return The child entity.
	 */
	EXPORT Entity *CALL EntityChild(Entity *entity, int index);

	/**
	 * Sets the absolute position of an entity in world space.
	 *
	 * @param entity The entity.
	 * @param x The world x-coordinate.
	 * @param y The world y-coordinate.
	 * @param z The world z-coordinate.
	 */
	EXPORT void CALL SetEntityPosition(Entity *entity, float x, float y, float z);

	/**
	 * Moves an entity to a new absolute position (same as SetEntityPosition).
	 *
	 * @param entity The entity.
	 * @param x The world x-coordinate.
	 * @param y The world y-coordinate.
	 * @param z The world z-coordinate.
	 */
	EXPORT void CALL MoveEntity(Entity *entity, float x, float y, float z);

	/**
	 * Translates an entity relative to its current position.
	 *
	 * @param entity The entity.
	 * @param x The relative translation in the x direction.
	 * @param y The relative translation in the y direction.
	 * @param z The relative translation in the z direction.
	 */
	EXPORT void CALL TranslateEntity(Entity *entity, float x, float y, float z);

	/**
	 * Gets the absolute x-coordinate of an entity in world space.
	 *
	 * @param entity The entity.
	 * @return The world x-coordinate.
	 */
	EXPORT float CALL GetEntityX(Entity *entity);

	/**
	 * Gets the absolute y-coordinate of an entity in world space.
	 *
	 * @param entity The entity.
	 * @return The world y-coordinate.
	 */
	EXPORT float CALL GetEntityY(Entity *entity);

	/**
	 * Gets the absolute z-coordinate of an entity in world space.
	 *
	 * @param entity The entity.
	 * @return The world z-coordinate.
	 */
	EXPORT float CALL GetEntityZ(Entity *entity);

	/**
	 * Gets the x-coordinate of an entity relative to its parent.
	 *
	 * @param entity The entity.
	 * @return The local x-coordinate.
	 */
	EXPORT float CALL GetEntityLocalX(Entity *entity);

	/**
	 * Gets the y-coordinate of an entity relative to its parent.
	 *
	 * @param entity The entity.
	 * @return The local y-coordinate.
	 */
	EXPORT float CALL GetEntityLocalY(Entity *entity);

	/**
	 * Gets the z-coordinate of an entity relative to its parent.
	 *
	 * @param entity The entity.
	 * @return The local z-coordinate.
	 */
	EXPORT float CALL GetEntityLocalZ(Entity *entity);

	/**
	 * Sets the rotation of an entity in Euler angles.
	 *
	 * @param entity The entity.
	 * @param pitch The rotation around the X axis (in degrees).
	 * @param yaw The rotation around the Y axis (in degrees).
	 * @param roll The rotation around the Z axis (in degrees).
	 */
	EXPORT void CALL SetEntityRotation(Entity *entity, float pitch, float yaw, float roll);

	/**
	 * Rotates an entity relative to its current rotation.
	 *
	 * @param entity The entity.
	 * @param pitch The relative rotation around the X axis (in degrees).
	 * @param yaw The relative rotation around the Y axis (in degrees).
	 * @param roll The relative rotation around the Z axis (in degrees).
	 */
	EXPORT void CALL TurnEntity(Entity *entity, float pitch, float yaw, float roll);

	/**
	 * Rotates an entity to point towards a position in world space.
	 *
	 * @param entity The entity.
	 * @param x The target x-coordinate.
	 * @param y The target y-coordinate.
	 * @param z The target z-coordinate.
	 */
	EXPORT void CALL PointEntity(Entity *entity, float x, float y, float z);

	/**
	 * Gets the pitch rotation of an entity.
	 *
	 * @param entity The entity.
	 * @return The pitch angle in degrees.
	 */
	EXPORT float CALL GetEntityPitch(Entity *entity);

	/**
	 * Gets the yaw rotation of an entity.
	 *
	 * @param entity The entity.
	 * @return The yaw angle in degrees.
	 */
	EXPORT float CALL GetEntityYaw(Entity *entity);

	/**
	 * Gets the roll rotation of an entity.
	 *
	 * @param entity The entity.
	 * @return The roll angle in degrees.
	 */
	EXPORT float CALL GetEntityRoll(Entity *entity);

	/**
	 * Sets the scale of an entity.
	 *
	 * @param entity The entity.
	 * @param x The scale factor for the x-axis.
	 * @param y The scale factor for the y-axis.
	 * @param z The scale factor for the z-axis.
	 */
	EXPORT void CALL SetEntityScale(Entity *entity, float x, float y, float z);

	/**
	 * Gets the x-axis scale factor of an entity.
	 *
	 * @param entity The entity.
	 * @return The x-scale.
	 */
	EXPORT float CALL GetEntityScaleX(Entity *entity);

	/**
	 * Gets the y-axis scale factor of an entity.
	 *
	 * @param entity The entity.
	 * @return The y-scale.
	 */
	EXPORT float CALL GetEntityScaleY(Entity *entity);

	/**
	 * Gets the z-axis scale factor of an entity.
	 *
	 * @param entity The entity.
	 * @return The z-scale.
	 */
	EXPORT float CALL GetEntityScaleZ(Entity *entity);

	/**
	 * Gets the width of an entity's bounding box.
	 *
	 * @param entity The entity.
	 * @return The width.
	 */
	EXPORT float CALL GetEntityWidth(Entity *entity);

	/**
	 * Gets the height of an entity's bounding box.
	 *
	 * @param entity The entity.
	 * @return The height.
	 */
	EXPORT float CALL GetEntityHeight(Entity *entity);

	/**
	 * Gets the depth of an entity's bounding box.
	 *
	 * @param entity The entity.
	 * @return The depth.
	 */
	EXPORT float CALL GetEntityDepth(Entity *entity);

	/**
	 * Gets the number of materials in an entity.
	 *
	 * @param entity The entity.
	 * @return The number of materials.
	 */
	EXPORT int CALL GetEntityNumMaterials(Entity *entity);

	/**
	 * Gets a material from an entity by index.
	 *
	 * @param entity The entity.
	 * @param index The material index (0-based).
	 * @return The material.
	 */
	EXPORT Material *CALL GetEntityMaterial(Entity *entity, int index);

	/**
	 * Calculates the distance from an entity to a point in world space.
	 *
	 * @param entity The entity.
	 * @param x The point x-coordinate.
	 * @param y The point y-coordinate.
	 * @param z The point z-coordinate.
	 * @return The distance.
	 */
	EXPORT float CALL GetEntityDistance(Entity *entity, float x, float y, float z);

	/**
	 * Calculates the squared distance from an entity to a point in world space.
	 *
	 * @param entity The entity.
	 * @param x The point x-coordinate.
	 * @param y The point y-coordinate.
	 * @param z The point z-coordinate.
	 * @return The squared distance.
	 */
	EXPORT float CALL GetEntitySquaredDistance(Entity *entity, float x, float y, float z);
}
