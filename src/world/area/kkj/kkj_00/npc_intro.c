#include "kkj_00.h"

EvtScript EVS_NpcIdle_RussT_Intro = {
    Loop(0)
        Call(GetSelfVar, 1, LVar0)
        IfEq(LVar0, 0)
            Call(SetNpcAnimation, NPC_RussT_01, ANIM_RussT_Talk)
            Call(SetSelfVar, 1, 1)
        Else
            Call(SetNpcAnimation, NPC_ShiverToad_01, ANIM_ShiverToad_Green_Talk)
            Call(SetSelfVar, 1, 0)
        EndIf
        Call(RandInt, 60, LVar0)
        Add(LVar0, 30)
        Wait(LVar0)
        Call(SetNpcAnimation, NPC_RussT_01, ANIM_RussT_Idle)
        Call(SetNpcAnimation, NPC_ShiverToad_01, ANIM_ShiverToad_Green_Idle)
        Wait(10)
    EndLoop
    End
};

EvtScript EVS_NpcIdle_Toadette_01_Intro = {
    Loop(0)
        Call(GetSelfVar, 1, LVar0)
        IfEq(LVar0, 0)
            Call(SetNpcAnimation, NPC_Toadette_01, ANIM_Toadette_Pink_Talk)
            Call(SetSelfVar, 1, 1)
        Else
            Call(SetNpcAnimation, NPC_Toadette_02, ANIM_Toadette_Green_Talk)
            Call(SetSelfVar, 1, 0)
        EndIf
        Call(RandInt, 60, LVar0)
        Add(LVar0, 30)
        Wait(LVar0)
        Call(SetNpcAnimation, NPC_Toadette_01, ANIM_Toadette_Pink_Idle)
        Call(SetNpcAnimation, NPC_Toadette_02, ANIM_Toadette_Green_Idle)
        Wait(10)
    EndLoop
    End
};

EvtScript EVS_NpcIdle_Toad_01_Intro = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Intro.index)
        Call(WaitForPlayerInputEnabled)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(AwaitPlayerLeave, LVar0, LVar2, 100)
        Wait(50)
        Call(SetNpcSpeed, NPC_Toad_01, 2.0)
        Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Walk)
        Call(NpcMoveTo, NPC_Toad_01, 60, 320, 0)
        Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Idle)
    EndIf
    Loop(0)
        Call(GetSelfVar, 1, LVar0)
        IfEq(LVar0, 0)
            Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Talk)
            Call(SetSelfVar, 1, 1)
        Else
            Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_Talk)
            Call(SetSelfVar, 1, 0)
        EndIf
        Call(RandInt, 60, LVar0)
        Add(LVar0, 30)
        Wait(LVar0)
        Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_Idle)
        Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Idle)
        Wait(10)
    EndLoop
    End
};

EvtScript EVS_NpcIdle_Toad_03_Intro = {
    Loop(0)
        Wait(150)
        Loop(2)
            Call(InterpNpcYaw, NPC_SELF, 90, 7)
            Wait(20)
            Call(InterpNpcYaw, NPC_SELF, 270, 7)
            Wait(20)
        EndLoop
    EndLoop
    Return
    End
};

EvtScript EVS_NpcInteract_Luigi_Intro = {
    Call(EnableNpcAI, NPC_Toad_01, false)
    Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_Idle)
    Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Luigi_Talk, ANIM_Luigi_Idle, 16, MSG_Intro_0025)
    Call(EnableNpcAI, NPC_Toad_01, true)
    Return
    End
};

EvtScript EVS_NpcInteract_Toad_01_Intro = {
    Call(SetNpcAnimation, NPC_Toad_01, ANIM_Toad_Red_Idle)
    Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 16, MSG_Intro_0029)
    Return
    End
};

EvtScript EVS_NpcInteract_Toad_02_Intro = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 16, MSG_Intro_002A)
    Return
    End
};

EvtScript EVS_NpcInteract_Toad_03_Intro = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toad_Yellow_Talk, ANIM_Toad_Yellow_Idle, 0, MSG_Intro_002B)
    Return
    End
};

EvtScript EVS_NpcInteract_Toadette_01_Intro = {
    Call(SetNpcAnimation, NPC_Toadette_01, ANIM_Toadette_Pink_Idle)
    Call(SetNpcAnimation, NPC_Toadette_02, ANIM_Toadette_Green_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 16, MSG_Intro_002C)
    Return
    End
};

EvtScript EVS_NpcInteract_Toadette_02_Intro = {
    Call(EnableNpcAI, NPC_Toadette_01, false)
    Call(SetNpcAnimation, NPC_Toadette_02, ANIM_Toadette_Green_Idle)
    Call(SetNpcAnimation, NPC_Toadette_01, ANIM_Toadette_Pink_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_Toadette_Green_Talk, ANIM_Toadette_Green_Idle, 16, MSG_Intro_002D)
    Call(EnableNpcAI, NPC_Toadette_01, true)
    Return
    End
};

EvtScript EVS_NpcInteract_RussT_Intro = {
    Call(SetNpcAnimation, NPC_ShiverToad_01, ANIM_ShiverToad_Green_Idle)
    Call(SetNpcAnimation, NPC_RussT_01, ANIM_RussT_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_RussT_Talk, ANIM_RussT_Idle, 16, MSG_Intro_0027)
    Return
    End
};

EvtScript EVS_NpcInteract_ShiverToad_Intro = {
    Call(EnableNpcAI, NPC_RussT_01, false)
    Call(SetNpcAnimation, NPC_RussT_01, ANIM_RussT_Idle)
    Call(SetNpcAnimation, NPC_ShiverToad_01, ANIM_ShiverToad_Green_Idle)
    Wait(10)
    Call(SpeakToPlayer, NPC_SELF, ANIM_ShiverToad_Green_Talk, ANIM_ShiverToad_Green_Idle, 16, MSG_Intro_0028)
    Call(EnableNpcAI, NPC_RussT_01, true)
    Return
    End
};

EvtScript EVS_NpcInteract_Penguin_01_Intro = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Penguin_Talk, ANIM_Penguin_Idle, 0, MSG_Intro_0030)
    Return
    End
};

EvtScript EVS_NpcInteract_ToadGuard_01_Intro = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ToadGuard_Red_Talk, ANIM_ToadGuard_Red_Idle, 16, MSG_Intro_002E)
    Return
    End
};

EvtScript EVS_NpcInteract_ToadGuard_02_Intro = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_ToadGuard_Blue_Talk, ANIM_ToadGuard_Blue_Idle, 16, MSG_Intro_002F)
    Return
    End
};

EvtScript EVS_NpcInit_Luigi_Intro = {
    Call(SetNpcCollisionSize, NPC_SELF, 46, 26)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Intro.index)
        Call(SetNpcPos, NPC_SELF, 0, 0, 580)
        Call(SetNpcYaw, NPC_SELF, 0)
    Else
        Call(SetNpcPos, NPC_SELF, 20, 0, 320)
        Call(SetNpcYaw, NPC_SELF, 90)
    EndIf
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Luigi_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Toad_01_Intro = {
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Intro.index)
        Call(SetNpcPos, NPC_SELF, 60, 0, 320)
        Call(SetNpcYaw, NPC_SELF, 270)
    EndIf
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Toad_01_Intro)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toad_01_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Toad_02_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toad_02_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Toad_03_Intro = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Toad_03_Intro)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toad_03_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Toadette_01_Intro = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Toadette_01_Intro)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toadette_01_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Toadette_02_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toadette_02_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_RussT_Intro = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_RussT_Intro)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_RussT_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_ShiverToad_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ShiverToad_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_Penguin_01_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Penguin_01_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_ToadGuard_01_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ToadGuard_01_Intro)
    Return
    End
};

EvtScript EVS_NpcInit_ToadGuard_02_Intro = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ToadGuard_02_Intro)
    Return
    End
};

NpcData NpcData_Characters_Intro[] = {
    {
        .id = NPC_Luigi,
        .pos = $Luigi.pos,
        .yaw = $Luigi.yaw,
        .init = &EVS_NpcInit_Luigi_Intro,
        .settings = &NpcSettings_Luigi,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
    {
        .id = NPC_Toad_01,
        .pos = $Toad_01.pos,
        .yaw = $Toad_01.yaw,
        .init = &EVS_NpcInit_Toad_01_Intro,
        .settings = &NpcSettings_Toadette,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
    {
        .id = NPC_Toad_02,
        .pos = $Toad_02.pos,
        .yaw = $Toad_02.yaw,
        .territory = $Toad_02.territory,
        .init = &EVS_NpcInit_Toad_02_Intro,
        .settings = &NpcSettings_Toad_Patrol,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
    },
    {
        .id = NPC_Toad_03,
        .pos = $Toad_03.pos,
        .yaw = $Toad_03.yaw,
        .init = &EVS_NpcInit_Toad_03_Intro,
        .settings = &NpcSettings_Toadette,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
    },
    {
        .id = NPC_Toadette_01,
        .pos = $Toadette_01.pos,
        .yaw = $Toadette_01.yaw,
        .init = &EVS_NpcInit_Toadette_01_Intro,
        .settings = &NpcSettings_Toadette,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
    },
    {
        .id = NPC_Toadette_02,
        .pos = $Toadette_02.pos,
        .yaw = $Toadette_02.yaw,
        .init = &EVS_NpcInit_Toadette_02_Intro,
        .settings = &NpcSettings_Toadette,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TOADETTE_GREEN_ANIMS,
    },
    {
        .id = NPC_RussT_01,
        .pos = $RussT_01.pos,
        .yaw = $RussT_01.yaw,
        .init = &EVS_NpcInit_RussT_Intro,
        .settings = &NpcSettings_RussT,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = RUSS_T_ANIMS,
    },
    {
        .id = NPC_ShiverToad_01,
        .pos = $ShiverToad_01.pos,
        .yaw = $ShiverToad_01.yaw,
        .init = &EVS_NpcInit_ShiverToad_Intro,
        .settings = &NpcSettings_Toad,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = SHIVER_TOAD_GREEN_ANIMS,
    },
    {
        .id = NPC_Penguin_01,
        .pos = $Penguin_01.pos,
        .yaw = $Penguin_01.yaw,
        .init = &EVS_NpcInit_Penguin_01_Intro,
        .settings = &NpcSettings_Penguin,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
    },
    {
        .id = NPC_ToadGuard_01,
        .pos = $ToadGuard_01.pos,
        .yaw = $ToadGuard_01.yaw,
        .init = &EVS_NpcInit_ToadGuard_01_Intro,
        .settings = &NpcSettings_ToadGuard,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
    },
    {
        .id = NPC_ToadGuard_02,
        .pos = $ToadGuard_02.pos,
        .yaw = $ToadGuard_02.yaw,
        .init = &EVS_NpcInit_ToadGuard_02_Intro,
        .settings = &NpcSettings_ToadGuard,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_BLUE_ANIMS,
    },
};

NpcGroupList IntroNPCs = {
    NPC_GROUP(NpcData_Characters_Intro),
    {}
};
