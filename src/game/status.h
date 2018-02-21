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

/// Get the start type
/// > 0, if golden, 1, if bronze
int status_star_type();

/// Set if the stage is the final stage
/// < state State
void status_set_if_final(bool state);

/// Get if the stage is the final stage
/// > True or false
bool status_get_if_final();

/// Set stage index
/// < index Index
void status_set_stage_index(int index);

#endif // __STATUS__