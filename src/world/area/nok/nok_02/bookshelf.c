#include "nok_02.h"

#if VERSION_JP
EvtScript EVS_80246E20_9E7260 = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_CH1_0138, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};
#endif

EvtScript EVS_Setup_Bookshelf = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_CH1_00A1, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};
