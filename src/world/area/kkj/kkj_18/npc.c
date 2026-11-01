#include "kkj_18.h"

#include "world/common/npc/GourmetGuy/idle.inc.c"
#include "world/common/npc/Dummy/idle.inc.c"

#include "world/common/enemy/Kammy/idle.inc.c"
#include "world/common/enemy/Koopatrol/idle.inc.c"

EvtScript EVS_NpcIdle_GourmetGuy = {
    Call(WaitForPlayerInputEnabled)
    Exec(EVS_ManageGourmetGuyScenes)
    Return
    End
};

EvtScript EVS_NpcInteract_GourmetGuy_Excited = {
    Call(SpeakToPlayer, NPC_GourmetGuy, ANIM_GourmetGuy_Talk, ANIM_GourmetGuy_Idle, 0, MSG_Peach_00A1)
    Return
    End
};

EvtScript EVS_NpcInteract_GourmetGuy_Scold = {
    Call(SpeakToPlayer, NPC_GourmetGuy, ANIM_GourmetGuy_Talk, ANIM_GourmetGuy_Idle, 0, MSG_Peach_00A6)
    Return
    End
};

EvtScript EVS_NpcInit_GourmetGuy = {
    Call(EnableGroup, MODEL_g12, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_g15, COLLIDER_FLAGS_UPPER_MASK)
    Call(SetNpcPos, NPC_SELF, 120, 0, -20)
    Call(SetNpcYaw, NPC_SELF, 270)
    IfEq(AF_KKJ_FinishedBakingCake, false)
        Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_GourmetGuy_Excited)
    Else
        Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_GourmetGuy_Scold)
    EndIf
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_GourmetGuy)
    Call(SetNpcAnimation, NPC_GourmetGuy_Knife, ANIM_GourmetGuy_Knife)
    Call(SetNpcFlagBits, NPC_GourmetGuy_Knife, NPC_FLAG_INVISIBLE, true)
    Call(EnableNpcShadow, NPC_GourmetGuy_Knife, false)
    Call(SetNpcPos, NPC_GourmetGuy_Knife, 60, 40, -15)
    Call(SetNpcYaw, NPC_GourmetGuy_Knife, 270)
    Call(SetNpcAnimation, NPC_GourmetGuy_Fork, ANIM_GourmetGuy_Fork)
    Call(SetNpcFlagBits, NPC_GourmetGuy_Fork, NPC_FLAG_INVISIBLE, true)
    Call(EnableNpcShadow, NPC_GourmetGuy_Fork, false)
    Call(SetNpcPos, NPC_GourmetGuy_Fork, 125, 40, -15)
    Call(SetNpcYaw, NPC_GourmetGuy_Fork, 270)
    Return
    End
};

AnimID LimitAnims_GourmetGuy[] = {
    ANIM_GourmetGuy_Idle,
    ANIM_GourmetGuy_Walk,
    ANIM_GourmetGuy_Panic,
    ANIM_GourmetGuy_Talk,
    ANIM_GourmetGuy_Eat,
    ANIM_GourmetGuy_SpitOut,
    ANIM_GourmetGuy_Surprise,
    ANIM_GourmetGuy_TalkSurprise,
    ANIM_GourmetGuy_Leap,
    ANIM_GourmetGuy_Inspect,
    ANIM_GourmetGuy_Knife,
    ANIM_GourmetGuy_Fork,
    ANIM_LIST_END
};

AnimID LimitAnims_Kammy[] = {
    ANIM_WorldKammy_Idle,
    ANIM_WorldKammy_Walk,
    ANIM_WorldKammy_Talk,
    ANIM_WorldKammy_Shout,
    ANIM_LIST_END
};

AnimID LimitAnims_Koopatrol[] = {
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_Talk,
    ANIM_WorldKoopatrol_Lift,
    ANIM_WorldKoopatrol_CarryFast,
    ANIM_LIST_END
};

NpcData NpcData_Characters[] = {
    {
        .id = NPC_Kammy,
        .pos = $Kammy.pos,
        .yaw = $Kammy.yaw,
        .settings = &NpcSettings_Kammy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = LimitAnims_Kammy,
    },
    {
        .id = NPC_Koopatrol_01,
        .pos = $Koopatrol_01.pos,
        .yaw = $Koopatrol_01.yaw,
        .settings = &NpcSettings_Koopatrol,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = LimitAnims_Koopatrol,
    },
    {
        .id = NPC_Koopatrol_02,
        .pos = $Koopatrol_02.pos,
        .yaw = $Koopatrol_02.yaw,
        .settings = &NpcSettings_Koopatrol,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = LimitAnims_Koopatrol,
    },
    {
        .id = NPC_GourmetGuy,
        .pos = $GourmetGuy.pos,
        .yaw = $GourmetGuy.yaw,
        .init = &EVS_NpcInit_GourmetGuy,
        .settings = &NpcSettings_GourmetGuy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = GOURMET_GUY_ANIMS,
        .limitAnimations = LimitAnims_GourmetGuy,
    },
    {
        .id = NPC_GourmetGuy_Knife,
        .pos = $GourmetGuy_Knife.pos,
        .yaw = $GourmetGuy_Knife.yaw,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = GOURMET_GUY_ANIMS,
        .limitAnimations = LimitAnims_GourmetGuy,
    },
    {
        .id = NPC_GourmetGuy_Fork,
        .pos = $GourmetGuy_Fork.pos,
        .yaw = $GourmetGuy_Fork.yaw,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = GOURMET_GUY_ANIMS,
        .limitAnimations = LimitAnims_GourmetGuy,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Characters),
    {}
};
