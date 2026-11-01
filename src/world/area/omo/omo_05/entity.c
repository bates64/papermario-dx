#include "omo_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    IfEq(GF_OMO05_Item_Cookbook, false)
        IfGt(GB_StoryProgress, STORY_CH4_GOT_TAYCE_TS_CAKE)
            Call(MakeMarkerEntity, $Item_Cookbook_1)
        EndIf
    EndIf
    Call(MakeMarkerEntity, $HiddenYellowBlock_DizzyDial_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_SuperSoda_1)
    Return
    End
};
