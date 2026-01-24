#pragma once

#include "../interface/engine.h"
#include "file_system_irrlicht.h"
#include "graphics_irrlicht.h"
#include "input_irrlicht.h"
#include "pixmap_manager_irrlicht.h"
#include "platform_irrlicht.h"
#include "screen_irrlicht.h"
#include "texture_manager_irrlicht.h"

struct EngineIrrlicht : public Engine
{
	EngineIrrlicht()
			: m_platform(),
				m_fs(m_platform),
				m_graphics(m_platform),
				m_input(m_platform),
				m_pixmap_mgr(m_platform),
				m_screen(m_platform),
				m_tex_mgr(m_platform)
	{
	}

	FileSystem &fileSystem()
	{
		return m_fs;
	}

	Graphics &graphics()
	{
		return m_graphics;
	}

	Input &input()
	{
		return m_input;
	}

	PixmapManager &pixmapManager()
	{
		return m_pixmap_mgr;
	}

	Screen &screen()
	{
		return m_screen;
	}

	TextureManager &textureManager()
	{
		return m_tex_mgr;
	}

private:
	PlatformIrrlicht m_platform;
	FileSystemIrrlicht m_fs;
	GraphicsIrrlicht m_graphics;
	InputIrrlicht m_input;
	PixmapManagerIrrlicht m_pixmap_mgr;
	ScreenIrrlicht m_screen;
	TextureManagerIrrlicht m_tex_mgr;
};
