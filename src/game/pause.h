/// Pause (header)
/// (c) 2018 Jani Nykänen

#ifndef __PAUSE__
#define __PAUSE__

#include "../engine/assets.h"

#include "stdbool.h"

/// Initialize pause
/// < ass Asset pack
void pause_init(ASSET_PACK* ass);

/// Control pause screen
/// < tm Time mul.
void pause_control(float tm);

/// Draw pause screen
void pause_draw();

/// Get if the pause screen is enabled
/// > True or false
bool pause_enabled();

/// Enable pause
void pause_enable();

/// Disable pause
void pause_disable();

#endif // __PAUSE__