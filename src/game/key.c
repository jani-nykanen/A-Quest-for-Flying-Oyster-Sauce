/// Key (source)
/// (c) 2018 Jani Nykänen

#include "key.h"

#include "../engine/graphics.h"

#include "player.h"
#include "status.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Key bitmap
static BITMAP* bmpKey;


// Key-player collision
static void key_player_collision(void* o, void* p)
{
    const float DIST = 8.0f;

    PLAYER* pl = (PLAYER*)p;
    KEY* k = (KEY*)o;

    if(k->flying || k->exist == false) return;

    if(fabs(pl->vpos.x-k->vpos.x) < DIST && fabs(pl->vpos.y-k->vpos.y) < DIST && pl->x == k->x && pl->y == k->y)
    {
        k->flying = true;
        k->preventMovement = true;
    }
}


// Fly
static void key_fly(KEY* k, float tm)
{
    const float ACC = 0.4f;
    const float MAX_SPEED = 6.0f;

    float targetX = 2.0f + status_get_key_count()*13.0f;
    float targetY = 4.0f;

    k->spr.frame = 0;
    k->floatTimer = 0.0f;

    float angle = atan2(targetY-k->vpos.y,targetX-k->vpos.x);

    VEC2 speed = vec2(cos(angle) * 1.0f, sin(angle) * 1.0f);
    speed.x *= (1.0f + k->speedMul);
    speed.y *= (1.0f + k->speedMul);

    if(k->speedMul < MAX_SPEED)
        k->speedMul += ACC * tm;
    else
        k->speedMul = MAX_SPEED;
    
    k->vpos.x += speed.x * tm;
    k->vpos.y += speed.y * tm;

    if(hypot(targetX-k->vpos.x,targetY-k->vpos.y) < 1.0f+k->speedMul)
    {
        k->exist = false;
        status_add_key();
    }
}


// Update key
static void key_update(void* o, float tm)
{
    KEY* k = (KEY*)o;
    k->preventMovement = false;
    if(!k->exist) return;

    // Fly
    if(k->flying)
    {
        key_fly(k,tm);
        k->preventMovement = true;
        return;
    }

    // Animate
    spr_animate(&k->spr,0,7,0,5,tm);

    // Float
    k->floatTimer += 0.1f *  tm;
    if(k->floatTimer > 2 * M_PI)
        k->floatTimer -= 2 * M_PI;
    
}


// Draw key
static void key_draw(void* o)
{
    KEY* k = (KEY*)o;
    if(!k->exist) return;

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
    k.onPlayerCollision = key_player_collision;
    k.exist = true;
    k.flying = false;
    k.preventMovement = false;
    k.speedMul = 0.0f;
    k.floatTimer = 0.0f;

    return k;
}
