/// Game scene (header)
/// (c) 2018 Jani Nykänen

#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "../engine/scene.h"

#include "../menu/info.h"

/// Set game stage
/// < info Stage info
void game_set_stage(STAGE_INFO info);

/// Reset game
void game_reset();

/// Swap game scene to the stage menu
void swap_to_stage_menu();

/// Get game scene
/// > Game scene
SCENE get_game_scene();

#endif // __GAME_SCENE__
