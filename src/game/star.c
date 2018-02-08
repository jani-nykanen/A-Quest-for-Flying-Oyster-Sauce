/// Star (source)
/// (c) 2018 Jani Nykänen

#include "star.h"

#include "../engine/graphics.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Star bitmap
static BITMAP* bmpStar;


// Update Star
static void star_update(void* o, float tm)
{
    STAR* s = (STAR*)o;
    if(!s->exist) return;

    // Float
    s->floatTimer += 0.075f *  tm;
    if(s->floatTimer > 2 * M_PI)
        s->floatTimer -= 2 * M_PI;

    // Animate
    spr_animate(&s->spr,0,11,0,4,tm);
}


// Draw Star
static void star_draw(void* o)
{
    STAR* s = (STAR*)o;

    spr_draw(&s->spr,bmpStar,
        (int)round(s->vpos.x),(int)round(s->vpos.y + cos(s->floatTimer)),0);
}


// Initialize
void star_init(ASSET_PACK* ass)
{
    bmpStar = (BITMAP*)get_asset(ass,"star");
}


// Create a new Star
STAR star_create(int x, int y)
{
    STAR s;

    s.x = x;
    s.y = y;
    s.vpos = vec2(x*16.0f,y*16.0f);
    s.spr = create_sprite(16,16);
    s.onDraw = star_draw;
    s.onUpdate = star_update;
    s.exist = true;

    s.floatTimer = 0.0f;

    return s;
}
