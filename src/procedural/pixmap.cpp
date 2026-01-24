#include "../interface/pixmap_manager.h"
#include "engine_internal.h"
#include "pixmap.h"

extern "C"
{
	EXPORT Pixmap *CALL CreatePixmap(int width, int height)
	{
		return GetEngine().pixmapManager().createPixmap(width, height);
	}

	EXPORT Pixmap *CALL CreatePixmapFromTexture(Texture *texture)
	{
		return GetEngine().pixmapManager().createPixmap(texture);
	}

	EXPORT Pixmap *CALL CreatePixmapFromScreen()
	{
		return GetEngine().pixmapManager().createPixmapFromScreen();
	}

	EXPORT Pixmap *CALL LoadPixmap(const char *filename)
	{
		return GetEngine().pixmapManager().loadPixmap(filename);
	}

	EXPORT void CALL FreePixmap(Pixmap *pixmap)
	{
		GetEngine().pixmapManager().freePixmap(pixmap);
	}

	EXPORT void CALL SavePixmap(const Pixmap *pixmap, const char *filename)
	{
		GetEngine().pixmapManager().savePixmap(pixmap, filename);
	}

	EXPORT int CALL ReadPixel(const Pixmap *pixmap, int x, int y)
	{
		return GetEngine().pixmapManager().readPixel(pixmap, x, y);
	}

	EXPORT void CALL WritePixel(Pixmap *pixmap, int x, int y, int color)
	{
		GetEngine().pixmapManager().writePixel(pixmap, x, y, color);
	}
	EXPORT int CALL GetPixmapWidth(const Pixmap *pixmap)
	{
		return GetEngine().pixmapManager().pixmapWidth(pixmap);
	}
	EXPORT int CALL GetPixmapHeight(const Pixmap *pixmap)
	{
		return GetEngine().pixmapManager().pixmapHeight(pixmap);
	}
}
