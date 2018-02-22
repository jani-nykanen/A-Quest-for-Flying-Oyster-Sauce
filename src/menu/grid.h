/// Grid (header)
/// (c) 2018 Jani Nykänen

#ifndef __GRID__
#define __GRID__

#include "../engine/assets.h"

/// Initialize grid
void grid_init(ASSET_PACK* ass);

/// Update grid
/// < tm Time mul.
void grid_update(float tm);

/// Draw grid
void grid_draw();

#endif // __GRID__