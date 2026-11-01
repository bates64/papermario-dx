#include "tik_18.h"
#include "entity.h"

API_CALLABLE(WakeSpikedGoomba) {
    Enemy* enemy = get_enemy_safe(NPC_SpikedGloomba);

    if (enemy != nullptr) {
        enemy->varTable[0] = true;
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_OnBreakBlock = {
    Call(WakeSpikedGoomba)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenYellowBlock_SuperShroom_1)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Call(MakeMarkerEntity, $BrickBlock_5)
    Call(MakeMarkerEntity, $BrickBlock_6)
    Return
    End
};
