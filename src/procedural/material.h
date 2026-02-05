/**
 * @file
 * Materials define the visual properties and rendering behavior of entity surfaces.
 * Materials can control textures, lighting, transparency, and various rendering modes.
 */
#pragma once

#include "common.h"

struct Material;
struct Texture;

extern "C"
{
	/**
	 * Sets the diffuse texture of a material.
	 *
	 * @param mat The material.
	 * @param tex The texture to set, or NULL to remove.
	 */
	EXPORT void CALL SetMaterialTexture(Material *mat, Texture *tex);

	/**
	 * Gets the diffuse texture of a material.
	 *
	 * @param mat The material.
	 * @return The texture, or NULL if none.
	 */
	EXPORT Texture *CALL GetMaterialTexture(const Material *mat);

	/**
	 * Sets the lightmap texture of a material.
	 *
	 * @param mat The material.
	 * @param tex The lightmap texture, or NULL to remove.
	 */
	EXPORT void CALL SetMaterialLightmap(Material *mat, Texture *tex);

	/**
	 * Gets the lightmap texture of a material.
	 *
	 * @param mat The material.
	 * @return The lightmap texture, or NULL if none.
	 */
	EXPORT Texture *CALL GetMaterialLightmap(const Material *mat);

	/**
	 * Sets whether a material uses transparency (with optional vertex alpha blending).
	 *
	 * @param mat The material.
	 * @param vertex_alpha True to use vertex alpha, false for texture alpha only.
	 */
	EXPORT void CALL SetMaterialTransparent(Material *mat, bool_t vertex_alpha);

	/**
	 * Checks if a material has transparency enabled.
	 *
	 * @param mat The material.
	 * @return True if transparent, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialTransparent(const Material *mat);

	/**
	 * Sets a material to use additive blending (adds color instead of replacing).
	 *
	 * @param mat The material.
	 */
	EXPORT void CALL SetMaterialAdditive(Material *mat);

	/**
	 * Checks if a material uses additive blending.
	 *
	 * @param mat The material.
	 * @return True if additive, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialAdditive(const Material *mat);

	/**
	 * Sets a material to use solid (opaque) rendering.
	 *
	 * @param mat The material.
	 */
	EXPORT void CALL SetMaterialSolid(Material *mat);

	/**
	 * Checks if a material is solid (opaque).
	 *
	 * @param mat The material.
	 * @return True if solid, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialSolid(const Material *mat);

	/**
	 * Enables or disables wireframe rendering for a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable wireframe, false to disable.
	 */
	EXPORT void CALL SetMaterialWireframe(Material *mat, bool_t enable);

	/**
	 * Checks if a material is rendered in wireframe mode.
	 *
	 * @param mat The material.
	 * @return True if wireframe, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialWireframe(const Material *mat);

	/**
	 * Enables or disables lighting on a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable lighting, false to disable.
	 */
	EXPORT void CALL SetMaterialLightingEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if lighting is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if lighting enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialLightingEnabled(const Material *mat);

	/**
	 * Enables or disables fog on a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable fog, false to disable.
	 */
	EXPORT void CALL SetMaterialFogEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if fog is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if fog enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialFogEnabled(const Material *mat);

	/**
	 * Enables or disables texture filtering on a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable filtering, false to disable.
	 */
	EXPORT void CALL SetMaterialFilteringEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if texture filtering is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if filtering enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialFilteringEnabled(const Material *mat);

	/**
	 * Enables or disables depth reading on a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable depth reading, false to disable.
	 */
	EXPORT void CALL SetMaterialDepthReadEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if depth reading is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if depth reading enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialDepthReadEnabled(const Material *mat);

	/**
	 * Enables or disables depth writing on a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable depth writing, false to disable.
	 */
	EXPORT void CALL SetMaterialDepthWriteEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if depth writing is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if depth writing enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialDepthWriteEnabled(const Material *mat);

	/**
	 * Enables or disables backface culling for a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable culling, false to disable.
	 */
	EXPORT void CALL SetMaterialBackfaceCullingEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if backface culling is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if culling enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialBackfaceCullingEnabled(const Material *mat);

	/**
	 * Enables or disables normal normalization for a material.
	 *
	 * @param mat The material.
	 * @param enable True to enable normalization, false to disable.
	 */
	EXPORT void CALL SetMaterialNormalizeEnabled(Material *mat, bool_t enable);

	/**
	 * Checks if normal normalization is enabled on a material.
	 *
	 * @param mat The material.
	 * @return True if normalization enabled, false otherwise.
	 */
	EXPORT bool_t CALL IsMaterialNormalizeEnabled(const Material *mat);

	/**
	 * Sets the diffuse color of a material.
	 *
	 * @param mat The material.
	 * @param color The diffuse color.
	 */
	EXPORT void CALL SetMaterialDiffuse(Material *mat, int color);

	/**
	 * Gets the diffuse color of a material.
	 *
	 * @param mat The material.
	 * @return The diffuse color.
	 */
	EXPORT int CALL GetMaterialDiffuse(const Material *mat);

	/**
	 * Sets the emissive (glow) color of a material.
	 *
	 * @param mat The material.
	 * @param color The emissive color.
	 */
	EXPORT void CALL SetMaterialEmissive(Material *mat, int color);

	/**
	 * Gets the emissive (glow) color of a material.
	 *
	 * @param mat The material.
	 * @return The emissive color.
	 */
	EXPORT int CALL GetMaterialEmissive(const Material *mat);

	/**
	 * Sets the ambient color of a material.
	 *
	 * @param mat The material.
	 * @param color The ambient color.
	 */
	EXPORT void CALL SetMaterialAmbient(Material *mat, int color);

	/**
	 * Gets the ambient color of a material.
	 *
	 * @param mat The material.
	 * @return The ambient color.
	 */
	EXPORT int CALL GetMaterialAmbient(const Material *mat);

	/**
	 * Sets the specular color of a material.
	 *
	 * @param mat The material.
	 * @param color The specular color.
	 */
	EXPORT void CALL SetMaterialSpecular(Material *mat, int color);

	/**
	 * Gets the specular color of a material.
	 *
	 * @param mat The material.
	 * @return The specular color.
	 */
	EXPORT int CALL GetMaterialSpecular(const Material *mat);

	/**
	 * Sets the shininess (specular exponent) of a material.
	 *
	 * @param mat The material.
	 * @param shininess The shininess value.
	 */
	EXPORT void CALL SetMaterialShininess(Material *mat, float shininess);

	/**
	 * Gets the shininess (specular exponent) of a material.
	 *
	 * @param mat The material.
	 * @return The shininess value.
	 */
	EXPORT float CALL GetMaterialShininess(const Material *mat);

	/**
	 * Transforms a texture within a material (offset, rotation, scale).
	 *
	 * @param mat The material.
	 * @param xoffset The x-offset for the texture.
	 * @param yoffset The y-offset for the texture.
	 * @param angle The rotation angle in degrees.
	 * @param xscale The x-scale factor.
	 * @param yscale The y-scale factor.
	 */
	EXPORT void CALL SetTextureTransform(Material *mat, float xoffset, float yoffset, float angle, float xscale, float yscale);
}
