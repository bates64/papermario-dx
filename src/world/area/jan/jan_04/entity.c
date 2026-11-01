#include "jan_04.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_VolcanoVase = EVT_OPEN_CHEST(ITEM_VOLCANO_VASE, GF_JAN04_Chest_VolcanoVase);

EvtScript EVS_MakeEntities = {
    Switch(GB_StoryProgress)
        CaseRange(STORY_CH5_BEGAN_PEACH_MISSION, STORY_CH8_REACHED_PEACHS_CASTLE)
            Call(MakeMarkerEntity, $Chest_VolcanoVase)
    EndSwitch
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Return
    End
};
