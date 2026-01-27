#pragma once

#include "../interface/engine.h"
#include "anim_model_manager_irrlicht.h"
#include "audio_manager_soloud.h"
#include "camera_manager_irrlicht.h"
#include "collision_manager_irrlicht.h"
#include "entity_manager_irrlicht.h"
#include "file_system_irrlicht.h"
#include "font_manager_impl.h"
#include "graphics_manager_irrlicht.h"
#include "input_manager_irrlicht.h"
#include "light_manager_irrlicht.h"
#include "material_manager_irrlicht.h"
#include "model_manager_irrlicht.h"
#include "pixmap_manager_irrlicht.h"
#include "platform_irrlicht.h"
#include "scene_manager_irrlicht.h"
#include "screen_manager_irrlicht.h"
#include "sprite_manager_irrlicht.h"
#include "texture_manager_irrlicht.h"

struct EngineIrrlicht : public Engine
{
	EngineIrrlicht()
			: m_platform(),
				m_anim_model_mgr(m_platform),
				m_camera_mgr(m_platform),
				m_collision_mgr(m_platform),
				m_entity_mgr(m_platform, m_collision_mgr),
				m_fs(m_platform),
				m_audio_mgr(m_fs),
				m_graphics_mgr(m_platform),
				m_input_mgr(m_platform),
				m_light_mgr(m_platform),
				m_material_mgr(),
				m_model_mgr(m_platform),
				m_pixmap_mgr(m_platform),
				m_scene_mgr(m_platform),
				m_screen_mgr(m_platform),
				m_sprite_mgr(m_platform),
				m_tex_mgr(m_platform),
				m_font_mgr(m_graphics_mgr, m_pixmap_mgr, m_tex_mgr, m_fs)
	{
		m_collision_mgr.entityManager(m_entity_mgr);
	}

	AnimModelManager &animModelManager()
	{
		return m_anim_model_mgr;
	}

	AudioManager &audioManager()
	{
		return m_audio_mgr;
	}

	CameraManager &cameraManager()
	{
		return m_camera_mgr;
	}

	CollisionManager &collisionManager()
	{
		return m_collision_mgr;
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

	LightManager &lightManager()
	{
		return m_light_mgr;
	}

	MaterialManager &materialManager()
	{
		return m_material_mgr;
	}

	ModelManager &modelManager()
	{
		return m_model_mgr;
	}

	PixmapManager &pixmapManager()
	{
		return m_pixmap_mgr;
	}

	SceneManager &sceneManager()
	{
		return m_scene_mgr;
	}

	ScreenManager &screenManager()
	{
		return m_screen_mgr;
	}

	SpriteManager &spriteManager()
	{
		return m_sprite_mgr;
	}

	TextureManager &textureManager()
	{
		return m_tex_mgr;
	}

private:
	PlatformIrrlicht m_platform;
	AnimModelManagerIrrlicht m_anim_model_mgr;
	CameraManagerIrrlicht m_camera_mgr;
	CollisionManagerIrrlicht m_collision_mgr;
	EntityManagerIrrlicht m_entity_mgr;
	FileSystemIrrlicht m_fs;
	AudioManagerSoLoud m_audio_mgr;
	GraphicsManagerIrrlicht m_graphics_mgr;
	InputManagerIrrlicht m_input_mgr;
	LightManagerIrrlicht m_light_mgr;
	MaterialManagerIrrlicht m_material_mgr;
	ModelManagerIrrlicht m_model_mgr;
	PixmapManagerIrrlicht m_pixmap_mgr;
	SceneManagerIrrlicht m_scene_mgr;
	ScreenManagerIrrlicht m_screen_mgr;
	SpriteManagerIrrlicht m_sprite_mgr;
	TextureManagerIrrlicht m_tex_mgr;
	FontManagerImpl m_font_mgr;
};
