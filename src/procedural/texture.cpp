#include "../interface/texture_manager.h"
#include "engine_internal.h"
#include "texture.h"

extern "C"
{
	EXPORT Texture *CALL CreateTexture(int width, int height)
	{
		return GetEngine().textureManager().createTexture(width, height);
	}

	EXPORT Texture *CALL CreateTextureFromPixmap(Pixmap *pixmap)
	{
		return GetEngine().textureManager().createTexture(pixmap);
	}

	EXPORT Texture *CALL LoadTexture(const char *filename)
	{
		return GetEngine().textureManager().loadTexture(filename);
	}

	EXPORT void CALL ClearTextureCache()
	{
		GetEngine().textureManager().clearTextureCache();
	}

	EXPORT void *CALL LockTexture(Texture *tex)
	{
		return GetEngine().textureManager().lockTexture(tex);
	}

	EXPORT void CALL UnlockTexture(Texture *tex)
	{
		GetEngine().textureManager().unlockTexture(tex);
	}

	EXPORT void CALL SetTextureColorKey(Texture *tex, int color)
	{
		GetEngine().textureManager().textureColorKey(tex, color);
	}

	EXPORT void CALL NormalizeTexture(Texture *tex, float amplitude)
	{
		GetEngine().textureManager().normalizeTexture(tex, amplitude);
	}

	EXPORT int CALL GetTextureWidth(const Texture *tex)
	{
		return GetEngine().textureManager().textureWidth(tex);
	}

	EXPORT int CALL GetTextureHeight(const Texture *tex)
	{
		return GetEngine().textureManager().textureHeight(tex);
	}

	EXPORT const char *CALL GetTextureFilename(const Texture *tex)
	{
		return GetEngine().textureManager().textureFilename(tex);
	}
}
