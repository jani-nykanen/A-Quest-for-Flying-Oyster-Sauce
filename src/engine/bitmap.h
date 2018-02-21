/// Bitmap (header)
/// (c) 2018 Jani Nykänen

#ifndef __BITMAP__
#define __BITMAP__

#include <SDL2/SDL.h>

/// Color
typedef struct
{
    Uint8 r,g,b,a;
}
COLOR;
#define rgb(r,g,b) (COLOR){r,g,b,255}
#define rgba(r,g,b,a) (COLOR){rg,b,a}

/// Bitmap type
typedef struct
{
    int w; /// Bitmap width
    int h; /// Bitmap height
    SDL_Texture* tex; /// Texture
    COLOR c; /// Color (needed in one place only)
}
BITMAP;

/// Load bitmap
/// < path Bitmap path
/// > Returns a new bitmap (pointer)
BITMAP* load_bitmap(const char* path);

/// Destroy bitmap
void destroy_bitmap(BITMAP* bmp);

#endif // __BITMAP__