/// Status (header)
/// (c) 2018 Jani Nykänen

#ifndef __STATUS__
#define __STATUS__

#include "../engine/assets.h"

#include "stdbool.h"

/// Initialize status
/// < ass Asset pack
void status_init(ASSET_PACK* ass);

/// Reset status
/// < soft Is a soft reset
void status_reset(bool soft);

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

/// Activate victory
void status_activate_victory();

/// Is the stage won
bool status_is_victory();

#endif // __STATUS__