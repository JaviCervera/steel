#pragma once

#include "../interface/input.h"
#include "platform_irrlicht.h"

struct InputIrrlicht : public Input
{
	InputIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform) {}

	void setMouseVisible(bool visible)
	{
		m_platform->setMouseVisible(visible);
	}

	void setMousePosition(int x, int y)
	{
		m_platform->setMousePosition(x, y);
	}

	int getMouseX() const
	{
		return m_platform->getMouseX();
	}

	int getMouseY() const
	{
		return m_platform->getMouseY();
	}

	int getMouseZ() const
	{
		return m_platform->getMouseZ();
	}

	bool isMouseButtonDown(int button) const
	{
		return m_platform->isMouseButtonDown(button);
	}

	bool isMouseButtonHit(int button) const
	{
		return m_platform->isMouseButtonHit(button);
	}

	bool isKeyDown(int key) const
	{
		return m_platform->isKeyDown(key);
	}

	bool isKeyHit(int key) const
	{
		return m_platform->isKeyHit(key);
	}

private:
	PlatformIrrlicht *m_platform;
};
