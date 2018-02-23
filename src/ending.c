/// Ending (source)
/// (c) 2018 Jani Nykänen

#include "ending.h"

#include "engine/app.h"
#include "engine/graphics.h"
#include "engine/assets.h"
#include "engine/sample.h"
#include "engine/music.h"

#include "vpad.h"
#include "global.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"


// Initialize endingions
static int ending_init()
{
    // ASSET_PACK* ass = get_global_assets();

    return 0;
}


// Update endingions
static void ending_update(float tm)
{

}


// Draw endingions
static void ending_draw()
{

}


// Swap to endingions
static void ending_on_swap()
{

}


// Get endingions scene
SCENE get_ending_scene()
{
    // Set scene functions
    SCENE s = (SCENE){ending_init,ending_update,ending_draw,NULL,ending_on_swap};

    // Set scene name
    set_scene_name(&s,"ending");

    return s;
}