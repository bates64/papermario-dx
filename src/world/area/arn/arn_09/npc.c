#include "arn_09.h"
#include "entity.h"
#include "animation_script.h"

extern AnimScript Entity_ScriptSpring_AnimLaunch;

#include "world/common/npc/TubbasHeart/idle.inc.c"

API_CALLABLE(PlaySpringAnimation) {
    Entity* entity = get_entity_by_index(0);

    if (entity == nullptr) {
        return ApiStatus_BLOCK;
    }

    play_model_animation(entity->virtualModelIndex, Entity_ScriptSpring_AnimLaunch);
    return ApiStatus_DONE2;
}

EvtScript EVS_NpcIdle_TubbasHeart = {
    Call(EnableNpcShadow, NPC_SELF, false)
    Call(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_JumpSad)
    Call(SetNpcJumpscale, NPC_SELF, Float(2.5))
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_TUBBA_HEART_JUMP, SOUND_SPACE_DEFAULT)
    Call(NpcJump0, NPC_SELF, 0, 25, -10, 6 * DT)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_SPRING, SOUND_SPACE_DEFAULT)
    Call(PlaySpringAnimation)
    Call(SetNpcAnimation, NPC_SELF, ANIM_TubbasHeart_JumpSad)
    Call(SetNpcJumpscale, NPC_SELF, Float(2.5))
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_TUBBA_HEART_JUMP, SOUND_SPACE_DEFAULT)
    Call(NpcJump0, NPC_SELF, 0, 200, 0, 15 * DT)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Set(GB_StoryProgress, STORY_CH3_HEART_ESCAPED_WELL)
    Return
    End
};

EvtScript EVS_NpcInit_TubbasHeart = {
    IfNe(GB_StoryProgress, STORY_CH3_HEART_FLED_SECOND_TUNNEL)
        Call(RemoveNpc, NPC_SELF)
    Else
        Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_TubbasHeart))
    EndIf
    Return
    End
};

NpcData NpcData_TubbasHeart = {
    .id = NPC_TubbasHeart,
    .pos = { 0.0f, 25.0f, 0.0f },
    .yaw = 270,
    .init = &EVS_NpcInit_TubbasHeart,
    .settings = &NpcSettings_TubbasHeart,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_DO_NOT_KILL,
    .drops = NO_DROPS,
    .animations = TUBBAS_HEART_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_TubbasHeart),
    {}
};
