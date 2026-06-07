#pragma once

#define AI_TEMP_STATE                  functionTemp[0]
#define AI_TEMP_STATE_AFTER_SUSPEND    functionTemp[1]

// macros for storing floating point values into enemy vars
#define AI_CEIL_FLT(x)   ((s32)(((x) * 100.0f) + 0.5f))
#define AI_PACK_FLT(x)   ((s32)((x) * 100.0f))
#define AI_UNPACK_FLT(x) ((f32)(x) / 100.0f)

#define ENEMY_INTANGIBLE_FLAGS \
    ( ENEMY_FLAG_SKIP_BATTLE \
    | ENEMY_FLAG_CANT_INTERACT \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    | ENEMY_FLAG_IGNORE_HAMMER \
    | ENEMY_FLAG_IGNORE_PARTNER \
    )

enum BasicAIStates {
    AI_STATE_WANDER_INIT            = 0,
    AI_STATE_WANDER                 = 1,
    AI_STATE_PATROL_INIT            = 0,
    AI_STATE_PATROL                 = 1,
    AI_STATE_HOP_INIT               = 0,
    AI_STATE_HOP                    = 1,
    AI_STATE_LOITER_INIT            = 2,
    AI_STATE_LOITER                 = 3,
    AI_STATE_LOITER_POST            = 4,
    AI_STATE_ALERT_INIT             = 10,
    AI_STATE_ALERT                  = 11,
    AI_STATE_CHASE_INIT             = 12,
    AI_STATE_CHASE                  = 13,
    AI_STATE_LOSE_PLAYER            = 14,
    AI_STATE_PATROL_RESUME          = 15,
    AI_STATE_SUSPEND                = 99,
};

void ai_suspend_for_time(Evt* script);
void basic_ai_suspend(Evt* script);

b32 ai_check_fwd_collisions(Npc* npc, f32 time, f32* outYaw, f32* outDistFwd, f32* outDistCW, f32* outDistCCW);
b32 is_point_outside_territory(s32 shape, f32 centerX, f32 centerZ, f32 pointX, f32 pointZ, f32 sizeX, f32 sizeZ);
b32 basic_ai_check_player_dist(EnemyDetectVolume* detect, Enemy* enemy, f32 radius, f32 fwdPosOffset, b8 useWorldYaw);
b32 ai_check_player_dist(Enemy* enemy, s32 chance, f32 radius, f32 moveSpeed);

void ai_enemy_play_sound(Npc* npc, s32 soundID, s32 upperSoundFlags);
void ai_try_set_state(Evt* script, s32 state);

// convenience wrappers for is_point_outside_territory
b32 is_point_outside_wander_territory(EnemyTerritoryWander* wander, f32 pointX, f32 pointZ);
b32 is_point_outside_detect_volume(EnemyDetectVolume* detect, f32 pointX, f32 pointZ);

// function signature used for state handlers in AI main functions
typedef void AIStateHandler(Evt* script, MobileAISettings* settings, EnemyDetectVolume* detect);

AIStateHandler(basic_ai_wander_init);
AIStateHandler(basic_ai_wander);
AIStateHandler(basic_ai_loiter_init);
AIStateHandler(basic_ai_loiter);
AIStateHandler(basic_ai_found_player_jump_init);
AIStateHandler(basic_ai_found_player_jump);
AIStateHandler(basic_ai_chase_init);
AIStateHandler(basic_ai_chase);
AIStateHandler(basic_ai_lose_player);

API_CALLABLE(BasicAI_Main);
