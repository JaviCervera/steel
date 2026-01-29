#pragma once

#include <irrlicht.h>
#include "../interface/graphics_manager.h"
#include "platform_irrlicht.h"

struct GraphicsManagerIrrlicht : public GraphicsManager
{
	GraphicsManagerIrrlicht(PlatformIrrlicht &platform)
			: m_platform(&platform),
				m_color(255, 255, 255, 255)
	{
	}

	void cls(int color)
	{
		video().setRenderTarget(NULL, true, false, irr::video::SColor(color));
	}

	void color(int color)
	{
		m_color = irr::video::SColor(color);
	}

	void viewport(int x, int y, int width, int height)
	{
		video().setViewPort(irr::core::rect<irr::s32>(x, y, x + width, y + height));
	}

	void plot(float x, float y)
	{
		line(x, y, x, y);
	}

	void line(float x1, float y1, float x2, float y2)
	{
		video().draw2DLine(irr::core::position2di(x1, y1), irr::core::position2di(x2, y2), m_color);
	}

	void rect(float x, float y, float width, float height)
	{
		video().draw2DRectangle(m_color, irr::core::rect<irr::s32>(x, y, x + width, y + height));
	}

	void texture(const Texture *tex, int src_x, int src_y, int src_width, int src_height, int dst_x, int dst_y, int dst_width, int dst_height)
	{
		if (!tex)
			return;
		irr::video::ITexture *itex = reinterpret_cast<irr::video::ITexture *>(const_cast<Texture *>(tex));
		if (src_width == 0)
			src_width = itex->getOriginalSize().Width - src_x;
		if (src_height == 0)
			src_height = itex->getOriginalSize().Height - src_y;
		if (dst_width == 0)
			dst_width = src_width;
		if (dst_height == 0)
			dst_height = src_height;
		irr::video::SColor colors[] = {m_color, m_color, m_color, m_color};
		video().draw2DImage(
				itex,
				irr::core::rect<irr::s32>(dst_x, dst_y, dst_x + dst_width, dst_y + dst_height),
				irr::core::rect<irr::s32>(src_x, src_y, src_x + src_width, src_y + src_height),
				NULL,
				colors,
				true);
	}

private:
	PlatformIrrlicht *m_platform;
	irr::video::SColor m_color;

	irr::video::IVideoDriver &video()
	{
		return *m_platform->device().getVideoDriver();
	}
};
