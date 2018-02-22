/// Sample (header)
/// (c) 2018 Jani Nykänen

#ifndef __SAMPLE__
#define __SAMPLE__

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "stdbool.h"

/// Sound effect type
typedef struct
{
    Mix_Chunk* chunk; /// Chunk
    int channel; /// Channel
    bool played; /// Has the sound been played at least once
}
SAMPLE;

/// Init sample
void init_samples();

/// Set global sample volume
/// < vol Volume in range 0-100
void set_global_sample_volume(int vol);

/// Load a sample
/// < path Path
/// > A new sound
SAMPLE* load_sample(const char* path);

/// Play a sample
/// < s Sample to play
/// < vol Volume
void play_sample(SAMPLE* s, float vol);

/// Stop all samples
void stop_all_samples();

/// Destroy a sample & free memory
/// < s Sample to destroy
void destroy_sample(SAMPLE* s);

/// Enable/disable samples
void enable_samples(bool state);

/// Get global sample volume
/// > Volume in range 0-100
int get_global_sample_volume();

#endif // __SAMPLE__