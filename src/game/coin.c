/// Coin (source)
/// (c) 2018 Jani Nykänen

#include "coin.h"

#include "../engine/graphics.h"
#include "../engine/sample.h"

#include "player.h"
#include "status.h"
#include "stage.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Coin bitmap
static BITMAP* bmpCoin;

// Sound effects
static SAMPLE* sCoin;


// Coin-player collision
static void coin_player_collision(void* o, void* p)
{
    const float DIST = 8.0f;

    PLAYER* pl = (PLAYER*)p;
    COIN* c = (COIN*)o;

    if(c->dying || c->exist == false) return;

    if( (fabs(pl->vpos.x-c->vpos.x) < DIST && fabs(pl->vpos.y-c->vpos.y) < DIST))
    {
        c->dying = true;
        c->preventMovement = true;
        c->spr.frame = 0;
        c->spr.count = 0;
        c->spr.row = 0;
        play_sample(sCoin,0.50f);

        if(c->type == 0)
            stage_toggle_purple_blocks();
        else
            stage_mutate();
    }
}


// Update coin
static void coin_update(void* o, float tm)
{
    COIN* c = (COIN*)o;
    c->preventMovement = false;
    if(!c->exist) return;

    // Dying
    if(c->dying)
    {
        if(c->spr.frame  < 5)
        {
            spr_animate(&c->spr,1 + c->type*2,0,5,5,tm);
        }
        else
        {
            c->exist = false;
        }
        return;
    }

    // Animate
    spr_animate(&c->spr,c->type*2,7 + c->type*4,0,5,tm);

    // Float
    c->floatTimer += 0.1f *  tm;
    if(c->floatTimer > 2 * M_PI)
        c->floatTimer -= 2 * M_PI;
    
}


// Draw coin
static void coin_draw(void* o)
{
    COIN* c = (COIN*)o;
    if(!c->exist) return;

    spr_draw(&c->spr,bmpCoin,
        (int)round(c->vpos.x),(int)round(c->vpos.y + sin(c->floatTimer)),0);
}


// Reset coin
static void coin_reset(void* o)
{
    COIN* c = (COIN*)o;

    c->dying = false;
}


// Initialize
void coin_init(ASSET_PACK* ass)
{
    // Get assets
    bmpCoin = (BITMAP*)get_asset(ass,"coin");
    sCoin = (SAMPLE*)get_asset(ass,"getCoin");
}


// Create a new coin
COIN coin_create(int x, int y, int type)
{
    COIN c;

    c.x = x;
    c.y = y;
    c.vpos = vec2(x*16.0f,y*16.0f);
    c.spr = create_sprite(16,16);
    c.onDraw = coin_draw;
    c.onUpdate = coin_update;
    c.onPlayerCollision = coin_player_collision;
    c.onReset = coin_reset;
    c.exist = true;
    c.dying = false;
    c.preventMovement = false;
    c.floatTimer = 0.0f;
    c.type = type;

    return c;
}
