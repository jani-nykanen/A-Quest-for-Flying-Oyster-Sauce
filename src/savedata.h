/// Save data (header)
/// (c) 2018 Jani Nykänen

#ifndef __SAVE_DATA__
#define __SAVE_DATA__

#include "SDL2/SDL.h"

// Let's assume there are only 25 stages
#define STAGE_COUNT 25

/// Save data type
typedef struct
{
    Uint8 stages[STAGE_COUNT];
}
SAVEDATA;

/// Read save data or create default if not exist
/// < path File path
/// > 0 on success, 1 on error
int read_save_data(const char* path);

/// Get global save data
SAVEDATA* get_global_save_data();

/// Save global save data
/// < path File path
int save_data(const char* path);

#endif // __SAVE_DATA__