/// Graphics (header)
/// (c) 2018 Jani Nykänen

#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "stdbool.h"

#include "bitmap.h"
#include "vector.h"

/// Flipping enumerations
enum
{
    FLIP_NONE = 0,
    FLIP_HORIZONTAL = 1,
    FLIP_VERTICAL = 2,
    FLIP_BOTH = 3,
};

/// Initialize graphics
void init_graphics();

/// Set the global renderer
/// < rend Renderer
void set_global_renderer(SDL_Renderer* rend);

/// Returns the global renderer
SDL_Renderer* get_global_renderer();

/// Clear screen
/// < r Red
/// < g Green
/// < b Blue
void clear(unsigned char r, unsigned char g, unsigned char b);

/// Set window dimensions
/// < w Width
/// < h Height
void set_dimensions(int w, int h);

/// Returns window dimensions
/// > Window dimensions
SDL_Point get_dimensions();

/// Draw a non-scaled bitmap
/// < b Bitmap to be drawn
/// < dx X coordinate
/// < dy Y coordinate
/// < flip Flip
void draw_bitmap(BITMAP* b, int dx, int dy, int flip);

/// Draw a scaled bitmap
/// < b Bitmap to be drawn
/// < dx X coordinate
/// < dy Y coordinate
/// < sx Horizontal scale
/// < sy Vertical scale
/// < flip Flip
void draw_scaled_bitmap(BITMAP* b, int dx, int dy, float sx, float sy, int flip);

/// Draw a bitmap region
/// < b Bitmap to be drawn
/// < sx Source X
/// < sy Source Y
/// < sw Source W
/// < sh Source H
/// < dx X coordinate
/// < dy Y coordinate
/// < flip Flip
void draw_bitmap_region(BITMAP* b, int sx, int sy, int sw, int sh, int dx, int dy, int flip);

/// Draw text using a bitmap font
/// < b Bitmap font
/// < text Text
/// < len Text length
/// < dx Destination x
/// < dy Destination y
/// < xoff X offset
/// < yoff Y offset
/// < center Center text
void draw_text(BITMAP* b, Uint8* text, int len, int dx, int dy, int xoff, int yoff, bool center);

/// Draw text with black borders using a bitmap font
/// < b Bitmap font
/// < text Text
/// < len Text length
/// < dx Destination x
/// < dy Destination y
/// < xoff X offset
/// < yoff Y offset
/// < center Center text
void draw_text_with_borders(BITMAP* b, Uint8* text, int len, int dx, int dy, int xoff, int yoff, bool center);

/// Draw a filled rectangle
/// < dx X coordinate
/// < dy Y coordinate
/// < w Width
/// < h Height
/// < c Color
void fill_rect(int x, int y, int w, int h, COLOR c);

/// Set bitmap drawing color
/// < b Bitmap
/// < c Color
void set_bitmap_color(BITMAP* b, COLOR c);

/// Translate graphics
/// < x Horizontal translation
/// < y Vertical translation
void translate(int x, int y);

#endif // __GRAPHICS__
