/// Screen transition (header)
/// (c) 2018 Jani Nykänen

#include "transition.h"

#include "engine/graphics.h"

#include "math.h"

// Black circle bitmap
static BITMAP* bmpCircle;

// Timer max
static const float TIMER_MAX = 60.0f;

// Fade mode
static int fadeMode;
// Transition speed
static float speed;
// Transition mode
static int mode;
// Timer
static float timer;

// Callback function
static void (*callback)(void);


// Initialize transition
void trn_init(ASSET_PACK* ass)
{
    mode = 0;
    fadeMode = BLACK_CIRCLE;
    speed = 1.0f;
    timer = 0.0f;

    // Get assets
    bmpCircle = (BITMAP*)get_asset(ass,"blackCircle");
}


// Set transition
void trn_set(int fading, int type, float s, void (*cb)(void))
{
    fadeMode = fading;
    speed = s;
    mode = type;
    timer = TIMER_MAX;
    callback = cb;
}


// Update transition
void trn_update(float tm)
{
    if(timer > 0.0f)
    {
        timer -= speed * tm;
        if(timer <= 0.0f && fadeMode == FADE_IN)
        {
            if(callback != NULL)
            {
                callback();
            }
            fadeMode = FADE_OUT;
            timer = TIMER_MAX;
        }
    }
}


// Draw transition
void trn_draw()
{
    if(timer <= 0.0f) return;

    float t = timer/TIMER_MAX;
    if(fadeMode == FADE_IN) t = 1.0f - t;

    COLOR black = rgb(0,0,0);

    if(mode == BLACK_VERTICAL)
    {
        int h = (int)round(96.0f * t);
        int y = 192 - h;

        fill_rect(0,0,256,h,black);
        fill_rect(0,y,256,h,black);
    }
    else if(mode == BLACK_CIRCLE)
    {
        t = 1.0f - t;
        int sw = (int)round(t * bmpCircle->w);
        int sh = (int)round(t * bmpCircle->h);

        int x = 128-sw/2;
        int y = 96-sh/2;

        // Draw circle
        draw_scaled_bitmap(bmpCircle,x,y,t,t,0);

        // Draw borders
        fill_rect(0,0,256,y,black);
        fill_rect(0,192-y,256,y,black);
        fill_rect(0,0,x,192,black);
        fill_rect(256-x,0,x,192,black);
    }
}


// Is active
bool trn_is_active()
{
    return timer > 0.0f;
}