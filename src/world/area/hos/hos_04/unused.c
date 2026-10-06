#include "hos_04.h"

API_CALLABLE(GetLastEntryID) {
    script->varTable[0] = gGameStatusPtr->entryID;
    return ApiStatus_DONE2;
}

EvtScript EVS_DoNothing = {
    Return
    End
};

EvtScript EVS_SetupUnused = {
    Call(GetLastEntryID)
    Switch(LVar0)
        CaseEq(hos_04_ENTRY_0)
            Set(LVar0, -1)
            Exec(EVS_DoNothing)
    EndSwitch
    Return
    End
};
