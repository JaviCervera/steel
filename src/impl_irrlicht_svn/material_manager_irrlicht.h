#pragma once

#include <irrlicht.h>
#include "../interface/material_manager.h"

struct MaterialManagerIrrlicht : public MaterialManager
{
	void materialTexture(Material *mat, Texture *tex)
	{
		if (!mat)
			return;
		if (cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
			cast(mat)->TextureLayer[1].Texture = reinterpret_cast<irr::video::ITexture *>(tex);
		else
			cast(mat)->TextureLayer[0].Texture = reinterpret_cast<irr::video::ITexture *>(tex);
	}

	Texture *materialTexture(const Material *mat)
	{
		if (!mat)
			return NULL;
		if (cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
			return reinterpret_cast<Texture *>(cast(mat)->TextureLayer[1].Texture);
		else
			return reinterpret_cast<Texture *>(cast(mat)->TextureLayer[0].Texture);
	}

	void materialLightmap(Material *mat, Texture *tex)
	{
		if (!mat)
			return;
		if (cast(mat)->MaterialType != irr::video::EMT_LIGHTMAP_LIGHTING)
			cast(mat)->TextureLayer[1].Texture = cast(mat)->TextureLayer[0].Texture;
		cast(mat)->TextureLayer[0].Texture = reinterpret_cast<irr::video::ITexture *>(tex);
		cast(mat)->MaterialType = irr::video::EMT_LIGHTMAP_LIGHTING;
	}

	Texture *materialLightmap(const Material *mat)
	{
		return (mat && cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
							 ? reinterpret_cast<Texture *>(cast(mat)->TextureLayer[0].Texture)
							 : NULL;
	}

	void materialTransparent(Material *mat, bool vertex_alpha)
	{
		if (!mat)
			return;
		if (cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
			cast(mat)->TextureLayer[0].Texture = cast(mat)->TextureLayer[1].Texture;
		cast(mat)->MaterialType =
				vertex_alpha
						? irr::video::EMT_TRANSPARENT_VERTEX_ALPHA
						: irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
	}

	bool isMaterialTransparent(const Material *mat)
	{
		return mat && (cast(mat)->MaterialType == irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL ||
									 cast(mat)->MaterialType == irr::video::EMT_TRANSPARENT_VERTEX_ALPHA);
	}

	void materialAdditive(Material *mat)
	{
		{
			if (!mat)
				return;
			if (cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
				cast(mat)->TextureLayer[0].Texture = cast(mat)->TextureLayer[1].Texture;
			cast(mat)->MaterialType = irr::video::EMT_TRANSPARENT_ADD_COLOR;
		}
	}

	bool isMaterialAdditive(const Material *mat)
	{
		return mat && cast(mat)->MaterialType == irr::video::EMT_TRANSPARENT_VERTEX_ALPHA;
	}

	void materialSolid(Material *mat)
	{
		if (!mat)
			return;
		if (cast(mat)->MaterialType == irr::video::EMT_LIGHTMAP_LIGHTING)
			cast(mat)->TextureLayer[0].Texture = cast(mat)->TextureLayer[1].Texture;
		cast(mat)->MaterialType = irr::video::EMT_SOLID;
	}

	bool isMaterialSolid(const Material *mat)
	{
		return mat && cast(mat)->MaterialType == irr::video::EMT_SOLID;
	}

	void materialWireframe(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_WIREFRAME, enable);
	}

	bool isMaterialWireframe(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_WIREFRAME);
	}

	void materialLightingEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_LIGHTING, enable);
	}

	bool isMaterialLightingEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_LIGHTING);
	}

	void materialFogEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_FOG_ENABLE, enable);
	}

	bool isMaterialFogEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_FOG_ENABLE);
	}

	void materialFilteringEnabled(Material *mat, bool enable)
	{
		if (!mat)
			return;
		if (enable)
		{
			cast(mat)->setFlag(irr::video::EMF_BILINEAR_FILTER, true);
			cast(mat)->setFlag(irr::video::EMF_TRILINEAR_FILTER, false);
			cast(mat)->setFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
		}
		else
		{
			cast(mat)->setFlag(irr::video::EMF_BILINEAR_FILTER, false);
			cast(mat)->setFlag(irr::video::EMF_TRILINEAR_FILTER, false);
			cast(mat)->setFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
		}
	}

	bool isMaterialFilteringEnabled(const Material *mat)
	{
		return mat && (cast(mat)->getFlag(irr::video::EMF_BILINEAR_FILTER) ||
									 cast(mat)->getFlag(irr::video::EMF_TRILINEAR_FILTER) ||
									 cast(mat)->getFlag(irr::video::EMF_ANISOTROPIC_FILTER));
	}

	void materialDepthReadEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_ZBUFFER, enable);
	}

	bool isMaterialDepthReadEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_ZBUFFER);
	}

	void materialDepthWriteEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_ZWRITE_ENABLE, enable);
	}

	bool isMaterialDepthWriteEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_ZWRITE_ENABLE);
	}

	void materialBackfaceCullingEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_BACK_FACE_CULLING, enable);
	}

	bool isMaterialBackfaceCullingEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_BACK_FACE_CULLING);
	}

	void materialNormalizeEnabled(Material *mat, bool enable)
	{
		if (mat)
			cast(mat)->setFlag(irr::video::EMF_NORMALIZE_NORMALS, enable);
	}

	bool isMaterialNormalizeEnabled(const Material *mat)
	{
		return mat && cast(mat)->getFlag(irr::video::EMF_NORMALIZE_NORMALS);
	}

	void materialDiffuse(Material *mat, int color)
	{
		if (mat)
			cast(mat)->DiffuseColor = irr::video::SColor(color);
	}

	int materialDiffuse(const Material *mat)
	{
		return mat ? cast(mat)->DiffuseColor.color : 0;
	}

	void materialEmissive(Material *mat, int color)
	{
		if (mat)
			cast(mat)->EmissiveColor = irr::video::SColor(color);
	}

	int materialEmissive(const Material *mat)
	{
		return mat ? cast(mat)->EmissiveColor.color : 0;
	}

	void materialAmbient(Material *mat, int color)
	{
		if (mat)
			cast(mat)->AmbientColor = irr::video::SColor(color);
	}

	int materialAmbient(const Material *mat)
	{
		return mat ? cast(mat)->AmbientColor.color : 0;
	}

	void materialSpecular(Material *mat, int color)
	{
		if (mat)
			cast(mat)->SpecularColor = irr::video::SColor(color);
	}

	int materialSpecular(const Material *mat)
	{
		return mat ? cast(mat)->SpecularColor.color : 0;
	}

	void materialShininess(Material *mat, float shininess)
	{
		if (mat)
			cast(mat)->Shininess = shininess;
	}

	float materialShininess(const Material *mat)
	{
		return mat ? cast(mat)->Shininess : 0;
	}

	void textureTransform(Material *mat, float xoffset, float yoffset, float angle, float xscale, float yscale)
	{
		if (!mat)
			return;
		irr::core::matrix4 mat_transform;
		mat_transform.buildTextureTransform(
				angle * irr::core::DEGTORAD,
				irr::core::vector2d<irr::f32>(0.5f, 0.5f),
				irr::core::vector2d<irr::f32>(xoffset, yoffset),
				irr::core::vector2d<irr::f32>(xscale, yscale));
		cast(mat)->setTextureMatrix(0, mat_transform);
	}

private:
	static irr::video::SMaterial *cast(Material *mat)
	{
		return reinterpret_cast<irr::video::SMaterial *>(mat);
	}

	static const irr::video::SMaterial *cast(const Material *mat)
	{
		return reinterpret_cast<const irr::video::SMaterial *>(mat);
	}
};
