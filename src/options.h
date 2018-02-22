/// Options scene (header)
/// (c) 2018 Jani Nykänen

#ifndef __OPTIONS__
#define __OPTIONS__

#include "engine/scene.h"

/// Get options scene
/// > Options scene
SCENE get_options_scene();

/// Save settings
/// < path File path
void save_settings(const char* path);

/// Read settings
/// < path File path
void read_settings(const char* path);

#endif // __OPTIONS__