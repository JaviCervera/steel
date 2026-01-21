#pragma once

typedef void Memblock;

extern "C"
{
  Memblock *CreateMemblock(int size);
  Memblock *LoadMemblock(const char *filename);
  void SaveMemblock(Memblock *memblock, const char *filename);
  void FreeMemblock(Memblock *memblock);
  int MemblockSize(const Memblock *memblock);
  void PokeByte(Memblock *memblock, int offset, int val);
  void PokeShort(Memblock *memblock, int offset, int val);
  void PokeInt(Memblock *memblock, int offset, int val);
  void PokeFloat(Memblock *memblock, int offset, float val);
  void PokeString(Memblock *memblock, int offset, const char *val);
  int PeekByte(const Memblock *memblock, int offset);
  int PeekShort(const Memblock *memblock, int offset);
  int PeekInt(const Memblock *memblock, int offset);
  float PeekFloat(const Memblock *memblock, int offset);
  const char *PeekString(const Memblock *memblock, int offset);
}
