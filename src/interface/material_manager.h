#pragma once

struct Material;
struct Texture;

struct MaterialManager
{
	virtual ~MaterialManager() {}
	virtual void materialTexture(Material *mat, Texture *tex) = 0;
	virtual Texture *materialTexture(const Material *mat) = 0;
	virtual void materialLightmap(Material *mat, Texture *tex) = 0;
	virtual Texture *materialLightmap(const Material *mat) = 0;
	virtual void materialTransparent(Material *mat, bool vertex_alpha) = 0;
	virtual bool isMaterialTransparent(const Material *mat) = 0;
	virtual void materialAdditive(Material *mat) = 0;
	virtual bool isMaterialAdditive(const Material *mat) = 0;
	virtual void materialSolid(Material *mat) = 0;
	virtual bool isMaterialSolid(const Material *mat) = 0;
	virtual void materialWireframe(Material *mat, bool enable) = 0;
	virtual bool isMaterialWireframe(const Material *mat) = 0;
	virtual void materialLightingEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialLightingEnabled(const Material *mat) = 0;
	virtual void materialFogEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialFogEnabled(const Material *mat) = 0;
	virtual void materialFilteringEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialFilteringEnabled(const Material *mat) = 0;
	virtual void materialDepthReadEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialDepthReadEnabled(const Material *mat) = 0;
	virtual void materialDepthWriteEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialDepthWriteEnabled(const Material *mat) = 0;
	virtual void materialBackfaceCullingEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialBackfaceCullingEnabled(const Material *mat) = 0;
	virtual void materialNormalizeEnabled(Material *mat, bool enable) = 0;
	virtual bool isMaterialNormalizeEnabled(const Material *mat) = 0;
	virtual void materialDiffuse(Material *mat, int color) = 0;
	virtual int materialDiffuse(const Material *mat) = 0;
	virtual void materialEmissive(Material *mat, int color) = 0;
	virtual int materialEmissive(const Material *mat) = 0;
	virtual void materialAmbient(Material *mat, int color) = 0;
	virtual int materialAmbient(const Material *mat) = 0;
	virtual void materialSpecular(Material *mat, int color) = 0;
	virtual int materialSpecular(const Material *mat) = 0;
	virtual void materialShininess(Material *mat, float shininess) = 0;
	virtual float materialShininess(const Material *mat) = 0;
	virtual void textureTransform(Material *mat, float xoffset, float yoffset, float angle, float xscale, float yscale) = 0;
};
