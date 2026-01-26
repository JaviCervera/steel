#pragma once

#include "../interface/scene_manager.h"
#include "platform_irrlicht.h"

struct SceneManagerIrrlicht : public SceneManager
{
	SceneManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform), m_coords()
	{
		scene().setAmbientLight(irr::video::SColor(COLOR_WHITE));
	}

	void drawScene(const Camera *camera)
	{
		irr::scene::ICameraSceneNode *irrcam =
				reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera));

		// Set look point
		irr::core::vector3df dest(0, 0, 100);
		irr::core::matrix4 matrix = irrcam->getAbsoluteTransformation();
		matrix.transformVect(dest);
		irrcam->setTarget(dest);

		// Draw
		scene().setActiveCamera(irrcam);
		scene().drawAll();
	}

	void screenCoords(const Camera *camera, float x, float y, float z)
	{
		const irr::core::position2di result = scene().getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(
				irr::core::vector3df(x, y, z),
				reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera)));
		m_coords = irr::core::vector3df(result.X, result.Y, 0);
	}

	void sceneCoords(const Camera *camera, float x, float y, float depth)
	{
		const irr::core::line3df line = scene().getSceneCollisionManager()->getRayFromScreenCoordinates(
				irr::core::position2di(x, y),
				reinterpret_cast<irr::scene::ICameraSceneNode *>(const_cast<Camera *>(camera)));
		m_coords = irr::core::vector3df(
				irr::core::lerp(line.start.X, line.end.X, depth),
				irr::core::lerp(line.start.Y, line.end.Y, depth),
				irr::core::lerp(line.start.Z, line.end.Z, depth));
	}

	float coordX()
	{
		return m_coords.X;
	}

	float coordY()
	{
		return m_coords.Y;
	}

	float coordZ()
	{
		return m_coords.Z;
	}

private:
	PlatformIrrlicht *m_platform;
	irr::core::vector3df m_coords;

	irr::scene::ISceneManager &scene()
	{
		return *m_platform->device().getSceneManager();
	}

	irr::video::IVideoDriver &video()
	{
		return *m_platform->device().getVideoDriver();
	}
};
