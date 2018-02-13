/// Status (source)
/// (c) 2018 Jani Nykänen

#include "status.h"

#include "../engine/graphics.h"

// Stage name size
#define STAGE_NAME_SIZE 64
// Turn string size
#define TURN_STRING_SIZE 32

// Font
static BITMAP* bmpFont;
// Key bitmap
static BITMAP* bmpKey;
// Icons bitmap
static BITMAP* bmpIcons;

// Key count
static int keyCount;
// Previous key count
static int prevKeyCount;
// Key remove pos
static float keyRemovePos;
// Is removing a key
static bool removingKey;

// Turn count
static int turnCount;
// Target turns
static int turnTarget;
// Turn string
static char turnString[TURN_STRING_SIZE];

// Stage name
static char stageName[STAGE_NAME_SIZE];

// Initialize status
void status_init(ASSET_PACK* ass)
{
    // Load assets
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpKey = (BITMAP*)get_asset(ass,"key");
    bmpIcons = (BITMAP*)get_asset(ass,"icons");

    // Set default values
    status_reset();
}


// Reset status
void status_reset()
{
    // Set default values

    keyCount = 0;
    prevKeyCount = 0;
    removingKey = false;
    keyRemovePos = 0.0f;

    turnCount = 0;
    turnTarget = 0;

    snprintf(stageName,STAGE_NAME_SIZE," ");
}


// Update status
void status_update(float tm)
{
    const float REMOVE_SPEED = 1.0f;

    if(!removingKey && prevKeyCount > keyCount)
    {
        removingKey = true;
        keyRemovePos = 0.0f;
    }
    else if(removingKey)
    {
        keyRemovePos += REMOVE_SPEED * tm;
        if(keyRemovePos > 20.0f)
        {
            removingKey = false;
        }
    }

    prevKeyCount = keyCount;

    snprintf(turnString,TURN_STRING_SIZE,"%d/%d",turnCount,turnTarget);
    
}


// Draw status
void status_draw()
{
    int i = 0;

    // Draw stage name
    draw_text(bmpFont,(Uint8*)stageName,-1,128,4,0,0,true);

    // Draw keys
    for(; i < keyCount; ++ i)
    {
        draw_bitmap_region(bmpKey,0,0,16,16,2 + i*13,4,0);
    }
    if(removingKey)
    {
        draw_bitmap_region(bmpKey,0,0,16,16,2 + (i)*13,4 - (int)round(keyRemovePos),0);
    }

    // Draw turns
    draw_bitmap_region(bmpIcons,0,0,16,16,192,0,0);
    draw_text(bmpFont,(Uint8*)turnString,-1,210,5,-1,0,false);
}


// Add key
void status_add_key()
{
    ++ keyCount;
}


// Remove key
void status_remove_key()
{
    if(keyCount > 0)
        -- keyCount;
}


// Get key count
int status_get_key_count()
{
    return keyCount;
}


// Set name
void status_set_stage_name(const char* name)
{
    snprintf(stageName,STAGE_NAME_SIZE,"%s",name);
}


// Add turn
void status_add_turn()
{
    ++ turnCount;
}


// Set turn target
void status_set_turn_target(int target)
{
    turnTarget = target;
}