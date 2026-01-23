#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../interface/file_system.h"
#include "engine_internal.h"
#include "memblock.h"

extern "C"
{
	EXPORT Memblock *CALL CreateMemblock(int size)
	{
		char *memblock = (char *)calloc(1, size + 4);
		((int *)memblock)[0] = (int)size;
		return (Memblock *)((int *)memblock + 1);
	}

	EXPORT Memblock *CALL LoadMemblock(const char *filename)
	{
		const size_t size = GetEngine().fileSystem().fileSize(filename);
		if (size == size_t(-1))
			return NULL;
		Memblock *memblock = CreateMemblock(size);
		GetEngine().fileSystem().readFile(filename, memblock, size);
		return memblock;
	}

	EXPORT void CALL SaveMemblock(Memblock *memblock, const char *filename)
	{
		FILE *f = fopen(filename, "wb");
		if (!f)
			return;
		fwrite(memblock, GetMemblockSize(memblock), 1, f);
		fclose(f);
	}

	EXPORT void CALL FreeMemblock(Memblock *memblock)
	{
		free((int *)memblock - 1);
	}

	EXPORT int CALL GetMemblockSize(const Memblock *memblock)
	{
		return ((const int *)memblock - 1)[0];
	}

	EXPORT void CALL PokeByte(Memblock *memblock, int offset, int val)
	{
		unsigned char b = (unsigned char)val;
		memcpy((char *)memblock + offset, &b, sizeof(unsigned char));
	}

	EXPORT void CALL PokeShort(Memblock *memblock, int offset, int val)
	{
		unsigned short s = (unsigned short)val;
		memcpy((char *)memblock + offset, &s, sizeof(unsigned short));
	}

	EXPORT void CALL PokeInt(Memblock *memblock, int offset, int val)
	{
		memcpy((char *)memblock + offset, &val, sizeof(val));
	}

	EXPORT void CALL PokeFloat(Memblock *memblock, int offset, float val)
	{
		memcpy((char *)memblock + offset, &val, sizeof(val));
	}

	EXPORT void CALL PokeString(Memblock *memblock, int offset, const char *val)
	{
		const int len = (int)strlen(val);
		PokeInt(memblock, offset, len);
		for (int i = 0; i < len; ++i)
		{
			PokeByte(memblock, offset + 4 + i, val[i]);
		}
	}

	EXPORT int CALL PeekByte(const Memblock *memblock, int offset)
	{
		unsigned char val;
		memcpy(&val, (const char *)memblock + offset, sizeof(val));
		return val;
	}

	EXPORT int CALL PeekShort(const Memblock *memblock, int offset)
	{
		unsigned short val;
		memcpy(&val, (const char *)memblock + offset, sizeof(val));
		return val;
	}

	EXPORT int CALL PeekInt(const Memblock *memblock, int offset)
	{
		int val;
		memcpy(&val, (const char *)memblock + offset, sizeof(val));
		return val;
	}

	EXPORT float CALL PeekFloat(const Memblock *memblock, int offset)
	{
		float val;
		memcpy(&val, (const char *)memblock + offset, sizeof(val));
		return val;
	}

	EXPORT const char *CALL PeekString(const Memblock *memblock, int offset)
	{
		static char *result = NULL;
		if (result)
			free(result);
		const int len = PeekInt(memblock, offset);
		result = static_cast<char *>(malloc(len + 1));
		for (int i = 0; i < len; ++i)
		{
			result[i] = static_cast<char>(PeekByte(memblock, offset + 4 + i));
		}
		result[len] = '\0';
		return result;
	}
}
