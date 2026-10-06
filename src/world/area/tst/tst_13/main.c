#include "tst_13.h"

void mdl_project_tex_coords(s32 modelID, Gfx* destGfx, Matrix4f destMtx, void* destVertices);

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

EntryList Entrances = {
    [tst_13_ENTRY_0]    {    0.0,    0.0,  100.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
};

#include "world/common/prefab/BetaFloorPanels.inc.c"

EvtScript EVS_NpcCreate_00 = {
    Return
    End
};

EvtScript EVS_NpcInteract_00 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldBombette_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_01 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldParakarry_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_02 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldBow_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_03 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldWatt_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_04 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldSushie_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_05 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldLakilester_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_06 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldLakilester_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_07 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldLakilester_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_08 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldGoombario_Idle)
    Return
    End
};

EvtScript EVS_NpcInteract_09 = {
    Call(SetNpcSprite, NPC_SELF, ANIM_WorldKooper_Idle)
    Return
    End
};

NpcSettings NpcSettings_00 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_00,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_01 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_01,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_02 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_02,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_03 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_03,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_04 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_04,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_05 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_05,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_06 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_06,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_07 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_07,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_08 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_08,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcSettings NpcSettings_09 = {
    .defaultAnim = ANIM_Koopa_Idle,
    .height = 24,
    .radius = 24,
    .onCreate = &EVS_NpcCreate_00,
    .onInteract = &EVS_NpcInteract_09,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcData NpcData_Testing[] = {
    {
        .id = NPC_00,
        .pos = { 0.0f, 0.0f, 0.0f },
        .yaw = 0,
        .settings = &NpcSettings_00,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_01,
        .pos = { 20.0f, 0.0f, 20.0f },
        .yaw = 0,
        .settings = &NpcSettings_01,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_02,
        .pos = { 40.0f, 0.0f, 40.0f },
        .yaw = 0,
        .settings = &NpcSettings_02,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_03,
        .pos = { 60.0f, 0.0f, 60.0f },
        .yaw = 0,
        .settings = &NpcSettings_03,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_04,
        .pos = { 80.0f, 0.0f, 80.0f },
        .yaw = 0,
        .settings = &NpcSettings_04,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_05,
        .pos = { 100.0f, 0.0f, 100.0f },
        .yaw = 0,
        .settings = &NpcSettings_05,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_06,
        .pos = { 120.0f, 0.0f, 120.0f },
        .yaw = 0,
        .settings = &NpcSettings_06,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_07,
        .pos = { 140.0f, 0.0f, 140.0f },
        .yaw = 0,
        .settings = &NpcSettings_07,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_08,
        .pos = { 160.0f, 0.0f, 160.0f },
        .yaw = 0,
        .settings = &NpcSettings_08,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
    {
        .id = NPC_09,
        .pos = { 180.0f, 0.0f, 180.0f },
        .yaw = 0,
        .settings = &NpcSettings_09,
        .flags = COMMON_PASSIVE_FLAGS,
        .animations = {
            .idle = ANIM_Koopa_Idle,
        },
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Testing),
    {}
};

#include "world/area/tst/tst_13/shockwave.vtx.inc.c"
#include "world/area/tst/tst_13/shockwave.gfx.inc.c"

Gfx dummy_gfx[] = {
    gsSPEndDisplayList()
};

s32 BuildGfxCallCount = 0;

void build_gfx_floor(void) {
    Matrix4f sp10;
    Matrix4f sp50;
    f32 x, y, z;

    BuildGfxCallCount++;
    guTranslateF(sp10, gPlayerStatus.pos.x, 0.0f, gPlayerStatus.pos.z);

    x = (sin_rad(BuildGfxCallCount / 50.0f) * 0.5) + 0.5;
    y = SQ(cos_rad(BuildGfxCallCount / 50.0f)) + 0.1;
    z = (sin_rad(BuildGfxCallCount / 50.0f) * 0.5) + 0.5;

    guScaleF(sp50, x, y, z);
    guMtxCatF(sp50, sp10, sp10);
    guMtxF2L(sp10, &gDisplayContext->matrixStack[gMatrixListPos]);
    mdl_project_tex_coords(MODEL_o152, tst_13_shockwave_gfx, sp10, nullptr);

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    mdl_draw_hidden_panel_surface(&gMainGfxPos, 1);
    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gMainGfxPos++, tst_13_shockwave_gfx);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}

s32 BetaPanelData[] = {
    MODEL_point, COLLIDER_point, -35, 0, -45, ITEM_HEART
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    Set(LVar0, Ref(BetaPanelData))
    Exec(EVS_BetaPanel_Setup)
    Call(SetModelCustomGfx, MODEL_o152, CUSTOM_GFX_0, -1)
    Call(SetCustomGfxBuilders, CUSTOM_GFX_0, 0, Ref(build_gfx_floor))
    Return
    End
};
