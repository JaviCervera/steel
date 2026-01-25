#include <stdlib.h>
#include "error.h"
#include "interface/file_system.h"
#include "procedural/color.h"
#include "procedural/data_file.h"
#include "procedural/drawing.h"
#include "procedural/engine.h"
#include "procedural/engine_internal.h"
#include "procedural/screen.h"
#include "scripting_lua.h"
#include "string.h"

#define SCRIPT_FILE "main.lua"

int main(int argc, char *argv[])
{
	InitEngine();
	atexit(FinishEngine);
	OpenScreen(640, 480, FALSE);
	const std::string path = (argc > 1) ? (std::string(argv[1]) + "/") : "";
	if (path != "")
		GetEngine().fileSystem().changeDir(path.c_str());
	GetEngine().fileSystem().addZip(DATA_FILE);
	ScriptingLua vm;
	if (!vm.load(SCRIPT_FILE))
		Error(vm.error());
	return 0;
}
