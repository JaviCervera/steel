#pragma once

#include "../interface/pixmap_manager.h"
#include "platform_irrlicht.h"

struct PixmapManagerIrrlicht : public PixmapManager
{
	PixmapManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform)
	{
	}

	Pixmap *createPixmap(int width, int height)
	{
		irr::core::array<irr::u8> data(width * height * 4);
		return reinterpret_cast<Pixmap *>(video().createImageFromData(
				m_platform->colorFormat(),
				irr::core::dimension2d<irr::u32>(width, height),
				data.pointer()));
	}

	Pixmap *createPixmap(Texture *texture)
	{
		irr::video::ITexture *tex = reinterpret_cast<irr::video::ITexture *>(texture);
		irr::video::IImage *img = video().createImageFromData(
				m_platform->colorFormat(),
				tex->getSize(),
				tex->lock());
		tex->unlock();
		return reinterpret_cast<Pixmap *>(img);
	}

	Pixmap *createPixmapFromScreen()
	{
		return reinterpret_cast<Pixmap *>(video().createScreenShot());
	}

	Pixmap *loadPixmap(const char *filename)
	{
		return reinterpret_cast<Pixmap *>(video().createImageFromFile(filename));
	}

	void freePixmap(Pixmap *pixmap)
	{
		if (pixmap)
			reinterpret_cast<irr::video::IImage *>(pixmap)->drop();
	}

	void savePixmap(const Pixmap *pixmap, const char *filename)
	{
		if (pixmap && filename)
			video().writeImageToFile(
					reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap)),
					filename,
					9);
	}

	int readPixel(const Pixmap *pixmap, int x, int y)
	{
		return pixmap
							 ? reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap))->getPixel(x, y).color
							 : 0;
	}

	void writePixel(Pixmap *pixmap, int x, int y, int color)
	{
		if (pixmap)
			reinterpret_cast<irr::video::IImage *>(pixmap)->setPixel(x, y, irr::video::SColor(color));
	}

	int pixmapWidth(const Pixmap *pixmap)
	{
		return pixmap
							 ? reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap))->getDimension().Width
							 : 0;
	}

	int pixmapHeight(const Pixmap *pixmap)
	{
		return pixmap
							 ? reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap))->getDimension().Height
							 : 0;
	}

private:
	PlatformIrrlicht *m_platform;

	irr::video::IVideoDriver &video()
	{
		return *m_platform->device().getVideoDriver();
	}
};
