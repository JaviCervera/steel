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
	virtual void *lockTexture(Texture *tex) = 0;
	virtual void unlockTexture(Texture *tex) = 0;
	virtual void textureColorKey(Texture *tex, int color) = 0;
	virtual void normalizeTexture(Texture *tex, float amplitude) = 0;
	virtual int textureWidth(const Texture *tex) = 0;
	virtual int textureHeight(const Texture *tex) = 0;
	virtual const char *textureFilename(const Texture *tex) = 0;
};
