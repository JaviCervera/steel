#pragma once

struct Scripting
{
	virtual bool load(const char *filename) = 0;
	virtual const char *error() const = 0;
};
