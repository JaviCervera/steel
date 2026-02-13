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
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#define SCRIPT_FILE "main.lua"

#ifdef _MSC_VER
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
#else
int main(int argc, char *argv[])
#endif
{
	InitEngine();
	atexit(FinishEngine);
#ifdef _MSC_VER
	LPSTR cmdline = GetCommandLineA();
	LPSTR program_name = strtok(cmdline, " ");
	LPSTR script = strtok(NULL, "");
	std::string path = script ? (std::string(script) + "/") : "";
	path.trim();
#else
	const std::string path = (argc > 1) ? (std::string(argv[1]) + "/") : "";
#endif
	if (path != "")
		GetEngine().fileSystem().changeDir(path.c_str());
	GetEngine().fileSystem().addZip(DATA_FILE);
	ScriptingLua vm;
	if (!vm.load(SCRIPT_FILE))
		Error(vm.error());
	return 0;
}
