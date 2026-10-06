#include "end_00.h"
#include "include_asset.h"

#include "../common/Credits.inc.c"

#if VERSION_PAL
#include "credits_title_pal.inc.c"
#include "credits_jobs_pal.inc.c"
#include "credits_names_pal.inc.c"
#else
#include "credits_title.inc.c"
#include "credits_jobs.inc.c"
#include "credits_names.inc.c"
#endif

EvtScript EVS_InitCredits = {
    Call(InitCredits)
    Return
    End
};

EvtScript EVS_ShowCredits_Jobs = {
    Call(ShowCreditList, Ref(Credits_Jobs))
    Return
    End
};

EvtScript EVS_ShowCredits_Names = {
    Call(ShowCreditList, Ref(Credits_Names))
    Return
    End
};

EvtScript EVS_ShowCredits_Title = {
    Call(ShowCreditList, Ref(Credits_Title))
    Return
    End
};
