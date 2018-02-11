/// Boulder (source)
/// (c) 2018 Jani Nykänen

#include "boulder.h"

#include "../engine/graphics.h"

#include "stage.h"

#include "stdio.h"
#include "math.h"

// Boulder bitmap
static BITMAP* bmpBoulder;


// Update boulder location to collision map
static void b_update_location(BOULDER* b)
{
    stage_set_collision_tile(b->x,b->y,1);

}


// Update boulder
static void boulder_update(void* o, float tm)
{
    BOULDER* b = (BOULDER*)o;

    if(!b->exist) return;

    spr_animate(&b->spr,0,0,0,0,tm);

    b_update_location(b);
}


// Draw boulder
static void boulder_draw(void* o)
{
    BOULDER* b = (BOULDER*)o;

    spr_draw(&b->spr,bmpBoulder,(int)round(b->vpos.x),(int)round(b->vpos.y) +1,0);
}


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
    b.onDraw = boulder_draw;
    b.onUpdate = boulder_update;
    b.exist = true;

    return b;
}
