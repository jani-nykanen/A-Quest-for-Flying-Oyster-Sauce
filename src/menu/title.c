/// Title (source)
/// (c) 2018 Jani Nykänen

#include "title.h"

#include "../engine/graphics.h"
#include "../engine/sample.h"
#include "../engine/music.h"
#include "../engine/app.h"

#include "../vpad.h"
#include "../transition.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpLogo;
static BITMAP* bmpFont;
static BITMAP* bmpSky4;
static BITMAP* bmpIntro;

// Sound effects
static SAMPLE* sPause;

// Music
static MUSIC* mMenu;

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


// Draw "created by" intro
static void draw_intro()
{
    float t = 1.0f;
    if(timer < 60.0f)
    {
        t = timer/60.0f;
    }
    else if(timer > 180.0f)
    {
        t = 1.0f + (timer-180.0f)/60.0f;
    }

    if(titlePhase == 1)
    {
        t = 2.0f - t;
    }

    int w = bmpIntro->w;
    int x = -128 + (int)round((256)*t);
    int sh = titlePhase * (bmpIntro->h/2);

    draw_bitmap_region(
        bmpIntro,0,sh,w,bmpIntro->h/2,x - w/2,96-bmpIntro->h/4
        + (int)round(sin(waveTimer) * 8),0);
}


// Initialize title screen
void title_init(ASSET_PACK* ass)
{
    // Get assets
    bmpLogo = (BITMAP*)get_asset(ass,"logo");
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpSky4 = (BITMAP*)get_asset(ass,"sky4");
    bmpIntro = (BITMAP*)get_asset(ass,"introImg");

    sPause = (SAMPLE*)get_asset(ass,"pause");

    mMenu = (MUSIC*)get_asset(ass,"menu");

    // Set default values
    titlePhase = 0;
    timer = 0.0f;
    waveTimer = 0.0f;
    active = true;
}


// Update title screen
void title_update(float tm)
{
     waveTimer += 0.05f * tm;

    if(titlePhase == 2)
    {
       

        // If enter/space pressed, start
        if(vpad_get_button(1) == PRESSED || vpad_get_button(0) == PRESSED)
        {
            play_sample(sPause,0.40f);
            trn_set(FADE_IN,BLACK_CIRCLE,2.0f,disable_title);
        }

        // If ESC pressed, quit
        if(vpad_get_button(3) == PRESSED)
        {
            play_sample(sPause,0.40f);
            trn_set(FADE_IN,BLACK_CIRCLE,2.0f,app_terminate);
        }
    }
    else
    {
        timer += 1.0f * tm;
        if(timer >= 240.0f)
        {
            timer -= 240.0f;
            ++ titlePhase;

            if(titlePhase == 2)
            {
                trn_set(FADE_OUT,BLACK_CIRCLE,1.0f,NULL);
                play_music(mMenu,0.80f,-1);
            }
        }

        // If enter/space pressed, skip intro
        if(vpad_get_button(0) == PRESSED || vpad_get_button(1) == PRESSED)
        {
            play_sample(sPause,0.40f);
            
            trn_set(FADE_OUT,BLACK_CIRCLE,1.0f,NULL);
            play_music(mMenu,0.80f,-1);
            titlePhase = 2;
        }
    }
}


// Draw title screen
void title_draw()
{
    clear(0,0,0);

    // Draw intro
    if(titlePhase < 2)
    {
        draw_intro();
        return;
    }

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