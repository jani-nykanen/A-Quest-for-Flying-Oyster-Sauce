/// Options scene (header)
/// (c) 2018 Jani Nykänen

#include "options.h"

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

// Bitmaps
static BITMAP* bmpFont;
static BITMAP* bmpIcons;

// Sound effects
static SAMPLE* sSelect;
static SAMPLE* sAccept;
static SAMPLE* sPause;

// Cursor position
static int cursorPos;
// Cursor wave
static float wave;


// Edit sound value
static void edit_sound_value(int v, int dir, int p, void (*cb)(int))
{
    if(cursorPos == p && ( (dir == 1 && v < 100) || (dir == -1 && v > 0)  ) )
    {
        play_sample(sSelect,0.40f);
        v += dir*10;
        if(v > 100) v = 100;
        if(v < 0) v = 0;
        cb(v);
    }
}


// Draw text
static void opt_draw_text(int dx, int dy, int h)
{
    const int START_Y = 18;
    const int END_Y = 24;
    const int YOFF = 14;

    char soundStr[16];
    snprintf(soundStr,16,"SOUND: %d",get_global_sample_volume());

    char musicStr[16];
    snprintf(musicStr,16,"MUSIC: %d",get_global_music_volume());

    set_bitmap_color(bmpFont,rgb(255,255,0));
    draw_text_with_borders(bmpFont,(Uint8*)"OPTIONS",-1,128,dy,-1,0,true);
    set_bitmap_color(bmpFont,rgb(255,255,255));
    
    draw_text(bmpFont,(Uint8*)soundStr,-1,dx,START_Y + dy,-1,0,false);
    draw_text(bmpFont,(Uint8*)musicStr,-1,dx,START_Y + dy + YOFF,-1,0,false);
    draw_text(bmpFont,(Uint8*)"FULL SCREEN",-1,dx,START_Y + dy + YOFF*2,-1,0,false);

    draw_text(bmpFont,(Uint8*)"Return",-1,dx,dy + h - END_Y,-1,0,false);

    
}


// Initialize options
static int opt_init()
{
    ASSET_PACK* ass = get_global_assets();

    // Get assets
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpIcons = (BITMAP*)get_asset(ass,"icons");

    sSelect = (SAMPLE*)get_asset(ass,"select");
    sAccept = (SAMPLE*)get_asset(ass,"accept");
    sPause = (SAMPLE*)get_asset(ass,"pause");

    wave = 0.0f;
    cursorPos = 3;

    return 0;
}


// Update options
static void opt_update(float tm)
{
    const float DELTA = 0.1f;

    // Escape pressed
    if(vpad_get_button(3) == PRESSED)
    {
        play_sample(sPause,0.40f);
        app_swap_to_previous_scene();
    }

    // Select
    if(vpad_get_button(0) == PRESSED || vpad_get_button(1) == PRESSED)
    {
        if(cursorPos > 1)
        {
            play_sample(sAccept,0.40f);
        }

        if(cursorPos == 3)
            app_swap_to_previous_scene();
        else if(cursorPos == 2)
            app_toggle_fullscreen();
    }

    // Cursor movement
    VEC2 stick = vpad_get_stick();
    VEC2 delta = vpad_get_delta();

    int oldPos = cursorPos;
    // Vertical movement
    if(delta.y > DELTA && stick.y > DELTA)
    {
        ++ cursorPos;   
        cursorPos = cursorPos % 4;
    }
    else if(delta.y < -DELTA && stick.y < -DELTA)
    {
        -- cursorPos;   
        if(cursorPos < 0) cursorPos += 4;
    }

    // Horizontal movement
    int soundVol = get_global_sample_volume();
    int musicVol = get_global_music_volume();

    if(delta.x > DELTA && stick.x > DELTA)
    {
        edit_sound_value(soundVol,1,0, set_global_sample_volume);
        edit_sound_value(musicVol,1,1, set_global_music_volume);
    }
    else if(delta.x < -DELTA && stick.x < -DELTA)
    {
        edit_sound_value(soundVol,-1,0, set_global_sample_volume);
        edit_sound_value(musicVol,-1,1, set_global_music_volume);
    }

    if(oldPos != cursorPos)
    {
        play_sample(sSelect,0.40f);
    }

    // Update wave
    wave += 0.1f * tm;
}


// Draw options
static void opt_draw()
{
    const int WIDTH = 128;
    const int HEIGHT = 88;

    int x = 128 - WIDTH / 2;
    int y = 96 - HEIGHT / 2;

    int yoff = cursorPos == 3 ? 15 : 14;

    // Draw box
    fill_rect(x,y,WIDTH,HEIGHT,rgb(255,255,255));
    fill_rect(x +1,y +1,WIDTH -2,HEIGHT -2,rgb(0,0,0));
    fill_rect(x +2,y +2,WIDTH -4,HEIGHT -4,rgb(75,170,255));

    // Draw text
    opt_draw_text(x+24,y + 8, HEIGHT);

    // Draw cursor
    draw_bitmap_region(
        bmpIcons,16,0,16,16,
        x+ 4 + (int)round(sin(wave)),
        y+8 + (cursorPos+1)*yoff,
        0);

}


// Swap to options
static void opt_on_swap()
{
    cursorPos = 3;
    wave = 0.0f;
}


// Get options scene
SCENE get_options_scene()
{
    // Set scene functions
    SCENE s = (SCENE){opt_init,opt_update,opt_draw,NULL,opt_on_swap};

    // Set scene name
    set_scene_name(&s,"options");

    return s;
}