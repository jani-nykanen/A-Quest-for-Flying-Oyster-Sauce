/// Stage info (source)
/// (c) 2018 Jani Nykänen

#include "info.h"

#include "SDL2/SDL.h"

#include "../lib/parseword.h"

#include "stdlib.h"

// A list of stages
static STAGE_INFO* stages;
// Stage count (max)
static int stageCount;


// Load stage info
int load_stage_info(int count, const char* path)
{
    stageCount = count;

    // Load word list
    WORDDATA* wd = parse_file(path);
    if(wd == NULL)
    {
        return 1;
    }

    // Allocate memory for the list of stages
    stages = (STAGE_INFO*)malloc(sizeof(STAGE_INFO) * count);
    if(stages == NULL)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,"Error!","Memory allocation error!\n",NULL);
        return 1;
    }

    // Read stage info
    int i = 0;
    int windex = 0;
    for(; i < stageCount; ++ i)
    {
        strcpy(stages[i].name,get_word(wd,windex ++));
        strcpy(stages[i].assetName,get_word(wd,windex ++));
        stages[i].difficulty = (int)strtol(get_word(wd, windex ++),NULL,10);
    }

    destroy_word_data(wd);

    return 0;
}


// Get stage info
STAGE_INFO get_stage_info(int index)
{
    if(index < 0 || index >= stageCount)
    {
        char empty[INFO_STR_MAX];
        STAGE_INFO sinfo;
        strcpy(sinfo.name,empty);
        strcpy(sinfo.assetName,empty);
        sinfo.difficulty = 0;
        return sinfo;
    }
    return stages[index];
}