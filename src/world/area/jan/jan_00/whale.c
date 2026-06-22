#include "jan_00.h"

#define WHALE_NPC_ID            NPC_Whale
#define WHALE_MODEL_TONGUE      MODEL_bero
#define WHALE_MODEL_EYES_OPEN   MODEL_o170
#define WHALE_MODEL_EYES_SHUT   MODEL_o183
#define WHALE_MODEL_JAW         MODEL_o173
#define WHALE_MODEL_LFIN        MODEL_o167
#define WHALE_MODEL_RFIN        MODEL_o168
#define WHALE_MODEL_GROUP_BODY  MODEL_dou
#define WHALE_MODEL_BODY        MODEL_karada
#define WHALE_MODEL_BELLY       MODEL_onaka

#define WHALE_HEAD_OFFSET       170.0f
#define WHALE_ROOT_OFFSET_X     55

#define WHALE_COLLIDER_SPEAK    NO_COLLIDER
#define WHALE_COLLIDER_SIDES    NO_COLLIDER

#include "world/common/prefab/Whale.inc.c"
