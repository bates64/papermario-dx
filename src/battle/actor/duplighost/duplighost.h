#pragma once

#include "battle/battle.h"
#include "script_api/battle.h"
#include "effects.h"

// Shared only within this actor overlay; copied forms are not public variants.

enum ActorPartIDs {
    PRT_MAIN        = 1,
    PRT_TARGET      = 2,
    PRT_SPINY       = 3,
    PRT_ZERO        = 0,
};

enum ActorVars {
    AVAR_Copy_ParentActorID     = 0,
    AVAR_Copy_PartnerLevel      = 1,
    AVAR_Kooper_Toppled         = 3,
    AVAR_Kooper_ToppleTurns     = 4,
    AVAR_State                  = 8,
    AVAL_State_ReadyToCopy      = 0, // will copy partner next turn
    AVAL_State_CopiedPartner    = 1, // currently transformed
    AVAL_State_ReadyToTackle    = 2, // will use flying tackle next turn
    AVAL_State_WaitToTackle     = 3, // do nothing this turn and tackle next turn (unused)
};

// These scripts run in the copied actor's context and retain ExecWait locals.
extern EvtScript EVS_Copy_OnDeath;
extern EvtScript EVS_Copy_OnHitElectric;
extern EvtScript EVS_Copy_OnShockHit;
extern EvtScript EVS_Copy_OnShockDeath;

extern Vec3i SummonPos;
extern Formation GoombarioFormation;
extern Formation KooperFormation;
extern Formation BombetteFormation;
extern Formation ParakarryFormation;
extern Formation BowFormation;
extern Formation WattFormation;
extern Formation SushieFormation;
extern Formation LakilesterFormation;
