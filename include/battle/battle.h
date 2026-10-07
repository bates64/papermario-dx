#ifndef _BATTLE_BATTLE_H_
#define _BATTLE_BATTLE_H_

#include "common.h"
#include "bound_script.h"
#include "message_ids.h"

// Terminates foreground model lists
#define STAGE_MODEL_LIST_END 0

enum BattlePositions {
    BTL_POS_GROUND_A  = 0,
    BTL_POS_GROUND_B  = 1,
    BTL_POS_GROUND_C  = 2,
    BTL_POS_GROUND_D  = 3,
    BTL_POS_AIR_A     = 4,
    BTL_POS_AIR_B     = 5,
    BTL_POS_AIR_C     = 6,
    BTL_POS_AIR_D     = 7,
    BTL_POS_HIGH_A    = 8,
    BTL_POS_HIGH_B    = 9,
    BTL_POS_HIGH_C    = 10,
    BTL_POS_HIGH_D    = 11,
    BTL_POS_TOP_A     = 12,
    BTL_POS_TOP_B     = 13,
    BTL_POS_TOP_C     = 14,
    BTL_POS_TOP_D     = 15,
    BTL_POS_CENTER    = 16,
};

enum BattleVars {
    BTL_VAR_DuplighostCopyFlags         = 0, // used by duplighost
    BTL_VAL_Duplighost_HasCopied        = 0x4,
    BTL_VAR_HyperSync                   = 1,
    BTL_VAL_HyperSync_None              = 0,
    BTL_VAL_HyperSync_Done              = 1,
    BTL_VAL_HyperSync_Active            = 2,
    // index of the last enemy boosted by a magikoopa
    // intended to prevent multiple boosts for the same actor in the same turn
    // selected enemies go from left to right and are reset if none are found
    BTL_VAR_Magikoopa_LastIndexBoosted  = 2,
    BTL_VAR_LastCopiedPartner           = 3, // used by duplighost
    BTL_VAR_KoopatrolSummonCount_0      = 4, // count summons from Koopatrol and 'children' originally from column 0
    BTL_VAR_KoopatrolSummonCount_1      = 5, // count summons from Koopatrol and 'children' originally from column 1
    BTL_VAR_KoopatrolSummonCount_2      = 6, // count summons from Koopatrol and 'children' originally from column 2
    BTL_VAR_KoopatrolSummonCount_3      = 7, // count summons from Koopatrol and 'children' originally from column 3
};

// document special actor vars referenced from other actors
enum CommonActorVars {
    AVAR_DryBones_Collapsed             = 8,
    AVAR_SpearGuy_Generation            = 1,
    AVAR_JungleFuzzy_Generation         = 0,
};

EXTERN_C s32 bActorNames[];

typedef struct ActorBlueprint {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s16 maxHP;
    /* 0x06 */ u8 type;
    /* 0x07 */ u8 level;
    /* 0x08 */ s16 partCount;
    /* 0x0A */ PAD(2);
    /* 0x0C */ struct ActorPartBlueprint* partsData;
    /* 0x10 */ EvtScript* initScript;
    /* 0x14 */ s32* statusTable;
    /* 0x18 */ u8 escapeChance;
    /* 0x19 */ u8 airLiftChance;
    /* 0x1A */ u8 hurricaneChance;
    /* 0x1B */ u8 spookChance;
    /* 0x1C */ u8 upAndAwayChance;
    /* 0x1D */ u8 spinSmashReq;
    /* 0x1E */ u8 powerBounceChance;
    /* 0x1F */ u8 coinReward;
    /* 0x20 */ Vec2b size;
    /* 0x22 */ Vec2b healthBarOffset;
    /* 0x24 */ Vec2b statusIconOffset;
    /* 0x26 */ Vec2b statusTextOffset;
} ActorBlueprint; // size = 0x28

/// Define public actor-overlay descriptors. Internal blueprints remain ordinary ActorBlueprint variables.
/// OVL_DEF_ACTOR() selects the default; OVL_DEF_ACTOR(name) takes an identifier token.
#define OVL_DEF_ACTOR(...) export ActorBlueprint _OVL_DEF_ACTOR_SYMBOL(__VA_ARGS__)
#define _OVL_DEF_ACTOR_SYMBOL(...) blueprint ## __VA_OPT__(_) ## __VA_ARGS__

#define ACTOR_BLUEPRINT_EXPORT_NAME "blueprint"
#define ACTOR_KEY_MAX 64

/// Split overlay[:variant], returning the variant (empty for the default) or nullptr if malformed.
const char* split_actor_ref(const char* ref, char overlay[ACTOR_KEY_MAX]);

typedef struct FormationRow {
    /* 0x00 */ ActorBlueprint* actor; ///< Direct blueprint when `overlay` is nullptr.
    /* 0x04 */ const char* overlay; ///< Actor reference: overlay or overlay:variant; nullptr selects a direct blueprint.
    /* 0x08 */ union {
    /*      */     s32    index;
    /*      */     Vec3i* vec;
    /* 0x08 */ } home;
    /* 0x0C */ s32 priority; ///< Actors with higher priority values take their turn first.
    /* 0x10 */ s32 var0;
    /* 0x14 */ s32 var1;
    /* 0x18 */ s32 var2;
    /* 0x1C */ s32 var3;
} FormationRow; // size = 0x20 * n

typedef FormationRow Formation[];

/// A battle stage. Its geometry is the stage.xml in its directory.
typedef struct Stage {
    /* 0x00 */ const char* texture;
    /* 0x04 */ EvtScript* preBattle;        // sets BattleStatus::controlScript on battle start
    /* 0x08 */ EvtScript* postBattle;       // sets BattleStatus::controlScript on battle end
    /* 0x0C */ const char* bg;
    /* 0x10 */ s32* foregroundModelList;
    /* 0x14 */ s32 stageEnemyCount;         // number of enemies in the stageFormation
    /* 0x18 */ Formation* stageFormation;   // extra enemies native to this stage
    /* 0x1C */ s32 stageEnemyChance;        // 1/(N+1) chance for stageFormation enemies to spawn
} Stage; // size = 0x20

#define BATTLE_STAGE_EXPORT_NAME "gBattleStage"

/// Define the descriptors exported by a battle-stage overlay, one per variant of the stage.
/// OVL_DEF_STAGE() is the default, and OVL_DEF_STAGE(name) the variant overlay:name.
#define OVL_DEF_STAGE(...) export Stage _OVL_DEF_STAGE_SYMBOL(__VA_ARGS__)
#define _OVL_DEF_STAGE_SYMBOL(...) gBattleStage ## __VA_OPT__(_) ## __VA_ARGS__

/// Load a stage by reference, such as "trd_05" or the variant "trd_05:b".
Stage* load_battle_stage(const char* ref);

/// The loaded stage's model data in the map filesystem, such as b_trd_05_shape.
extern char gBattleStageShapeName[];
/// The loaded stage's collision data in the map filesystem, such as b_trd_05_hit.
extern char gBattleStageHitName[];

/// Release only after battle scripts/actors are gone and the renderer has switched to the world.
void unload_battle_stage(void);

/// A named formation and its default stage within a battle-area overlay.
typedef struct Battle {
    /* 0x00 */ const char* name; ///< Stable formation key, unique within its area.
    /* 0x04 */ s32 formationSize;
    /* 0x08 */ Formation* formation;
    /* 0x0C */ const char* stage;         // stage overlay name
    /* 0x10 */ EvtScript* onBattleStart;    // sets BattleStatus::controlScript on battle start, overrides Stage::preBattle
} Battle; // size = 0x14

typedef Battle BattleList[];

/// Descriptor exported by a battle-area overlay. Tables use explicit counts, not terminators.
typedef struct BattleArea {
    /* 0x00 */ BattleList* battles;
    /* 0x04 */ s32 battleCount;
} BattleArea; // size = 0x08

#define BATTLE_AREA_EXPORT_NAME "gBattleArea"

/// Define a battle-area descriptor from its BattleList, without a terminator.
#define OVL_DEF_BATTLE_AREA(battleList) \
    export const BattleArea gBattleArea = { \
        .battles = &(battleList), \
        .battleCount = ARRAY_COUNT(battleList), \
    }

#define BATTLE_REF_MAX 128
#define BATTLE_KEY_MAX 64

// Returns the area/key split, or nullptr for a malformed reference.
const char* split_battle_ref(const char* ref, char area[BATTLE_KEY_MAX]);

const BattleArea* get_loaded_battle_area(void);

// Like the stage, the area must outlive all battle scripts, actors, and rendering.
void unload_battle_area(void);

#define BATTLE(formation, stage) { #formation, ARRAY_COUNT(formation), (Formation*) formation, stage }
#define BATTLE_WITH_SCRIPT(formation, stage, script) { #formation, ARRAY_COUNT(formation), (Formation*) formation, stage, &script }

/// Formation entry for an actor located in an overlay
/// Select OVL_DEF_ACTOR() with "overlay", or OVL_DEF_ACTOR(name) with "overlay:name"
#define OVL_ACTOR_BY_IDX(_ref, _idx, _priority, args...) { .overlay = _ref, .home = { .index = _idx }, .priority = _priority, args }
#define OVL_ACTOR_BY_POS(_ref, _pos, _priority, args...) { .overlay = _ref, .home = { .vec = &_pos }, .priority = _priority, args }

/// Formation entry for an internal actor in the current overlay (e.g., "hole" in monty_mole)
#define RAW_ACTOR_BY_IDX(_name, _idx, _priority, args...) { .actor = &_name, .home = { .index = _idx }, .priority = _priority, args }
#define RAW_ACTOR_BY_POS(_name, _pos, _priority, args...) { .actor = &_name, .home = { .vec = &_pos }, .priority = _priority, args }

typedef struct ActorSounds {
    /* 0x00 */ s32 walk[2];
    /* 0x08 */ s32 fly[2];
    /* 0x10 */ s32 jump;
    /* 0x14 */ s32 hurt;
    /* 0x18 */ s16 delay[2]; ///< Number of frames to wait between walk/fly sounds. Negative values are in distance.
} ActorSounds; // size = 0x1C

EXTERN_C ActorSounds bActorSoundTable[];

typedef struct ActorOffsets {
    /* 0x00 */ Vec3b tattleCam;
    /* 0x03 */ s8 shadow;
} ActorOffsets; // size = 0x04

typedef struct CelebrationAnimEntry {
    /* 0x00 */ s32 weight;
    /* 0x04 */ AnimID anim;
} CelebrationAnimEntry;

typedef CelebrationAnimEntry CelebrationOptionSet[8];

typedef struct CelebrationAnimOptions {
    /* 0x00 */ s16 randomChance;
    /* 0x02 */ s16 hpBasedChance;
    /* 0x04 */ CelebrationOptionSet options[5];
} CelebrationAnimOptions; // size = 0x144

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

extern Battle* gCurrentBattlePtr;

extern ActorOffsets bActorOffsets[];

void load_demo_battle(u32 index);
Actor* create_actor(Formation formation);

#define EXEC_DEATH_NO_SPINNING -12345
#define ACTOR_API_SKIP_ARG -12345678

#define DANGER_THRESHOLD  5
#define PERIL_THRESHOLD   1

#define POPUP_MSG_ON 99
#define POPUP_MSG_OFF 0

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
