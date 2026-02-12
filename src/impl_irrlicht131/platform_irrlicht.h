#pragma once

#include <irrlicht.h>
#include "../interface/color.h"
#include "../interface/input_codes.h"

struct IrrlichtEventReceiver : public irr::IEventReceiver
{
	bool OnEvent(irr::SEvent event)
	{
		switch (event.EventType)
		{
		case irr::EET_KEY_INPUT_EVENT:
			pressKey(event.KeyInput.Key, event.KeyInput.PressedDown);
			break;
		case irr::EET_MOUSE_INPUT_EVENT:
			switch (event.MouseInput.Event)
			{
			case irr::EMIE_MOUSE_MOVED:
				m_mouse_speed = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y) - m_mouse_last_pos;
				m_mouse_last_pos = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y);
				break;
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				pressMouseButton(MOUSE_LEFT, true);
				break;
			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				pressMouseButton(MOUSE_RIGHT, true);
				break;
			case irr::EMIE_MMOUSE_PRESSED_DOWN:
				pressMouseButton(MOUSE_MIDDLE, true);
				break;
			case irr::EMIE_LMOUSE_LEFT_UP:
				pressMouseButton(MOUSE_LEFT, false);
				break;
			case irr::EMIE_RMOUSE_LEFT_UP:
				pressMouseButton(MOUSE_RIGHT, false);
				break;
			case irr::EMIE_MMOUSE_LEFT_UP:
				pressMouseButton(MOUSE_MIDDLE, false);
				break;
			case irr::EMIE_MOUSE_WHEEL:
				m_mouse_wheel += event.MouseInput.Wheel;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		return false;
	}

	void clearInputs()
	{
		memset(m_key_hit, false, irr::KEY_KEY_CODES_COUNT * sizeof(bool));
		memset(m_mouse_button_hit, false, 3 * sizeof(bool));
	}

	bool m_key_down[irr::KEY_KEY_CODES_COUNT];
	bool m_key_hit[irr::KEY_KEY_CODES_COUNT];
	bool m_key_was_hit[irr::KEY_KEY_CODES_COUNT];
	bool m_mouse_button_down[3];
	bool m_mouse_button_hit[3];
	bool m_mouse_button_was_hit[3];
	int m_mouse_wheel;
	irr::core::position2di m_mouse_speed;
	irr::core::position2di m_mouse_last_pos;

private:
	void pressKey(int key, bool pressed)
	{
		if (pressed & !m_key_was_hit[key])
			m_key_hit[key] = pressed;
		m_key_was_hit[key] = pressed;
		m_key_down[key] = pressed;
	}

	void pressMouseButton(int button, bool pressed)
	{
		if (pressed & !m_mouse_button_was_hit[button])
			m_mouse_button_hit[button] = pressed;
		m_mouse_button_was_hit[button] = pressed;
		m_mouse_button_down[button] = pressed;
	}
};

struct PlatformIrrlicht
{
	PlatformIrrlicht()
			: m_event_receiver(),
				m_device(NULL),
				m_running(false),
				m_last_msecs(0),
				m_frame_msecs(0),
				m_delta(0) {}

	~PlatformIrrlicht()
	{
		closeScreen();
	}

	void openScreen(int width, int height, bool fullscreen)
	{
		closeScreen();

		m_device = irr::createDevice(
				irr::video::EDT_OPENGL,
				irr::core::dimension2d<irr::s32>(width, height),
				desktopDepth(),
				fullscreen,
				false,
				false,
				&m_event_receiver);
		if (m_device)
		{
			m_device->getVideoDriver()->beginScene(false, true, irr::video::SColor());
			m_running = true;
			m_last_msecs = m_device->getTimer()->getRealTime();
			m_delta = 0;
		}
	}

	void closeScreen()
	{
		if (m_device)
		{
			m_device->getVideoDriver()->endScene();
			m_device->closeDevice();
			m_device->run();
			m_device->drop();
			m_device = NULL;
			m_running = false;
		}
	}

	void screenTitle(const char *title)
	{
		if (m_device)
			m_device->setWindowCaption(irr::core::stringw(title).c_str());
	}

	void screenResizable(bool resizable)
	{
		if (m_device)
			m_device->setResizeAble(resizable);
	}

	void screenFPS(int fps)
	{
		if (m_device)
			m_frame_msecs = (fps > 0) ? (1000 / fps) : 0;
	}

	void refreshScreen()
	{
		if (m_device)
		{
			m_device->getVideoDriver()->endScene();
			m_event_receiver.clearInputs();
			m_running = m_device->run() && m_device->getVideoDriver() != NULL;
			if (!m_running)
				return;
			const int wait = m_frame_msecs - (m_device->getTimer()->getRealTime() - m_last_msecs);
			if (wait > 0)
				m_device->sleep(wait);
			const int msecs = m_device->getTimer()->getRealTime();
			m_delta = (msecs - m_last_msecs) / 1000.0f;
			m_last_msecs = msecs;
			m_device->getVideoDriver()->beginScene(false, true, irr::video::SColor());
		}
	}

	bool isRunning() const
	{
		return m_running;
	}

	int screenWidth() const
	{
		return m_device ? m_device->getVideoDriver()->getScreenSize().Width : 0;
	}

	int screenHeight() const
	{
		return m_device ? m_device->getVideoDriver()->getScreenSize().Height : 0;
	}

	int screenFPS() const
	{
		return m_device ? m_device->getVideoDriver()->getFPS() : 0;
	}

	int desktopWidth() const
	{
		return m_device ? m_device->getVideoModeList()->getDesktopResolution().Width : 0;
	}

	int desktopHeight() const
	{
		return m_device ? m_device->getVideoModeList()->getDesktopResolution().Height : 0;
	}

	float delta() const
	{
		return m_delta;
	}

	void setMouseVisible(bool visible)
	{
		if (m_device)
			m_device->getCursorControl()->setVisible(visible);
	}

	void setMousePosition(int x, int y)
	{
		if (m_device)
			m_device->getCursorControl()->setPosition(x, y);
	}

	int getMouseX() const
	{
		return m_device ? m_device->getCursorControl()->getPosition().X : 0;
	}

	int getMouseY() const
	{
		return m_device ? m_device->getCursorControl()->getPosition().Y : 0;
	}

	int getMouseZ() const
	{
		return m_event_receiver.m_mouse_wheel;
	}

	bool isMouseButtonDown(int button) const
	{
		return m_event_receiver.m_mouse_button_down[button];
	}

	bool isMouseButtonHit(int button) const
	{
		return m_event_receiver.m_mouse_button_hit[button];
	}

	bool isKeyDown(int key) const
	{
		return m_event_receiver.m_key_down[key];
	}

	bool isKeyHit(int key) const
	{
		return m_event_receiver.m_key_hit[key];
	}

	irr::IrrlichtDevice &device()
	{
		if (!m_device)
			openScreen(640, 480, false);
		return *m_device;
	}

	irr::video::ECOLOR_FORMAT colorFormat()
	{
		return m_device->getVideoDriver()->getTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT)
							 ? irr::video::ECF_A8R8G8B8
							 : irr::video::ECF_A1R5G5B5;
	}

private:
	IrrlichtEventReceiver m_event_receiver;
	irr::IrrlichtDevice *m_device;
	bool m_running;
	int m_last_msecs;
	int m_frame_msecs;
	float m_delta;

	static int desktopDepth()
	{
		irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_NULL);
		const int depth = device->getVideoModeList()->getDesktopDepth();
		device->drop();
		return depth;
	}
};
