#include "error.h"
#include "interface/file_system.h"
#include "procedural/color.h"
#include "procedural/drawing.h"
#include "procedural/engine.h"
#include "procedural/engine_internal.h"
#include "procedural/screen.h"
#include "scripting.h"

#define SCRIPT_FILE "main.lua"
#define PACKAGE_FILE "package.dat"

int main(int argc, char *argv[])
{
  InitEngine();
  atexit(FinishEngine);
  OpenScreen(640, 480, FALSE);
  const std::string path = (argc > 1) ? (std::string(argv[1]) + "/") : "";
  if (path != "")
    GetEngine().fileSystem().changeDir(path.c_str());
  GetEngine().fileSystem().addZip(PACKAGE_FILE);
  Scripting vm;
  if (!vm.loadScript(SCRIPT_FILE))
    Error(vm.error().c_str());
  return 0;
}
