#include "tst_03.h"
#include "world/area/tst/tst_02.h"
#include "world/area/tst/tst_04.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};

EvtScript EVS_GotoMap_tst_02_1 = {
    Call(GotoMap, $tst_02.EntityTest)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tst_04_0 = {
    Call(GotoMap, $tst_04.EntityTest)
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_GotoMap_tst_02_1, TRIGGER_WALL_PUSH, COLLIDER_deilitw, 1, 0)
    BindTrigger(EVS_GotoMap_tst_04_0, TRIGGER_WALL_PUSH, COLLIDER_deilite, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_puku, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_pukut, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_puku,  COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_pukut, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o264, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o265, SURFACE_TYPE_SPIKES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o236, SURFACE_TYPE_LAVA)
    Return
    End
};
