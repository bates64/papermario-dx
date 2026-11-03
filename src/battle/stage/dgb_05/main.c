#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_PreBattle = {
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
