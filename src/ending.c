/// Ending (source)
/// (c) 2018 Jani Nykänen

#include "ending.h"

#include "engine/app.h"
#include "engine/graphics.h"
#include "engine/assets.h"
#include "engine/sample.h"
#include "engine/music.h"
#include "engine/sprite.h"

#include "game/status.h"

#include "vpad.h"
#include "global.h"
#include "transition.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Music
static MUSIC* mEnding;
static MUSIC* mClear;

// Sound effects
static SAMPLE* sFailure;
static SAMPLE* sAccept;

// Bitmaps
static BITMAP* bmpSky5;
static BITMAP* bmpPlayer;
static BITMAP* bmpTiles;
static BITMAP* bmpFont;
static BITMAP* bmpTheEnd;

// Phase
static int phase;
// Timer
static float timer;
// Player positions
static float plPos;

// Is victory
static bool isVictory;

// Player sprite
static SPRITE sprPlayer;


// Swap to "The End" phase
static void swap_to_final_phase()
{
    trn_set(FADE_OUT,BLACK_CIRCLE,1.0f,NULL);
    play_music(mClear,0.70f,1);
    phase = 3;
}


// Go back to the menu
static void go_to_menu()
{
    app_swap_scene("menu");
}


// Draw "Too bad!" text
static void draw_defeat(int dx, int dy)
{
    draw_text(bmpFont,(Uint8*)"TOO BAD!",-1,dx,dy,-1,0,true);

    draw_text(bmpFont,
        (Uint8*)"You must collect every golden star\nto reach the bottle of flying\noyster sauce. Come back later!",
        -1,dx-114,dy+18,-1,0,false);
}


// Draw "Victory!" text
static void draw_victory(int dx, int dy)
{
    draw_text(bmpFont,(Uint8*)"VICTORY!",-1,dx,dy,-1,0,true);

    draw_text(bmpFont,
        (Uint8*)"Congratulations! The bottle of\nflying oyster sauce is now\nyours. And no one cares.",
        -1,dx-114,dy+18,-1,0,false);
}



// Draw background
static void draw_bg(int dx, int dy)
{
    // Draw outside box
    fill_rect(dx-2,dy-2,bmpSky5->w+4,bmpSky5->h+4,rgb(255,255,255));
    fill_rect(dx-1,dy-1,bmpSky5->w+2,bmpSky5->h+2,rgb(0,0,0));

    // Draw sky
    draw_bitmap(bmpSky5,dx,dy,0);

    // Draw ground
    int i = 0;
    for(; i < bmpSky5->w / 16; ++ i)
    {
        draw_bitmap_region(bmpTiles,0,0,16,16,dx + i*16,dy + bmpSky5->h-16,0);
    }
}


// Draw player
static void draw_player(int dx, int dy)
{
    spr_draw(&sprPlayer,bmpPlayer,dx + plPos-12, dy-15 +bmpSky5->h-20,FLIP_HORIZONTAL);
}


// Reset ending
static void ending_reset()
{
    phase = 0;
    timer = 0.0f;
    plPos = 152.0f;

    isVictory = status_get_star_count(2) == 25;
}


// Initialize endingions
static int ending_init()
{
    ASSET_PACK* ass = get_global_assets();

    // Get assets
    mEnding = (MUSIC*)get_asset(ass,"ending");
    mClear = (MUSIC*)get_asset(ass,"clear");

    sFailure = (SAMPLE*)get_asset(ass,"failure");
    sAccept = (SAMPLE*)get_asset(ass,"accept");

    bmpSky5 = (BITMAP*)get_asset(ass,"sky5");
    bmpPlayer = (BITMAP*)get_asset(ass,"player");
    bmpTiles = (BITMAP*)get_asset(ass,"tiles1");
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpTheEnd = (BITMAP*)get_asset(ass,"theEnd");

    // Create sprite
    sprPlayer = create_sprite(24,24);

    return 0;
}


// Update endingions
static void ending_update(float tm)
{
    if(trn_is_active() && phase > 0) return;
    
    if(trn_is_active() || phase == 0)
    {
        spr_animate(&sprPlayer,0,0,3,8,tm);

        timer += 1.0f * tm;
        if(timer >= 30.0f)
            ++ phase;
    }
    else if(phase == 1)
    {
        spr_animate(&sprPlayer,1,0,5,5,tm);
        plPos -= 4 * 0.5f * tm;
        if(plPos < 64.0f)
        {
            plPos = 64.0f;
            ++ phase;
            sprPlayer.frame = 0;
            sprPlayer.count = 0;

            if(!isVictory)
            {
                stop_music();
                play_sample(sFailure,0.40f);
            }
        }
    }
    else if(phase == 2)
    {
        if(isVictory)
        {
            spr_animate(&sprPlayer,7,0,3,8,tm);
        }
        else
        {
            if(sprPlayer.frame < 2)
            {
                spr_animate(&sprPlayer,8,0,2,20,tm);
            }
        }

        if(vpad_get_button(0) == PRESSED 
        || vpad_get_button(1) == PRESSED)
        {
            play_sample(sAccept,0.40f);
            if(isVictory)
            {
                trn_set(FADE_IN,BLACK_VERTICAL,1.0f,swap_to_final_phase);
                fade_out_music(1000);
            }
            else
            {
                trn_set(FADE_IN,BLACK_CIRCLE,1.0f,go_to_menu);
            }
        }
    }
    else
    {
        if(vpad_get_button(0) == PRESSED 
        || vpad_get_button(1) == PRESSED)
        {
            play_sample(sAccept,0.40f);
            trn_set(FADE_IN,BLACK_CIRCLE,1.0f,go_to_menu);
        }
    }
}


// Draw endingions
static void ending_draw()
{
    clear(0,0,0);

    // Draw "The End"
    if(phase == 3)
    {
        draw_bitmap(bmpTheEnd,128-bmpTheEnd->w/2,96-bmpTheEnd->h/2,0);
        return;
    }

    draw_bg(128-80,12);
    draw_player(128-80,12);

    if(phase == 2)
    {
        if(isVictory)
        {
            draw_victory(128,132);
        }
        else
        {
            draw_defeat(128,132);
        }
    }
}


// Swap to endingions
static void ending_on_swap()
{
    play_music(mEnding,0.70f,-1);
    ending_reset();
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