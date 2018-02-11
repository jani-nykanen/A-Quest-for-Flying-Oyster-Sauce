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