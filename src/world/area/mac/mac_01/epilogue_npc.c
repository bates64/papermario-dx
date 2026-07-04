#include "mac_01.h"

EvtScript N(EVS_NpcInteract_Kolorado_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Kolorado_Talk, ANIM_Kolorado_Idle, 0, MSG_Outro_003C)
    Return
    End
};

EvtScript N(EVS_NpcInit_Kolorado_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Kolorado_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_KoloradoWife_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_KoloradoWife_Talk, ANIM_KoloradoWife_Idle, 0, MSG_Outro_003D)
    Return
    End
};

EvtScript N(EVS_NpcInit_KoloradoWife_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_KoloradoWife_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_KoopaKoot_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_KoopaKoot_Talk, ANIM_KoopaKoot_Idle, 0, MSG_Outro_003E)
    Return
    End
};

EvtScript N(EVS_NpcInit_KoopaKoot_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_KoopaKoot_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Bobomb_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldBobomb_Blue_Talk, ANIM_WorldBobomb_Blue_Idle, 0, MSG_Outro_004E)
    Return
    End
};

EvtScript N(EVS_NpcInit_Bobomb_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Bobomb_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Koopa_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Koopa_Talk, ANIM_Koopa_Idle, 0, MSG_Outro_004F)
    Return
    End
};

EvtScript N(EVS_NpcInit_Koopa_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Koopa_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Rowf_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Rowf_Talk, ANIM_Rowf_Idle, 0, MSG_Outro_0040)
    Return
    End
};

EvtScript N(EVS_NpcInit_Rowf_Epilogue) = {
    Call(SetNpcPos, NPC_SELF, -225, 0, 320)
    Call(SetNpcYaw, NPC_SELF, 270)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Rowf_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Rhuff_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Rowf_Talk, ANIM_Rowf_Idle, 0, MSG_Outro_0041)
    Return
    End
};

EvtScript N(EVS_NpcInit_Rhuff_Epilogue) = {
    Call(SetNpcScale, NPC_SELF, Float(0.75), Float(0.75), Float(0.75))
    Call(SetNpcPos, NPC_SELF, -250, 0, 295)
    Call(SetNpcYaw, NPC_SELF, 270)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Rhuff_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_01_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_Outro_0050)
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_01_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_01_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_02_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Green_Talk, ANIM_Dryite_Green_Idle, 0, MSG_Outro_0051)
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_02_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_02_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Chanterelle_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Chanterelle_Talk, ANIM_Chanterelle_Idle, 16, MSG_Outro_0052)
    Return
    End
};

EvtScript N(EVS_NpcInit_Chanterelle_Epilogue) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_Chanterelle_Sing)
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Chanterelle_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Poet_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Poet_Talk, ANIM_Musician_Poet_Idle, 16, MSG_Outro_0053)
    Return
    End
};

EvtScript N(EVS_NpcInit_Poet_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Poet_Epilogue)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Composer_Epilogue) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Musician_Composer_Talk, ANIM_Musician_Composer_Idle, 16, MSG_Outro_0054)
    Return
    End
};

EvtScript N(EVS_NpcInit_Composer_Epilogue) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Composer_Epilogue)))
    Return
    End
};

AnimID N(LimitAnims_Kolorado_Epilogue)[] = {
    ANIM_Kolorado_Still,
    ANIM_Kolorado_Idle,
    ANIM_Kolorado_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_KoloradoWife_Epilogue)[] = {
    ANIM_KoloradoWife_Still,
    ANIM_KoloradoWife_Idle,
    ANIM_KoloradoWife_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_KoopaKoot_Epilogue)[] = {
    ANIM_KoopaKoot_Still,
    ANIM_KoopaKoot_Idle,
    ANIM_KoopaKoot_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Koopa_Epilogue)[] = {
    ANIM_Koopa_Still,
    ANIM_Koopa_Idle,
    ANIM_Koopa_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bobomb_Epilogue)[] = {
    ANIM_WorldBobomb_Green_Still,
    ANIM_WorldBobomb_Green_Idle,
    ANIM_WorldBobomb_Green_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_Koopas_Epilogue)[] = {
    {
        .id = NPC_Kolorado,
        .pos = { 60.0f, 0.0f, -120.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Kolorado_Epilogue),
        .settings = &N(NpcSettings_Kolorado),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KOLORADO_ANIMS,
        .limitAnimations = N(LimitAnims_Kolorado_Epilogue),
    },
    {
        .id = NPC_KoloradoWife,
        .pos = { 100.0f, 0.0f, -110.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_KoloradoWife_Epilogue),
        .settings = &N(NpcSettings_KoloradoWife),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KOLORADO_WIFE_ANIMS,
        .limitAnimations = N(LimitAnims_KoloradoWife_Epilogue),
    },
    {
        .id = NPC_KoopaKoot,
        .pos = { -330.0f, 0.0f, 330.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_KoopaKoot_Epilogue),
        .settings = &N(NpcSettings_KoopaKoot),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KOOPA_KOOT_ANIMS,
        .limitAnimations = N(LimitAnims_KoopaKoot_Epilogue),
    },
    {
        .id = NPC_Koopa,
        .pos = { 300.0f, 20.0f, -100.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Koopa_Epilogue),
        .settings = &N(NpcSettings_Koopa),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = KOOPA_ANIMS,
        .limitAnimations = N(LimitAnims_Koopa_Epilogue),
    },
    {
        .id = NPC_Bobomb,
        .pos = { 252.0f, 20.0f, -100.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Bobomb_Epilogue),
        .settings = &N(NpcSettings_Bobomb),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = BOBOMB_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_Bobomb_Epilogue),
    },
};

AnimID N(LimitAnims_Rowf_Epilogue)[] = {
    ANIM_Rowf_Still,
    ANIM_Rowf_Idle,
    ANIM_Rowf_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_RowfAndRhuff_Epilogue)[] = {
    {
        .id = NPC_Rowf,
        .pos = { -213.0f, -54.0f, 256.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Rowf_Epilogue),
        .settings = &N(NpcSettings_Dummy),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Rowf_Idle,
        },
        .limitAnimations = N(LimitAnims_Rowf_Epilogue),
        .tattle = MSG_NpcTattle_Rowf,
    },
    {
        .id = NPC_Rhuff,
        .pos = { -250.0f, 0.0f, 263.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Rhuff_Epilogue),
        .settings = &N(NpcSettings_Dummy),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Rowf_Idle,
        },
        .limitAnimations = N(LimitAnims_Rowf_Epilogue),
        .tattle = MSG_NpcTattle_Rhuff,
    },
};

AnimID N(LimitAnims_Dryite_Epilogue)[] = {
    ANIM_Dryite_Green_Still,
    ANIM_Dryite_Green_Idle,
    ANIM_Dryite_Green_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_Dryites_Epilogue)[] = {
    {
        .id = NPC_Dryite_01,
        .pos = { -10.0f, 0.0f, 360.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Dryite_01_Epilogue),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Dryite_Epilogue),
    },
    {
        .id = NPC_Dryite_02,
        .pos = { 25.0f, 0.0f, 300.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Dryite_02_Epilogue),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Dryite_Epilogue),
    },
};

AnimID N(LimitAnims_Chanterelle_Epilogue)[] = {
    ANIM_Chanterelle_Still,
    ANIM_Chanterelle_Idle,
    ANIM_Chanterelle_Sing,
    ANIM_Chanterelle_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Poet_Epilogue)[] = {
    ANIM_Musician_Poet_Still,
    ANIM_Musician_Poet_Idle,
    ANIM_Musician_Poet_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_Artists_Epilogue)[] = {
    {
        .id = NPC_Chanterelle,
        .pos = { 260.0f, 20.0f, 560.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Chanterelle_Epilogue),
        .settings = &N(NpcSettings_Chanterelle),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = CHANTERELLE_ANIMS,
        .limitAnimations = N(LimitAnims_Chanterelle_Epilogue),
        .tattle = MSG_NpcTattle_PopDiva_CantSing,
    },
    {
        .id = NPC_Poet,
        .pos = { 230.0f, 20.0f, 500.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Poet_Epilogue),
        .settings = &N(NpcSettings_MusicianPoet),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = MUSICIAN_POET_ANIMS,
        .limitAnimations = N(LimitAnims_Poet_Epilogue),
        .tattle = MSG_NpcTattle_MasterPoet,
    },
    {
        .id = NPC_Composer,
        .pos = { 300.0f, 20.0f, 500.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Composer_Epilogue),
        .settings = &N(NpcSettings_MusicianComposer),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = MUSICIAN_COMPOSER_ANIMS,
        .limitAnimations = N(LimitAnims_Poet_Epilogue),
        .tattle = MSG_NpcTattle_Composer,
    },
};

NpcGroupList N(EpilogueNPCs) = {
    NPC_GROUP(N(NpcData_Koopas_Epilogue)),
    NPC_GROUP(N(NpcData_RowfAndRhuff_Epilogue)),
    NPC_GROUP(N(NpcData_Dryites_Epilogue)),
    NPC_GROUP(N(NpcData_Artists_Epilogue)),
    NPC_GROUP(N(NpcData_Townsfolk)),
    {}
};
