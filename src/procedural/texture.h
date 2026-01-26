#pragma once

#include "common.h"

struct Pixmap;
struct Texture;

extern "C"
{
	EXPORT Texture *CALL CreateTexture(int width, int height);
	EXPORT Texture *CALL CreateTextureFromPixmap(Pixmap *pixmap);
	EXPORT Texture *CALL LoadTexture(const char *filename);
	EXPORT void CALL FreeTexture(Texture *tex);
	EXPORT void CALL ClearTextureCache();
	EXPORT int CALL GetTextureWidth(const Texture *tex);
	EXPORT int CALL GetTextureHeight(const Texture *tex);
	EXPORT const char *CALL GetTextureFilename(const Texture *tex);
}
