#pragma once

#include <math.h>
#include <string.h>
#include "../../lib/stb/stb_truetype.h"
#include "../interface/color.h"
#include "../interface/file_system.h"
#include "../interface/font_manager.h"
#include "../interface/graphics_manager.h"
#include "../interface/pixmap_manager.h"
#include "../interface/texture_manager.h"

#define _min(A, B) ((A <= B) ? A : B)
#define _max(A, B) ((A >= B) ? A : B)

struct Font
{
	Texture *tex;
	stbtt_bakedchar glyphs[94]; // ASCII 32..126
	float height;
	float max_height;

	Font(float height)
			: tex(NULL),
				height(height),
				max_height(0)
	{
	}
};

struct FontManagerImpl : public FontManager
{
	FontManagerImpl(GraphicsManager &graphics, PixmapManager &pixmap_mgr, TextureManager &texture_mgr, FileSystem &fs)
			: m_graphics_mgr(&graphics),
				m_pixmap_mgr(&pixmap_mgr),
				m_texture_mgr(&texture_mgr),
				m_fs(&fs)
	{
	}

	Font *loadFont(const char *filename, int height)
	{
		const size_t size = m_fs->fileSize(filename);
		if (size == size_t(-1))
			return NULL;

		Font *font = new Font(height);

		// Load font file
		unsigned char *ttf = new unsigned char[size];
		m_fs->readFile(filename, ttf, size);

		// Bake font into alpha buffer
		int w = 256, h = 256;
		unsigned char *alpha_buffer = new unsigned char[w * h];
		while (stbtt_BakeFontBitmap(
							 ttf,
							 0,
							 height,
							 alpha_buffer,
							 w,
							 h,
							 32,
							 sizeof(font->glyphs) / sizeof(font->glyphs[0]),
							 font->glyphs) <= 0)
		{
			if (w == h)
				w *= 2;
			else
				h *= 2;
			delete[] alpha_buffer;
			alpha_buffer = new unsigned char[w * h];
		}
		delete[] ttf;

		// Copy into pixmap
		Pixmap *pixmap = m_pixmap_mgr->createPixmap(w, h);
		for (int py = 0; py < h; ++py)
		{
			for (int px = 0; px < w; ++px)
			{
				m_pixmap_mgr->writePixel(pixmap, px, py, Color::fade(COLOR_WHITE, alpha_buffer[py * w + px]));
			}
		}
		delete[] alpha_buffer;

		// Create texture
		font->tex = m_texture_mgr->createTexture(pixmap);
		m_pixmap_mgr->freePixmap(pixmap);

		// Get max char height
		float x = 0, y = 0;
		float miny = 999999, maxy = -999999;
		stbtt_aligned_quad q;
		font->max_height = -999999;
		const size_t len = sizeof(font->glyphs) / sizeof(font->glyphs[0]);
		for (size_t i = 0; i < len; ++i)
		{
			stbtt_GetBakedQuad(
					font->glyphs,
					m_texture_mgr->textureWidth(font->tex),
					m_texture_mgr->textureHeight(font->tex),
					i,
					&x,
					&y,
					&q,
					true);
			miny = _min(miny, q.y0);
			maxy = _max(maxy, q.y1);
		}
		font->max_height = maxy - miny;

		return font;
	}

	void freeFont(Font *font)
	{
		m_texture_mgr->freeTexture(font->tex);
		delete font;
	}

	void drawText(const Font *font, const char *text, float x, float y)
	{
		if (!font || !text)
			return;
		float fx = x;
		float fy = y + font->max_height;
		for (size_t i = 0; text[i]; ++i)
		{
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(
					font->glyphs,
					m_texture_mgr->textureWidth(font->tex),
					m_texture_mgr->textureHeight(font->tex),
					int(_min(text[i] - 32, 94)),
					&fx,
					&fy,
					&q,
					true);
			const float src_x = q.s0 * m_texture_mgr->textureWidth(font->tex);
			const float src_y = q.t0 * m_texture_mgr->textureHeight(font->tex);
			const float src_width = (q.s1 - q.s0) * m_texture_mgr->textureWidth(font->tex);
			const float src_height = (q.t1 - q.t0) * m_texture_mgr->textureHeight(font->tex);
			if (src_width > 0 && src_height > 0)
				m_graphics_mgr->texture(font->tex, src_x, src_y, src_width, src_height, q.x0, q.y0, q.x1 - q.x0, q.y1 - q.y0);
		}
	}

	int textWidth(const Font *font, const char *text)
	{
		if (!font || !text)
			return 0;
		float x = 0, y = 0;
		stbtt_aligned_quad q = {0};
		for (size_t i = 0; text[i]; ++i)
		{
			stbtt_GetBakedQuad(
					font->glyphs,
					m_texture_mgr->textureWidth(font->tex),
					m_texture_mgr->textureHeight(font->tex),
					int(_min(text[i] - 32, 94)),
					&x,
					&y,
					&q,
					true);
		}
		return q.x1;
	}

	int textHeight(const Font *font, const char *text)
	{
		if (!font)
			return 0;
		float x = 0, y = 0, miny = 999999, maxy = -999999;
		stbtt_aligned_quad q = {0};
		for (size_t i = 0; text[i]; ++i)
		{
			stbtt_GetBakedQuad(
					font->glyphs,
					m_texture_mgr->textureWidth(font->tex),
					m_texture_mgr->textureHeight(font->tex),
					int(_min(text[i] - 32, 94)),
					&x,
					&y,
					&q,
					true);
			miny = _min(miny, q.y0);
			maxy = _max(maxy, q.y1);
		}
		return maxy - miny;
	}

private:
	GraphicsManager *m_graphics_mgr;
	PixmapManager *m_pixmap_mgr;
	TextureManager *m_texture_mgr;
	FileSystem *m_fs;
};
