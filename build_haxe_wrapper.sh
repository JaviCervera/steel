#!/bin/sh
cd `dirname $0`

mkdir _build/haxe
swig -xml -xmllite -c++ -o _build/haxe/steel.xml steel.i
haxe --run HaxeWrapperBuilder
rm _build/haxe/steel.xml
