/// Status (source)
/// (c) 2018 Jani Nykänen

#include "status.h"

#include "../engine/graphics.h"

// Stage name size
#define STAGE_NAME_SIZE 64
// Turn string size
#define TURN_STRING_SIZE 32

// Victory time max
static const float VIC_TIMER_MAX = 60.0f;

// Font
static BITMAP* bmpFont;
// Key bitmap
static BITMAP* bmpKey;
// Icons bitmap
static BITMAP* bmpIcons;
// Complete bitmap
static BITMAP* bmpComplete;

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

// Victory timer
static float vicTimer;
// Is victory reached
static bool victory;
// Victory phase
static int vicPhase;
// Cursor position
static int cursorPos;


// Update victory
static void update_victory(float tm)
{
    if(vicPhase == 0)
    {
        vicTimer += 1.0f * tm;
        if(vicTimer >= VIC_TIMER_MAX)
        {
            vicTimer = 0.0f;
            ++ vicPhase;
        }
    }
}


// Draw menu
static void draw_menu(int tx, int ty)
{
    const int YOFF = 14;

    fill_rect(tx-20,ty-4,136,32,rgb(85,85,85));

    int x = 0;
    int y = 0;
    set_bitmap_color(bmpFont,rgb(0,0,0));
    for(y = -1; y <= 1; ++ y)
    {
        for(x = -1; x <= 1; ++ x)
        {
            
            if(x == y && x == 0) continue;

            draw_text(bmpFont,(Uint8*)"Stage Selection",-1,tx+x,ty+y,-1,0,false);
            draw_text(bmpFont,(Uint8*)"Play Again",-1,tx+x,ty+y + YOFF,-1,0,false);
        }
    }

    set_bitmap_color(bmpFont,rgb(255,255,255));

    draw_text(bmpFont,(Uint8*)"Stage Selection",-1,tx,ty,-1,0,false);
    draw_text(bmpFont,(Uint8*)"Play Again",-1,tx,ty + YOFF,-1,0,false);
}


// Draw victory
static void draw_victory()
{
    float t = 1.0f;
    if(vicPhase == 0)
    {
        t = 1.0f / VIC_TIMER_MAX * vicTimer;
    }

    int bw = bmpComplete->w;
    int complPos = -bw + (int)floor(t*(bw + 128.0f-bw/2));

    draw_bitmap(bmpComplete,complPos,40,0);

    draw_menu(56,144);
}


// Initialize status
void status_init(ASSET_PACK* ass)
{
    // Load assets
    bmpFont = (BITMAP*)get_asset(ass,"font");
    bmpKey = (BITMAP*)get_asset(ass,"key");
    bmpIcons = (BITMAP*)get_asset(ass,"icons");
    bmpComplete = (BITMAP*)get_asset(ass,"compl");

    // Set default values
    status_reset(false);
}


// Reset status
void status_reset(bool soft)
{
    // Set default values
    keyCount = 0;
    prevKeyCount = 0;
    removingKey = false;
    keyRemovePos = 0.0f;
    vicTimer = 0.0f;
    vicPhase = 0;
    victory = false;
    turnCount = 0;
    cursorPos = 0;

    if(!soft)
    {
        turnTarget = 0;
        snprintf(stageName,STAGE_NAME_SIZE," ");
    }
    else
    {
        snprintf(turnString,TURN_STRING_SIZE,"%d/%d",turnCount,turnTarget);
    }
}


// Update status
void status_update(float tm)
{
    const float REMOVE_SPEED = 1.0f;

    // If victory, no need to update the status, just update
    // the victory screen
    if(victory)
    {
        update_victory(tm);
        return;
    }

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

    // If turn count pass turn target
    if(turnCount > turnTarget)
        set_bitmap_color(bmpFont,rgb(255,0,0));
    draw_text(bmpFont,(Uint8*)turnString,-1,210,5,-1,0,false);

    set_bitmap_color(bmpFont,rgb(255,255,255));

    // Draw victory, if victorous
    if(victory)
    {
        draw_victory();
    }
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


// Activate
void status_activate_victory()
{
    victory = true;
    vicTimer = 0.0f;
    vicPhase = 0;
}


// Is victory
bool status_is_victory()
{
    return victory;
}