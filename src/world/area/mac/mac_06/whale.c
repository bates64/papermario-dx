#include "mac_06.h"

#define WHALE_MODEL_TONGUE      MODEL_bero
#define WHALE_MODEL_EYES_OPEN   MODEL_o170
#define WHALE_MODEL_EYES_SHUT   MODEL_o183
#define WHALE_MODEL_JAW         MODEL_o173
#define WHALE_MODEL_LFIN        MODEL_o167
#define WHALE_MODEL_RFIN        MODEL_o168
#define WHALE_MODEL_GROUP_BODY  MODEL_dou
#define WHALE_MODEL_BODY        MODEL_karada
#define WHALE_MODEL_BELLY       MODEL_onaka
#define WHALE_HEAD_OFFSET       70.0f
#define WHALE_ROOT_OFFSET_X     130
#define WHALE_SHOUT_FIN_PERIOD  25
#define WHALE_WALK_ANGLE        30
#define WHALE_RESET_GEYSER_VAR

#include "world/common/atomic/WhaleGeyser.inc.c"
#include "world/common/atomic/WhaleAnim.inc.c"
