#pragma once

#include <stdio.h>
#include <stdlib.h>
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
		char name[32];
		sprintf(name, "%d", rand());
		return reinterpret_cast<Texture *>(video().addTexture(
				irr::core::dimension2di(width, height),
				name,
				m_platform->colorFormat()));
	}

	Texture *createTexture(const Pixmap *pixmap)
	{
		char name[32];
		sprintf(name, "%d", rand());
		return reinterpret_cast<Texture *>(video().addTexture(
				name,
				reinterpret_cast<irr::video::IImage *>(const_cast<Pixmap *>(pixmap))));
	}

	Texture *loadTexture(const char *filename)
	{
		return reinterpret_cast<Texture *>(video().getTexture(filename));
	}

	void freeTexture(Texture *texture)
	{
		video().removeTexture(reinterpret_cast<irr::video::ITexture *>(texture));
	}

	void clearTextureCache()
	{
		video().removeAllTextures();
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
};
