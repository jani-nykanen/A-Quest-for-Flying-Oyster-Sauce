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
        printf("Existing save data not found.\n");
        return 0;
    }

    // Read stage data
    fread(&saveData.stages,STAGE_COUNT,1,f);

    fclose(f);

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

    fwrite(&saveData.stages,STAGE_COUNT,1,f);
    fclose(f);
    
    return 0;
}