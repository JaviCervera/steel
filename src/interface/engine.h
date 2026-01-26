#pragma once

struct CameraManager;
struct EntityManager;
struct FileSystem;
struct FontManager;
struct GraphicsManager;
struct InputManager;
struct LightManager;
struct MaterialManager;
struct ModelManager;
struct PixmapManager;
struct SceneManager;
struct ScreenManager;
struct TextureManager;

struct Engine
{
	virtual ~Engine() {};
	virtual CameraManager &cameraManager() = 0;
	virtual EntityManager &entityManager() = 0;
	virtual FileSystem &fileSystem() = 0;
	virtual FontManager &fontManager() = 0;
	virtual GraphicsManager &graphicsManager() = 0;
	virtual InputManager &inputManager() = 0;
	virtual LightManager &lightManager() = 0;
	virtual MaterialManager &materialManager() = 0;
	virtual ModelManager &modelManager() = 0;
	virtual PixmapManager &pixmapManager() = 0;
	virtual SceneManager &sceneManager() = 0;
	virtual ScreenManager &screenManager() = 0;
	virtual TextureManager &textureManager() = 0;
};
