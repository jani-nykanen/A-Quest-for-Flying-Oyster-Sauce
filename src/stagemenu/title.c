/// Title (source)
/// (c) 2018 Jani Nykänen

#include "title.h"

#include "../engine/graphics.h"

#include "../vpad.h"
#include "../transition.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpLogo;
static BITMAP* bmpFont;
static BITMAP* bmpSky4;

// Title phase
static int titlePhase;
// Title timer
static float timer;
// Wave timer
static float waveTimer;

// Is title screen active;
static bool active;


// Disable title
static void disable_title()
{
    active = false;
}


// Initialize title screen
void title_init(ASSET_PACK* ass)
{
    // Get assets
    bmpLogo = (BITMAP*)get_asset(ass,"logo");
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpSky4 = (BITMAP*)get_asset(ass,"sky4");

    // Set default values
    titlePhase = 2;
    timer = 0.0f;
    waveTimer = 0.0f;
    active = true;
}


// Update title screen
void title_update(float tm)
{
    if(titlePhase == 2)
    {
        waveTimer += 0.05f * tm;

        if(vpad_get_button(1) == PRESSED)
        {
            trn_set(FADE_IN,BLACK_VERTICAL,2.0f,disable_title);
        }
    }
}


// Draw title screen
void title_draw()
{
    clear(0,0,0);

    // Draw background
    draw_bitmap(bmpSky4,0,0,0);

    // Draw logo
    draw_bitmap(bmpLogo,0,(int)round(sin(waveTimer)*2.0f),0);

    // Draw "Press enter"
    if( (int)round(waveTimer * 0.75f) % 2 == 0 )
    {
        set_bitmap_color(bmpFont,rgb(255,255,0));
        draw_text(bmpFont,(Uint8*)"Press Enter to Start",-1,128,152,-1,0,true);
        set_bitmap_color(bmpFont,rgb(255,255,255));
    }

    // Draw (c)
    draw_text(bmpFont,(Uint8*)"(c) 2018 Jani Nyk*nen",-1,128,192-9,-1,0,true);
}


// Toggle title screen
void title_toggle(bool state)
{
    active = state;
}


// Is title active
bool title_is_on()
{
    return active;
}