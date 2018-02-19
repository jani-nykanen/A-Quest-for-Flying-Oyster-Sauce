/// Game scene (source)
/// (c) 2018 Jani Nykänen

#include "game.h"

#include "../engine/app.h"
#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/controls.h"
#include "../engine/assets.h"
#include "../engine/music.h"
#include "../engine/sample.h"

#include "../vpad.h"
#include "../global.h"
#include "../transition.h"

#include "../stagemenu/stagemenu.h"

#include "stage.h"
#include "objects.h"
#include "status.h"
#include "pause.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

// Theme music
static MUSIC* mTheme;

// Sound effects
static SAMPLE* sPause;
static SAMPLE* sRestart;


// Init game
static int game_init()
{
    ASSET_PACK* ass = get_global_assets();

    // Initialize game components
    obj_init(ass);
    stage_init(ass);
    status_init(ass);
    pause_init(ass);

    // Set stage name
    status_set_stage_name("Test Stage");
    // Set stage turn target
    status_set_turn_target(50);

    // Get assets
    mTheme = (MUSIC*)get_asset(ass,"theme");
    sPause = (SAMPLE*)get_asset(ass,"pause");
    sRestart = (SAMPLE*)get_asset(ass,"restart");

    return 0;
}


// Update game
static void game_update(float tm)
{
    // If transiting, skip
    if(trn_is_active())
        return;

    // If paused, update pause & skip the rest
    if(pause_enabled())
    {
        pause_control(tm);
        return;
    }

    // Update game components
    stage_update(tm);
    obj_update(tm);
    status_update(tm);

    // Reset if the reset button is pressed
    if(vpad_get_button(2) == PRESSED)
    {
        play_sample(sRestart,0.40f);
        trn_set(FADE_IN,BLACK_VERTICAL,2.0f,game_reset);
    }

    // Pause if the pause or escape button is pressed
    if(!status_is_victory() && (vpad_get_button(1) == PRESSED || vpad_get_button(3) == PRESSED) )
    {
        play_sample(sPause,0.30f);
        pause_enable();
    }
}


// Draw game
static void game_draw()
{
    // Draw game components
    stage_draw();
    obj_draw();
    status_draw();
    pause_draw();
}


// Destroy game
static void game_destroy()
{

}


// Scene swapped
static void game_on_swap()
{
    pause_disable();
    game_reset();
}


// Set stage
void game_set_stage(STAGE_INFO info)
{
    // Clear objects
    obj_clear();

    // Set map
    stage_set_main_stage(info.assetName);

    // Set stage name
    status_set_stage_name(info.name);
    // Set stage turn target
    status_set_turn_target(info.turnCount);

    // Create objects
    stage_reset(false);

    // Reset
    game_reset();
}


// Reset game
void game_reset()
{
    // Reset components
    stage_reset(true);
    status_reset(true);
    obj_reset();

    // Reset music
    play_music(mTheme,0.70f,-1);
}


// Swap scene to stage menu
void swap_to_stage_menu()
{
    app_swap_scene("smenu");
}


// Get game scene
SCENE get_game_scene()
{
    // Set scene functions
    SCENE s = (SCENE){game_init,game_update,game_draw,game_destroy,game_on_swap};

    // Set scene name
    set_scene_name(&s,"game");

    return s;
}
