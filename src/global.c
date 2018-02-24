/// Global scene (source)
/// (c) 2018 Jani Nykänen

#define SDL_MAIN_HANDLED

#include "global.h"

#include "lib/parseword.h"

#include "engine/graphics.h"
#include "engine/assets.h"
#include "engine/music.h"
#include "engine/app.h"

#include "vpad.h"
#include "transition.h"
#include "savedata.h"
#include "options.h"

#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// Global asset pack
static ASSET_PACK* globalAssets;


static void read_keyconfig(const char* path)
{
    WORDDATA* wd = parse_file(path);
    if(wd == NULL)
    {
        // Use default config
        vpad_add_button(0,(int)SDL_SCANCODE_SPACE,0);
        vpad_add_button(1,(int)SDL_SCANCODE_RETURN,7);
        vpad_add_button(2,(int)SDL_SCANCODE_R,3);
        vpad_add_button(3,(int)SDL_SCANCODE_ESCAPE,6);
    }

    int i = 0;
    for(; i < wd->wordCount; i += 3)
    {
        vpad_add_button
            ((int)strtol(get_word(wd,i),NULL,10),
            (int)strtol(get_word(wd,i +1),NULL,10),
            (int)strtol(get_word(wd,i +2),NULL,10));
    }
}


// Initialize global scene
static int global_init()
{
    // Init vpad & read key configuration
    vpad_init();
    read_keyconfig("keyconfig.list");

    // Load global assets
    globalAssets = load_asset_pack("assets/global.ass");
    if(globalAssets == NULL)
    {
        return 1;
    }
    
    // Initialize global components
    trn_init(globalAssets);

    // Load save data
    if(read_save_data("save.dat") == 1)
    {
        printf("Failed to create/read a save file.\n");
    }

    // Read settings
    read_settings("settings.dat");

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


// Destroy global scene
static void global_destroy()
{
    // Save data
    save_data("save.dat");

    // Save settings
    save_settings("settings.dat");
}


// Return the global scene
SCENE get_global_scene()
{
    // Set scene functions
    SCENE s = (SCENE){global_init,global_update,global_draw,global_destroy};
        
    // Set scene name
    set_scene_name(&s,"global");

    return s; 

}


// Get asssets
ASSET_PACK* get_global_assets()
{
    return globalAssets;
}
