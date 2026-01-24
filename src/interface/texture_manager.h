#pragma once

struct Pixmap;
struct Texture;

struct TextureManager
{
	virtual ~TextureManager() {}
	virtual Texture *createTexture(int width, int height) = 0;
	virtual Texture *createTexture(const Pixmap *pixmap) = 0;
	virtual Texture *loadTexture(const char *filename) = 0;
	virtual void clearTextureCache() = 0;
	virtual int textureWidth(const Texture *tex) = 0;
	virtual int textureHeight(const Texture *tex) = 0;
	virtual const char *textureFilename(const Texture *tex) = 0;
};
