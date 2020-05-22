#pragma once
#include <string>

/*
 * Register a mod
 */
void RegisterMod(std::string path);

/*
 * Pre Init
 * Called when all mod registered
 * Just before the core of mod has created
 */
void ModPreInit();