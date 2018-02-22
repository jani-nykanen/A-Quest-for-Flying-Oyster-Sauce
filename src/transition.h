/// Screen transition (header)
/// (c) 2018 Jani Nykänen

#ifndef __TRANSITION__
#define __TRANSITION__

#include "engine/assets.h"

#include "stdbool.h"

/// Fade directions
enum
{
    FADE_OUT = 0,
    FADE_IN = 1,
};

/// Transition types
enum
{
    BLACK_VERTICAL = 0,
    BLACK_CIRCLE = 1,
};

/// Initialize transition
/// < ass Assets
void trn_init(ASSET_PACK* ass);

/// Set transition
/// < fading In or out
/// < type Transition type
/// < speed Transition speed (1.0 by default)
/// < cb Callback
void trn_set(int fading, int type, float speed, void (*cb)(void));

/// Update transition
/// < tm Time multiplier
void trn_update(float tm);

/// Draw transition
void trn_draw();

/// Is a screen transition happening
bool trn_is_active();

#endif // __TRANSITION__