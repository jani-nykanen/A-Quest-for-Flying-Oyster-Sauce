/// Graphics (source)
/// (c) 2018 Jani Nykänen

#include "graphics.h"

#include "mathext.h"

#include "malloc.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// Global renderer
static SDL_Renderer* grend;
// Window dim
static SDL_Point windowDim;

// Translate x
static int transX;
// Translate y
static int transY;


// Initialize graphics
void init_graphics()
{
    transX = 0;
    transY = 0;
}


// Set global renderer
void set_global_renderer(SDL_Renderer* rend)
{
    grend = rend;
}


// Get grend
SDL_Renderer* get_global_renderer()
{
    return grend;
}


// Clear screen
void clear(unsigned char r, unsigned char g, unsigned char b)
{
    SDL_SetRenderDrawColor(grend, r,g,b, 255);
    SDL_RenderClear(grend);
}


// Set window dimensions
void set_dimensions(int w, int h)
{
    windowDim.x = w;
    windowDim.y = h;
}


// Get window dimensions
SDL_Point get_dimensions()
{
    return windowDim;
}


// Draw a non-scaled bitmap
void draw_bitmap(BITMAP* b, int dx, int dy, int flip)
{
    dx += transX;
    dy += transY;

    SDL_Rect dest;

    dest.x = dx;
    dest.y = dy;
    dest.w = b->w;
    dest.h = b->h;

    SDL_RenderCopyEx(grend,b->tex,NULL,&dest,0,NULL,(SDL_RendererFlip)flip);
}


// Draw scaled bitmap
void draw_scaled_bitmap(BITMAP* b, int dx, int dy, float sx, float sy, int flip)
{
    dx += transX;
    dy += transY;

    SDL_Rect dest;

    dest.x = dx;
    dest.y = dy;
    dest.w = (int)round(b->w * sx);
    dest.h = (int)round(b->h * sy);

    SDL_RenderCopyEx(grend,b->tex,NULL,&dest,0,NULL,(SDL_RendererFlip)flip);
}


// Draw a bitmap region
void draw_bitmap_region(BITMAP* b, int sx, int sy, int sw, int sh, int dx, int dy, int flip)
{
    dx += transX;
    dy += transY;

    SDL_Rect src, dest;

    dest.x = dx;
    dest.y = dy;
    dest.w = sw;
    dest.h = sh;

    src.x = sx;
    src.y = sy;
    src.w = sw;
    src.h = sh;

    SDL_RenderCopyEx(grend,b->tex,&src,&dest,0,NULL,(SDL_RendererFlip)flip);
}


// Draw text using a bitmap font
void draw_text(BITMAP* b, Uint8* text, int len, int dx, int dy, int xoff, int yoff, bool center)
{
    if(len == -1) len = strlen((const char*)text);

    dx += transX;
    dy += transY;

    int x = dx;
    int y = dy;
    int cw = b->w / 16;
    int ch = cw; //  b->h / 16;
    int i=0;
    Uint8 c;
    int sx;
    int sy;

    if(center)
    {
        dx -= (int) ( ((float)len+1)/2.0f * (float)(cw+xoff) );
        x = dx;
    }

    for(; i < len && text[i] != '\0'; i++)
    {
        c = text[i];
        if(c == '\n')
        {
            x = dx;
            y += yoff + ch;
            continue;
        }

        sx = c % 16;
        sy = c / 16;

        draw_bitmap_region(b,sx*cw,sy*ch,cw,ch,x,y,0);

        x += cw + xoff;
    }
}


// Draw text with borders
void draw_text_with_borders(BITMAP* b, Uint8* text, int len, int dx, int dy, int xoff, int yoff, bool center)
{
    int x = -1;
    int y = -1;

    for(; y <= 1; ++ y)
    {
        for(x=-1; x <= 1; ++ x)
        {
            if(x == y && x == 0) continue;

            SDL_SetTextureColorMod(b->tex,0,0,0);
            draw_text(b,text,len,dx +x,dy +y,xoff,yoff,center);
        }
    }

    SDL_SetTextureColorMod(b->tex,b->c.r,b->c.g,b->c.b);
    draw_text(b,text,len,dx,dy,xoff,yoff,center);
}


// Fill rectangle
void fill_rect(int x, int y, int w, int h, COLOR c)
{
    SDL_Rect dst = (SDL_Rect){x,y,w,h};
    SDL_SetRenderDrawColor(grend,c.r,c.g,c.b,c.a);
    SDL_RenderFillRect(grend,&dst);
}


// Set bitmap color
void set_bitmap_color(BITMAP* b, COLOR c)
{
    SDL_SetTextureColorMod(b->tex,c.r,c.g,c.b);
    b->c = c;
}


// Translate graphics
void translate(int x, int y)
{
    transX = x;
    transY = y;
}