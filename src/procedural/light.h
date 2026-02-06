/**
 * @file
 * Lighting for 3D scenes with support for directional and point lights.
 * Lights can be configured with diffuse, ambient, and specular colors.
 * Lights are entities, so any entity function can be used on them, such as
 * setting their position, rotation, scale, etc.
 */
#pragma once

#include "common.h"

struct Light;

extern "C"
{
	/**
	 * Creates a new directional light.
	 *
	 * @return A new directional light entity.
	 */
	EXPORT Light *CALL CreateDirectionalLight();

	/**
	 * Creates a new point light.
	 *
	 * @return A new point light entity.
	 */
	EXPORT Light *CALL CreatePointLight();

	/**
	 * Sets the diffuse color of a light.
	 *
	 * @param light The light.
	 * @param color The diffuse color.
	 */
	EXPORT void CALL SetLightDiffuse(Light *light, int color);

	/**
	 * Gets the diffuse color of a light.
	 *
	 * @param light The light.
	 * @return The diffuse color.
	 */
	EXPORT int CALL GetLightDiffuse(const Light *light);

	/**
	 * Sets the ambient color of a light.
	 *
	 * @param light The light.
	 * @param color The ambient color.
	 */
	EXPORT void CALL SetLightAmbient(Light *light, int color);

	/**
	 * Gets the ambient color of a light.
	 *
	 * @param light The light.
	 * @return The ambient color.
	 */
	EXPORT int CALL GetLightAmbient(const Light *light);

	/**
	 * Sets the specular color of a light.
	 *
	 * @param light The light.
	 * @param color The specular color.
	 */
	EXPORT void CALL SetLightSpecular(Light *light, int color);

	/**
	 * Gets the specular color of a light.
	 *
	 * @param light The light.
	 * @return The specular color.
	 */
	EXPORT int CALL GetLightSpecular(const Light *light);

	/**
	 * Sets the radius of a point light.
	 *
	 * @param light The light.
	 * @param radius The light radius.
	 */
	EXPORT void CALL SetLightRadius(Light *light, float radius);

	/**
	 * Gets the radius of a point light.
	 *
	 * @param light The light.
	 * @return The light radius.
	 */
	EXPORT float CALL GetLightRadius(const Light *light);
}
