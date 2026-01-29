#!/bin/sh
cd `dirname $0`

echo "# Creating folders for CMake ..."
mkdir _CMAKE
mkdir _CMAKE/_IRRLICHT
mkdir _CMAKE/_STEEL

echo "# Generating Lua wrapper ..."
swig -lua -c++ -o src/lua_wrapper.cpp steel.i

echo "# Building Irrlicht ..."
cd _CMAKE/_IRRLICHT
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DIRRLICHT_SHARED=OFF ../../lib/irrlicht_svn
make -j8
cd ../..

echo "# Building STEEL ..."
cd _CMAKE/_STEEL
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_RC_FLAGS="-O coff" ../..
make -j8
mv steel ../../_build/steel
cd ../..
