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

	EXPORT void CALL FreeTexture(Texture *tex)
	{
		GetEngine().textureManager().freeTexture(tex);
	}

	EXPORT void CALL ClearTextureCache()
	{
		GetEngine().textureManager().clearTextureCache();
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
