# ![steel](logo.png) STEEL Game Engine

A retro 3D game engine using C++, Lua, Irrlicht and OpenAL.

The engine runs on Windows (any version from 98 up), Linux and macOS.

![steel](logo/logo_small.png)

## Generating documentation

```shell
rmdir doc_out
doxygen
python gen_doc.py
```

## TODO

* Use SoLoud instead of OpenAL.
* Add SetMaterialTrackVertexColorsEnabled and IsMaterialTrackVertexColorsEnabled.
* Add GUI functions.
* Split documentation in multiple files.
* Manually generate Lua wrapper based on Swig's XML export.
* Generate macOS bundle.
* Emscripten build.
* Joystick support.
* Shadows.
* Terrain.
* Water.
