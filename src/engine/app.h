/// Application core (header)
/// (c) 2018 Jani Nykänen

#ifndef __APPLICATION__
#define __APPLICATION__

#include "SDL2/SDL.h"
#include "scene.h"
#include "config.h"

/// Toggle fullscreen mode
void app_toggle_fullscreen();

/// Swap scene
/// < name The name of the new scene
void app_swap_scene(const char* name);

/// Terminate application
void app_terminate();

/// Run application
/// < arrScenes An array of scenes
/// < count Amount of elements in the array
/// < c Configuration data
/// > An error code, 0 on success, 1 on error
int app_run(SCENE* arrScenes, int count, CONFIG c);

/// Ask if the user wants to quit
/// > 1 if yes, 0 otherwise
int ask_to_quit();

#endif // __APPLICATION__