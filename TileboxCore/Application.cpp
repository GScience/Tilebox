#include "Application.h"
#include "ModLoader.h"

void Application::Launch(LaunchArgs args)
{
	RegisterMod("mods/TileboxMod.dll");

	ModPreInit();
}
