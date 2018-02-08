/// Stage (source)
/// (c) 2018 Jani Nykänen

#include "stage.h"

#include "../engine/graphics.h"
#include "../lib/tmxc.h"

#include "objects.h"

#include "math.h"
#include "stdlib.h"

// Bitmaps
static BITMAP* bmpSky;
static BITMAP* bmpClouds;
static BITMAP* bmpTiles;

// Map
static TILEMAP* mapMain;

// Cloud position
static float cloudPos;
// Lava position
static float lavaPos;


// Is the tile in (x+dx,y+dy) same as in (x,y)
static bool is_same_tile(TILEMAP* t, int l, int id, int x, int y, int dx, int dy)
{
    if(x+dx < 0 || y +dy < 0 || x+dx >= t->width || y+dy >= t->height)
        return true;

    LAYER data = t->layers[l];

    return id == data[(y+dy)*t->width + x + dx];
}


// Draw a piece of tile
static void draw_tile_piece(int tx, int ty, int x, int y)
{
    draw_bitmap_region(bmpTiles,tx*8,ty*8,8,8,x,y,0);
}


// Draw soil tile
static void draw_tile_soil(TILEMAP* t, int x, int y)
{
    POINT t11, t12, t21, t22;

    bool leftGreen = false;
    bool rightGreen = false;

    t11 = point(2,0);
    t12 = point(0,1);
    t21 = point(3,0);
    t22 = point(1,1);

    // Bottom tile is different
    if(!is_same_tile(t,0,1,x,y,0,1))
    {
        t12 = point(10,0);
        t22 = point(11,0);
    }

    // Right tile is different
    if(!is_same_tile(t,0,1,x,y,1,0))
    {
        t21 = point(5,0);
        t22 = point(5,1);

        // Bottom
        if(!is_same_tile(t,0,1,x,y,0,1))
        {
            t22 = point(3,1);
        }
    }

    // Left tile is different
    if(!is_same_tile(t,0,1,x,y,-1,0))
    {
        t11 = point(4,0);
        t12 = point(4,1);

        // Bottom
        if(!is_same_tile(t,0,1,x,y,0,1))
        {
            t12 = point(2,1);
        }
    }

    // Upper tile is different
    if(!is_same_tile(t,0,1,x,y,0,-1))
    {
        t11 = point(0,0);
        t21 = point(1,0);

        // Right
        if(!is_same_tile(t,0,1,x,y,1,0))
        {
            t21 = point(9,1);
            rightGreen = true;
        }

        // Left
        if(!is_same_tile(t,0,1,x,y,-1,0))
        {
            t11 = point(8,1);
            leftGreen = true;
        }
    }

    // Bottom-right corner
    if(!is_same_tile(t,0,1,x,y,1,1) && is_same_tile(t,0,1,x,y,1,0) 
        && is_same_tile(t,0,1,x,y,0,1))
    {
        t22 = point(8,0);
    }

    // Bottom-left corner
    if(!is_same_tile(t,0,1,x,y,-1,1) && is_same_tile(t,0,1,x,y,-1,0) 
        && is_same_tile(t,0,1,x,y,0,1))
    {
        t12 = point(9,0);
    }

    // Top-right corner
    if(!is_same_tile(t,0,1,x,y,1,-1) && is_same_tile(t,0,1,x,y,1,0) 
        && is_same_tile(t,0,1,x,y,0,-1))
    {
        t21 = point(6,1);
    }

    // Top-left corner
    if(!is_same_tile(t,0,1,x,y,-1,-1) && is_same_tile(t,0,1,x,y,-1,0) 
        && is_same_tile(t,0,1,x,y,0,-1))
    {
        t11 = point(7,1);
    }

    // Draw tile pieces
    draw_tile_piece(t11.x,t11.y,x*16,y*16);
    draw_tile_piece(t21.x,t21.y,x*16 + 8,y*16);
    draw_tile_piece(t12.x,t12.y,x*16,y*16 + 8);
    draw_tile_piece(t22.x,t22.y,x*16 + 8,y*16 + 8);

    if(leftGreen)
        draw_tile_piece(6,0,x*16 - 8,y*16);
    if(rightGreen)
        draw_tile_piece(7,0,x*16 +16,y*16);
}


// Draw vine
static void draw_vine(TILEMAP* t, int x, int y)
{
    int sx1 = 96;
    int sx2 = 96;
    int sy1 = 0;
    int sy2 = 8;

    // Above
    if(!is_same_tile(t,0,2,x,y,0,-1) && !is_same_tile(t,0,1,x,y,0,-1))
    {
        sx1 += 16;
    }

    // Below
    if(!is_same_tile(t,0,2,x,y,0,1) && !is_same_tile(t,0,1,x,y,0,1))
    {
        sx2 += 16;
    }

    // Upper part
    draw_bitmap_region(bmpTiles,sx1,sy1,16,8,x*16,y*16,0);
    // Bottom part
    draw_bitmap_region(bmpTiles,sx2,sy2,16,8,x*16,y*16 + 8,0);
}


// Draw spikes
static void draw_spikes(TILEMAP* t, int x, int y)
{
    draw_bitmap_region(bmpTiles,144,0,16,8,x*16,y*16,0);

    // Left
    if(!is_same_tile(t,0,4,x,y,-1,0) && !is_same_tile(t,0,1,x,y,-1,0))
    {
        draw_bitmap_region(bmpTiles,144,8,8,8,x*16,y*16 + 8,0);
    }
    else
    {
        if(is_same_tile(t,0,4,x,y,-1,0))
            draw_bitmap_region(bmpTiles,144,8,8,8,x*16,y*16 + 8,0);
        else
            draw_bitmap_region(bmpTiles,160,0,8,8,x*16,y*16 + 8,0);
    }

    // Right
    if(!is_same_tile(t,0,4,x,y,1,0) && !is_same_tile(t,0,1,x,y,1,0))
    {
        draw_bitmap_region(bmpTiles,152,8,8,8,x*16 + 8,y*16 + 8,0);
    }
    else
    {
        draw_bitmap_region(bmpTiles,168,8,8,8,x*16+8,y*16 + 8,0);
    }
}


// Draw lava
static void draw_lava(TILEMAP* t, int x, int y)
{
    int i = 0;

    int lpos = (int)round(lavaPos) % 16;
    int lposy = (int)round(sin(lavaPos / 2.0f) * 1.0f) +1;
    int sy = (!is_same_tile(t,0,3,x,y,0,-1)) ? 0 : 8;
    
    draw_bitmap_region(bmpTiles,128,8,16,8,x*16, y*16+8, 0);
    for(; i < 2; ++ i)
    {
        draw_bitmap_region(bmpTiles,128,sy,16,8,x*16 + lpos + i*16, y*16 + lposy, 0);
    }
}


// Draw an "other kind of" solid object, like lock
static void draw_other_solid(TILEMAP* t,int id, int x, int y, int dx, int dy)
{
    POINT t11, t12, t21, t22;

    t11 = point(6+dx,dy);
    t12 = point(6+dx,dy+1);
    t21 = point(6+dx+1,dy);
    t22 = point(6+dx+1,dy+1);

    // Free directions
    bool bottom = (!is_same_tile(t,0,1,x,y,0,1) && !is_same_tile(t,0,id,x,y,0,1));
    bool top = (!is_same_tile(t,0,1,x,y,0,-1) && !is_same_tile(t,0,id,x,y,0,-1));
    bool left = (!is_same_tile(t,0,1,x,y,-1,0) && !is_same_tile(t,0,id,x,y,-1,0));
    bool right = (!is_same_tile(t,0,1,x,y,1,0) && !is_same_tile(t,0,id,x,y,1,0));

    // Bottom
    if(bottom)
    {
        if(left)
            t12 = point(dx,dy+1);
        else
            t12 = point(dx+4,dy+1);

        if(right)
            t22 = point(dx+1,dy+1);
        else
            t22 = point(dx+5,dy+1);
    }
    else
    {
        if(left)
            t12 = point(dx+2,dy+1);

        if(right)
            t22 = point(dx+3,dy+1);
    }

    // Top
    if(top)
    {
        if(left)
            t11 = point(dx,dy);
        else
            t11 = point(dx+4,dy);

        if(right)
            t21 = point(dx+1,dy);
        else
            t21 = point(dx+5,dy);
    }
    else
    {
        if(left)
            t11 = point(dx+2,dy);

        if(right)
            t21 = point(dx+3,dy);
    }

    // Draw tile pieces
    draw_tile_piece(t11.x,t11.y,x*16,y*16);
    draw_tile_piece(t21.x,t21.y,x*16 + 8,y*16);
    draw_tile_piece(t12.x,t12.y,x*16,y*16 + 8);
    draw_tile_piece(t22.x,t22.y,x*16 + 8,y*16 + 8);
}


// Draw map
static void draw_map(TILEMAP* t)
{
    int x = 0;
    int y = 0;
    int id = 0;
    LAYER data = t->layers[0];

    // Draw only lava
    for(y=0; y < t->height; ++ y)
    {
        for(x=0; x < t->width; ++ x)
        {
            id = data[y*t->width + x];
            if(id != 3) continue;
            draw_lava(t, x,y);
        }
    }

    // Draw the rest of tiles
    for(y=0; y < t->height; ++ y)
    {
        for(x=0; x < t->width; ++ x)
        {
            id = data[y*t->width + x];
            if(id == 0) continue;

            if(id == 1)
            {
                draw_tile_soil(t, x,y);
            }
            else if(id == 2)
            {
                draw_vine(t, x,y);
            }
            else if(id == 4)
            {
                draw_spikes(t,x,y);
            }
            else if(id == 5)
            {
                draw_other_solid(t,5,x,y,0,2);
            }
            else if(id == 6)
            {
                draw_other_solid(t,6,x,y,22,0);
            }
        }
    }
}


// Draw stage background
static void draw_background()
{
    int i = 0;

    draw_bitmap(bmpSky,0,0,0);
    for(; i < 2; ++ i)
    {
        draw_bitmap(bmpClouds,(int)round(cloudPos + i * 256),192 - bmpClouds->h,0);
    }
}


// Create objects from the tilemap
static void create_objects(TILEMAP* t)
{
    int x = 0;
    int y = 0;
    int id = 0;
    LAYER data = t->layers[0];

    // Draw only lava
    for(y=0; y < t->height; ++ y)
    {
        for(x=0; x < t->width; ++ x)
        {
            id = data[y*t->width + x];
            if(id >= 8)
            {
                obj_add(id,x,y);
            }
        }
    }
}


// Initialize stage
void stage_init(ASSET_PACK* ass)
{
    // Get assets
    bmpSky = (BITMAP*)get_asset(ass,"sky1");
    bmpClouds = (BITMAP*)get_asset(ass,"clouds1");
    bmpTiles = (BITMAP*)get_asset(ass,"tiles1");
    mapMain = (TILEMAP*)get_asset(ass,"testMap");

    // Create objects
    create_objects(mapMain);

    // Set variables to their default values
    cloudPos = 0.0f;
    lavaPos = 0.0f;
}


// Update stage
void stage_update(float tm)
{
    const float CLOUD_SPEED = 0.5f;
    const float LAVA_SPEED = 0.125f;

    // Update cloud position
    cloudPos -= CLOUD_SPEED * tm;
    if(cloudPos <= -bmpClouds->w)
    {
        cloudPos += bmpClouds->w;
    }

    // Update lava position
    lavaPos -= LAVA_SPEED * tm;
    if(lavaPos <= -M_PI*2 * 16.0f)
    {
        lavaPos += M_PI*2 * 16.0f;
    }
}


// Draw stage
void stage_draw()
{
    draw_background();
    draw_map(mapMain);
}