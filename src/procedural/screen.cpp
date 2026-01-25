#include "../interface/file_system.h"
#include "../interface/screen_manager.h"
#include "data_file.h"
#include "engine_internal.h"
#include "screen.h"

extern "C"
{
	EXPORT void CALL OpenScreen(int width, int height, bool_t fullscreen)
	{
		GetEngine().screenManager().open(width, height, fullscreen);
		GetEngine().fileSystem().addZip(DATA_FILE);
	}

	EXPORT void CALL CloseScreen()
	{
		GetEngine().screenManager().close();
	}

	EXPORT void CALL SetScreenTitle(const char *title)
	{
		GetEngine().screenManager().title(title);
	}

	EXPORT void CALL SetScreenResizable(bool_t resizable)
	{
		GetEngine().screenManager().resizable(resizable);
	}

	EXPORT void CALL SetScreenFPS(int fps)
	{
		GetEngine().screenManager().fps(fps);
	}

	EXPORT void CALL RefreshScreen()
	{
		GetEngine().screenManager().refresh();
	}

	EXPORT bool_t CALL IsScreenOpened()
	{
		return GetEngine().screenManager().isRunning();
	}

	EXPORT int CALL GetScreenWidth()
	{
		return GetEngine().screenManager().width();
	}

	EXPORT int CALL GetScreenHeight()
	{
		return GetEngine().screenManager().height();
	}

	EXPORT int CALL GetScreenFPS()
	{
		return GetEngine().screenManager().fps();
	}

	EXPORT int CALL GetDesktopWidth()
	{
		return GetEngine().screenManager().desktopWidth();
	}

	EXPORT int CALL GetDesktopHeight()
	{
		return GetEngine().screenManager().desktopHeight();
	}

	EXPORT float CALL GetDelta()
	{
		return GetEngine().screenManager().delta();
	}
}
