/// Enemy (source)
/// (c) 2018 Jani Nykänen

#include "enemy.h"

#include "../engine/graphics.h"

#include "../vpad.h"

#include "stage.h"
#include "player.h"
#include "status.h"

#include "stdio.h"
#include "math.h"

// Enemy bitmap
static BITMAP* bmpEnemy;


// Boulder-player collision
static void enemy_player_collision(void* o, void* p)
{
    // PLAYER* pl = (PLAYER*)p;
    ENEMY* e = (ENEMY*)o;

    if(!e->exist) return;
}


// Animate
static void enemy_animate(ENEMY* e, float tm)
{
    spr_animate(&e->spr,e->id,0,3,8,tm);
}


// Update enemy
static void enemy_update(void* o, float tm)
{
    ENEMY* e = (ENEMY*)o;
    e->preventMovement = false;
    if(!e->exist) return;

    enemy_animate(e,tm);
}


// Draw enemy
static void enemy_draw(void* o)
{
    ENEMY* e = (ENEMY*)o;
    if(e->exist == false) return;

   
    spr_draw(&e->spr,bmpEnemy,e->vpos.x-4,e->vpos.y-4 +1,0);
    
}


// Initialize
void enemy_init(ASSET_PACK* ass)
{
    bmpEnemy = (BITMAP*)get_asset(ass,"enemy");
}


// Create a new enemy
ENEMY enemy_create(int x, int y, int id)
{
    ENEMY b;

    b.x = x;
    b.y = y;
    b.id = id;
    b.vpos = vec2(x*16.0f,y*16.0f);
    b.spr = create_sprite(24,24);
    b.onDraw = enemy_draw;
    b.onUpdate = enemy_update;
    b.onPlayerCollision = enemy_player_collision;
    b.exist = true;
    b.preventMovement = false;
    b.moving = false;
    b.dir = x % 2 == 0 ? 1 : -1;

    // stage_set_collision_tile(b.x,b.y,1);

    return b;
}
