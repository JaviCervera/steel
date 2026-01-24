#pragma once

#include "common.h"

struct Pixmap;
struct Texture;

extern "C"
{
	EXPORT Pixmap *CALL CreatePixmap(int width, int height);
	EXPORT Pixmap *CALL CreatePixmapFromTexture(Texture *texture);
	EXPORT Pixmap *CALL CreatePixmapFromScreen();
	EXPORT Pixmap *CALL LoadPixmap(const char *filename);
	EXPORT void CALL FreePixmap(Pixmap *pixmap);
	EXPORT void CALL SavePixmap(const Pixmap *pixmap, const char *filename);
	EXPORT int CALL ReadPixel(const Pixmap *pixmap, int x, int y);
	EXPORT void CALL WritePixel(Pixmap *pixmap, int x, int y, int color);
	EXPORT int CALL GetPixmapWidth(const Pixmap *pixmap);
	EXPORT int CALL GetPixmapHeight(const Pixmap *pixmap);
}
