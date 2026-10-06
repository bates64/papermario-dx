#include "lava_piranha.h"
#include "sprite/npc/LavaPiranha.h"
#include "sprite/npc/BattleKolorado.h"
#include "sprite/npc/LavaBud.h"
#include "sprite/npc/PetitPiranha.h"
#include "sprite/player.h"
#include "animation_script.h"
#include "entity.h"
#include "ld_addrs.h"
#include "mapfs/kzn_bt05_shape.h"
#include "include_asset.h"

enum ActorPartIDs {
    PRT_MAIN        = 1,
    PRT_TARGET      = 2,
};

enum ActorVars {
    AVAR_Flags          = 2,
    AVAL_Flag_Kolorado  = 1,
};

enum ActorParams {
    DMG_SPIT_FIRE       = 5,
    DMG_FIRE_BREATH     = 7,
};

// unused data
static Vtx Quad1[] = {
    {{{   -16,     0,     0 }, 0, {     0,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,     0,     0 }, 0, {  1024,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,    39,     0 }, 0, {  1024,  1280 }, {   0,   0,   0, 255 }}},
    {{{   -16,    39,     0 }, 0, {     0,  1280 }, {   0,   0,   0, 255 }}},
};

static Gfx DList1[] = {
    gsSPEndDisplayList(),
};

static EntityModelScript ModelScript1 = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(DList1, 60)
    ems_Restart
    ems_End
    ems_End
};

static Vtx Quad2[] = {
    {{{   -16,     0,     0 }, 0, {     0,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,     0,     0 }, 0, {  1024,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,    39,     0 }, 0, {  1024,  1280 }, {   0,   0,   0, 255 }}},
    {{{   -16,    39,     0 }, 0, {     0,  1280 }, {   0,   0,   0, 255 }}},
};

static Gfx DList2[] = {
    gsSPEndDisplayList(),
};

static EntityModelScript ModelScript2 = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(DList2, 60)
    ems_Restart
    ems_End
    ems_End
};

static Vtx Quad3[] = {
    {{{   -16,     0,     0 }, 0, {     0,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,     0,     0 }, 0, {  1024,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,    39,     0 }, 0, {  1024,  1280 }, {   0,   0,   0, 255 }}},
    {{{   -16,    39,     0 }, 0, {     0,  1280 }, {   0,   0,   0, 255 }}},
};

static Gfx DList3[] = {
    gsSPEndDisplayList(),
};

static EntityModelScript ModelScript3 = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(DList3, 60)
    ems_Restart
    ems_End
    ems_End
};

static Vtx Quad4[] = {
    {{{   -16,     0,     0 }, 0, {     0,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,     0,     0 }, 0, {  1024,     0 }, {   0,   0,   0, 255 }}},
    {{{    15,    39,     0 }, 0, {  1024,  1280 }, {   0,   0,   0, 255 }}},
    {{{   -16,    39,     0 }, 0, {     0,  1280 }, {   0,   0,   0, 255 }}},
};

static Gfx DList4[] = {
    gsSPEndDisplayList(),
};

static EntityModelScript ModelScript4 = {
    ems_SetRenderMode(RENDER_MODE_ALPHATEST)
    ems_Draw(DList4, 60)
    ems_Restart
    ems_End
    ems_End
};

INCLUDE_IMG("battle/area/kzn2/lava_piranha_vine.png", D_8021C940_5A3020);
INCLUDE_PAL("battle/area/kzn2/lava_piranha_vine.pal", D_8021CD40_5A3420);
#include "battle/area/kzn2/lava_piranha_vine.gfx.inc.c"

static EvtScript EVS_Init;
static EvtScript EVS_Idle;
static EvtScript EVS_TakeTurn;
static EvtScript EVS_HandleEvent;
static EvtScript EVS_HandlePhase;
static EvtScript EVS_InitVines;
static EvtScript EVS_Hit;
static EvtScript EVS_Hit_Inner;
static EvtScript EVS_ComboHit;
static EvtScript EVS_BurnHit;
static EvtScript EVS_PlayIdleAnimation;
static EvtScript EVS_Death;
static EvtScript EVS_Attack_SpitFire;
static EvtScript EVS_Attack_FireBreath;
static EvtScript EVS_RemovePetitPiranha;
static EvtScript EVS_Scene_KoloradoToTheRescue;

static s32 FieryDefense[];

API_CALLABLE(GetAnimatedPositionByTreeIndex);
API_CALLABLE(GetAnimatedRotationByTreeIndex);
API_CALLABLE(GetAnimatedModelRootPosition);
API_CALLABLE(SetPartImmunityBits);
API_CALLABLE(DeleteAnimatedModel);

static Formation LeftBudFormation;
static Formation RightBudFormation;

static s32 DefaultAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaPiranha_Idle,
    STATUS_KEY_STONE,     ANIM_LavaPiranha_Still,
    STATUS_KEY_SLEEP,     ANIM_LavaPiranha_Sleep,
    STATUS_KEY_POISON,    ANIM_LavaPiranha_Idle,
    STATUS_KEY_STOP,      ANIM_LavaPiranha_Still,
    STATUS_KEY_STATIC,    ANIM_LavaPiranha_Still,
    STATUS_KEY_PARALYZE,  ANIM_LavaPiranha_Still,
    STATUS_KEY_PARALYZE,  ANIM_LavaPiranha_Still,
    STATUS_KEY_DIZZY,     ANIM_LavaPiranha_Sleep,
    STATUS_END,
};

static s32 FieryAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaPiranha_TongueWag,
    STATUS_KEY_STONE,     ANIM_LavaPiranha_Still,
    STATUS_KEY_SLEEP,     ANIM_LavaPiranha_TongueWag,
    STATUS_KEY_POISON,    ANIM_LavaPiranha_TongueWag,
    STATUS_KEY_STOP,      ANIM_LavaPiranha_Still,
    STATUS_KEY_STATIC,    ANIM_LavaPiranha_Still,
    STATUS_KEY_PARALYZE,  ANIM_LavaPiranha_Still,
    STATUS_KEY_PARALYZE,  ANIM_LavaPiranha_Still,
    STATUS_KEY_DIZZY,     ANIM_LavaPiranha_Dizzy,
    STATUS_END,
};

static s32 StunnedAnims[] = {
    STATUS_KEY_NORMAL,    ANIM_LavaPiranha_Stunned,
    STATUS_KEY_STOP,      ANIM_LavaPiranha_Still,
    STATUS_END,
};

static s32 DefenseTable[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,    0,
    ELEMENT_ICE,      0,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

static s32 FieryDefense[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,   -2,
    ELEMENT_ICE,     -2,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

static s32 StunnedDefense[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_WATER,    0,
    ELEMENT_ICE,      0,
    ELEMENT_FIRE,    99,
    ELEMENT_BLAST,    0,
    ELEMENT_END,
};

static s32 StatusTable[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,              25,
    STATUS_KEY_POISON,              0,
    STATUS_KEY_FROZEN,              0,
    STATUS_KEY_DIZZY,              25,
    STATUS_KEY_UNUSED,              0,
    STATUS_KEY_STATIC,              0,
    STATUS_KEY_PARALYZE,           40,
    STATUS_KEY_SHRINK,              0,
    STATUS_KEY_STOP,               40,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,         -1,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,         -1,
    STATUS_TURN_MOD_UNUSED,         0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,      -1,
    STATUS_TURN_MOD_SHRINK,        -1,
    STATUS_TURN_MOD_STOP,          -2,
    STATUS_END,
};

static ActorPartBlueprint ActorParts[] = {
    {
        .flags = ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 40 },
        .opacity = 255,
        .idleAnimations = DefaultAnims,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -8 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_DEFAULT_TARGET | ACTOR_PART_FLAG_PRIMARY_TARGET,
        .index = PRT_TARGET,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 40 },
        .opacity = 255,
        .idleAnimations = nullptr,
        .defenseTable = DefenseTable,
        .eventFlags = 0,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -8 },
    },
};

OVL_DEF_ACTOR() = {
    .flags = 0,
    .type = ACTOR_TYPE_LAVA_PIRANHA_PHASE_1,
    .level = ACTOR_LEVEL_LAVA_PIRANHA_PHASE_1,
    .maxHP = 40,
    .partCount = ARRAY_COUNT(ActorParts),
    .partsData = ActorParts,
    .initScript = &EVS_Init,
    .statusTable = StatusTable,
    .escapeChance = 0,
    .airLiftChance = 0,
    .hurricaneChance = 0,
    .spookChance = 0,
    .upAndAwayChance = 0,
    .spinSmashReq = 4,
    .powerBounceChance = 70,
    .coinReward = 0,
    .size = { 50, 50 },
    .healthBarOffset = { 20, -10 },
    .statusIconOffset = { 5, 45 },
    .statusTextOffset = { 30, 47 },
};

enum {
    VINE_RENDER_STATE_NONE      = -1,
    VINE_RENDER_STATE_DIRTY     = 0,
    VINE_RENDER_STATE_OK        = 1,
};

// These DMA buffers live as long as the actor overlay and its battle animators.
BSS u8 Vine3Base[0x2000] ALIGNED(8);
BSS u8 Vine2Base[0x3000] ALIGNED(8);
BSS u8 Vine1Base[0x3000] ALIGNED(8);
BSS u8 Vine0Base[0x4000] ALIGNED(8);

typedef struct VineBuffer {
    u8* data;
    u32 capacity;
} VineBuffer;

static const VineBuffer VineBuffers[NUM_VINES] = {
    [VINE_0] = { Vine0Base, sizeof(Vine0Base) },
    [VINE_1] = { Vine1Base, sizeof(Vine1Base) },
    [VINE_2] = { Vine2Base, sizeof(Vine2Base) },
    [VINE_3] = { Vine3Base, sizeof(Vine3Base) },
};

#define VINE_ANIM_ENTRY(name) { world_model_anim_kzn_##name##_ROM_START, world_model_anim_kzn_##name##_ROM_END }

typedef struct VineAnim {
    u8* start;
    u8* end;
} VineAnim;

static const VineAnim VineAnims[] = {
    [VINE_ANIM_BOSS_IDLE]                   VINE_ANIM_ENTRY(00),
    [VINE_ANIM_BOSS_TWITCH]                 VINE_ANIM_ENTRY(01),
    [VINE_ANIM_BOSS_ATTACK]                 VINE_ANIM_ENTRY(02),
    [VINE_ANIM_BOSS_POST_ATTACK]            VINE_ANIM_ENTRY(03),
    [VINE_ANIM_BOSS_STUNNED_HEAVY_HIT]      VINE_ANIM_ENTRY(04),
    [VINE_ANIM_BOSS_STUNNED_LIGHT_HIT]      VINE_ANIM_ENTRY(05),
    [VINE_ANIM_BOSS_HEAVY_HIT]              VINE_ANIM_ENTRY(06),
    [VINE_ANIM_BOSS_LIGHT_HIT]              VINE_ANIM_ENTRY(07),
    [VINE_ANIM_BOSS_STUNNED_DEATH_BEGIN]    VINE_ANIM_ENTRY(08),
    [VINE_ANIM_BOSS_DEATH_BEGIN]            VINE_ANIM_ENTRY(09),
    [VINE_ANIM_BOSS_DEATH_MIDDLE]           VINE_ANIM_ENTRY(0A),
    [VINE_ANIM_BOSS_DEATH_COLLAPSE]         VINE_ANIM_ENTRY(0B),
    [VINE_ANIM_BOSS_EMERGE]                 VINE_ANIM_ENTRY(0C),
    [VINE_ANIM_BOSS_STUN]                   VINE_ANIM_ENTRY(0D),
    [VINE_ANIM_BOSS_RECOVER]                VINE_ANIM_ENTRY(0E),
    [VINE_ANIM_BOSS_DUP_EMERGE]             VINE_ANIM_ENTRY(0F),
    [VINE_ANIM_BOSS_SINK_AWAY]              VINE_ANIM_ENTRY(10),
    [VINE_ANIM_BOSS_TALK]                   VINE_ANIM_ENTRY(11),
    [VINE_ANIM_BUD_ATTACK]                  VINE_ANIM_ENTRY(12),
    [VINE_ANIM_BUD_STUNNED_HEAVY_HIT]       VINE_ANIM_ENTRY(13),
    [VINE_ANIM_BUD_STUNNED_LIGHT_HIT]       VINE_ANIM_ENTRY(14),
    [VINE_ANIM_BUD_HEAVY_HIT]               VINE_ANIM_ENTRY(15),
    [VINE_ANIM_BUD_LIGHT_HIT]               VINE_ANIM_ENTRY(16),
    [VINE_ANIM_BUD_STUNNED_DEATH_BEGIN]     VINE_ANIM_ENTRY(17),
    [VINE_ANIM_BUD_DEATH_BEGIN]             VINE_ANIM_ENTRY(18),
    [VINE_ANIM_BUD_DEATH_MIDDLE]            VINE_ANIM_ENTRY(19),
    [VINE_ANIM_BUD_DEATH_COLLAPSE]          VINE_ANIM_ENTRY(1A),
    [VINE_ANIM_BUD_STUN]                    VINE_ANIM_ENTRY(1B),
    [VINE_ANIM_BUD_EMERGE]                  VINE_ANIM_ENTRY(1C),
    [VINE_ANIM_BUD_RECOVER]                 VINE_ANIM_ENTRY(1D),
    [VINE_ANIM_BUD_TWITCH]                  VINE_ANIM_ENTRY(1E),
    [VINE_ANIM_BUD_IDLE]                    VINE_ANIM_ENTRY(1F),
    [VINE_ANIM_BUD_DUP_EMERGE]              VINE_ANIM_ENTRY(20),
    [VINE_ANIM_BUD_SINK_AWAY]               VINE_ANIM_ENTRY(21),
    [VINE_ANIM_EXTRA_IDLE]                  VINE_ANIM_ENTRY(22),
    [VINE_ANIM_EXTRA_DEATH]                 VINE_ANIM_ENTRY(23),
    [VINE_ANIM_EXTRA_EMERGE]                VINE_ANIM_ENTRY(24),
};

API_CALLABLE(LoadVineAnim) {
    Bytecode* args = script->ptrReadPos;
    s32 animIndex = evt_get_variable(script, *args++);
    s32 vineIndex = evt_get_variable(script, *args++);
    u32 size;

    ASSERT_MSG((u32)animIndex < ARRAY_COUNT(VineAnims), "Invalid vine animation %ld", animIndex);
    ASSERT_MSG((u32)vineIndex < ARRAY_COUNT(VineBuffers), "Invalid vine buffer %ld", vineIndex);
    size = (u32)VineAnims[animIndex].end - (u32)VineAnims[animIndex].start;
    ASSERT_MSG(size > 0 && size <= VineBuffers[vineIndex].capacity,
        "Vine animation %ld (%lu bytes) does not fit buffer %ld", animIndex, size, vineIndex);

    dma_copy(VineAnims[animIndex].start, VineAnims[animIndex].end, VineBuffers[vineIndex].data);
    return ApiStatus_DONE2;
}

static BSS LavaPiranhaVine VineData[NUM_VINES];
static BSS s32 VineRenderState;

static void make_vine_interpolation(LavaPiranhaVine* vine) {
    Evt dummyEvt;
    Evt* dummyEvtPtr = &dummyEvt;
    s32 args[4];
    s32 count;

    // setup dummy call to LoadPath
    args[0] = 3 * vine->boneCount;      // generate three output samples per input
    args[1] = (s32) &vine->bonePos;     // points
    args[2] = vine->boneCount;          // num vectors
    args[3] = EASING_LINEAR;
    dummyEvtPtr->ptrReadPos = args;
    LoadPath(dummyEvtPtr, 1);

    count = 0;
    do {
        GetNextPathPos(dummyEvtPtr, 1);
        vine->points[count].x = evt_get_float_variable(dummyEvtPtr, LVar1);
        vine->points[count].y = evt_get_float_variable(dummyEvtPtr, LVar2);
        vine->points[count].z = evt_get_float_variable(dummyEvtPtr, LVar3);
        count++;
    } while (dummyEvtPtr->varTable[0] != 0);
    vine->numPoints = count;
}

static API_CALLABLE(SetVineBonePos) {
    Bytecode* args = script->ptrReadPos;
    s32 vineIdx = evt_get_variable(script, *args++);
    s32 jointIdx = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    LavaPiranhaVine* vine = &VineData[vineIdx];

    vine->bonePos[jointIdx].x = x;
    vine->bonePos[jointIdx].y = y;
    vine->bonePos[jointIdx].z = z;
    return ApiStatus_DONE2;
}

static API_CALLABLE(SetVineBoneRot) {
    Bytecode* args = script->ptrReadPos;
    s32 vineIdx = evt_get_variable(script, *args++);
    s32 jointIdx = evt_get_variable(script, *args++);
    s32 rx = evt_get_variable(script, *args++);
    s32 ry = evt_get_variable(script, *args++);
    f32 rz = evt_get_variable(script, *args++);
    LavaPiranhaVine* vine = &VineData[vineIdx];

    vine->boneRot[jointIdx] = rz;
    return ApiStatus_DONE2;
}

static API_CALLABLE(SetVineBoneScale) {
    Bytecode* args = script->ptrReadPos;
    s32 vineIdx = evt_get_variable(script, *args++);
    s32 jointIdx = evt_get_variable(script, *args++);
    s32 sx = evt_get_variable(script, *args++);
    s32 sy = evt_get_variable(script, *args++);
    s32 sz = evt_get_variable(script, *args++);
    LavaPiranhaVine* vine = &VineData[vineIdx];

    // do nothing
    return ApiStatus_DONE2;
}

static void appendGfx_vines(void* data) {
    Vtx_t* vtxBuffer;
    Vtx_t* vtx;

    f32 boneLength;
    s32 boneCount;

    f32 angle;
    f32 nextAngle;
    f32 curAngle1;
    f32 curAngle2;

    f32 alphaCoord;
    f32 alphaFrac;
    s32 nearest;

    s32 numPoints;
    s32 i, j;

    f32 deltaX, deltaY;
    f32 posX, posY, posZ;

    if (VineRenderState == VINE_RENDER_STATE_NONE) {
        return;
    }

    if (VineRenderState == VINE_RENDER_STATE_DIRTY) {
        for (i = 0; i < NUM_VINES; i++) {
            LavaPiranhaVine* vine = &VineData[i];

            switch (i) {
                default:
                    return;
                case VINE_0:
                    boneCount = 9;
                    boneLength = 10.0f;
                    break;
                case VINE_1:
                    boneCount = 7;
                    boneLength = 8.0f;
                    break;
                case VINE_2:
                    boneCount = 7;
                    boneLength = 8.0f;
                    break;
                case VINE_3:
                    boneCount = 5;
                    boneLength = 8.0f;
                    break;
            }

            vine->boneCount = boneCount;
            vine->boneLength = boneLength;

            for (j = 0; j < boneCount; j++) {
                if (j == (boneCount - 1)) {
                    vine->boneRot[j] += 90.0f;
                } else {
                    curAngle1 = vine->boneRot[j];
                    nextAngle = vine->boneRot[j + 1];
                    if (nextAngle - curAngle1 > 180.0f) {
                        curAngle1 += 360.0f;
                    } else if (nextAngle - curAngle1 < -180.0f) {
                        nextAngle += 360.0f;
                    }
                    // average cur and next angles
                    vine->boneRot[j] = ((curAngle1 + nextAngle) / 2.0) + 90.0;
                }
            }

            make_vine_interpolation(vine);
        }

        VineRenderState = VINE_RENDER_STATE_OK;
    }

    gDPPipeSync(gMainGfxPos++);
    gSPDisplayList(gMainGfxPos++, D_8021CF40_5A3620);

    for (i = 0; i < NUM_VINES; i++) {
        LavaPiranhaVine* vine = &VineData[i];

        boneLength = vine->boneLength;
        boneCount = vine->boneCount;
        numPoints = vine->numPoints;

        // we'll build the vertex data and place it in the display list, so jump forward
        // here and leave space behind for the gSPBranchList command followed by two vertices
        // for each point in numPoints

        vtxBuffer = (Vtx_t*)(gMainGfxPos + 1);
        gSPBranchList(gMainGfxPos, &gMainGfxPos[1 + 2 * (2 * numPoints)]);
        vtx = (Vtx_t*) (++gMainGfxPos);
        gMainGfxPos = &gMainGfxPos[2 * (2 * numPoints)];

        for (j = 0; j < numPoints; j++) {
            posX = vine->points[j].x;
            posY = vine->points[j].y;
            posZ = vine->points[j].z;

            alphaCoord = ((f32) j * boneCount) / numPoints;
            nearest = (s32) alphaCoord;
            alphaFrac = alphaCoord - (f32)nearest;

            if (nearest + 1 >= boneCount) {
                angle = vine->boneRot[boneCount - 1];
            } else {
                curAngle2 = vine->boneRot[nearest];
                nextAngle = vine->boneRot[nearest + 1];
                if (nextAngle - curAngle2 > 180.0f) {
                    nextAngle -= 360.0f;
                }
                if (nextAngle - curAngle2 < -180.0f) {
                    nextAngle += 360.0f;
                }
                angle = ((nextAngle - curAngle2) * alphaFrac) + curAngle2;
            }

            deltaX =  sin_deg(angle) * boneLength;
            deltaY = -cos_deg(angle) * boneLength;

            vtx->ob[0] = posX + deltaX;
            vtx->ob[1] = posY + deltaY;
            vtx->ob[2] = posZ;
            vtx->tc[0] = j * 0x140;
            vtx->tc[1] = 0;
            vtx->cn[0] = j * 50;
            vtx->cn[1] = j * 120;
            vtx->cn[2] = j * 30;
            vtx++;

            vtx->ob[0] = posX - deltaX;
            vtx->ob[1] = posY - deltaY;
            vtx->ob[2] = posZ;
            vtx->tc[0] = j * 0x140;
            vtx->tc[1] = 0x400;
            vtx->cn[0] = j * 50;
            vtx->cn[1] = j * 120;
            vtx->cn[2] = j * 30;
            vtx++;
        }

        for (j = 0; j < numPoints - 1; j++) {
            gSPVertex(gMainGfxPos++, &vtxBuffer[2*j], 4, 0);
            gSP2Triangles(gMainGfxPos++, 1, 0, 2, 0, 1, 2, 3, 0);
        }
    }

    gDPPipeSync(gMainGfxPos++);
}

static void worker_render_piranha_vines(void) {
    RenderTask renderTask;

    renderTask.appendGfx = &appendGfx_vines;
    renderTask.appendGfxArg = 0;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_SURFACE_OPA;

    queue_render_task(&renderTask);
}

static API_CALLABLE(MarkVineInterpolationDirty) {
    VineRenderState = VINE_RENDER_STATE_DIRTY;
    return ApiStatus_DONE2;
}

static API_CALLABLE(CreateVineRenderer) {
    VineRenderState = VINE_RENDER_STATE_NONE;
    create_worker_scene(nullptr, &worker_render_piranha_vines);
    return ApiStatus_DONE2;
}

static s32 unused;
static s32 unusedArray[64];

static EvtScript EVS_Init = {
    UseArray(unusedArray)
    Call(EnableGroup, MODEL_mae, true)
    Call(EnableGroup, MODEL_ato, false)
    Call(SetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, false)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_STUNNED)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, 0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, 0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Boss_Dying, false)
    Call(SetActorVar, ACTOR_SELF, AVAR_Flags, 0)
    Set(LVar0, 30)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaPiranha_Idle)
    Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaPiranha_Hurt)
    Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
    Call(LoadAnimatedModel, VINE_0, Ref(MainHeadVineModel))
    Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Call(SetAnimatedModelRootPosition, VINE_0, 0, 0, 0)
    Call(SetAnimatorFlags, VINE_0, MODEL_ANIMATOR_FLAG_HIDDEN, 1)
    Call(LoadAnimatedModel, VINE_1, Ref(SideHeadVineModel))
    Call(LoadVineAnim, VINE_ANIM_BUD_IDLE, VINE_1)
    Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
    Call(SetAnimatedModelRootPosition, VINE_1, 0, 0, 0)
    Call(SetAnimatorFlags, VINE_1, MODEL_ANIMATOR_FLAG_HIDDEN, 1)
    Call(LoadAnimatedModel, VINE_2, Ref(SideHeadVineModel))
    Call(LoadVineAnim, VINE_ANIM_BUD_IDLE, VINE_2)
    Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
    Call(SetAnimatedModelRootPosition, VINE_2, 50, 14, 20)
    Call(SetAnimatorFlags, VINE_2, MODEL_ANIMATOR_FLAG_HIDDEN, 1)
    Call(LoadAnimatedModel, VINE_3, Ref(ExtraVineModel))
    Call(LoadVineAnim, VINE_ANIM_EXTRA_IDLE, VINE_3)
    Call(PlayModelAnimation, VINE_3, VINE_3_BASE)
    Call(SetAnimatedModelRootPosition, VINE_3, 0, 0, 3)
    Call(SetAnimatorFlags, VINE_3, MODEL_ANIMATOR_FLAG_HIDDEN, 1)
    Call(SummonEnemy, Ref(LeftBudFormation), false)
    Call(SummonEnemy, Ref(RightBudFormation), false)
    Wait(2)
    Exec(EVS_InitVines)
    Call(CreateNpc, NPC_BTL_COMPANION, ANIM_BattleKolorado_Idle)
    Call(SetNpcYaw, NPC_BTL_COMPANION, 90)
    Call(SetNpcPos, NPC_BTL_COMPANION, -300, 0, 0)
    Call(BindTakeTurn, ACTOR_SELF, Ref(EVS_TakeTurn))
    Call(BindIdle, ACTOR_SELF, Ref(EVS_Idle))
    Call(BindHandleEvent, ACTOR_SELF, Ref(EVS_HandleEvent))
    Call(BindHandlePhase, ACTOR_SELF, Ref(EVS_HandlePhase))
    Call(ForceHomePos, ACTOR_BUD_1, 57, 57, 0)
    Call(ForceHomePos, ACTOR_BUD_2, 107, 71, 20)
    Call(HPBarToHome, ACTOR_BUD_1)
    Call(HPBarToHome, ACTOR_BUD_2)
    Call(CreateVineRenderer)
    Return
    End
};

static EvtScript EVS_Idle = {
    Label(0)
        Call(GetActorHP, ACTOR_SELF, LVar0)
        IfEq(LVar0, 0)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_BOSS, AVAR_Boss_IsSecondPhase, LVar0)
        IfFalse(LVar0)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfNe(LVar0, PIRANHA_STATE_STUNNED)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        Sub(LVar0, 1)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        IfNe(LVar0, 0)
            Goto(99)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchMode, LVar0)
        Add(LVar0, 1)
        IfGe(LVar0, 3)
            Set(LVar0, 0)
        EndIf
        Set(LVar0, 30)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_NextTwitchTime, LVar0)
        Call(LoadVineAnim, VINE_ANIM_BOSS_TWITCH, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Label(99)
        Wait(1)
        Goto(0)
    Return
    End
};

static EvtScript EVS_HandlePhase = {
    Call(GetBattlePhase, LVar0)
    Switch(LVar0)
        CaseEq(PHASE_PLAYER_END)
            Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
            IfEq(LVar0, true)
                Call(GetActorVar, ACTOR_SELF, AVAR_Flags, LVar0)
                IfNotFlag(LVar0, AVAL_Flag_Kolorado)
                    BitwiseOrConst(LVar0, AVAL_Flag_Kolorado)
                    Call(SetActorVar, ACTOR_SELF, AVAR_Flags, LVar0)
                    ExecWait(EVS_Scene_KoloradoToTheRescue)
                EndIf
            EndIf
        CaseDefault
    EndSwitch
    Return
    End
};

static EvtScript EVS_Scene_KoloradoToTheRescue = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(EnableBattleStatusBar, false)
    Call(SpeakToPlayer, NPC_BTL_COMPANION, -1, -1, 0, MSG_CH5_0104)
    Thread
        Loop(9)
            Call(PlaySoundAtNpc, NPC_BTL_COMPANION, SOUND_ACTOR_STEP_A, SOUND_SPACE_DEFAULT)
            Wait(2)
            Call(PlaySoundAtNpc, NPC_BTL_COMPANION, SOUND_ACTOR_STEP_B, SOUND_SPACE_DEFAULT)
            Wait(2)
        EndLoop
    EndThread
    Call(SetNpcAnimation, NPC_BTL_COMPANION, ANIM_BattleKolorado_WalkSad)
    Call(SetNpcAnimationSpeed, NPC_BTL_COMPANION, Float(2.0))
    Call(SetNpcSpeed, NPC_BTL_COMPANION, Float(10.0))
    Call(NpcMoveTo, NPC_BTL_COMPANION, 70, 0, 0)
    Call(PlaySoundAtNpc, NPC_BTL_COMPANION, SOUND_TOUCH_LAVA, SOUND_SPACE_DEFAULT)
    Call(SetNpcAnimationSpeed, NPC_BTL_COMPANION, Float(1.0))
    Call(SetNpcJumpscale, NPC_BTL_COMPANION, Float(1.0))
    Call(SetNpcAnimation, NPC_BTL_COMPANION, ANIM_BattleKolorado_Injured)
    Thread
        Loop(10)
            Call(GetNpcPos, NPC_BTL_COMPANION, LVar0, LVar1, LVar2)
            PlayEffect(EFFECT_SMOKE_BURST, 0, LVar0, LVar1, LVar2, Float(1.0), 20)
            Wait(2)
        EndLoop
    EndThread
    Call(NpcJump0, NPC_BTL_COMPANION, 70, 180, 0, 20)
    Call(SpeakToPlayer, NPC_BTL_COMPANION, -1, -1, 0, MSG_CH5_0105)
    Call(SetNpcYaw, NPC_BTL_COMPANION, 270)
    Call(SetNpcPos, NPC_BTL_COMPANION, 50, 180, 0)
    Thread
        Loop(10)
            Call(GetNpcPos, NPC_BTL_COMPANION, LVar0, LVar1, LVar2)
            PlayEffect(EFFECT_SMOKE_BURST, 0, LVar0, LVar1, LVar2, Float(1.0), 20)
            Wait(2)
        EndLoop
    EndThread
    Call(NpcJump0, NPC_BTL_COMPANION, 50, 0, 0, 20)
    Call(NpcJump0, NPC_BTL_COMPANION, 50, 0, 0, 6)
    Call(NpcJump0, NPC_BTL_COMPANION, 50, 0, 0, 3)
    Wait(8)
    Call(SetNpcAnimation, NPC_BTL_COMPANION, ANIM_BattleKolorado_Hurt)
    Call(SetNpcJumpscale, NPC_BTL_COMPANION, Float(0.7))
    Call(NpcJump0, NPC_BTL_COMPANION, 50, 0, 0, 12)
    Thread
        Loop(4)
            Call(PlaySoundAtNpc, NPC_BTL_COMPANION, SOUND_ACTOR_STEP_A, SOUND_SPACE_DEFAULT)
            Wait(2)
            Call(PlaySoundAtNpc, NPC_BTL_COMPANION, SOUND_ACTOR_STEP_B, SOUND_SPACE_DEFAULT)
            Wait(2)
        EndLoop
    EndThread
    Call(SetNpcAnimation, NPC_BTL_COMPANION, ANIM_BattleKolorado_Run)
    Call(SetNpcSpeed, NPC_BTL_COMPANION, Float(8.0))
    Call(NpcMoveTo, NPC_BTL_COMPANION, -60, 0, 0)
    Call(SpeakToPlayer, NPC_BTL_COMPANION, ANIM_BattleKolorado_Shout, ANIM_BattleKolorado_ShoutStill, 5, MSG_CH5_0106)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_RUN_AWAY)
    Call(SetNpcAnimation, NPC_BTL_COMPANION, ANIM_BattleKolorado_Run)
    Call(SetNpcSpeed, NPC_BTL_COMPANION, Float(6.0))
    Call(NpcMoveTo, NPC_BTL_COMPANION, -300, 0, 0)
    Call(EnableBattleStatusBar, true)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static API_CALLABLE(SetFlameProperties) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, *args++);
    FlameFXData* flameData = effect->data.flame;
    s32 posX = evt_get_variable(script, *args++);
    s32 posY = evt_get_variable(script, *args++);
    f32 angle = evt_get_variable(script, *args++);
    s32 radius = evt_get_variable(script, *args++);
    s32 offsetY = evt_get_variable(script, *args++);
    s32 scalePercent = evt_get_variable(script, *args++);

    flameData->pos.x = posX - cos_deg(angle) * radius;
    flameData->pos.y = (posY + offsetY) - sin_deg(angle) * radius;
    flameData->baseScale = scalePercent * 0.01f;
    return ApiStatus_DONE2;
}

static EvtScript EVS_InitVines = {
    UseArray(unusedArray)
    Label(0)
        // ---------------------------------------------------------------
        // set ACTOR_BOSS position and orientation to tip of VINE_0
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 10, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_BOSS, PRT_MAIN, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 10, LVar0, LVar1, LVar2)
        Call(SetPartRotation, ACTOR_BOSS, PRT_MAIN, LVar0, 0, LVar2)
        Call(MarkVineInterpolationDirty)
        // ---------------------------------------------------------------
        // set position and orientation for VINE_0 bones
        // VINE_0, bone 0
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 10, LVar0, LVar1, LVar2)
        Sub(LVar2, 2)
        Call(SetVineBonePos, VINE_0, 0, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 10, LVar0, LVar1, LVar2)
        Add(LVar2, 90)
        Call(SetVineBoneRot, VINE_0, 0, LVar0, 0, LVar2)
        Call(SetVineBoneScale, VINE_0, 0, 1, 1, 1)
        // VINE_0, bone 1
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 5, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 1, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 1, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 1, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 2
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 9, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 2, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 9, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 2, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 3
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 4, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 3, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 3, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 4
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 8, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 4, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 8, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 4, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 5
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 3, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 5, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 5, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 6
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 7, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 6, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 7, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 6, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 7
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 2, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 7, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 7, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 7, Float(0.714), Float(0.714), Float(1.0))
        // VINE_0, bone 8
        Call(GetAnimatedPositionByTreeIndex, VINE_0, 6, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_0, 8, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_0, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_0, 8, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_0, 8, Float(0.714), Float(0.714), Float(1.0))
        // ---------------------------------------------------------------
        // set ACTOR_BUD_1 position and orientation to tip of VINE_1
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 8, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_BUD_1, PRT_MAIN, LVar0, LVar1, LVar2)
        Sub(LVar0, 8)
        Call(SetPartPos, ACTOR_BUD_1, PRT_TARGET, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 8, LVar0, LVar1, LVar2)
        Call(SetPartRotation, ACTOR_BUD_1, PRT_MAIN, LVar0, 0, LVar2)
        // ---------------------------------------------------------------
        // set position and orientation for VINE_1 bones
        // VINE_1, bone 0
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 8, LVar0, LVar1, LVar2)
        Sub(LVar2, 2)
        Call(SetVineBonePos, VINE_1, 0, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 8, LVar0, LVar1, LVar2)
        Add(LVar2, 90)
        Call(SetVineBoneRot, VINE_1, 0, LVar0, 0, LVar2)
        Call(SetVineBoneScale, VINE_1, 0, 1, 1, 1)
        // VINE_1, bone 1
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 4, LVar0, LVar1, LVar2)
        Sub(LVar2, 2)
        Call(SetVineBonePos, VINE_1, 1, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 1, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 1, Float(0.714), Float(0.714), Float(1.0))
        // VINE_1, bone 2
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 7, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_1, 2, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 7, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 2, Float(0.714), Float(0.714), Float(1.0))
        // VINE_1, bone 3
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 3, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_1, 3, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 3, Float(0.714), Float(0.714), Float(1.0))
        // VINE_1, bone 4
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 6, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_1, 4, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 4, Float(0.714), Float(0.714), Float(1.0))
        // VINE_1, bone 5
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 2, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_1, 5, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 5, Float(0.714), Float(0.714), Float(1.0))
        // VINE_1, bone 6
        Call(GetAnimatedPositionByTreeIndex, VINE_1, 5, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_1, 6, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_1, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_1, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_1, 6, Float(0.714), Float(0.714), Float(1.0))
        // ---------------------------------------------------------------
        // set ACTOR_BUD_2 position and orientation to tip of VINE_2
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 8, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_BUD_2, PRT_MAIN, LVar0, LVar1, LVar2)
        Call(SetPartPos, ACTOR_BUD_2, PRT_TARGET, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 8, LVar0, LVar1, LVar2)
        Call(SetPartRotation, ACTOR_BUD_2, PRT_MAIN, LVar0, 0, LVar2)
        // ---------------------------------------------------------------
        // set position and orientation for VINE_2 bones
        // VINE_2, bone 0
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 8, LVar0, LVar1, LVar2)
        Sub(LVar2, 2)
        Call(SetVineBonePos, VINE_2, 0, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 8, LVar0, LVar1, LVar2)
        Add(LVar2, 90)
        Call(SetVineBoneRot, VINE_2, 0, LVar0, 0, LVar2)
        Call(SetVineBoneScale, VINE_2, 0, 1, 1, 1)
        // VINE_2, bone 1
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 4, LVar0, LVar1, LVar2)
        Sub(LVar2, 2)
        Call(SetVineBonePos, VINE_2, 1, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 1, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 1, Float(0.714), Float(0.714), Float(1.0))
        // VINE_2, bone 2
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 7, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_2, 2, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 7, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 2, Float(0.714), Float(0.714), Float(1.0))
        // VINE_2, bone 3
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 3, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_2, 3, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 3, Float(0.714), Float(0.714), Float(1.0))
        // VINE_2, bone 4
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 6, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_2, 4, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 4, Float(0.714), Float(0.714), Float(1.0))
        // VINE_2, bone 5
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 2, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_2, 5, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 5, Float(0.714), Float(0.714), Float(1.0))
        // VINE_2, bone 6
        Call(GetAnimatedPositionByTreeIndex, VINE_2, 5, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_2, 6, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_2, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_2, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_2, 6, Float(0.714), Float(0.714), Float(1.0))
        // ---------------------------------------------------------------
        // set position and orientation for VINE_3 bones
        // VINE_3, bone 0
        Call(GetAnimatedPositionByTreeIndex, VINE_3, 4, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_3, 0, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_3, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_3, 0, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_3, 0, Float(0.714), Float(0.714), Float(1.0))
        // VINE_3, bone 1
        Call(GetAnimatedPositionByTreeIndex, VINE_3, 6, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_3, 1, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_3, 6, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_3, 1, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_3, 1, Float(0.714), Float(0.714), Float(1.0))
        // VINE_3, bone 2
        Call(GetAnimatedPositionByTreeIndex, VINE_3, 3, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_3, 2, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_3, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_3, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_3, 2, Float(0.714), Float(0.714), Float(1.0))
        // VINE_3, bone 3
        Call(GetAnimatedPositionByTreeIndex, VINE_3, 5, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_3, 3, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_3, 5, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_3, 3, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_3, 3, Float(0.714), Float(0.714), Float(1.0))
        // VINE_3, bone 4
        Call(GetAnimatedPositionByTreeIndex, VINE_3, 2, LVar0, LVar1, LVar2)
        Call(SetVineBonePos, VINE_3, 4, LVar0, LVar1, LVar2)
        Call(GetAnimatedRotationByTreeIndex, VINE_3, 2, LVar0, LVar1, LVar2)
        Call(SetVineBoneRot, VINE_3, 4, LVar0, LVar1, LVar2)
        Call(SetVineBoneScale, VINE_3, 4, Float(0.714), Float(0.714), Float(1.0))
        // ---------------------------------------------------------------
        // set flame positions
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(GetAnimatedPositionByTreeIndex, VINE_0, 10, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_0, 10, LVar4, LVar5, LVar6)
            Set(LVar7, 30)
            Set(LVar8, -30)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameSize, LVar9)
            Call(SetFlameProperties, LVar0, LVar1, LVar2, LVar6, LVar7, LVar8, LVar9)
        EndIf
        Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(GetAnimatedPositionByTreeIndex, VINE_1, 8, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_1, 8, LVar4, LVar5, LVar6)
            Set(LVar7, 10)
            Set(LVar8, -15)
            Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_FlameSize, LVar9)
            Call(SetFlameProperties, LVar0, LVar1, LVar2, LVar6, LVar7, LVar8, LVar9)
        EndIf
        Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(GetAnimatedPositionByTreeIndex, VINE_2, 8, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_2, 8, LVar4, LVar5, LVar6)
            Set(LVar7, 10)
            Set(LVar8, -15)
            Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_FlameSize, LVar9)
            Call(SetFlameProperties, LVar0, LVar1, LVar2, LVar6, LVar7, LVar8, LVar9)
        EndIf
        Wait(1)
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfNotFlag(LVar0, ACTOR_FLAG_NO_DMG_APPLY)
        Goto(0)
    EndIf
    Return
    End
};

static EvtScript EVS_HandleEvent = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    Call(SetAnimatorFlags, VINE_0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
    Call(GetLastElement, LVarE)
    Call(GetLastEvent, ACTOR_SELF, LVar0)
    Switch(LVar0)
        CaseEq(EVENT_BEGIN_FIRST_STRIKE)
        CaseEq(EVENT_HIT_COMBO)
            ExecWait(EVS_ComboHit)
            ExecWait(EVS_PlayIdleAnimation)
        CaseEq(EVENT_HIT)
            ExecWait(EVS_Hit)
            ExecWait(EVS_PlayIdleAnimation)
        CaseEq(EVENT_DEATH)
            ExecWait(EVS_Death)
            Return
        CaseEq(EVENT_BURN_HIT)
            IfFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_BurnHit)
            Else
                ExecWait(EVS_Hit)
                ExecWait(EVS_PlayIdleAnimation)
            EndIf
        CaseEq(EVENT_BURN_DEATH)
            ExecWait(EVS_Death)
            Return
        CaseEq(EVENT_SPIN_SMASH_HIT)
            ExecWait(EVS_Hit)
            ExecWait(EVS_PlayIdleAnimation)
        CaseEq(EVENT_SPIN_SMASH_DEATH)
            ExecWait(EVS_Death)
            Return
        CaseEq(EVENT_SHOCK_HIT)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_LavaPiranha_Hurt)
            ExecWait(EVS_Enemy_ShockHit)
        CaseEq(EVENT_SHOCK_DEATH)
            ExecWait(EVS_Death)
            Return
        CaseEq(EVENT_ZERO_DAMAGE)
            IfNotFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_ComboHit)
                ExecWait(EVS_PlayIdleAnimation)
            EndIf
        CaseEq(EVENT_IMMUNE)
            IfNotFlag(LVarE, DAMAGE_TYPE_FIRE)
                ExecWait(EVS_Hit)
                ExecWait(EVS_PlayIdleAnimation)
            EndIf
        CaseEq(EVENT_AIR_LIFT_FAILED)
        CaseEq(EVENT_SPIKE_TAUNT)
        CaseEq(EVENT_END_FIRST_STRIKE)
        CaseEq(EVENT_RECOVER_STATUS)
            Call(SetAnimatorFlags, VINE_0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
        CaseEq(EVENT_30)
            SetConst(LVar0, PRT_MAIN)
            SetConst(LVar1, ANIM_LavaPiranha_Hurt)
            ExecWait(EVS_Enemy_Hit)
            Wait(1000)
        CaseDefault
    EndSwitch
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
    IfFalse(LVar0)
        Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar1)
        IfEq(LVar1, PIRANHA_STATE_FIERY)
            Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
        Else
            Call(ForceHomePos, ACTOR_SELF, 83, 67, 0)
        EndIf
    EndIf
    Call(GetStatusFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, STATUS_FLAG_STOP)
        Call(SetAnimatorFlags, VINE_0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 1)
    EndIf
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static EvtScript EVS_BurnHit = {
    Thread
        Wait(1)
        Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
        IfFalse(LVar0)
            Goto(10)
        EndIf
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar2)
        IfEq(LVar2, PIRANHA_STATE_FIERY)
            Goto(10)
        EndIf
        Set(LVar0, ACTOR_BOSS)
        ExecWait(EVS_Ignite)
        Label(10)
    EndThread
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
    IfTrue(LVar0)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_STUNNED)
            Call(LoadVineAnim, VINE_ANIM_BOSS_RECOVER, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaPiranha_Idle)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaPiranha_Hurt)
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(FieryAnims))
            Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(FieryDefense))
            Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(FieryDefense))
            Thread
                Wait(14)
                Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
                Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            EndThread
        EndIf
    EndIf
    Return
    End
};

static EvtScript EVS_TakeTurn = {
    Call(GetActorFlags, ACTOR_SELF, LVar0)
    IfFlag(LVar0, ACTOR_FLAG_NO_DMG_APPLY)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
    Switch(LVar0)
        CaseEq(0)
            ExecWait(EVS_Attack_SpitFire)
        CaseDefault
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_FIERY)
                ExecWait(EVS_Attack_FireBreath)
            Else
                Call(GetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, LVar0)
                Sub(LVar0, 1)
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, LVar0)
                IfLe(LVar0, 0)
                    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
                    Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
                    Call(SetBattleCamTarget, 80, 70, 0)
                    Call(SetBattleCamDist, 300)
                    Call(SetBattleCamOffsetY, 30)
                    Call(MoveBattleCamOver, 30)
                    Wait(30)
                    Loop(10)
                        Call(LoadVineAnim, VINE_ANIM_BOSS_TWITCH, VINE_0)
                        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
                        Wait(4)
                    EndLoop
                    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
                    Call(MoveBattleCamOver, 15)
                    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_RECOVER)
                    Set(LVar0, ACTOR_BOSS)
                    ExecWait(EVS_Ignite)
                    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_TongueWag)
                    Call(LoadVineAnim, VINE_ANIM_BOSS_RECOVER, VINE_0)
                    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
                    Wait(14)
                    Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
                    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
                    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};

static Vec3i SummonPos = { 260, 0, 0 };

static Formation LeftBudFormation = {
    RAW_ACTOR_BY_POS(BudBlueprint, SummonPos, 80, 1, 0, 0, 0),
};

static Formation RightBudFormation = {
    RAW_ACTOR_BY_POS(BudBlueprint, SummonPos, 70, 2, 50, 14, 20),
};

static EvtScript EVS_Attack_SpitFire = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Thread
        Wait(8)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 80, 70, 0)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 45)
        Wait(57)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
    EndThread
    Call(LoadVineAnim, VINE_ANIM_BOSS_ATTACK, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Wait(14)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_SpitFireIn)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_INHALE)
    Wait(45)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_SpitFireOut)
    Call(GetPartOffset, ACTOR_SELF, PRT_MAIN, LVar0, LVar1, LVar2)
    Sub(LVar0, 50)
    Sub(LVar1, 15)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    Sub(LVar3, 40)
    Set(LVar4, -10)
    PlayEffect(EFFECT_63, 1, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 20, 20)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_SPIT_FIRE)
    Wait(19)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    PlayEffect(EFFECT_EMBERS, 0, LVar3, 0, LVar5, 50, 50, Float(1.0), 40, 55, Float(1.0), Float(1.0))
    Call(LoadVineAnim, VINE_ANIM_BOSS_POST_ATTACK, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, DAMAGE_TYPE_FIRE, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVarA)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Idle)
            Wait(19)
            Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            IfEq(LVarA, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_FIRE, SUPPRESS_EVENT_ALL, 0, DMG_SPIT_FIRE, BS_FLAGS1_TRIGGER_EVENTS)
    Set(LVarF, LVar0)
    Switch(LVarF)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
        CaseOrEq(HIT_RESULT_10)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Idle)
            Wait(19)
            Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            IfEq(LVarF, 10)
                Return
            EndIf
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        EndCaseGroup
    EndSwitch
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static EvtScript EVS_Attack_FireBreath = {
    Call(UseIdleAnimation, ACTOR_SELF, false)
    Call(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    Thread
        Wait(8)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 80, 70, 0)
        Call(SetBattleCamDist, 300)
        Call(SetBattleCamOffsetY, 30)
        Call(MoveBattleCamOver, 45)
        Wait(54)
        Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
        Call(MoveBattleCamOver, 15)
    EndThread
    Call(LoadVineAnim, VINE_ANIM_BOSS_ATTACK, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Wait(14)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Talk)
    Wait(10)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_INHALE)
    Wait(45)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_FireBreathOut)
    Call(GetPartOffset, ACTOR_SELF, PRT_MAIN, LVar0, LVar1, LVar2)
    Sub(LVar0, 40)
    Set(LVar1, -10)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(GetGoalPos, ACTOR_SELF, LVar3, LVar4, LVar5)
    PlayEffect(EFFECT_63, 0, LVar0, LVar1, LVar2, LVar3, LVar4, LVar5, Float(1.0), 16, 40)
    Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_FIRE_BREATH)
    Wait(15)
    Thread
        Wait(24)
        PlayEffect(EFFECT_EMBERS, 0, LVar3, 0, LVar5, 50, 50, Float(1.0), 40, 55, Float(1.0), Float(1.0))
    EndThread
    Call(EnemyTestTarget, ACTOR_SELF, LVarA, DAMAGE_TYPE_FIRE, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS)
    Switch(LVarA)
        CaseOrEq(HIT_RESULT_MISS)
        CaseOrEq(HIT_RESULT_LUCKY)
            Wait(20)
            Call(LoadVineAnim, VINE_ANIM_BOSS_POST_ATTACK, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_FireBreathIn)
            Wait(19)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_TongueWag)
            Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            IfEq(LVarA, HIT_RESULT_LUCKY)
                Call(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EndIf
            Wait(15)
            Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
            Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
            Call(UseIdleAnimation, ACTOR_SELF, true)
            Return
        EndCaseGroup
    EndSwitch
    Wait(2)
    Call(SetGoalToTarget, ACTOR_SELF)
    Call(EnemyDamageTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_FIRE, SUPPRESS_EVENT_ALL, 0, DMG_FIRE_BREATH, BS_FLAGS1_TRIGGER_EVENTS)
    Wait(20)
    Call(LoadVineAnim, VINE_ANIM_BOSS_POST_ATTACK, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_FireBreathIn)
    Wait(19)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_TongueWag)
    Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
    Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    IfEq(LVarF, 10)
        Return
    EndIf
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
    Call(UseIdleAnimation, ACTOR_SELF, true)
    Return
    End
};

static s32 FakeoutMusicTime;

static API_CALLABLE(ManageFakeoutMusic) {
    FakeoutMusicTime++;

    // play 'end battle' song
    if (isInitialCall) {
        sfx_play_sound(SOUND_JINGLE_WON_BATTLE);
        bgm_set_song(0, SONG_BATTLE_END, 0, 500, 8);
        return ApiStatus_BLOCK;
    }

    switch (FakeoutMusicTime) {
        case 80:
            // after a short time, stop the 'end battle' song
            bgm_init_music_players();
            return ApiStatus_BLOCK;
        case 340:
            // restart the boss theme with the more intense variation
            bgm_set_song(0, SONG_LAVA_PIRANHA_BATTLE, 1, 500, 8);
            return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

static s32 LavaPiranhaSinkPositions[];

static API_CALLABLE(GetSinkPosLavaPiranha) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    s32 outVar = *args++;

    evt_set_variable(script, outVar, LavaPiranhaSinkPositions[index]);
    return ApiStatus_DONE2;
}

static s32 LavaBudSinkPositions[];

static API_CALLABLE(GetSinkPosLavaBud) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    s32 outVar = *args++;

    evt_set_variable(script, outVar, LavaBudSinkPositions[index]);
    return ApiStatus_DONE2;
}

static EvtScript EVS_Death = {
    Call(SetActorVar, ACTOR_SELF, AVAR_Boss_Dying, true)
    ExecWait(EVS_Hit)
    Label(0)
        Call(GetBattleFlags, LVar0)
        IfFlag(LVar0, BS_FLAGS1_EXECUTING_MOVE)
            Wait(1)
            Goto(0)
        EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar2)
    IfEq(LVar2, 0)
        Call(ClearStatusEffects, ACTOR_SELF)
        Call(ClearStatusEffects, ACTOR_BUD_1)
        Call(ClearStatusEffects, ACTOR_BUD_2)
        Call(SetAnimatorFlags, VINE_0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
        Call(GetActorVar, ACTOR_BUD_1, AVAR_Bud_WhichVine, LVar0)
        Call(SetAnimatorFlags, LVar0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
        Call(GetActorVar, ACTOR_BUD_2, AVAR_Bud_WhichVine, LVar0)
        Call(SetAnimatorFlags, LVar0, MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION, 0)
        Call(CancelEnemyTurn, 1)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 240)
        Call(LoadVineAnim, VINE_ANIM_BOSS_DEATH_BEGIN, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Call(LoadVineAnim, VINE_ANIM_EXTRA_DEATH, VINE_3)
        Call(PlayModelAnimation, VINE_3, VINE_3_BASE)
        Wait(10)
        Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_BEGIN, VINE_1)
        Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
        Wait(5)
        Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_BEGIN, VINE_2)
        Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
        Wait(4)
        Thread
            Call(PlaySound, SOUND_LRAW_RUMBLE)
            Call(ShakeCam, CAM_BATTLE, 0, 119, Float(0.3))
            Call(PlaySound, SOUND_LRAW_RUMBLE | SOUND_ID_TRIGGER_CHANGE_SOUND)
        EndThread
        Call(StartRumbleWithParams, 80, 234)
        Call(HideHealthBar, ACTOR_SELF)
        Call(HideHealthBar, ACTOR_BUD_1)
        Call(HideHealthBar, ACTOR_BUD_2)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_PlayDead)
        Call(LoadVineAnim, VINE_ANIM_BOSS_DEATH_MIDDLE, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_DEFEAT)
            Wait(35)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, VINE_0, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, VINE_0, LVar2, LVar3, LVar4)
                Call(GetSinkPosLavaPiranha, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(10)
        Call(SetAnimation, ACTOR_BUD_1, PRT_MAIN, ANIM_LavaBud_PlayDead)
        Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_MIDDLE, VINE_1)
        Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
        Thread
            Wait(45)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, VINE_1, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, VINE_1, LVar2, LVar3, LVar4)
                Call(GetSinkPosLavaBud, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(5)
        Call(SetAnimation, ACTOR_BUD_2, PRT_MAIN, ANIM_LavaBud_PlayDead)
        Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_MIDDLE, VINE_2)
        Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
        Thread
            Wait(45)
            Set(LVar0, 0)
            Set(LVar1, 0)
            Loop(0)
                Call(GetAnimatedModelRootPosition, VINE_2, LVar2, LVar3, LVar4)
                Add(LVar3, LVar1)
                Call(SetAnimatedModelRootPosition, VINE_2, LVar2, LVar3, LVar4)
                Call(GetSinkPosLavaBud, LVar0, LVar1)
                Add(LVar0, 1)
                Wait(1)
                IfEq(LVar1, 99)
                    BreakLoop
                EndIf
            EndLoop
        EndThread
        Wait(35)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, -45)
        Call(MoveBattleCamOver, 110)
        Wait(60)
        Call(SetAnimatedModelRootPosition, VINE_0, 0, -250, 0)
        Call(SetAnimatedModelRootPosition, VINE_1, 0, -250, 0)
        Call(SetAnimatedModelRootPosition, VINE_2, 0, -250, 0)
        Call(SetActorPos, ACTOR_SELF, 100, 0, 0)
        Call(DropStarPoints, ACTOR_SELF)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_ACTOR_DEATH)
        Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
        Wait(65)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Call(SetBattleCamTarget, LVar0, LVar1, LVar2)
        Call(SetBattleCamDist, 240)
        Call(SetBattleCamOffsetY, 40)
        Call(MoveBattleCamOver, 20)
        Wait(20)
        Thread
            Call(ManageFakeoutMusic)
        EndThread
        Wait(80)
        Thread
            Call(PlaySound, SOUND_LRAW_RUMBLE)
            Call(ShakeCam, CAM_BATTLE, 0, 165, Float(1.2))
            Call(PlaySound, SOUND_LRAW_RUMBLE | SOUND_ID_TRIGGER_CHANGE_SOUND)
        EndThread
        Call(StartRumbleWithParams, 80, 300)
        Call(UseIdleAnimation, ACTOR_PLAYER, false)
        Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_LookUp)
        Wait(20)
        Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_EMOTE_QUESTION)
        Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
        Add(LVar1, 20)
        PlayEffect(EFFECT_EMOTE, EMOTE_QUESTION, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0)
        Call(GetActorPos, ACTOR_PARTNER, LVar0, LVar1, LVar2)
        Add(LVar1, 10)
        PlayEffect(EFFECT_EMOTE, EMOTE_QUESTION, 0, LVar0, LVar1, LVar2, 20, 315, 30, 0)
        Wait(50)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 360)
        Call(SetBattleCamOffsetY, -60)
        Call(MoveBattleCamOver, 30)
        Wait(40)
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 90, 90, 0)
        Call(SetBattleCamDist, 200)
        Call(SetBattleCamOffsetY, -60)
        Call(MoveBattleCamOver, 40)
        Wait(40)
        Thread
            Call(UseIdleAnimation, ACTOR_PLAYER, false)
            Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_Flail)
            Wait(40)
            Call(UseIdleAnimation, ACTOR_PLAYER, true)
        EndThread
        Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
        Call(SetBattleCamTarget, 30, 90, 0)
        Call(SetBattleCamDist, 460)
        Call(SetBattleCamOffsetY, 0)
        Call(MoveBattleCamOver, 30)
        Call(StartRumbleWithParams, 180, 16)
        Thread
            Call(ShakeCam, CAM_BATTLE, 0, 4, Float(3.0))
            Call(ShakeCam, CAM_BATTLE, 0, 10, Float(1.0))
        EndThread
        ChildThread
            Wait(50)
            Call(UseBattleCamPreset, BTL_CAM_REPOSITION)
            Call(SetBattleCamTarget, 90, 90, 0)
            Call(SetBattleCamDist, 360)
            Call(SetBattleCamOffsetY, 0)
            Call(MoveBattleCamOver, 40)
            Wait(85)
        EndChildThread
        Call(SetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, true)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaPiranha_TongueWag)
        Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaPiranha_Sleep)
        Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_UnkAnim1, ANIM_LavaBud_IdleFiery)
        Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_UnkAnim2, ANIM_LavaBud_HurtFiery)
        Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_UnkAnim1, ANIM_LavaBud_IdleFiery)
        Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_UnkAnim2, ANIM_LavaBud_HurtFiery)
        Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(BudFieryAnims))
        Call(SetIdleAnimations, ACTOR_BUD_1, PRT_MAIN, Ref(BudFieryAnims))
        Call(SetIdleAnimations, ACTOR_BUD_2, PRT_MAIN, Ref(BudFieryAnims))
        Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(FieryDefense))
        Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(FieryDefense))
        Call(SetDefenseTable, ACTOR_BUD_1, PRT_MAIN, Ref(BudFieryDefense))
        Call(SetDefenseTable, ACTOR_BUD_1, PRT_TARGET, Ref(BudFieryDefense))
        Call(SetDefenseTable, ACTOR_BUD_2, PRT_MAIN, Ref(BudFieryDefense))
        Call(SetDefenseTable, ACTOR_BUD_2, PRT_TARGET, Ref(BudFieryDefense))
        Call(SetPartImmunityBits, ACTOR_SELF, PRT_MAIN, ELEMENT_FIRE, 1)
        Call(SetPartImmunityBits, ACTOR_SELF, PRT_TARGET, ELEMENT_FIRE, 1)
        Call(SetPartImmunityBits, ACTOR_BUD_1, PRT_MAIN, ELEMENT_FIRE, 1)
        Call(SetPartImmunityBits, ACTOR_BUD_1, PRT_TARGET, ELEMENT_FIRE, 1)
        Call(SetPartImmunityBits, ACTOR_BUD_2, PRT_MAIN, ELEMENT_FIRE, 1)
        Call(SetPartImmunityBits, ACTOR_BUD_2, PRT_TARGET, ELEMENT_FIRE, 1)
        Call(SetPartFlagBits, ACTOR_BUD_1, PRT_TARGET, ACTOR_PART_FLAG_DAMAGE_IMMUNE, false)
        Call(SetPartFlagBits, ACTOR_BUD_2, PRT_TARGET, ACTOR_PART_FLAG_DAMAGE_IMMUNE, false)
        Set(LVar0, ACTOR_BOSS)
        ExecWait(EVS_Ignite)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_TongueWag)
        Set(LVar0, ACTOR_BUD_1)
        ExecWait(EVS_Ignite)
        Call(SetAnimation, ACTOR_BUD_1, PRT_MAIN, ANIM_LavaBud_IdleFiery)
        Set(LVar0, ACTOR_BUD_2)
        ExecWait(EVS_Ignite)
        Call(SetAnimation, ACTOR_BUD_2, PRT_MAIN, ANIM_LavaBud_IdleFiery)
        Call(SetActorType, ACTOR_SELF, ACTOR_TYPE_LAVA_PIRANHA_PHASE_2)
        Call(SetActorType, ACTOR_BUD_1, ACTOR_TYPE_LAVA_BUD_PHASE_2)
        Call(SetActorType, ACTOR_BUD_2, ACTOR_TYPE_LAVA_BUD_PHASE_2)
        Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_TYPE_CHANGED, true)
        Call(SetActorFlagBits, ACTOR_BUD_1, ACTOR_FLAG_TYPE_CHANGED, true)
        Call(SetActorFlagBits, ACTOR_BUD_2, ACTOR_FLAG_TYPE_CHANGED, true)
        Call(GetEnemyMaxHP, ACTOR_SELF, LVar0)
        Call(SetEnemyHP, ACTOR_SELF, LVar0)
        Call(GetEnemyMaxHP, ACTOR_BUD_1, LVar0)
        Call(SetEnemyHP, ACTOR_BUD_1, LVar0)
        Call(GetEnemyMaxHP, ACTOR_BUD_2, LVar0)
        Call(SetEnemyHP, ACTOR_BUD_2, LVar0)
        Call(EnableModel, MODEL_h01, true)
        Call(EnableModel, MODEL_h02, true)
        Call(EnableModel, MODEL_h03, true)
        Call(EnableModel, MODEL_h04, true)
        Call(EnableModel, MODEL_h05, true)
        Call(EnableModel, MODEL_h06, true)
        Call(EnableModel, MODEL_h07, true)
        Call(EnableModel, MODEL_h08, true)
        Call(EnableModel, MODEL_h10, true)
        Call(EnableModel, MODEL_h11, true)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_EMERGE)
        PlayEffect(EFFECT_EMBERS, 0, 100, 0, 0, 70, 80, Float(2.5), 80, 55, Float(2.0), Float(2.0))
        Call(LoadAnimatedModel, SHATTER_GROUND, Ref(ShatterGroundModel))
        Call(PlayModelAnimation, SHATTER_GROUND, Ref(AS_ShatterGround))
        Call(SetAnimatedModelRootPosition, SHATTER_GROUND, 0, 0, 0)
        Call(EnableGroup, MODEL_mae, false)
        Call(EnableGroup, MODEL_ato, true)
        Thread
            Wait(45)
            Call(DeleteAnimatedModel, SHATTER_GROUND)
        EndThread
        Call(LoadVineAnim, VINE_ANIM_BOSS_EMERGE, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Call(SetAnimatedModelRootPosition, VINE_0, 0, 0, 0)
        Wait(5)
        Call(SetAnimatedModelRootPosition, VINE_2, 50, 14, 20)
        Call(LoadVineAnim, VINE_ANIM_BUD_EMERGE, VINE_2)
        Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
        Wait(10)
        Call(SetAnimatedModelRootPosition, VINE_1, 0, 0, 0)
        Call(LoadVineAnim, VINE_ANIM_BUD_EMERGE, VINE_1)
        Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
        Wait(45)
        Call(SetAnimatedModelRootPosition, VINE_3, 0, 0, 0)
        Call(LoadVineAnim, VINE_ANIM_EXTRA_EMERGE, VINE_3)
        Call(PlayModelAnimation, VINE_3, VINE_3_BASE)
        Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Talk)
        Wait(5)
        Call(LoadVineAnim, VINE_ANIM_BUD_IDLE, VINE_2)
        Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
        Wait(10)
        Call(LoadVineAnim, VINE_ANIM_BUD_IDLE, VINE_1)
        Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
        Wait(30)
        Call(LoadVineAnim, VINE_ANIM_EXTRA_IDLE, VINE_3)
        Call(PlayModelAnimation, VINE_3, VINE_3_BASE)
        Call(GetEnemyMaxHP, ACTOR_BUD_1, LVar0)
        Call(SetEnemyHP, ACTOR_BUD_1, LVar0)
        Call(GetEnemyMaxHP, ACTOR_BUD_2, LVar0)
        Call(SetEnemyHP, ACTOR_BUD_2, LVar0)
        Call(SetActorVar, ACTOR_SELF, AVAR_Boss_Dying, false)
        Call(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_ENABLE)
        Call(UseIdleAnimation, ACTOR_SELF, true)
    Else
        Call(HideHealthBar, ACTOR_BUD_1)
        Call(HideHealthBar, ACTOR_BUD_2)
        Set(LVar0, ACTOR_PETIT_1)
        ExecWait(EVS_RemovePetitPiranha)
        Set(LVar0, ACTOR_PETIT_2)
        ExecWait(EVS_RemovePetitPiranha)
        Call(LoadVineAnim, VINE_ANIM_EXTRA_DEATH, VINE_3)
        Call(PlayModelAnimation, VINE_3, VINE_3_BASE)
        Thread
            Call(PlaySound, SOUND_LRAW_RUMBLE)
            Call(ShakeCam, CAM_BATTLE, 0, 100, Float(0.5))
            Call(ShakeCam, CAM_BATTLE, 0, 8, Float(0.2))
            Call(PlaySound, SOUND_LRAW_RUMBLE | SOUND_ID_TRIGGER_CHANGE_SOUND)
        EndThread
        Call(StartRumbleWithParams, 80, 216)
        Thread
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_WRITHE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_STUNNED)
                Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_DEATH_BEGIN, VINE_0)
                Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Else
                Call(LoadVineAnim, VINE_ANIM_BOSS_DEATH_BEGIN, VINE_0)
                Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            EndIf
            Wait(19)
            Call(HideHealthBar, ACTOR_SELF)
            Call(LoadVineAnim, VINE_ANIM_BOSS_DEATH_MIDDLE, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_FIERY)
                PlayEffect(EFFECT_EMBERS, 0, 105, 60, 2, 80, 60, Float(1.8), 90, 100, Float(1.5), Float(1.5))
            EndIf
            Wait(121)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_COLLAPSE)
            Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Sleep)
            Call(LoadVineAnim, VINE_ANIM_BOSS_DEATH_COLLAPSE, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Wait(30)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameSize, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.01))
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameSize, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(12)
            Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_STUNNED)
                Call(LoadVineAnim, VINE_ANIM_BUD_STUNNED_DEATH_BEGIN, VINE_1)
                Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
            Else
                Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_BEGIN, VINE_1)
                Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
            EndIf
            Wait(19)
            Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_MIDDLE, VINE_1)
            Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
            Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_FIERY)
                PlayEffect(EFFECT_EMBERS, 0, 67, 30, 2, 50, 40, Float(1.3), 30, 70, Float(1.2), Float(1.2))
            EndIf
            Wait(96)
            Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_COLLAPSE, VINE_1)
            Call(PlayModelAnimation, VINE_1, VINE_1_BASE)
            Wait(30)
            Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_FlameSize, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.01))
                Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_FlameSize, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(5)
            Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_STUNNED)
                Call(LoadVineAnim, VINE_ANIM_BUD_STUNNED_DEATH_BEGIN, VINE_2)
                Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
            Else
                Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_BEGIN, VINE_2)
                Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
            EndIf
            Wait(19)
            Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_MIDDLE, VINE_2)
            Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
            Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_PiranhaState, LVar0)
            IfEq(LVar0, PIRANHA_STATE_FIERY)
                PlayEffect(EFFECT_EMBERS, 0, 120, 35, 5, 50, 40, Float(1.3), 30, 70, Float(1.2), Float(1.2))
            EndIf
            Wait(96)
            Call(LoadVineAnim, VINE_ANIM_BUD_DEATH_COLLAPSE, VINE_2)
            Call(PlayModelAnimation, VINE_2, VINE_2_BASE)
            Wait(30)
            Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_FlameSize, LVar0)
            Set(LVar1, 100)
            Loop(50)
                Sub(LVar1, 2)
                SetF(LVar2, LVar0)
                MulF(LVar2, LVar1)
                MulF(LVar2, Float(0.01))
                Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_FlameSize, LVar2)
                Wait(1)
            EndLoop
        EndThread
        Thread
            Wait(150)
            Set(LVar0, 14)
            Loop(14)
                Sub(LVar0, 1)
                Call(SetAnimatedModelRootPosition, VINE_2, 50, LVar0, 20)
                Wait(2)
            EndLoop
        EndThread
        Wait(212)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_HEAVY_NPC_LANDING)
        Call(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_LavaPiranha_Dead)
        Call(SetAnimation, ACTOR_BUD_1, PRT_MAIN, ANIM_LavaBud_Dead)
        Call(SetAnimation, ACTOR_BUD_2, PRT_MAIN, ANIM_LavaBud_Dead)
        PlayEffect(EFFECT_SHOCKWAVE, 0, -60, 0, 2)
        Thread
            Call(StartRumbleWithParams, 180, 16)
            Call(ShakeCam, CAM_BATTLE, 0, 5, Float(4.0))
        EndThread
        Wait(3)
        Call(SetActorPos, ACTOR_SELF, -60, 0, 0)
        Call(DropStarPoints, ACTOR_SELF)
        Call(PlaySoundAtActor, ACTOR_SELF, SOUND_ACTOR_DEATH)
        Wait(15)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
            Call(RemoveEffect, LVar0)
        EndIf
        Call(GetActorVar, ACTOR_BUD_1, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_FlameEffect, nullptr)
            Call(RemoveEffect, LVar0)
        EndIf
        Call(GetActorVar, ACTOR_BUD_2, AVAR_Common_FlameEffect, LVar0)
        IfNe(LVar0, nullptr)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_FlameEffect, nullptr)
            Call(RemoveEffect, LVar0)
        EndIf
        Wait(5)
        Call(SetActorFlagBits, ACTOR_BOSS, ACTOR_FLAG_NO_DMG_APPLY, true)
        Call(SetPartFlagBits, ACTOR_BOSS, PRT_MAIN, ACTOR_PART_FLAG_NO_TARGET, true)
        Call(SetPartFlagBits, ACTOR_BOSS, PRT_TARGET, ACTOR_PART_FLAG_NO_TARGET, true)
        Call(SetActorFlagBits, ACTOR_BUD_1, ACTOR_FLAG_NO_DMG_APPLY, true)
        Call(SetActorFlagBits, ACTOR_BUD_2, ACTOR_FLAG_NO_DMG_APPLY, true)
    EndIf
    Return
    End
};

static s32 FakeoutMusicTime = 0;

static EvtScript EVS_RemovePetitPiranha = {
    Call(ActorExists, LVar0, LVar1)
    IfEq(LVar1, 0)
        Return
    EndIf
    Call(GetActorHP, LVar0, LVar1)
    IfEq(LVar1, 0)
        Return
    EndIf
    Thread
        Call(SetAnimation, LVar0, 1, ANIM_PetitPiranha_Hurt)
        Wait(10)
        Set(LVar2, 0)
        Loop(24)
            Call(SetPartRotation, LVar0, 1, 0, LVar2, 0)
            Add(LVar2, 30)
            Wait(1)
        EndLoop
        Call(GetActorPos, LVar0, LVar3, LVar4, LVar5)
        PlayEffect(EFFECT_BIG_SMOKE_PUFF, LVar3, LVar4, LVar5)
        Set(LVar3, 0)
        Loop(12)
            Call(SetPartRotation, LVar0, 1, LVar3, LVar2, 0)
            Add(LVar3, 8)
            Wait(1)
        EndLoop
        Call(RemoveActor, LVar0)
    EndThread
    Return
    End
};

static s32 LavaPiranhaSinkPositions[] = {
    -1,  0, -1, -1, -1, -1, -2, -1,
    -2, -2, -2, -2, -3, -2, -3, -3,
    -3, -3, -3, -3, -4, -4, -3, -4,
    -4, -4, -5, -4, -4, -5, -5, -5,
    -4, -5, -6, -5, -5, -6, -5, -6,
    -5, -6, -6, -6, -6, -6, -7, -6,
    -6, -7, -6, -7, -6, 99
};

static s32 LavaBudSinkPositions[] = {
    -1,  0, -1,  0, -1, -1, -1, -2,
    -1, -2, -2, -1, -3, -2, -2, -3,
    -2, -3, -3, -3, -3, -4, -3, -4,
    -4, -3, -5, -4, -4, -3, -5, -5,
    -5, -5, -5, -5, -5, -6, -5, -6,
    -6, -6, -6, -6, -7, -6, -7, -7,
    -7, -7, -7, 99
};

static API_CALLABLE(GetFlamePosition) {
    Bytecode* args = script->ptrReadPos;
    s32 posX = evt_get_variable(script, *args++);
    s32 posY = evt_get_variable(script, *args++);
    f32 angle = evt_get_variable(script, *args++);
    s32 radius = evt_get_variable(script, *args++);
    s32 deltaY = evt_get_variable(script, *args++);

    posX = posX - cos_deg(angle) * radius;
    posY = (posY + deltaY) - sin_deg(angle) * radius;
    evt_set_variable(script, *args++, posX);
    evt_set_variable(script, *args++, posY);
    return ApiStatus_DONE2;
}

EvtScript EVS_Ignite = {
    Switch(LVar0)
        CaseEq(ACTOR_BUD_1)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_FlameSize, 35)
            Call(GetAnimatedPositionByTreeIndex, VINE_1, 8, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_1, 8, LVar4, LVar5, LVar6)
            Set(LVar7, 10)
            Set(LVar8, -15)
            Call(GetFlamePosition, LVar1, LVar2, LVar6, LVar7, LVar8, LVar3, LVar4)
            Call(GetPartOffset, ACTOR_BUD_1, PRT_MAIN, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            PlayEffect(EFFECT_FLAME, FX_FLAME_RED, LVar3, LVar4, LVar2, Float(0.3), LVarA)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_FlameEffect, LVarA)
            Call(SetIdleAnimations, ACTOR_BUD_1, PRT_MAIN, Ref(BudFieryAnims))
            Call(SetDefenseTable, ACTOR_BUD_1, PRT_MAIN, Ref(BudFieryDefense))
            Call(SetDefenseTable, ACTOR_BUD_1, PRT_TARGET, Ref(BudFieryDefense))
            Call(SetPartEventBits, ACTOR_BUD_1, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetPartEventBits, ACTOR_BUD_1, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_UnkAnim1, ANIM_LavaBud_IdleFiery)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_UnkAnim2, ANIM_LavaBud_HurtFiery)
            Call(SetActorVar, ACTOR_BUD_1, AVAR_Common_PiranhaState, PIRANHA_STATE_FIERY)
            Call(SetPartFlagBits, ACTOR_BUD_1, PRT_TARGET, ACTOR_PART_FLAG_NO_TARGET, false)
            Call(SetActorFlagBits, ACTOR_BUD_1, ACTOR_FLAG_NO_HEALTH_BAR, false)
        CaseEq(ACTOR_BUD_2)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_FlameSize, 35)
            Call(GetAnimatedPositionByTreeIndex, VINE_2, 8, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_2, 8, LVar4, LVar5, LVar6)
            Set(LVar7, 10)
            Set(LVar8, -15)
            Call(GetFlamePosition, LVar1, LVar2, LVar6, LVar7, LVar8, LVar3, LVar4)
            Call(GetPartOffset, ACTOR_BUD_2, PRT_MAIN, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            PlayEffect(EFFECT_FLAME, FX_FLAME_RED, LVar3, LVar4, LVar2, Float(0.3), LVarA)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_FlameEffect, LVarA)
            Call(SetIdleAnimations, ACTOR_BUD_2, PRT_MAIN, Ref(BudFieryAnims))
            Call(SetDefenseTable, ACTOR_BUD_2, PRT_MAIN, Ref(BudFieryDefense))
            Call(SetDefenseTable, ACTOR_BUD_2, PRT_TARGET, Ref(BudFieryDefense))
            Call(SetPartEventBits, ACTOR_BUD_2, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetPartEventBits, ACTOR_BUD_2, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_UnkAnim1, ANIM_LavaBud_IdleFiery)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_UnkAnim2, ANIM_LavaBud_HurtFiery)
            Call(SetActorVar, ACTOR_BUD_2, AVAR_Common_PiranhaState, PIRANHA_STATE_FIERY)
            Call(SetPartFlagBits, ACTOR_BUD_2, PRT_TARGET, ACTOR_PART_FLAG_NO_TARGET, false)
            Call(SetActorFlagBits, ACTOR_BUD_2, ACTOR_FLAG_NO_HEALTH_BAR, false)
        CaseDefault
            Call(SetActorVar, ACTOR_BOSS, AVAR_Common_FlameSize, 70)
            Call(GetAnimatedPositionByTreeIndex, VINE_0, 10, LVar1, LVar2, LVar3)
            Call(GetAnimatedRotationByTreeIndex, VINE_0, 10, LVar4, LVar5, LVar6)
            Set(LVar7, 30)
            Set(LVar8, -30)
            Call(GetFlamePosition, LVar1, LVar2, LVar6, LVar7, LVar8, LVar3, LVar4)
            Call(GetPartOffset, ACTOR_BOSS, PRT_MAIN, LVar0, LVar1, LVar2)
            Sub(LVar2, 3)
            PlayEffect(EFFECT_FLAME, FX_FLAME_RED, LVar3, LVar4, LVar2, Float(0.7), LVarA)
            Call(SetActorVar, ACTOR_BOSS, AVAR_Common_FlameEffect, LVarA)
            Call(SetIdleAnimations, ACTOR_BOSS, PRT_MAIN, Ref(FieryAnims))
            Call(SetDefenseTable, ACTOR_BOSS, PRT_MAIN, Ref(FieryDefense))
            Call(SetDefenseTable, ACTOR_BOSS, PRT_TARGET, Ref(FieryDefense))
            Call(SetPartEventBits, ACTOR_BOSS, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetPartEventBits, ACTOR_BOSS, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, true)
            Call(SetActorVar, ACTOR_BOSS, AVAR_Common_UnkAnim1, ANIM_LavaPiranha_TongueWag)
            Call(SetActorVar, ACTOR_BOSS, AVAR_Common_UnkAnim2, ANIM_LavaPiranha_Sleep)
            Call(SetActorVar, ACTOR_BOSS, AVAR_Common_PiranhaState, PIRANHA_STATE_FIERY)
            Call(ForceHomePos, ACTOR_SELF, 61, 61, 0)
            Call(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_NO_HEALTH_BAR, false)
    EndSwitch
    Return
    End
};

static EvtScript EVS_ComboHit = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
    IfEq(LVar0, PIRANHA_STATE_DEAD)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_LIGHT_HIT, VINE_0)
        Else
            Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_HEAVY_HIT, VINE_0)
        EndIf
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Wait(29)
        Wait(14)
    Else
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(LoadVineAnim, VINE_ANIM_BOSS_LIGHT_HIT, VINE_0)
        Else
            Call(LoadVineAnim, VINE_ANIM_BOSS_HEAVY_HIT, VINE_0)
        EndIf
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Wait(29)
        Wait(14)
    EndIf
    Return
    End
};

static EvtScript EVS_Hit = {
    ExecWait(EVS_Hit_Inner)
    Return
    End
};

static EvtScript EVS_Hit_Inner = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    // first phase
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
    IfFalse(LVar0)
        Call(GetLastDamage, ACTOR_SELF, LVar0)
        IfLt(LVar0, 4)
            Call(LoadVineAnim, VINE_ANIM_BOSS_LIGHT_HIT, VINE_0)
        Else
            Call(LoadVineAnim, VINE_ANIM_BOSS_HEAVY_HIT, VINE_0)
        EndIf
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Wait(29)
        Wait(14)
        Return
    EndIf
    // second phase
    IfFlag(LVarE, DAMAGE_TYPE_WATER | DAMAGE_TYPE_ICE)
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_STUNNED)
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_LIGHT_HIT, VINE_0)
            Else
                Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_HEAVY_HIT, VINE_0)
            EndIf
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Wait(29)
            Wait(14)
        Else
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_StunTurnsLeft, 2)
            Call(LoadVineAnim, VINE_ANIM_BOSS_HEAVY_HIT, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Call(GetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, LVar0)
            IfNe(LVar0, nullptr)
                Call(RemoveEffect, LVar0)
                Call(SetActorVar, ACTOR_SELF, AVAR_Common_FlameEffect, nullptr)
                Call(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
                PlayEffect(EFFECT_COLD_BREATH, 0, LVar0, LVar1, LVar2, Float(3.0), 50)
            EndIf
            Call(SetIdleAnimations, ACTOR_SELF, PRT_MAIN, Ref(StunnedAnims))
            Call(SetDefenseTable, ACTOR_SELF, PRT_MAIN, Ref(StunnedDefense))
            Call(SetDefenseTable, ACTOR_SELF, PRT_TARGET, Ref(StunnedDefense))
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, ANIM_LavaPiranha_Sleep)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim2, ANIM_LavaPiranha_Hurt)
            Call(SetPartEventBits, ACTOR_SELF, PRT_MAIN, ACTOR_EVENT_FLAG_FIREY, false)
            Call(SetPartEventBits, ACTOR_SELF, PRT_TARGET, ACTOR_EVENT_FLAG_FIREY, false)
            Wait(29)
            Call(PlaySoundAtActor, ACTOR_SELF, SOUND_LAVA_PIRANHA_WITHER)
            Call(LoadVineAnim, VINE_ANIM_BOSS_STUN, VINE_0)
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Wait(14)
            Call(SetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, PIRANHA_STATE_STUNNED)
        EndIf
    Else
        Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
        IfEq(LVar0, PIRANHA_STATE_STUNNED)
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_LIGHT_HIT, VINE_0)
            Else
                Call(LoadVineAnim, VINE_ANIM_BOSS_STUNNED_HEAVY_HIT, VINE_0)
            EndIf
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            Wait(29)
            Wait(14)
        Else
            Call(GetLastDamage, ACTOR_SELF, LVar0)
            IfLt(LVar0, 4)
                Call(LoadVineAnim, VINE_ANIM_BOSS_LIGHT_HIT, VINE_0)
            Else
                Call(LoadVineAnim, VINE_ANIM_BOSS_HEAVY_HIT, VINE_0)
            EndIf
            Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
            PlayEffect(EFFECT_EMBERS, 0, 80, 50, 0, 60, 50, Float(1.5), 36, 42, Float(0.8), Float(0.8))
            Wait(29)
            Wait(14)
        EndIf
    EndIf
    Return
    End
};

static EvtScript EVS_PlayIdleAnimation = {
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_UnkAnim1, LVar0)
    Call(SetAnimation, ACTOR_SELF, PRT_MAIN, LVar0)
    Call(GetActorVar, ACTOR_SELF, AVAR_Boss_IsSecondPhase, LVar0)
    IfFalse(LVar0)
        Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
        Return
    EndIf
    Call(GetActorVar, ACTOR_SELF, AVAR_Common_PiranhaState, LVar0)
    IfEq(LVar0, PIRANHA_STATE_STUNNED)
        Call(LoadVineAnim, VINE_ANIM_BOSS_TWITCH, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    Else
        Call(LoadVineAnim, VINE_ANIM_BOSS_IDLE, VINE_0)
        Call(PlayModelAnimation, VINE_0, VINE_0_BASE)
    EndIf
    Return
    End
};
