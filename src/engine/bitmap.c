/// Bitmap (source)
/// (c) 2018 Jani Nykänen

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

#include "bitmap.h"
#include "graphics.h"

#include "stdlib.h"
#include "math.h"
#include "stdio.h"


// Load bitmap
BITMAP* load_bitmap(const char* path)
{
    // Allocate memory
    BITMAP* bmp = (BITMAP*)malloc(sizeof(BITMAP));
    if(bmp == NULL)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Failed to allocate memory for a bitmap!\n",NULL);
        return NULL;
    }

    int comp;
    // Load image
    Uint8* pdata = stbi_load(path,&bmp->w,&bmp->h,&comp,4);
    if(pdata == NULL)
    {
        char err[256];
        snprintf(err,256,"Failed to load a bitmap in %s!\n",path);
         SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!",err,NULL);
        return NULL;
    }

    // Create surface
    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)pdata, bmp->w, bmp->h, 32, bmp->w*4,
                                             0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    if(surf == NULL)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Failed to create a surface!",NULL);
        return NULL;
    }

    // Create texture
    bmp->tex = SDL_CreateTextureFromSurface(get_global_renderer(),surf);
    if(bmp->tex == NULL)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Failed to create a texture from a surface!",NULL);
        return NULL;
    }

    // Free surface
    SDL_FreeSurface(surf);

    // Free data
    stbi_image_free(pdata);

    return bmp;
}


// Destroy bitmap
void destroy_bitmap(BITMAP* bmp)
{
    if(bmp == NULL) return;

    SDL_DestroyTexture(bmp->tex);
    free(bmp);
}
