/// Stage (header)
/// (c) 2018 Jani Nykänen

#ifndef __STAGE__
#define __STAGE__

#include "../engine/assets.h"
#include "../engine/vector.h"

#include "stdbool.h"

/// Reset stage
/// < soft Is a soft reset
void stage_reset(bool soft);

/// Initialize stage
/// < ass Asset pack
void stage_init(ASSET_PACK* ass);

/// Update stage
/// < tm Time mul.
void stage_update(float tm);

/// Draw stage
void stage_draw();

/// Get collision map
/// > Collision map
int* stage_get_collision_map();

/// Get current map dimensions
/// > Dimensions
POINT stage_get_map_size();

/// Is the tile in x,y solid
/// < x X coordinate
/// < y Y coordinate
/// > True or false
bool stage_is_solid(int x, int y);

/// Is the tile in x,y vine
/// < x X coordinate
/// < y Y coordinate
/// > True or false
bool stage_is_vine(int x, int y);

/// Set collision tile value
/// < x X coordinate
/// < y Y coordinate
/// < id Tile ID
void stage_set_collision_tile(int x, int y, int id);

/// Set tile value
/// < x X coordinate
/// < y Y coordinate
/// < id Tile ID
void stage_set_tile(int x, int y, int id);

/// Is the tile in x,y lava
/// < x X coordinate
/// < y Y coordinate
/// > True or false
bool stage_is_lava(int x, int y);

/// Is the tile harmful
/// < x X coordinate
/// < y Y coordinate
/// > True or false
int stage_is_harmful(int x, int y);

/// Set shake timer
/// < s Shake value
void stage_set_shake_timer(float s);

/// Set main stage
/// < name Stage asset name
void stage_set_main_stage(const char* name);

/// Toggle purple blocks
void stage_toggle_purple_blocks();

#endif // __STAGE__