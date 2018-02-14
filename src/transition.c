/// Screen transition (header)
/// (c) 2018 Jani Nykänen

#include "transition.h"

#include "engine/graphics.h"

#include "math.h"

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

static void (*callback)(void);

// Initialize transition
void trn_init()
{
    mode = 0;
    fadeMode = FADE_IN;
    speed = 1.0f;
    timer = 0.0f;
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
}


// Is active
bool trn_is_active()
{
    return timer > 0.0f;
}