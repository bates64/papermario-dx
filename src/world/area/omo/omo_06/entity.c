#include "omo_06.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_Mailbag = {
    Set(LVarA, ITEM_MAILBAG)
    Set(GF_OMO06_Chest_Mailbag, true)
    ExecWait(EVS_Chest_GetItem)
    Set(GF_MAC01_MailbagStolen, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_ThunderRage_1)
    Call(MakeMarkerEntity, $Chest_Mailbag)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
