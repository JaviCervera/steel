#pragma once

#include "../interface/screen_manager.h"
#include "platform_irrlicht.h"

struct ScreenManagerIrrlicht : public ScreenManager
{
	ScreenManagerIrrlicht(PlatformIrrlicht &platform) : m_platform(&platform) {}

	void open(int width, int height, bool fullscreen)
	{
		m_platform->openScreen(width, height, fullscreen);
	}

	void close()
	{
		m_platform->closeScreen();
	}

	void title(const char *title)
	{
		m_platform->screenTitle(title);
	}

	void resizable(bool resizable)
	{
		m_platform->screenResizable(resizable);
	}

	void fps(int fps)
	{
		m_platform->screenFPS(fps);
	}

	void refresh()
	{
		m_platform->refreshScreen();
	}

	bool isRunning() const
	{
		return m_platform->isRunning();
	}

	int width() const
	{
		return m_platform->screenWidth();
	}

	int height() const
	{
		return m_platform->screenHeight();
	}

	int fps() const
	{
		return m_platform->screenFPS();
	}

	int desktopWidth() const
	{
		return m_platform->desktopWidth();
	}

	int desktopHeight() const
	{
		return m_platform->desktopHeight();
	}

	float delta() const
	{
		return m_platform->delta();
	}

private:
	PlatformIrrlicht *m_platform;
};
