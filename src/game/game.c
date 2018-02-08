/// Game scene (source)
/// (c) 2018 Jani Nykänen

#include "game.h"

#include "../engine/app.h"
#include "../engine/graphics.h"
#include "../engine/bitmap.h"
#include "../engine/controls.h"
#include "../engine/assets.h"

#include "../vpad.h"
#include "../global.h"

#include "stage.h"
#include "objects.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

// Bitmap font
static BITMAP* bmpFont;


// Init game
static int game_init()
{
    ASSET_PACK* ass = get_global_assets();
    bmpFont = (BITMAP*)get_asset(ass,"font");

    // Initialize game components
    obj_init(ass);
    stage_init(ass);

    return 0;
}


// Update game
static void game_update(float tm)
{
    // Update game components
    stage_update(tm);
    obj_update(tm);
}


// Draw game
static void game_draw()
{
    // Draw game components
    stage_draw();
    obj_draw();
}


// Destroy game
static void game_destroy()
{

}


// Scene swapped
static void game_on_swap()
{

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
