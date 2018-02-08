/// Game object base (source)
/// (c) 2018 Jani Nykänen

#include "obase.h"


// Update object
void object_update(OBJECT* o, float tm)
{
    if(o == NULL || o->onUpdate == NULL) return;

    o->onUpdate((void*)o,tm);
}


// Draw object
void object_draw(OBJECT* o)
{
    if(o == NULL || o->onDraw == NULL) return;

    o->onDraw((void*)o);
}