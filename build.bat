@echo off

set PATH=%~dp0TDM-GCC-32\bin;%PATH%

echo # Creating folders for CMake ...
mkdir _CMAKE\_IRRLICHT
mkdir _CMAKE\_STEEL

echo # Building Irrlicht ...
cd _CMAKE/_IRRLICHT
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DIRRLICHT_SHARED=OFF ../../lib/irrlicht12
mingw32-make -j8
cd ../..

echo # Building STEEL ...
cd _CMAKE/_STEEL
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RC_FLAGS="-O coff" ../..
mingw32-make -j8
move "steel.exe" "..\..\_build\steel.exe"
cd ../..

pause
