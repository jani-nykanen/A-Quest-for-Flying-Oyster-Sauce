/// Bitmap (header)
/// (c) 2018 Jani Nykänen

#ifndef __BITMAP__
#define __BITMAP__

#include <SDL2/SDL.h>

/// Bitmap type
typedef struct
{
    int w; /// Bitmap width
    int h; /// Bitmap height
    SDL_Texture* tex; /// Texture
}
BITMAP;

/// Load bitmap
/// < path Bitmap path
/// > Returns a new bitmap (pointer)
BITMAP* load_bitmap(const char* path);

/// Destroy bitmap
void destroy_bitmap(BITMAP* bmp);

#endif // __BITMAP__