#pragma once

#include "../interface/texture_manager.h"
#include "platform_irrlicht.h"

struct TextureManagerIrrlicht : public TextureManager
{
	TextureManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform)
	{
	}

	Texture *createTexture(int width, int height)
	{
		return reinterpret_cast<Texture *>(video().addTexture(
				irr::core::dimension2di(width, height),
				"",
				format()));
	}

	Texture *createTexture(const Pixmap *pixmap)
	{
		return reinterpret_cast<Texture *>(video().addTexture(
				"",
				reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap))));
	}

	Texture *loadTexture(const char *filename)
	{
		return reinterpret_cast<Texture *>(video().getTexture(filename));
	}

	void clearTextureCache()
	{
		video().removeAllTextures();
	}

	void *lockTexture(Texture *tex)
	{
		return tex ? reinterpret_cast<irr::video::ITexture *>(tex)->lock() : NULL;
	}

	void unlockTexture(Texture *tex)
	{
		if (tex)
			reinterpret_cast<irr::video::ITexture *>(tex)->unlock();
	}

	void textureColorKey(Texture *tex, int color)
	{
		if (tex)
			video().makeColorKeyTexture(reinterpret_cast<irr::video::ITexture *>(tex), m_platform->irrColor(color));
	}

	void normalizeTexture(Texture *tex, float amplitude)
	{
		if (tex)
			video().makeNormalMapTexture(reinterpret_cast<irr::video::ITexture *>(tex), amplitude);
	}

	int textureWidth(const Texture *tex)
	{
		return tex
							 ? reinterpret_cast<irr::video::ITexture *>(const_cast<Texture *>(tex))->getOriginalSize().Width
							 : 0;
	}

	int textureHeight(const Texture *tex)
	{
		return tex
							 ? reinterpret_cast<irr::video::ITexture *>(const_cast<Texture *>(tex))->getOriginalSize().Height
							 : 0;
	}

	const char *textureFilename(const Texture *tex)
	{
		return tex
							 ? reinterpret_cast<irr::video::ITexture *>(const_cast<Texture *>(tex))->getName().c_str()
							 : "";
	}

private:
	PlatformIrrlicht *m_platform;

	irr::video::IVideoDriver &video()
	{
		return *m_platform->device().getVideoDriver();
	}

	irr::video::ECOLOR_FORMAT format()
	{
		return video().getTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT)
							 ? irr::video::ECF_A8R8G8B8
							 : irr::video::ECF_A1R5G5B5;
	}
};
