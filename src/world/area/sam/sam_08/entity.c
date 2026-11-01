#include "sam_08.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_SAM08_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(-800, 210, -130, 0)
    Call(MakeMarkerEntity, $Item_Pebble_1)
    IfLt(GB_StoryProgress, STORY_CH7_DEFEATED_FIRST_DUPLIGHOST)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    Return
    End
};
