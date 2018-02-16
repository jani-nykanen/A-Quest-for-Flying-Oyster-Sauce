/// Global scene (source)
/// (c) 2018 Jani Nykänen

#define SDL_MAIN_HANDLED

#include "global.h"

#include "engine/graphics.h"
#include "engine/assets.h"
#include "engine/music.h"

#include "vpad.h"
#include "transition.h"

#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// Global asset pack
static ASSET_PACK* globalAssets;


// Initialize global scene
static int global_init()
{
    // Init vpad
    vpad_init();
    vpad_add_button(0,(int)SDL_SCANCODE_SPACE,0);
    vpad_add_button(1,(int)SDL_SCANCODE_RETURN,7);
    vpad_add_button(2,(int)SDL_SCANCODE_R,6);

    // Load global assets
    globalAssets = load_asset_pack("assets/global.ass");
    if(globalAssets == NULL)
    {
        return 1;
    }
    
    // Initialize global components
    trn_init();
    trn_set(FADE_OUT,BLACK_VERTICAL,1.0f,NULL);

    return 0;
}


// Update global scene
static void global_update(float tm)
{
    vpad_update();
    trn_update(tm);
}


// Draw global scene
static void global_draw()
{
    trn_draw();
}


// Return the global scene
SCENE get_global_scene()
{
    // Set scene functions
    SCENE s = (SCENE){global_init,global_update,global_draw,NULL};
        
    // Set scene name
    set_scene_name(&s,"global");

    return s; 

}


// Get asssets
ASSET_PACK* get_global_assets()
{
    return globalAssets;
}
