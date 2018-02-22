/// Title (header)
/// (c) 2018 Jani Nykänen

#ifndef __TITLE__
#define __TITLE__

#include "../engine/assets.h"

#include "stdbool.h"

/// Initialize title screen
/// < ass Asset pack
void title_init(ASSET_PACK* ass);

/// Update title screen
/// < tm Time mul.
void title_update(float tm);

/// Draw title screen
void title_draw();

/// Toggle title screen
/// < state State
void title_toggle(bool state);

/// Is title active
/// > True or false
bool title_is_on();

#endif // __TITLE__