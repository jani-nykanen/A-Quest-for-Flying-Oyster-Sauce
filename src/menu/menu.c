/// Stage Menu scene (source)
/// (c) 2018 Jani Nykänen

#include "menu.h"

#include "../engine/assets.h"
#include "../engine/bitmap.h"
#include "../engine/graphics.h"
#include "../engine/app.h"
#include "../engine/sample.h"
#include "../engine/music.h"

#include "../global.h"
#include "../vpad.h"
#include "../transition.h"

#include "grid.h"
#include "info.h"
#include "title.h"

#include "stdlib.h"
#include "math.h"

// Bitmap
static BITMAP* bmpSky2;
static BITMAP* bmpClouds;

// Music
static MUSIC* mMenu;

// Sound effects
static SAMPLE* sPause;

// Cloud position
static float cloudPos;


// Draw background
static void draw_background()
{
    int i = 0;

    draw_bitmap(bmpSky2,0,0,0);
    for(; i < 2; ++ i)
    {
        draw_bitmap(bmpClouds,(int)round(cloudPos + i * 256),192 - bmpClouds->h,0);
    }
}


// Init stage menu
static int menu_init()
{
    ASSET_PACK* ass = get_global_assets();

    // Get assets
    bmpSky2 = (BITMAP*)get_asset(ass,"sky2");
    bmpClouds = (BITMAP*)get_asset(ass,"clouds1");

    sPause = (SAMPLE*)get_asset(ass,"pause");
    mMenu = (MUSIC*)get_asset(ass,"menu");

    // Initialize components
    grid_init(ass);

    // Read stage list
    if(load_stage_info(25, "assets/stages.list") == 1)
    {
        return 1;
    }

    // Initialize title
    title_init(ass);

    return 0;
}


// Update menu
static void menu_update(float tm)
{
    if(trn_is_active()) return;
    if(title_is_on())
    {
        title_update(tm);
        return;   
    }

    // Update components
    grid_update(tm);

    // Update clouds
    cloudPos -= 0.5f * tm;
    if(cloudPos < -bmpClouds->w)
        cloudPos += bmpClouds->w;

    // If ESC pressed, quit
    if(vpad_get_button(3) == PRESSED)
    {
        play_sample(sPause,0.40f);
        trn_set(FADE_IN,BLACK_CIRCLE,2.0f,app_terminate);
    }
}


// Draw stage menu
static void menu_draw()
{
    if(title_is_on())
    {
        title_draw();
        return;   
    }

    draw_background();
    grid_draw();
}


// Destroy stage menu
static void menu_destroy()
{

}


// Scene swapped
static void menu_on_swap()
{
    play_music(mMenu,0.80f,-1);
}


// Get stage menu scene
SCENE get_menu_scene()
{
    // Set scene functions
    SCENE s = (SCENE){menu_init,menu_update,menu_draw,menu_destroy,menu_on_swap};

    // Set scene name
    set_scene_name(&s,"menu");

    return s;
}
