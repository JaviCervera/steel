# ![steel](logo.png) STEEL Game Engine

A retro 3D game engine using C++, Lua, Irrlicht and OpenAL.

A Windows 95 version is available using an old version of Irrlicht
(and with some extra bugs).

![steel](logo/logo_small.png)

## Generating documentation

```shell
rmdir doc_out
doxygen
python gen_doc.py
```

## TODO

* Split documentation in multiple files.
* Generate macOS bundle.
* Emscripten build.
* Fix Irrlicht 1.3.1 collisions.
* Joystick support.
* Shadows.
* Terrain.
* Water.
