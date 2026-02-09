/**
 * @file
 * Directory utilities for listing and accessing file system directories.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Gets the contents of a directory as a string,
	 * with each entry separated by a newline character.
	 *
	 * @param dir The path to the directory.
	 * @return A string containing the directory contents.
	 */
	EXPORT const char *CALL GetDirContents(const char *dir);
}
