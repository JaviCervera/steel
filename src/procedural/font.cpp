#define STB_TRUETYPE_IMPLEMENTATION
#include "../../lib/stb/stb_truetype.h"
#undef STB_TRUETYPE_IMPLEMENTATION
#include "../interface/font_manager.h"
#include "engine_internal.h"
#include "font.h"

extern "C"
{
	EXPORT Font *CALL LoadFont(const char *filename, int height)
	{
		return GetEngine().fontManager().loadFont(filename, height);
	}

	EXPORT void CALL FreeFont(Font *font)
	{
		GetEngine().fontManager().freeFont(font);
	}

	EXPORT int CALL GetTextWidth(Font *font, const char *text)
	{
		return GetEngine().fontManager().textWidth(font, text);
	}

	EXPORT int CALL GetTextHeight(Font *font, const char *text)
	{
		return GetEngine().fontManager().textHeight(font, text);
	}
}
