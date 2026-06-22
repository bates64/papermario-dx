#pragma once

#include "sprite/npc/Kolorado.h"

// Whale does not have a sprite.
// Instead, the Whale models are synced to to animations of a hidden
// dummy Kolorado NPC. This allows the Whale to be controlled just
// like any other NPC (e.g., using the Speech API calls).
//
// The mapping between Whale and Kolorado animations are arbitrary,
// they need only exist as valid animations in his sprite. He was
// probably chosen simply because he's already present in every map
// where the Whale is.

#define XNIM_Whale_Idle         ANIM_Kolorado_Still
#define XNIM_Whale_Swim         ANIM_Kolorado_Idle
#define XNIM_Whale_OpenMouth    ANIM_Kolorado_Yell
#define XNIM_Whale_CloseMouth   ANIM_Kolorado_IdleSad

#define XNIM_Whale_Talk         ANIM_Kolorado_Walk
#define XNIM_Whale_Sleep        ANIM_Kolorado_WalkSad
#define XNIM_Whale_Shiver       ANIM_Kolorado_Run
#define XNIM_Whale_Shake        ANIM_Kolorado_Panic

#define XNIM_Whale_Sick         ANIM_Kolorado_Talk
#define XNIM_Whale_Spout        ANIM_Kolorado_Shout
#define XNIM_Whale_Still        ANIM_Kolorado_TalkSad
// unused -- ANIM_Kolorado_Fallen

#define XNIM_Whale_WakeUp       ANIM_Kolorado_HurtStill
// unused -- ANIM_Kolorado_Hurt
// unused -- ANIM_Kolorado_Thrown
