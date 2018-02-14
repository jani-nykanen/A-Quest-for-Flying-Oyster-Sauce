/// Game object base (source)
/// (c) 2018 Jani Nykänen

#include "obase.h"


// Update object
void object_update(OBJECT* o, float tm)
{
    if(o == NULL || o->onUpdate == NULL) return;

    o->onUpdate((void*)o,tm);
}


// Object-player collision
void object_player_collision(OBJECT* o, OBJECT* p)
{
    if(o == NULL || p == NULL || o->onPlayerCollision == NULL) return;

    o->onPlayerCollision((void*)o,(void*)p);
}


// Draw object
void object_draw(OBJECT* o)
{
    if(o == NULL || o->onDraw == NULL) return;

    o->onDraw((void*)o);
}


// Reset
void object_reset(OBJECT* o)
{
    o->x = o->startPos.x;
    o->y = o->startPos.y;
    o->vpos.x = o->x * 16.0f;
    o->vpos.y = o->y * 16.0f;
    o->exist = true;

    if(o->onReset != NULL)
    {
        o->onReset(o);
    }
}