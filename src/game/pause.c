/// Pause (source)
/// (c) 2018 Jani Nykänen

#include "pause.h"

#include "../engine/graphics.h"
#include "../engine/music.h"
#include "../engine/sample.h"
#include "../engine/app.h"

#include "../vpad.h"
#include "../transition.h"

#include "game.h"

#include "stdlib.h"
#include "math.h"

// Is pause enabled
static bool paused;

// Cursor pos
static int cursorPos;
// Wave timer
static float wave;

// Bitmaps
static BITMAP* bmpCursor;
static BITMAP* bmpFont;

// Sound effects
static SAMPLE* sSelect;
static SAMPLE* sAccept;


// Initialize pause
void pause_init(ASSET_PACK* ass)
{
    cursorPos = 0;
    wave = 0.0f;

    // Get assets
    bmpCursor = (BITMAP*)get_asset(ass,"icons");
    bmpFont = (BITMAP*)get_asset(ass,"font");

    sSelect = (SAMPLE*)get_asset(ass,"select");
    sAccept = (SAMPLE*)get_asset(ass,"accept");
}


// Control pause screen
void pause_control(float tm)
{
    float DELTA = 0.1f;

    // Button input
    if(vpad_get_button(1) == PRESSED || vpad_get_button(0) == PRESSED)
    {
        play_sample(sAccept,0.50f);
        if(cursorPos == 0)
            paused = false;
        else if(cursorPos == 1)
        {
            paused = false;
            trn_set(FADE_IN,BLACK_VERTICAL,2.0f,game_reset);
        }
        else if(cursorPos == 3)
            app_terminate();
    }

    // Cursor movement
    float sticky = vpad_get_stick().y;
    float deltay = vpad_get_delta().y;

    int oldPos = cursorPos;
    if(deltay > DELTA && sticky > DELTA)
    {
        ++ cursorPos;   
        cursorPos = cursorPos % 4;
    }
    else if(deltay < -DELTA && sticky < -DELTA)
    {
        -- cursorPos;   
        if(cursorPos < 0) cursorPos += 4;
    }

    if(oldPos != cursorPos)
    {
        play_sample(sSelect,0.40f);
    }

    // Update wave
    wave += 0.1f * tm;
}


// Draw pause screen
void pause_draw()
{
    if(!paused) return;

    int w = 80;
    int h = 64;

    // Draw box
    fill_rect(128-w/2,96-h/2,w,h,rgb(255,255,255));
    fill_rect(128-w/2+1,96-h/2+1,w-2,h-2,rgb(0,0,0));
    fill_rect(128-w/2+2,96-h/2+2,w-4,h-4,rgb(85,170,255));

    int tpos = 22;
    int yoff = 15;

    // Draw text
    draw_text(bmpFont,(Uint8*)"Resume",-1,128-w/2 + tpos,96-h/2 + 4,-1,0,false);
    draw_text(bmpFont,(Uint8*)"Restart",-1,128-w/2 + tpos,96-h/2 + 4 +yoff,-1,0,false);
    draw_text(bmpFont,(Uint8*)"Options",-1,128-w/2 + tpos,96-h/2 + 4 +yoff*2,-1,0,false);
    draw_text(bmpFont,(Uint8*)"Quit",-1,128-w/2 + tpos,96-h/2 + 4 +yoff*3,-1,0,false);

    // Draw cursor
    draw_bitmap_region(
        bmpCursor,16,0,16,16,
        128-w/2+ 4 + (int)round(sin(wave)),
        96-h/2 + cursorPos*yoff,
        0);
}


// Get if the pause screen is enabled
bool pause_enabled()
{
    return paused;
}

// Enable pause
void pause_enable()
{
    paused = true;

    cursorPos = 0;
}