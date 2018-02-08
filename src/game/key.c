/// Key (source)
/// (c) 2018 Jani Nykänen

#include "key.h"

#include "../engine/graphics.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Key bitmap
static BITMAP* bmpKey;


// Update key
static void key_update(void* o, float tm)
{
    KEY* k = (KEY*)o;
    if(!k->exist) return;

    // Float
    k->floatTimer += 0.1f *  tm;
    if(k->floatTimer > 2 * M_PI)
        k->floatTimer -= 2 * M_PI;

    // Animate
    spr_animate(&k->spr,0,7,0,5,tm);
}


// Draw key
static void key_draw(void* o)
{
    KEY* k = (KEY*)o;

    spr_draw(&k->spr,bmpKey,
        (int)round(k->vpos.x),(int)round(k->vpos.y + sin(k->floatTimer)),0);
}


// Initialize
void key_init(ASSET_PACK* ass)
{
    bmpKey = (BITMAP*)get_asset(ass,"key");
}


// Create a new key
KEY key_create(int x, int y)
{
    KEY k;

    k.x = x;
    k.y = y;
    k.vpos = vec2(x*16.0f,y*16.0f);
    k.spr = create_sprite(16,16);
    k.onDraw = key_draw;
    k.onUpdate = key_update;
    k.exist = true;

    k.floatTimer = 0.0f;

    return k;
}
