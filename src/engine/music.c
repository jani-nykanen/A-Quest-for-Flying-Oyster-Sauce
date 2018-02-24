/// Music (source)
/// (c) 2018 Jani Nykänen

#include "music.h"

#include "SDL2/SDL.h"

#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"


// Global music volume
static int globalMusicVol;
// Is music playing
static bool playing;
// Music enabled
static bool musicEnabled;
// Old volume
static float oldVol;


// Init music
int init_music()
{
    globalMusicVol = 100;
    playing = false;
    musicEnabled = true;
    oldVol = 1.0f;

    // Init formats
    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(flags);
    if( (initted&flags) != flags) 
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Failed to init audio!\n",NULL);
        return 0;
    }

    // Open audio
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512)==-1) 
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Failed to open audio!\n",NULL);
        return 1;
    }

    return 0;
}   


// Load music
MUSIC* load_music(const char* path)
{
    MUSIC* m = (MUSIC*)malloc(sizeof(MUSIC));
    if(m == NULL)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Memory allocation error!\n",NULL);
        return NULL;
    }

    m->data = Mix_LoadMUS(path);
    if(m->data == NULL)
    {
        char err [64];
        snprintf(err,64,"Failed to load a file in %s!",path);

        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!",err,NULL);
        return NULL;
    }
    return m;
}


// Play music
void play_music(MUSIC* mus, float vol, int loops)
{
    if(!musicEnabled) return;

    oldVol = vol;

    float mvol = (float)globalMusicVol / 100.0f;

    int v = (int)(128 * vol * mvol);
    if(v > 128) v = 128;
    if(v < 0) v = 0;

    Mix_HaltMusic();
    Mix_VolumeMusic(v);
    Mix_FadeInMusic(mus->data, loops,1000);

    playing = true;
}


// Destroy music
void destroy_music(MUSIC* m)
{
    if(m == NULL) return;

    Mix_FreeMusic(m->data);
    free(m);
}


// Stop music
void stop_music()
{
    if(!musicEnabled) return;

    Mix_FadeOutMusic(1000);
}


// Fade out
void fade_out_music(int ms)
{
    Mix_FadeOutMusic(ms);
}


// Enable music
void enable_music(bool state)
{
    if(!state)
    {
        Mix_PauseMusic();
        globalMusicVol = 0;
    }
    else
    {
        Mix_ResumeMusic();
        globalMusicVol = 100;
    }
    musicEnabled = state;
    
}


// Set global music volume
void set_global_music_volume(int vol)
{
    float mvol = (float)vol / 100.0f;
    int v = (int)(128 * oldVol * mvol);

    Mix_VolumeMusic(v);

    globalMusicVol = vol;
}


// Return global music volume
int get_global_music_volume()
{
    return globalMusicVol;
}