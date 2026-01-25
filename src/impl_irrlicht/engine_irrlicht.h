#pragma once

#include "../interface/engine.h"
#include "entity_manager_irrlicht.h"
#include "file_system_irrlicht.h"
#include "font_manager_impl.h"
#include "graphics_manager_irrlicht.h"
#include "input_manager_irrlicht.h"
#include "pixmap_manager_irrlicht.h"
#include "platform_irrlicht.h"
#include "screen_manager_irrlicht.h"
#include "texture_manager_irrlicht.h"

struct EngineIrrlicht : public Engine
{
	EngineIrrlicht()
			: m_platform(),
				m_entity_mgr(m_platform),
				m_fs(m_platform),
				m_graphics_mgr(m_platform),
				m_input_mgr(m_platform),
				m_pixmap_mgr(m_platform),
				m_screen_mgr(m_platform),
				m_tex_mgr(m_platform),
				m_font_mgr(m_graphics_mgr, m_pixmap_mgr, m_tex_mgr, m_fs)
	{
	}

	EntityManager &entityManager()
	{
		return m_entity_mgr;
	}

	FileSystem &fileSystem()
	{
		return m_fs;
	}

	FontManager &fontManager()
	{
		return m_font_mgr;
	}

	GraphicsManager &graphicsManager()
	{
		return m_graphics_mgr;
	}

	InputManager &inputManager()
	{
		return m_input_mgr;
	}

	PixmapManager &pixmapManager()
	{
		return m_pixmap_mgr;
	}

	ScreenManager &screenManager()
	{
		return m_screen_mgr;
	}

	TextureManager &textureManager()
	{
		return m_tex_mgr;
	}

private:
	PlatformIrrlicht m_platform;
	EntityManagerIrrlicht m_entity_mgr;
	FileSystemIrrlicht m_fs;
	GraphicsManagerIrrlicht m_graphics_mgr;
	InputManagerIrrlicht m_input_mgr;
	PixmapManagerIrrlicht m_pixmap_mgr;
	ScreenManagerIrrlicht m_screen_mgr;
	TextureManagerIrrlicht m_tex_mgr;
	FontManagerImpl m_font_mgr;
};
