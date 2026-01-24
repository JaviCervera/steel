#pragma once

struct Pixmap;
struct Texture;

struct PixmapManager
{
	virtual ~PixmapManager() {}
	virtual Pixmap *createPixmap(int width, int height) = 0;
	virtual Pixmap *createPixmap(Texture *texture) = 0;
	virtual Pixmap *createPixmapFromScreen() = 0;
	virtual Pixmap *loadPixmap(const char *filename) = 0;
	virtual void freePixmap(Pixmap *pixmap) = 0;
	virtual void savePixmap(const Pixmap *pixmap, const char *filename) = 0;
	virtual int readPixel(const Pixmap *pixmap, int x, int y) = 0;
	virtual void writePixel(Pixmap *pixmap, int x, int y, int color) = 0;
	virtual int pixmapWidth(const Pixmap *pixmap) = 0;
	virtual int pixmapHeight(const Pixmap *pixmap) = 0;
};
