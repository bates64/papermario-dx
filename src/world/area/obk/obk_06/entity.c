#include "obk_06.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_OBK06_Item_BoosPortrait, false)
        Call(MakeMarkerEntity, $Item_BooPortrait_1)
        Thread
            Loop(0)
                IfNe(GF_OBK06_Item_BoosPortrait, false)
                    Set(GB_StoryProgress, STORY_CH3_GOT_BOO_PORTRAIT)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
        EndThread
    EndIf
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Return
    End
};
