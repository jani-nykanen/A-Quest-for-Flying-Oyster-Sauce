/// Stage Menu scene (source)
/// (c) 2018 Jani Nykänen

#include "stagemenu.h"

#include "../engine/assets.h"
#include "../engine/bitmap.h"
#include "../engine/graphics.h"

#include "../global.h"

#include "grid.h"

#include "stdlib.h"
#include "math.h"

// Bitmap
static BITMAP* bmpSky2;
static BITMAP* bmpClouds;

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
static int smenu_init()
{
    ASSET_PACK* ass = get_global_assets();

    // Get assets
    bmpSky2 = (BITMAP*)get_asset(ass,"sky2");
    bmpClouds = (BITMAP*)get_asset(ass,"clouds1");

    // Initialize components
    grid_init(ass);

    return 0;
}


// Update smenu
static void smenu_update(float tm)
{
    // Update components
    grid_update(tm);

    // Update clouds
    cloudPos -= 0.5f * tm;
    if(cloudPos < -bmpClouds->w)
        cloudPos += bmpClouds->w;
}


// Draw stage menu
static void smenu_draw()
{
    draw_background();
    grid_draw();
}


// Destroy stage menu
static void smenu_destroy()
{

}


// Scene swapped
static void smenu_on_swap()
{

}


// Get stage menu scene
SCENE get_stage_menu_scene()
{
    // Set scene functions
    SCENE s = (SCENE){smenu_init,smenu_update,smenu_draw,smenu_destroy,smenu_on_swap};

    // Set scene name
    set_scene_name(&s,"smenu");

    return s;
}
