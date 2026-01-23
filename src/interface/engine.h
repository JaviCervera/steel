#pragma once

struct FileSystem;
struct Graphics;
struct Input;
struct Screen;
struct TextureManager;

struct Engine
{
	virtual ~Engine() {};
	virtual FileSystem &fileSystem() = 0;
	virtual Graphics &graphics() = 0;
	virtual Input &input() = 0;
	virtual Screen &screen() = 0;
	virtual TextureManager &textureManager() = 0;
};
