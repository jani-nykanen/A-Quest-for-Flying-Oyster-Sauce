/// Player (source)
/// (c) 2018 Jani Nykänen

#include "player.h"

#include "../engine/graphics.h"

// Player bitmap
static BITMAP* bmpPlayer;


// Initialize player
void pl_init(ASSET_PACK* ass)
{
    bmpPlayer = (BITMAP*)get_asset(ass,"player");
}


// Create a new player
PLAYER pl_create(int x, int y)
{
    PLAYER pl;
    pl.x = x;
    pl.y = y;
    pl.vpos.x = 16.0f*x;
    pl.vpos.y = 16.0f*y;
    pl.spr = create_sprite(24,24);

    return pl;
}


// Update player
void pl_update(PLAYER* pl, float tm)
{
    spr_animate(&pl->spr,0,0,3,10,tm);
}


// Draw player
void pl_draw(PLAYER* pl)
{
    spr_draw(&pl->spr,bmpPlayer,(int)round(pl->vpos.x) - 4,(int)round(pl->vpos.y) -4 + 1,0);
}
