/**
 * @file
 * Engine initialization and shutdown functionality.
 * These functions must be called to set up and clean up the engine's internal systems.
 */
#pragma once

#include "common.h"

extern "C"
{
	/**
	 * Initializes the engine and all its subsystems.
	 * This must be called before using any other engine functions.
	 */
	EXPORT void CALL InitEngine();

	/**
	 * Shuts down the engine and releases all resources.
	 * This should be called at the end of the program.
	 */
	EXPORT void CALL FinishEngine();
}
