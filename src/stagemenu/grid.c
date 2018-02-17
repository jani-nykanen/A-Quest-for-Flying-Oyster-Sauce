/// Grid (source)
/// (c) 2018 Jani Nykänen

#include "grid.h"

#include "../engine/graphics.h"
#include "../engine/app.h"
#include "../engine/sample.h"

#include "../vpad.h"
#include "../transition.h"

#include "math.h"
#include "stdio.h"
#include "stdbool.h"

// Bitmaps
static BITMAP* bmpStageButtons;
static BITMAP* bmpBigCursor;

// Sound effects
static SAMPLE* sAccept;
static SAMPLE* sSelect;

// Cursor position
static POINT cursorPos;
// Virtual cursor position
static VEC2 vpos;
// Target position
static VEC2 target;
// Is cursor moving
static bool cursorMoving;
// Cursor wave
static float wave;


// Change to game scene
static void change_to_game()
{
    app_swap_scene("game");
}


// Draw buttons
static void draw_buttons(int dx, int dy)
{
    int dim = 32;

    int x = 0;
    int y = 0;

    // Draw borders
    fill_rect(dx-2,dy-2,dim*5 + 4, dim*5 + 4, rgb(0,0,0));
    fill_rect(dx-1,dy-1,dim*5 + 2, dim*5 + 2, rgb(255,255,255));

    int sh = 0;
    int sw = 0;
    // Draw buttons
    for(; y < 5; ++ y)
    {
        for(x = 0; x < 5; ++ x)
        {
            sh = (x == cursorPos.x && y == cursorPos.y) ? dim : 0;
            sw = (x == 2 && y == 2) ? (dim*3) : 0;

            draw_bitmap_region(
                bmpStageButtons,sw,sh,dim,dim,dx + x*dim, dy + y*dim, 0);
        }
    }
}


// Move coordinate
static void move_coord(float* coord,  float* target, float speed, float tm)
{
    if(*target > *coord)
    {
        *coord += speed * tm;
        if(*coord >= *target)
        {
            coord = target;
        }
    }
    else if(*target < *coord)
    {
        *coord -= speed * tm;
        if(*coord  <= *target)
        {
            coord = target;
        }
    }

}


// Move cursor
static void move_cursor(float tm)
{
    const float DELTA = 4.0f;
    const float SPEED = 8.0f;

    move_coord(&vpos.x,&target.x,SPEED,tm);
    move_coord(&vpos.y,&target.y,SPEED,tm);

    if(fabs(vpos.x-target.x) < DELTA && fabs(vpos.y-target.y) < DELTA)
    {
        vpos = target;
        cursorMoving = false;
    }
}


// Initialize grid
void grid_init(ASSET_PACK* ass)
{
    // Get assets
    bmpStageButtons = (BITMAP*)get_asset(ass,"stageButtons");
    bmpBigCursor = (BITMAP*)get_asset(ass,"bigCursor");

    sSelect = (SAMPLE*)get_asset(ass,"select");
    sAccept = (SAMPLE*)get_asset(ass,"accept");

    // Set default values
    cursorPos = point(0,0);
    vpos = vec2(0,0);
    target = vec2(0,0);
    cursorMoving = false;
    wave = 0.0f;
}


// Update grid
void grid_update(float tm)
{
    const float DELTA = 0.1f;
    const int GRID_COUNT = 5;
    const int DIM = 32;

    // Update wave
    wave += 0.1f * tm;

    // Move cursor virtual position
    if(cursorMoving)
    {
        move_cursor(tm);
        return;
    }

    // Move actual cursor
    VEC2 stick = vpad_get_stick();
    VEC2 delta = vpad_get_delta();
    
    POINT oldPos = cursorPos;
    if(delta.y > DELTA && stick.y > DELTA)
    {
        ++ cursorPos.y;   
        cursorPos.y = cursorPos.y % GRID_COUNT;
    }
    else if(delta.y < -DELTA && stick.y < -DELTA)
    {
        -- cursorPos.y;   
        if(cursorPos.y < 0) cursorPos.y += GRID_COUNT;
    }
    else if(delta.x > DELTA && stick.x > DELTA)
    {
        ++ cursorPos.x;   
        cursorPos.x = cursorPos.x % GRID_COUNT;
    }
    else if(delta.x < -DELTA && stick.x < -DELTA)
    {
        -- cursorPos.x;   
        if(cursorPos.x < 0) cursorPos.x += GRID_COUNT;
    }

    // If moved, set moving
    if(!(oldPos.x == cursorPos.x && oldPos.y == cursorPos.y))
    {
        cursorMoving = true;
        target.x = cursorPos.x * DIM;
        target.y = cursorPos.y * DIM;

        play_sample(sSelect,0.40f);
    }

    // Button pressed
    if(vpad_get_button(0) == PRESSED || vpad_get_button(1) == PRESSED)
    {
        trn_set(FADE_IN,BLACK_VERTICAL,2.0f,change_to_game);

        play_sample(sAccept,0.50f);
    }
}


// Draw grid
void grid_draw()
{
    const int DX = 128-80;
    const int DY = 16;

    // Draw buttons
    draw_buttons(DX,DY);

    // Draw cursor
    draw_bitmap(bmpBigCursor,DX + vpos.x + 16,
        DY + vpos.y + 16 + (int)round(sin(wave) * 2.0f),0);
}