/// Save data (source)
/// (c) 2018 Jani Nykänen

#include "savedata.h"

#include "malloc.h"
#include "stdio.h"

// Global save data
static SAVEDATA saveData;


// Read save data
int read_save_data(const char* path)
{
    // Clear save data
    int i = 0;
    for(; i < STAGE_COUNT; ++ i)
    {
        saveData.stages[i] = 0;
    }

    // Open file
    FILE* f = fopen(path,"rb");
    if(f == NULL)
    {
        // Create a new save data
        f = fopen(path,"wb");
        if(f == NULL)
        {
            return 1;
        }

        // Save 25 zeros
        Uint8 zero = 0;
        int i = 0;
        for(i = 0; i < STAGE_COUNT; ++ i)
        {
            if(fwrite(&zero,1,1,f) == 0)
            {
                return 1;
            }
            
        }

        return 0;
    }

    // Read stage data
    if(fread(&saveData.stages,STAGE_COUNT,1,f) == 0)
    {
        return 1;
    }

    return 0;
}


// Get global save data
SAVEDATA* get_global_save_data()
{
    return &saveData;
}


// Save global save data
int save_data(const char* path)
{
    FILE* f = fopen(path,"wb");
    if(f == NULL)
    {
        return 1;
    }
    if(fwrite(&saveData.stages,STAGE_COUNT,1,f) == 0)
    {
        return 1;
    }
    return 0;
}