/**
 * @file
 * Memory blocks for binary data handling, loading, and saving.
 * Memblocks support reading and writing various data types at specified offsets.
 */
#pragma once

typedef void Memblock;

extern "C"
{
	/**
	 * Creates a new memory block of specified size.
	 *
	 * @param size The size of the memory block in bytes.
	 * @return A new memblock.
	 */
	EXPORT Memblock *CALL CreateMemblock(int size);

	/**
	 * Loads a memory block from a file.
	 *
	 * @param filename The path to the file to load.
	 * @return A new memblock, or NULL if loading fails.
	 */
	EXPORT Memblock *CALL LoadMemblock(const char *filename);

	/**
	 * Saves a memory block to a file.
	 *
	 * @param memblock The memblock to save.
	 * @param filename The path to save to.
	 */
	EXPORT void CALL SaveMemblock(Memblock *memblock, const char *filename);

	/**
	 * Frees a memory block and releases its resources.
	 *
	 * @param memblock The memblock to free.
	 */
	EXPORT void CALL FreeMemblock(Memblock *memblock);

	/**
	 * Gets the size of a memory block in bytes.
	 *
	 * @param memblock The memblock.
	 * @return The size in bytes.
	 */
	EXPORT int CALL GetMemblockSize(const Memblock *memblock);

	/**
	 * Writes a byte value to a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @param val The value to write.
	 */
	EXPORT void CALL PokeByte(Memblock *memblock, int offset, int val);

	/**
	 * Writes a short (2-byte) value to a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @param val The value to write.
	 */
	EXPORT void CALL PokeShort(Memblock *memblock, int offset, int val);

	/**
	 * Writes an integer (4-byte) value to a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @param val The value to write.
	 */
	EXPORT void CALL PokeInt(Memblock *memblock, int offset, int val);

	/**
	 * Writes a float (4-byte) value to a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @param val The value to write.
	 */
	EXPORT void CALL PokeFloat(Memblock *memblock, int offset, float val);

	/**
	 * Writes a string to a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @param val The string to write.
	 */
	EXPORT void CALL PokeString(Memblock *memblock, int offset, const char *val);

	/**
	 * Reads a byte value from a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @return The byte value.
	 */
	EXPORT int CALL PeekByte(const Memblock *memblock, int offset);

	/**
	 * Reads a short (2-byte) value from a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @return The short value.
	 */
	EXPORT int CALL PeekShort(const Memblock *memblock, int offset);

	/**
	 * Reads an integer (4-byte) value from a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @return The integer value.
	 */
	EXPORT int CALL PeekInt(const Memblock *memblock, int offset);

	/**
	 * Reads a float (4-byte) value from a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @return The float value.
	 */
	EXPORT float CALL PeekFloat(const Memblock *memblock, int offset);

	/**
	 * Reads a string from a memory block at the specified offset.
	 *
	 * @param memblock The memblock.
	 * @param offset The byte offset.
	 * @return The string value.
	 */
	EXPORT const char *CALL PeekString(const Memblock *memblock, int offset);
}
