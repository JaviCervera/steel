#pragma once

#include "../interface/material_manager.h"
#include "engine_internal.h"
#include "material.h"

extern "C"
{
	EXPORT void CALL SetMaterialTexture(Material *mat, Texture *tex)
	{
		GetEngine().materialManager().materialTexture(mat, tex);
	}

	EXPORT Texture *CALL GetMaterialTexture(const Material *mat)
	{
		return GetEngine().materialManager().materialTexture(mat);
	}

	EXPORT void CALL SetMaterialLightmap(Material *mat, Texture *tex)
	{
		GetEngine().materialManager().materialLightmap(mat, tex);
	}

	EXPORT Texture *CALL GetMaterialLightmap(const Material *mat)
	{
		return GetEngine().materialManager().materialLightmap(mat);
	}

	EXPORT void CALL SetMaterialTransparent(Material *mat, bool_t vertex_alpha)
	{
		GetEngine().materialManager().materialTransparent(mat, vertex_alpha);
	}

	EXPORT bool_t CALL IsMaterialTransparent(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialTransparent(mat);
	}

	EXPORT void CALL SetMaterialAdditive(Material *mat)
	{
		GetEngine().materialManager().materialAdditive(mat);
	}

	EXPORT bool_t CALL IsMaterialAdditive(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialAdditive(mat);
	}

	EXPORT void CALL SetMaterialSolid(Material *mat)
	{
		GetEngine().materialManager().materialSolid(mat);
	}

	EXPORT bool_t CALL IsMaterialSolid(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialSolid(mat);
	}

	EXPORT void CALL SetMaterialWireframe(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialWireframe(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialWireframe(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialWireframe(mat);
	}

	EXPORT void CALL SetMaterialLightingEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialLightingEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialLightingEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialLightingEnabled(mat);
	}

	EXPORT void CALL SetMaterialFogEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialFogEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialFogEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialFogEnabled(mat);
	}

	EXPORT void CALL SetMaterialFilteringEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialFilteringEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialFilteringEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialFilteringEnabled(mat);
	}

	EXPORT void CALL SetMaterialDepthReadEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialDepthReadEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialDepthReadEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialDepthReadEnabled(mat);
	}

	EXPORT void CALL SetMaterialDepthWriteEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialDepthWriteEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialDepthWriteEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialDepthWriteEnabled(mat);
	}

	EXPORT void CALL SetMaterialBackfaceCullingEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialBackfaceCullingEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialBackfaceCullingEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialBackfaceCullingEnabled(mat);
	}

	EXPORT void CALL SetMaterialNormalizeEnabled(Material *mat, bool_t enable)
	{
		GetEngine().materialManager().materialNormalizeEnabled(mat, enable);
	}

	EXPORT bool_t CALL IsMaterialNormalizeEnabled(const Material *mat)
	{
		return GetEngine().materialManager().isMaterialNormalizeEnabled(mat);
	}

	EXPORT void CALL SetMaterialDiffuse(Material *mat, int color)
	{
		GetEngine().materialManager().materialDiffuse(mat, color);
	}

	EXPORT int CALL GetMaterialDiffuse(const Material *mat)
	{
		return GetEngine().materialManager().materialDiffuse(mat);
	}

	EXPORT void CALL SetMaterialEmissive(Material *mat, int color)
	{
		GetEngine().materialManager().materialEmissive(mat, color);
	}

	EXPORT int CALL GetMaterialEmissive(const Material *mat)
	{
		return GetEngine().materialManager().materialEmissive(mat);
	}

	EXPORT void CALL SetMaterialAmbient(Material *mat, int color)
	{
		GetEngine().materialManager().materialAmbient(mat, color);
	}

	EXPORT int CALL GetMaterialAmbient(const Material *mat)
	{
		return GetEngine().materialManager().materialAmbient(mat);
	}

	EXPORT void CALL SetMaterialSpecular(Material *mat, int color)
	{
		GetEngine().materialManager().materialSpecular(mat, color);
	}

	EXPORT int CALL GetMaterialSpecular(const Material *mat)
	{
		return GetEngine().materialManager().materialSpecular(mat);
	}

	EXPORT void CALL SetMaterialShininess(Material *mat, float shininess)
	{
		GetEngine().materialManager().materialShininess(mat, shininess);
	}

	EXPORT float CALL GetMaterialShininess(const Material *mat)
	{
		return GetEngine().materialManager().materialShininess(mat);
	}

	EXPORT void CALL SetTextureTransform(Material *mat, float xoffset, float yoffset, float angle, float xscale, float yscale)
	{
		GetEngine().materialManager().textureTransform(mat, xoffset, yoffset, angle, xscale, yscale);
	}
}
