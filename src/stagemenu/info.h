/// Stage info (header)
/// (c) 2018 Jani Nykänen

#ifndef __STAGE_INFO__
#define __STAGE_INFO__

#define INFO_STR_MAX 32

/// Stage info type
typedef struct
{
    char name[INFO_STR_MAX];
    char assetName[INFO_STR_MAX];
    int difficulty;
}
STAGE_INFO;

/// Load stage info
/// < count Stage count (max)
/// < path List path
/// > 1 on error, 0 on success
int load_stage_info(int count, const char* path);

/// Get stage info
/// < index Stage index
/// > Stage info
STAGE_INFO get_stage_info(int index);

#endif // __STAGE_INFO__