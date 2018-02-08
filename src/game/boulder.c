/// Boulder (source)
/// (c) 2018 Jani Nykänen

#include "boulder.h"

#include "../engine/graphics.h"

// Boulder bitmap
static BITMAP* bmpBoulder;


// Initialize
void boulder_init(ASSET_PACK* ass)
{
    bmpBoulder = (BITMAP*)get_asset(ass,"boulder");
}


// Create a new boulder
BOULDER boulder_create(int x, int y)
{
    BOULDER b;

    b.x = x;
    b.y = y;
    b.vpos = vec2(x*16.0f,y*16.0f);
    b.spr = create_sprite(16,16);

    return b;
}


// Update boulder
void boulder_update(BOULDER* b, float tm)
{
    if(!b->exist) return;

    spr_animate(&b->spr,0,0,0,0,tm);
}


// Draw boulder
void boulder_draw(BOULDER* b)
{
    spr_draw(&b->spr,bmpBoulder,(int)round(b->vpos.x),(int)round(b->vpos.y) +1,0);
}