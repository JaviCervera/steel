#include "../interface/file_system.h"
#include "engine_internal.h"
#include "dir.h"

extern "C"
{
	EXPORT const char *CALL GetDirContents(const char *dir)
	{
		return GetEngine().fileSystem().dirContents(dir);
	}
}
