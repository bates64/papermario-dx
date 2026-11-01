#include "isk_09.h"
#include "entity.h"
#include "effects.h"

#include "world/common/entity/Chest.inc.c"

API_CALLABLE(DismissGotItem) {
    Entity* bigChest = get_entity_by_index(script->varTable[0]);
    bigChest->dataBuf.chest->gotItemDone = true;
    return ApiStatus_DONE2;
}

EvtScript EVS_SetChestCollisionClosed = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_takara00, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_takara01, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_SetChestCollisionOpened = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_takara00, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_takara01, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_SetupGiantChest_SuperHammer = {
    IfEq(GF_ISK09_GiantChest, false)
        ExecWait(EVS_SetChestCollisionClosed)
        Loop(0)
            IfEq(GF_ISK09_GiantChest, true)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(PartnerIsFlying, LVar0)
        IfEq(LVar0, true)
            Thread
                Call(DisablePartnerAI, false)
                Call(NpcFlyTo, NPC_PARTNER, -222, -347, -531, 20, 0, EASING_LINEAR)
                Call(InterpNpcYaw, NPC_PARTNER, 70, 0)
                Loop(0)
                    IfEq(GB_StoryProgress, STORY_CH2_GOT_SUPER_HAMMER)
                        BreakLoop
                    EndIf
                    Wait(1)
                EndLoop
                Call(EnablePartnerAI)
            EndThread
        EndIf
        Wait(60)
        Exec(EVS_PlayUpgradeSong)
        Call(ShowMessageAtScreenPos, MSG_Menus_017D, 160, 40)
        Call(DismissGotItem)
        Set(GB_StoryProgress, STORY_CH2_GOT_SUPER_HAMMER)
    EndIf
    ExecWait(EVS_SetChestCollisionOpened)
    Return
    End
};

EvtScript EVS_OpenChest_SlowGo = EVT_OPEN_CHEST(ITEM_SLOW_GO, GF_ISK09_Chest_SlowGo);

EvtScript EVS_SmashBlock_Stone = {
    Set(GF_ISK09_Hammer2Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $GiantChest)
    Exec(EVS_SetupGiantChest_SuperHammer)
    IfEq(GF_ISK09_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    EndIf
    Call(MakeMarkerEntity, $Chest_SlowGo)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_3.pos.x, $FlamePos_3.pos.y, $FlamePos_3.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_4.pos.x, $FlamePos_4.pos.y, $FlamePos_4.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_5.pos.x, $FlamePos_5.pos.y, $FlamePos_5.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_6.pos.x, $FlamePos_6.pos.y, $FlamePos_6.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_7.pos.x, $FlamePos_7.pos.y, $FlamePos_7.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_8.pos.x, $FlamePos_8.pos.y, $FlamePos_8.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_9.pos.x, $FlamePos_9.pos.y, $FlamePos_9.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_10.pos.x, $FlamePos_10.pos.y, $FlamePos_10.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_11.pos.x, $FlamePos_11.pos.y, $FlamePos_11.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_12.pos.x, $FlamePos_12.pos.y, $FlamePos_12.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_13.pos.x, $FlamePos_13.pos.y, $FlamePos_13.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_14.pos.x, $FlamePos_14.pos.y, $FlamePos_14.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_15.pos.x, $FlamePos_15.pos.y, $FlamePos_15.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_16.pos.x, $FlamePos_16.pos.y, $FlamePos_16.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_17.pos.x, $FlamePos_17.pos.y, $FlamePos_17.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_18.pos.x, $FlamePos_18.pos.y, $FlamePos_18.pos.z, 0.3, LVar0)
    Return
    End
};
