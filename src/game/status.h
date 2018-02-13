/// Status (header)
/// (c) 2018 Jani Nykänen

#ifndef __STATUS__
#define __STATUS__

#include "../engine/assets.h"

/// Initialize status
/// < ass Asset pack
void status_init(ASSET_PACK* ass);

/// Reset status
void status_reset();

/// Update status
/// < tm Time mul.
void status_update(float tm); 

/// Draw status
void status_draw();

/// Add key
void status_add_key();

/// Remove key
void status_remove_key();

/// Get amount of keys
/// > Key count
int status_get_key_count();

/// Set stage name
/// < name New name
void status_set_stage_name(const char* name);

/// Add turn
void status_add_turn();

/// Set turn target
/// < target New target
void status_set_turn_target(int target);

#endif // __STATUS__