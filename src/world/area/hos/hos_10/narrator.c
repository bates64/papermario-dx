#ifdef VERSION_JP
#include "hos_10.h"

#include "../common/Narrator.inc.c"

#define DURATION_INTRO_MSG (50)

IntroMessage N(JP_IntroMessages_0)[] = {
    { INTRO_MSG_BLANK, 155 },
    { MSG_Intro_JP_001E, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 5                  },
    { MSG_Intro_JP_001F, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 30                 },
    { MSG_Intro_JP_0020, DURATION_INTRO_MSG },
    { MSG_Intro_JP_0021, DURATION_INTRO_MSG },
    {}, // end of list
};

IntroMessage N(JP_IntroMessages_1)[] = {
    { MSG_Intro_JP_006A, 155 },
    { MSG_Intro_JP_0031, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 5                  },
    { MSG_Intro_JP_0032, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 30                 },
    { MSG_Intro_JP_0033, DURATION_INTRO_MSG },
    { MSG_Intro_JP_0034, DURATION_INTRO_MSG },
    {}, // end of list
};

IntroMessage N(JP_IntroMessages_2)[] = {
    { MSG_Intro_JP_006A, 155 },
    { MSG_Intro_JP_0044, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 5                  },
    { MSG_Intro_JP_0045, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 30                 },
    { MSG_Intro_JP_0046, DURATION_INTRO_MSG },
    { MSG_Intro_JP_0047, DURATION_INTRO_MSG },
    {}, // end of list
};

IntroMessage N(JP_IntroMessages_3)[] = {
    { MSG_Intro_JP_006A, 155 },
    { MSG_Intro_JP_0057, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 5                  },
    { MSG_Intro_JP_0058, DURATION_INTRO_MSG },
    { MSG_Intro_JP_006A, 30                 },
    { MSG_Intro_JP_0059, DURATION_INTRO_MSG },
    { MSG_Intro_JP_005A, DURATION_INTRO_MSG },
    {}, // end of list
};

IntroMessage* N(IntroMessages)[] = {
    N(JP_IntroMessages_0),
    N(JP_IntroMessages_1),
    N(JP_IntroMessages_2),
    N(JP_IntroMessages_3)
};

void N(curtain_callback_jp_narration)(void) {
    N(UpdateIntroMessages)(N(IntroMessages));
}

EvtScript N(EVS_SetupNarrator) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(hos_10_ENTRY_3)
            Call(N(SetCurtainCallback), Ref(N(curtain_callback_jp_narration)))
    EndSwitch
    Return
    End
};
#endif
