@echo off

set PATH=%~dp0TDM-GCC-32\bin;%PATH%

echo # Creating folders for CMake ...
mkdir _CMAKE\_IRRLICHT
mkdir _CMAKE\_STEEL

echo # Generating Lua wrapper ...
swig -lua -c++ -o src/lua_wrapper.cpp steel.i
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

echo # Building Irrlicht ...
cd _CMAKE/_IRRLICHT
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DIRRLICHT_SHARED=OFF ../../lib/irrlicht131
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
mingw32-make -j8
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
cd ../..

echo # Building runtime ...
cd _CMAKE/_STEEL
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_RC_FLAGS="-O coff" ../..
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
mingw32-make -j8
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
move "steel.exe" "..\..\_build\runtime.win32.exe"
cd ../..

echo # Building compiler ...
MonkeyXPro85e\bin\transcc_winnt -target=C++_Tool -config=Release compiler/steel.monkey
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
move compiler/steel.buildv85e\cpptool\main_winnt.exe _build/steel.exe
echo.
