
#include "sam_12.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH7_GOT_STAR_STONE)
            Call(MakeMarkerEntity, $Item_StarStone_1)
            Set(MV_StarStoneItemID, LVar0)
        CaseGe(STORY_CH7_GOT_STAR_STONE)
            Call(MakeMarkerEntity, $Item_StarStone_2)
    EndSwitch
    Return
    End
};
