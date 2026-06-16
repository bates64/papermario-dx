#pragma once
#include "npc.h"
#include "sprite/npc/Goompa.h"
#include "sprite/npc/Gooma.h"
#include "sprite/npc/Goompapa.h"
#include "sprite/npc/Goomama.h"
#include "sprite/npc/Goombaria.h"

#define GOOMPA_ANIMS \
{ \
    .idle   = ANIM_Goompa_Idle, \
    .walk   = ANIM_Goompa_Walk, \
    .run    = ANIM_Goompa_Run, \
    .chase  = ANIM_Goompa_Run, \
    .alert  = ANIM_Goompa_Idle, \
    .unused = ANIM_Goompa_Idle, \
    .death  = ANIM_Goompa_Still, \
    .hit    = ANIM_Goompa_Still, \
    .anim_8 = ANIM_Goompa_Run, \
    .anim_9 = ANIM_Goompa_Run, \
    .anim_A = ANIM_Goompa_Run, \
    .anim_B = ANIM_Goompa_Run, \
    .anim_C = ANIM_Goompa_Run, \
    .anim_D = ANIM_Goompa_Run, \
    .anim_E = ANIM_Goompa_Run, \
    .anim_F = ANIM_Goompa_Run, \
}

#define GOOMA_ANIMS \
{ \
    .idle   = ANIM_Gooma_Idle, \
    .walk   = ANIM_Gooma_Walk, \
    .run    = ANIM_Gooma_Run, \
    .chase  = ANIM_Gooma_Run, \
    .alert  = ANIM_Gooma_Idle, \
    .unused = ANIM_Gooma_Idle, \
    .death  = ANIM_Gooma_Still, \
    .hit    = ANIM_Gooma_Still, \
    .anim_8 = ANIM_Gooma_Run, \
    .anim_9 = ANIM_Gooma_Run, \
    .anim_A = ANIM_Gooma_Run, \
    .anim_B = ANIM_Gooma_Run, \
    .anim_C = ANIM_Gooma_Run, \
    .anim_D = ANIM_Gooma_Run, \
    .anim_E = ANIM_Gooma_Run, \
    .anim_F = ANIM_Gooma_Run, \
}

#define GOOMPAPA_ANIMS \
{ \
    .idle   = ANIM_Goompapa_Idle, \
    .walk   = ANIM_Goompapa_Walk, \
    .run    = ANIM_Goompapa_Run, \
    .chase  = ANIM_Goompapa_Run, \
    .alert  = ANIM_Goompapa_Idle, \
    .unused = ANIM_Goompapa_Idle, \
    .death  = ANIM_Goompapa_Still, \
    .hit    = ANIM_Goompapa_Still, \
    .anim_8 = ANIM_Goompapa_Run, \
    .anim_9 = ANIM_Goompapa_Run, \
    .anim_A = ANIM_Goompapa_Run, \
    .anim_B = ANIM_Goompapa_Run, \
    .anim_C = ANIM_Goompapa_Run, \
    .anim_D = ANIM_Goompapa_Run, \
    .anim_E = ANIM_Goompapa_Run, \
    .anim_F = ANIM_Goompapa_Run, \
}

#define GOOMAMA_ANIMS \
{ \
    .idle   = ANIM_Goomama_Idle, \
    .walk   = ANIM_Goomama_Walk, \
    .run    = ANIM_Goomama_Run, \
    .chase  = ANIM_Goomama_Run, \
    .alert  = ANIM_Goomama_Idle, \
    .unused = ANIM_Goomama_Idle, \
    .death  = ANIM_Goomama_Still, \
    .hit    = ANIM_Goomama_Still, \
    .anim_8 = ANIM_Goomama_Run, \
    .anim_9 = ANIM_Goomama_Run, \
    .anim_A = ANIM_Goomama_Run, \
    .anim_B = ANIM_Goomama_Run, \
    .anim_C = ANIM_Goomama_Run, \
    .anim_D = ANIM_Goomama_Run, \
    .anim_E = ANIM_Goomama_Run, \
    .anim_F = ANIM_Goomama_Run, \
}

#define GOOMBARIO_ANIMS \
{ \
    .idle   = ANIM_WorldGoombario_Idle, \
    .walk   = ANIM_WorldGoombario_Walk, \
    .run    = ANIM_WorldGoombario_Run, \
    .chase  = ANIM_WorldGoombario_Run, \
    .alert  = ANIM_WorldGoombario_Idle, \
    .unused = ANIM_WorldGoombario_Idle, \
    .death  = ANIM_WorldGoombario_Still, \
    .hit    = ANIM_WorldGoombario_Still, \
    .anim_8 = ANIM_WorldGoombario_Run, \
    .anim_9 = ANIM_WorldGoombario_Run, \
    .anim_A = ANIM_WorldGoombario_Run, \
    .anim_B = ANIM_WorldGoombario_Run, \
    .anim_C = ANIM_WorldGoombario_Run, \
    .anim_D = ANIM_WorldGoombario_Run, \
    .anim_E = ANIM_WorldGoombario_Run, \
    .anim_F = ANIM_WorldGoombario_Run, \
}

#define GOOMBARIA_ANIMS \
{ \
    .idle   = ANIM_Goombaria_Idle, \
    .walk   = ANIM_Goombaria_Walk, \
    .run    = ANIM_Goombaria_Run, \
    .chase  = ANIM_Goombaria_Run, \
    .alert  = ANIM_Goombaria_Idle, \
    .unused = ANIM_Goombaria_Idle, \
    .death  = ANIM_Goombaria_Still, \
    .hit    = ANIM_Goombaria_Still, \
    .anim_8 = ANIM_Goombaria_Run, \
    .anim_9 = ANIM_Goombaria_Run, \
    .anim_A = ANIM_Goombaria_Run, \
    .anim_B = ANIM_Goombaria_Run, \
    .anim_C = ANIM_Goombaria_Run, \
    .anim_D = ANIM_Goombaria_Run, \
    .anim_E = ANIM_Goombaria_Run, \
    .anim_F = ANIM_Goombaria_Run, \
}
