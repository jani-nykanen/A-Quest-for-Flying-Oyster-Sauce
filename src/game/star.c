/// Star (source)
/// (c) 2018 Jani Nykänen

#include "star.h"

#include "../engine/graphics.h"

#include "player.h"
#include "status.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Star bitmap
static BITMAP* bmpStar;


// Player collision
static void star_player_collision(void * o, void * p)
{
    
    STAR* s = (STAR*)o;
    PLAYER* pl = (PLAYER*) p;

    if(s->collected) return;

    if(( (!pl->moving && !pl->falling)
     || (fabs(pl->vpos.x-s->vpos.x) < 4 && fabs(pl->vpos.y-s->vpos.y) < 4 ) )
        && pl->x == s->x && pl->y == s->y)
    {
        pl->victorous = true;
        s->collected = true;
        s->vpos.y -= 16.0f;

        pl->vpos.x = pl->x*16.0f;
        pl->vpos.y = pl->y*16.0f;

        status_activate_victory();

    }
}


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
    spr_animate(&s->spr,status_star_type(),11,0,4,tm);
}


// Draw Star
static void star_draw(void* o)
{
    STAR* s = (STAR*)o;

    spr_draw(&s->spr,bmpStar,
        (int)round(s->vpos.x),(int)round(s->vpos.y + cos(s->floatTimer)),0);
}


// Reset star
static void star_reset(void* o)
{
    STAR* s = (STAR*)o;
    s->collected = false;
    s->floatTimer = 0.0f;
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
    s.onPlayerCollision = star_player_collision;
    s.onReset = star_reset;
    s.preventMovement = false;
    s.exist = true;
    s.collected = false;

    s.floatTimer = 0.0f;

    return s;
}
