/// Music (header)
/// (c) 2018 Jani Nykänen

#ifndef __MUSIC__
#define __MUSIC__

#include "SDL2/SDL_mixer.h"

#include "stdbool.h"

/// Music
typedef struct
{
    Mix_Music* data;
}
MUSIC;

/// Init music
int init_music();

/// Load music
/// < path File path
MUSIC* load_music(const char* path);

/// Play music
/// < mus Music to play
/// < vol Volume
/// < loops Loops
void play_music(MUSIC* mus, float vol, int loops);

/// Destroy music
/// < m Music
void destroy_music(MUSIC* m);

/// Stop music
void stop_music();

/// Fade out music
/// < ms Milliseconds
void fade_out_music(int ms);

/// Set global music volume
/// < state State
void enable_music(bool state);

/// Set global music volume
/// < vol Volume in range 0-100
void set_global_music_volume(int vol);

/// Return global music volume
/// > Volume
int get_global_music_volume();

#endif // __MUSIC__