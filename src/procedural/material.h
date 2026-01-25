#pragma once

#include "common.h"

struct Material;
struct Texture;

extern "C"
{
	EXPORT void CALL SetMaterialTexture(Material *mat, Texture *tex);
	EXPORT Texture *CALL GetMaterialTexture(const Material *mat);
	EXPORT void CALL SetMaterialLightmap(Material *mat, Texture *tex);
	EXPORT Texture *CALL GetMaterialLightmap(const Material *mat);
	EXPORT void CALL SetMaterialTransparent(Material *mat, bool_t vertex_alpha);
	EXPORT bool_t CALL IsMaterialTransparent(const Material *mat);
	EXPORT void CALL SetMaterialAdditive(Material *mat);
	EXPORT bool_t CALL IsMaterialAdditive(const Material *mat);
	EXPORT void CALL SetMaterialSolid(Material *mat);
	EXPORT bool_t CALL IsMaterialSolid(const Material *mat);
	EXPORT void CALL SetMaterialWireframe(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialWireframe(const Material *mat);
	EXPORT void CALL SetMaterialLightingEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialLightingEnabled(const Material *mat);
	EXPORT void CALL SetMaterialFogEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialFogEnabled(const Material *mat);
	EXPORT void CALL SetMaterialFilteringEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialFilteringEnabled(const Material *mat);
	EXPORT void CALL SetMaterialDepthReadEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialDepthReadEnabled(const Material *mat);
	EXPORT void CALL SetMaterialDepthWriteEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialDepthWriteEnabled(const Material *mat);
	EXPORT void CALL SetMaterialBackfaceCullingEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialBackfaceCullingEnabled(const Material *mat);
	EXPORT void CALL SetMaterialNormalizeEnabled(Material *mat, bool_t enable);
	EXPORT bool_t CALL IsMaterialNormalizeEnabled(const Material *mat);
	EXPORT void CALL SetMaterialDiffuse(Material *mat, int color);
	EXPORT int CALL GetMaterialDiffuse(const Material *mat);
	EXPORT void CALL SetMaterialEmissive(Material *mat, int color);
	EXPORT int CALL GetMaterialEmissive(const Material *mat);
	EXPORT void CALL SetMaterialAmbient(Material *mat, int color);
	EXPORT int CALL GetMaterialAmbient(const Material *mat);
	EXPORT void CALL SetMaterialSpecular(Material *mat, int color);
	EXPORT int CALL GetMaterialSpecular(const Material *mat);
	EXPORT void CALL SetMaterialShininess(Material *mat, float shininess);
	EXPORT float CALL GetMaterialShininess(const Material *mat);
	EXPORT void CALL SetTextureTransform(Material *mat, float xoffset, float yoffset, float angle, float xscale, float yscale);
}
