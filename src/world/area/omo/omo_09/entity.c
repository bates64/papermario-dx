#include "omo_09.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_Dictionary = {
    Set(LVarA, ITEM_DICTIONARY)
    Set(GF_OMO09_Chest_Dictionary, true)
    ExecWait(EVS_Chest_GetItem)
    Set(GF_MAC00_DictionaryStolen, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $Item_Coin_4)
    Call(MakeMarkerEntity, $Item_Coin_5)
    Call(MakeMarkerEntity, $Item_Coin_6)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Call(MakeMarkerEntity, $Item_Coin_7)
    Call(MakeMarkerEntity, $Item_Coin_8)
    Call(MakeMarkerEntity, $Item_Coin_9)
    Call(MakeMarkerEntity, $Item_Coin_10)
    Call(MakeMarkerEntity, $Item_Coin_11)
    Call(MakeMarkerEntity, $Item_Coin_12)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(UseDynamicShadow, true)
    Call(MakeMarkerEntity, $Chest_Dictionary)
    IfEq(GF_OMO09_Defeated_MysteryNoteThief, true)
        IfEq(GF_OMO09_Item_MysteryNote, false)
            Call(MakeMarkerEntity, $Item_MysteryNote_1)
        EndIf
    EndIf
    Return
    End
};
