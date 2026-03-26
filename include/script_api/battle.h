#ifndef _SCRIPT_API_BATTLE_H_
#define _SCRIPT_API_BATTLE_H_

#include "common_structs.h"
#include "evt.h"

#include "script_api/common.h"
#include "battle/action_cmd.h"

#include "effects.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/// @evtapi
/// @param presetIndex
API_CALLABLE(UseBattleCamPreset);

/// @evtapi
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetBattleCamTarget);

/// @evtapi
/// @param offsetY
API_CALLABLE(SetBattleCamOffsetY);

/// @evtapi
/// @param offsetY
API_CALLABLE(AddBattleCamOffsetY);

/// @evtapi
/// @param yaw
API_CALLABLE(SetBattleCamYaw);

/// @evtapi
/// @param actorID
API_CALLABLE(BattleCamTargetActor);

/// @evtapi
/// @param duration
API_CALLABLE(MoveBattleCamOver);

/// @evtapi
/// @param dist
API_CALLABLE(SetBattleCamDist);

/// @evtapi
/// @param dist
API_CALLABLE(AddBattleCamDist);

/// @evtapi
/// @param frozen
API_CALLABLE(FreezeBattleCam);

/// @evtapi
/// @param disable
API_CALLABLE(DisableBattleCamClampX);

/// @evtapi
/// @param messageIndex
/// @param duration
API_CALLABLE(ShowMessageBox);

/// @evtapi
/// @param messageIndex
/// @param duration
/// @param varValue
API_CALLABLE(ShowVariableMessageBox);

/// @evtapi
/// @param outResult
API_CALLABLE(IsMessageBoxDisplayed);

/// @evtapi
API_CALLABLE(WaitForMessageBoxDone);

/// @evtapi
API_CALLABLE(ForceCloseMessageBox);

/// @evtapi
/// @param duration
API_CALLABLE(SetMessageBoxDuration);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(ItemDamageEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param status
/// @param statusChance
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(ItemAfflictEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param debuffType
/// @param spookChance
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(ItemSpookEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(ItemCheckHit);

/// @evtapi
/// @param messageID
/// @param actorID
/// @param partIndex
/// @param talkAnim
/// @param idleAnim
API_CALLABLE(ActorSpeak);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param talkAnim
/// @param idleAnim
API_CALLABLE(EndActorSpeech);

/// @evtapi
/// @param messageID
/// @evtout LVar0 selectedIndex
API_CALLABLE(ShowBattleChoice);

/// @evtapi
/// @param addr
API_CALLABLE(OverrideBattleDmaDest);

/// @evtapi
/// @param index
API_CALLABLE(LoadBattleDmaData);

/// @evtapi
/// @param enable
API_CALLABLE(EnableBattleFloorReflections);

/// @evtapi
/// @param mode
API_CALLABLE(SetDarknessMode);

/// @evtapi
/// @param actorID
/// @param soundID
API_CALLABLE(PlaySoundAtActor);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param soundID
API_CALLABLE(PlaySoundAtPart);

/// @evtapi
/// @param visible
API_CALLABLE(SetForegroundModelsVisibleUnchecked);

/// @evtapi
/// @param visible
API_CALLABLE(SetForegroundModelsVisible);

/// @evtapi
/// @param outStatus
/// @param typeFlag
/// @param chance
/// @param duration
API_CALLABLE(MakeStatusField);

/// @evtapi
/// @param outValue
API_CALLABLE(MultiplyByActorScale);

/// @evtapi
/// @param outX
/// @param outY
API_CALLABLE(MultiplyVec2ByActorScale);

/// @evtapi
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(MultiplyVec3ByActorScale);

/// @evtapi
/// @param outDamage
API_CALLABLE(ApplyShrinkFromOwner);

/// @evtapi
/// @param type
API_CALLABLE(StartRumble);

/// @evtapi
/// @evtout LVar0 result
API_CALLABLE(HasMerleeCastsLeft);

/// @evtapi
/// @param x
/// @param y
/// @param z
/// @param amount
API_CALLABLE(SpawnRecoverHeartFX);

/// @evtapi
/// @param x
/// @param y
/// @param z
/// @param amount
API_CALLABLE(SpawnRecoverFlowerFX);

/// @evtapi
API_CALLABLE(IncrementPlayerHP);

/// @evtapi
API_CALLABLE(IncrementPlayerFP);

/// @evtapi
/// @param frequency
/// @param duration
API_CALLABLE(StartRumbleWithParams);

/// @evtapi
/// @evtout LVar0 itemScript
/// @evtout LVar1 success
API_CALLABLE(LoadItemScript);

/// @evtapi
API_CALLABLE(LoadMoveScript);

/// @evtapi
/// @param battleSection
API_CALLABLE(LoadBattleSection);

/// @evtapi
/// @param outPhase
API_CALLABLE(GetBattlePhase);

/// @evtapi
/// @param outElement
API_CALLABLE(GetLastElement);

/// @evtapi
/// @param damageSource
API_CALLABLE(SetDamageSource);

/// @evtapi
/// @param outDamageSource
API_CALLABLE(GetDamageSource);

/// @evtapi
/// @param actorID
API_CALLABLE(SetGoalToHome);

/// @evtapi
/// @param actorID
API_CALLABLE(SetIdleGoalToHome);

/// @evtapi
/// @param actorID
/// @param index
API_CALLABLE(SetGoalToIndex);

/// @evtapi
/// @param actorID
/// @param outIndex
API_CALLABLE(GetIndexFromPos);

/// @evtapi
/// @param actorID
/// @param outIndex
API_CALLABLE(GetIndexFromHome);

/// @evtapi
/// @param actorID
/// @param targetSelectionFlags
/// @param outCount
API_CALLABLE(CountTargets);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(ForceHomePos);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetHomePos);

/// @evtapi
/// @param actorID
API_CALLABLE(SetGoalToTarget);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(SetPartGoalToTarget);

/// @evtapi
/// @param actorID
API_CALLABLE(SetGoalToFirstTarget);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetGoalPos);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetIdleGoal);

/// @evtapi
/// @param actorID
/// @param dx
/// @param dy
/// @param dz
API_CALLABLE(AddGoalPos);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetGoalPos);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetIdleGoal);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartTarget);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetActorPos);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartPos);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetHomePos);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetActorPos);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPartPos);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param offsetX
/// @param offsetY
API_CALLABLE(SetEnemyTargetOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param animID
API_CALLABLE(SetAnimation);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outAnimID
API_CALLABLE(GetAnimation);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param rate
API_CALLABLE(SetAnimationRate);

/// @evtapi
/// @param actorID
/// @param yaw
API_CALLABLE(SetActorYaw);

/// @evtapi
/// @param actorID
/// @param outYaw
API_CALLABLE(GetActorYaw);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param yaw
API_CALLABLE(SetPartYaw);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outYaw
API_CALLABLE(GetPartYaw);

/// @evtapi
/// @param actorID
/// @param jumpScale
API_CALLABLE(SetActorJumpGravity);

/// @evtapi
/// @param actorID
/// @param jumpScale
API_CALLABLE(SetActorIdleJumpGravity);

/// @evtapi
/// @param actorID
/// @param moveSpeed
API_CALLABLE(SetActorSpeed);

/// @evtapi
/// @param actorID
/// @param moveSpeed
API_CALLABLE(SetActorIdleSpeed);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param jumpScale
API_CALLABLE(SetPartJumpGravity);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param moveSpeed
API_CALLABLE(SetPartMoveSpeed);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param jumpRise
/// @param jumpFall
/// @param jumpLand
API_CALLABLE(SetJumpAnimations);

/// @evtapi
/// @param actorID
/// @param dx
/// @param dy
/// @param dz
API_CALLABLE(AddActorPos);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetActorDispOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartDispOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPartDispOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param dx
/// @param dy
/// @param dz
API_CALLABLE(AddPartDispOffset);

/// @evtapi
/// @param freeze
API_CALLABLE(FreezeBattleState);

/// @evtapi
/// @param actorID
/// @param varIndex
/// @param outValue
API_CALLABLE(GetActorVar);

/// @evtapi
/// @param actorID
/// @param varIndex
/// @param value
API_CALLABLE(SetActorVar);

/// @evtapi
/// @param actorID
/// @param varIndex
/// @param amount
API_CALLABLE(AddActorVar);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param varIndex
/// @param outValue
API_CALLABLE(GetPartMovementVar);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param varIndex
/// @param value
API_CALLABLE(SetPartMovementVar);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param varIndex
/// @param amount
API_CALLABLE(AddPartMovementVar);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetActorRotation);

/// @evtapi
/// @param actorID
/// @param dx
/// @param dy
/// @param dz
API_CALLABLE(SetActorRotationOffset);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetActorRotation);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPartRotation);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param dx
/// @param dy
/// @param dz
API_CALLABLE(SetPartRotationOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartRotation);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetActorScale);

/// @evtapi
/// @param actorID
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetActorScaleModifier);

/// @evtapi
/// @param actorID
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetActorScale);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
API_CALLABLE(SetPartScale);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outX
/// @param outY
/// @param outZ
API_CALLABLE(GetPartScale);

/// @evtapi
/// @param outFlags
API_CALLABLE(GetBattleFlags);

/// @evtapi
/// @param flags
/// @param mode
API_CALLABLE(SetBattleFlagBits);

/// @evtapi
/// @param outFlags
API_CALLABLE(GetBattleFlags2);

/// @evtapi
/// @param flags
/// @param mode
API_CALLABLE(SetBattleFlagBits2);

/// @evtapi
/// @param actorID
/// @param flags
API_CALLABLE(SetActorFlags);

/// @evtapi
/// @param actorID
/// @param flags
/// @param mode
API_CALLABLE(SetActorFlagBits);

/// @evtapi
/// @param actorID
/// @param outFlags
API_CALLABLE(GetActorFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
API_CALLABLE(SetPartFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
/// @param mode
API_CALLABLE(SetPartFlagBits);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
API_CALLABLE(SetPartTargetFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
/// @param mode
API_CALLABLE(SetPartTargetFlagBits);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outFlags
API_CALLABLE(GetPartFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outFlags
API_CALLABLE(GetPartTargetFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
API_CALLABLE(SetPartEventFlags);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param flags
/// @param mode
API_CALLABLE(SetPartEventBits);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outFlags
API_CALLABLE(GetPartEventFlags);

/// @evtapi
/// @param actorID
API_CALLABLE(HPBarToHome);

/// @evtapi
/// @param actorID
API_CALLABLE(HPBarToCurrent);

/// @evtapi
/// @param actorID
/// @param offsetX
/// @param offsetY
API_CALLABLE(SetHPBarOffset);

/// @evtapi
/// @param actorID
/// @param iconOffsetX
/// @param iconOffsetY
/// @param textOffsetX
/// @param textOffsetY
API_CALLABLE(SetActorStatusOffsets);

/// @evtapi
/// @param formationPtr
/// @param priority
/// @evtout LVar0 newActorID
API_CALLABLE(SummonEnemy);

/// @evtapi
/// @param outActorID
API_CALLABLE(GetOwnerID);

/// @evtapi
/// @param actorID
API_CALLABLE(SetOwnerID);

/// @evtapi
/// @param actorID
/// @param outExists
API_CALLABLE(ActorExists);

/// @evtapi
/// @param starPowersMask
API_CALLABLE(SetEnabledStarPowers);

/// @evtapi
/// @param mask
API_CALLABLE(SetBattleInputMask);

/// @evtapi
/// @param down
/// @param pressed
/// @param held
API_CALLABLE(SetBattleInputButtons);

/// @evtapi
/// @param buttons
/// @param outResult
API_CALLABLE(CheckButtonPress);

/// @evtapi
/// @param buttons
/// @param outResult
API_CALLABLE(CheckButtonHeld);

/// @evtapi
/// @param buttons
/// @param outResult
API_CALLABLE(CheckButtonDown);

/// @evtapi
/// @param outState
API_CALLABLE(GetBattleState);

/// @evtapi
/// @param targetSelectionFlags
API_CALLABLE(CreateCurrentPosTargetList);

/// @evtapi
/// @param targetSelectionFlags
API_CALLABLE(CreateHomeTargetList);

/// @evtapi
API_CALLABLE(InitTargetIterator);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(SetOwnerTarget);

/// @evtapi
/// @param mode
/// @param outResult
API_CALLABLE(ChooseNextTarget);

/// @evtapi
/// @param outLength
API_CALLABLE(GetTargetListLength);

/// @evtapi
/// @param outActorID
/// @param outPartIndex
API_CALLABLE(GetOwnerTarget);

/// @evtapi
/// @param outTargetID
/// @param outTargetPart
API_CALLABLE(func_8026E914);

/// @evtapi
/// @param outActorID
API_CALLABLE(GetPlayerActorID);

/// @evtapi
/// @param actorID
/// @param outDist
API_CALLABLE(GetDistanceToGoal);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param palAdjustment
API_CALLABLE(SetActorPaletteEffect);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param decorationIndex
/// @param decorationType
API_CALLABLE(AddActorDecoration);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param decorationIndex
API_CALLABLE(RemoveActorDecoration);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param decorationIndex
/// @param data0
/// @param data1
/// @param data2
/// @param data3
API_CALLABLE(ModifyActorDecoration);

/// @evtapi
/// @param actorID
/// @param useIdle
API_CALLABLE(UseIdleAnimation);

/// @evtapi
/// @param actorID
/// @param outFlags
API_CALLABLE(GetStatusFlags);

/// @evtapi
/// @param buffsFlags
API_CALLABLE(RemovePlayerBuffs);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param alpha
API_CALLABLE(SetPartAlpha);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(CreatePartShadow);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(RemovePartShadow);

/// @evtapi
/// @param rate
API_CALLABLE(SetEndBattleFadeOutRate);

/// @evtapi
/// @param index
/// @param value
API_CALLABLE(SetBattleVar);

/// @evtapi
/// @param index
/// @param outValue
API_CALLABLE(GetBattleVar);

/// @evtapi
/// @param actorID
API_CALLABLE(ResetAllActorSounds);

/// @evtapi
/// @param actorID
/// @param soundType
/// @param sound1
/// @param sound2
API_CALLABLE(SetActorSounds);

/// @evtapi
/// @param actorID
/// @param soundType
/// @param sound1
/// @param sound2
API_CALLABLE(ResetActorSounds);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param soundType
/// @param sound1
/// @param sound2
API_CALLABLE(SetPartSounds);

/// @evtapi
/// @param actorID
/// @param actorType
API_CALLABLE(SetActorType);

/// @evtapi
/// @param actorID
API_CALLABLE(ShowShockEffect);

/// @evtapi
/// @param actorID
/// @param outValue
API_CALLABLE(GetActorAttackBoost);

/// @evtapi
/// @param actorID
/// @param outValue
API_CALLABLE(GetActorDefenseBoost);

/// @evtapi
/// @param actorID
/// @param amount
API_CALLABLE(BoostAttack);

/// @evtapi
/// @param actorID
/// @param amount
API_CALLABLE(BoostDefense);

/// @evtapi
/// @param actorID
/// @param duration
API_CALLABLE(VanishActor);

/// @evtapi
/// @param actorID
/// @param duration
API_CALLABLE(ElectrifyActor);

/// @evtapi
/// @param actorID
/// @param amount
/// @param plural
API_CALLABLE(HealActor);

/// @evtapi
API_CALLABLE(WaitForBuffDone);

/// @evtapi
/// @param sourceActorID
/// @param targetActorID
API_CALLABLE(CopyBuffs);

/// @evtapi
/// @param outCategory
/// @param outItem
/// @param outMove
API_CALLABLE(GetMenuSelection);

/// @evtapi
/// @param moveTime
API_CALLABLE(PlayerFallToGoal);

/// @evtapi
API_CALLABLE(PlayerLandJump);

/// @evtapi
/// @param moveTime
API_CALLABLE(PlayerRunToGoal);

/// @evtapi
/// @param moveTime
/// @param outSkipped
API_CALLABLE(CancelablePlayerRunToGoal);

/// @evtapi
/// @param outValue
API_CALLABLE(GetPlayerHP);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(PlayerDamageEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param powerBounceCounter
/// @param flagsModifier
API_CALLABLE(PlayerPowerBounceEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(PlayerTestEnemy);

/// @evtapi
/// @param damageAmount
/// @param event
API_CALLABLE(DispatchDamagePlayerEvent);

/// @evtapi
/// @param enabled
API_CALLABLE(EnablePlayerBlur);

/// @evtapi
/// @param moveTime
/// @param moveArcAmplitude
API_CALLABLE(PlayerBasicJumpToGoal);

/// @evtapi
/// @param moveTime
/// @param moveArcAmplitude
API_CALLABLE(PlayerSuperJumpToGoal);

/// @evtapi
/// @param moveTime
/// @param moveArcAmplitude
API_CALLABLE(PlayerUltraJumpToGoal);

/// @evtapi
/// @param outQuality
API_CALLABLE(GetPlayerActionQuality);

/// @evtapi
/// @param actorID
/// @param script
API_CALLABLE(BindTakeTurn);

/// @evtapi
/// @param actorID
API_CALLABLE(PauseTakeTurn);

/// @evtapi
/// @param actorID
API_CALLABLE(ResumeTakeTurn);

/// @evtapi
/// @param actorID
/// @param script
API_CALLABLE(BindIdle);

/// @evtapi
/// @param actorID
/// @param mode
API_CALLABLE(EnableIdleScript);

/// @evtapi
/// @param actorID
/// @param script
API_CALLABLE(BindHandleEvent);

/// @evtapi
/// @param actorID
/// @param script
API_CALLABLE(BindHandlePhase);

/// @evtapi
/// @param actorID
/// @param moveTime
/// @param useJumpAnims
/// @param makeDustEffects
/// @param playJumpSounds
API_CALLABLE(JumpToGoal);

/// @evtapi
/// @param actorID
/// @param moveTime
/// @param useJumpAnims
/// @param makeDustEffects
API_CALLABLE(IdleJumpToGoal);

/// @evtapi
/// @param actorID
/// @param moveTime
/// @param bounceDivisor
API_CALLABLE(JumpWithBounce);

/// @evtapi
/// @param actorID
API_CALLABLE(LandJump);

/// @evtapi
/// @param actorID
/// @param moveTime
API_CALLABLE(FallToGoal);

/// @evtapi
/// @param actorID
/// @param moveTime
/// @param moveArcAmplitude
API_CALLABLE(RunToGoal);

/// @evtapi
/// @param actorID
/// @param moveTime
API_CALLABLE(IdleRunToGoal);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
/// @param moveTime
/// @param dustFlag
API_CALLABLE(JumpPartTo);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
/// @param moveTime
API_CALLABLE(FallPartTo);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(LandJumpPart);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
/// @param drawDustEffects
API_CALLABLE(RunPartTo);

/// @evtapi
/// @param actorID
/// @param duration
/// @param arcHeight
/// @param easing
API_CALLABLE(FlyToGoal);

/// @evtapi
/// @param actorID
/// @param duration
/// @param arcHeight
/// @param easing
API_CALLABLE(IdleFlyToGoal);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param x
/// @param y
/// @param z
/// @param duration
/// @param arcHeight
/// @param easing
API_CALLABLE(FlyPartTo);

/// @evtapi
/// @param actorID
/// @param outEvent
API_CALLABLE(GetLastEvent);

/// @evtapi
/// @param attackerID
/// @param defenderID
API_CALLABLE(SetTargetActor);

/// @evtapi
/// @param actorID
/// @param newHP
API_CALLABLE(SetEnemyHP);

/// @evtapi
/// @param actorID
/// @param outHP
API_CALLABLE(GetActorHP);

/// @evtapi
/// @param actorID
/// @param outMaxHP
API_CALLABLE(GetEnemyMaxHP);

/// @evtapi
/// @param actorID
API_CALLABLE(RemoveActor);

/// @evtapi
/// @param actorID
API_CALLABLE(DropStarPoints);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param defenseTablePtr
API_CALLABLE(SetDefenseTable);

/// @evtapi
/// @param actorID
/// @param statusTablePtr
API_CALLABLE(SetStatusTable);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param idleAnimsPtr
API_CALLABLE(SetIdleAnimations);

/// @evtapi
/// @param actorID
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(EnemyDamageTarget);

/// @evtapi
/// @param actorID
/// @param outResult
API_CALLABLE(EnemyFollowupAfflictTarget);

/// @evtapi
/// @param actorID
/// @param outResult
/// @param damageType
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(EnemyTestTarget);

/// @evtapi
/// @param actorID
/// @param damageAmount
/// @param event
API_CALLABLE(DispatchDamageEvent);

/// @evtapi
/// @param actorID
/// @param event
API_CALLABLE(DispatchEvent);

/// @evtapi
/// @param actorID
API_CALLABLE(ShowHealthBar);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param offsetX
/// @param offsetY
API_CALLABLE(SetTargetOffset);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param offsetX
/// @param offsetY
API_CALLABLE(SetProjectileTargetOffset);

/// @evtapi
/// @param actorID
/// @param enabled
API_CALLABLE(EnableActorBlur);

/// @evtapi
/// @param actorID
/// @param status
/// @param duration
API_CALLABLE(AfflictActor);

/// @evtapi
/// @param actorID
/// @param outValue
API_CALLABLE(GetInstigatorValue);

/// @evtapi
/// @param outTrigger
API_CALLABLE(GetEncounterTrigger);

/// @evtapi
API_CALLABLE(YieldTurn);

/// @evtapi
/// @param actorID
/// @param sizeX
/// @param sizeY
API_CALLABLE(SetActorSize);

/// @evtapi
/// @param actorID
/// @param outSizeX
/// @param outSizeY
API_CALLABLE(GetActorSize);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param sizeX
/// @param sizeY
API_CALLABLE(SetPartSize);

/// @evtapi
/// @param actorID
/// @param outType
API_CALLABLE(GetOriginalActorType);

/// @evtapi
/// @param actorID
/// @param outType
API_CALLABLE(GetCurrentActorType);

/// @evtapi
/// @param actorID
/// @param outDamage
API_CALLABLE(GetLastDamage);

/// @evtapi
/// @param actorID
/// @param enabled
API_CALLABLE(EnableActorGlow);

/// @evtapi
/// @param actorID
/// @param outResult
API_CALLABLE(WasStatusInflicted);

/// @evtapi
/// @param sourceActorID
/// @param targetActorID
API_CALLABLE(CopyStatusEffects);

/// @evtapi
/// @param actorID
API_CALLABLE(ClearStatusEffects);

/// @evtapi
/// @param actorID
/// @param homeIndex
/// @param outTargetIndex
API_CALLABLE(MakeOwnerTargetIndex);

/// @evtapi
/// @param actorID
/// @param outLevel
API_CALLABLE(GetActorLevel);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(PartnerDamageEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param status
/// @param statusChance
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(PartnerAfflictEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param powerBounceCounter
/// @param flagsModifier
API_CALLABLE(PartnerPowerBounceEnemy);

/// @evtapi
/// @param outResult
/// @param damageType
/// @param suppressEventFlags
/// @param debuffType
/// @param damageAmount
/// @param flagsModifier
API_CALLABLE(PartnerTestEnemy);

/// @evtapi
API_CALLABLE(DeletePartner);

/// @evtapi
/// @evtout LVar0 intensity
API_CALLABLE(GetDamageIntensity);

/// @evtapi
/// @param effectPtr
/// @param x
/// @param y
/// @param z
API_CALLABLE(AddEffectOffset);

/// @evtapi
/// @evtout LVar0 starPowerScript
/// @evtout LVar1 success
API_CALLABLE(LoadStarPowerScript);

/// @evtapi
/// @param x
/// @param y
/// @param z
API_CALLABLE(ForceBattleCamTarget);

/// @evtapi
/// @param param
/// @param value
API_CALLABLE(SetBattleCamParam);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param outNotify
API_CALLABLE(GetPartAnimNotify);

/// @evtapi
API_CALLABLE(PartnerYieldTurn); ///< YieldTurn copy

/// @evtapi
/// @param preTargetMode
/// @param postTargetMode
/// @param done
API_CALLABLE(SetBattleCamTargetingModes);

/// @evtapi
/// @param presetIndex
API_CALLABLE(UseBattleCamPresetImmediately);

/// @evtapi
/// @param presetIndex
API_CALLABLE(UseBattleCamPresetWait);

/// @evtapi
/// @param actorID
API_CALLABLE(HideHealthBar);

/// @evtapi
/// @param outQuality
API_CALLABLE(GetPartnerActionQuality);

/// @evtapi
/// @param enable
API_CALLABLE(EnableBattleStatusBar);

/// @evtapi
API_CALLABLE(PlayerYieldTurn);

/// @evtapi
/// @param moveTime
/// @param moveArcAmplitude
/// @param landingBehavior
API_CALLABLE(PlayerHopToGoal);

/// @evtapi
/// @param state
API_CALLABLE(WaitForState);

/// @evtapi
/// @param flags
API_CALLABLE(SetBattleMenuEnabledFlags);

/// @evtapi
/// @param state
API_CALLABLE(SetBattleState);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param targetPriorityOffset
API_CALLABLE(func_8027D434);

/// @evtapi
/// @param actorID
/// @param outFlags
API_CALLABLE(func_8026F1A0);

/// @evtapi
/// @param actorID
/// @param index
/// @param soundID
API_CALLABLE(PlayLoopingSoundAtActor);

/// @evtapi
/// @param actorID
/// @param index
API_CALLABLE(StopLoopingSoundAtActor);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param enable
API_CALLABLE(EnableActorPaletteEffects);

/// @evtapi
/// @param actorID
/// @param partIndex
/// @param blendPalA
/// @param blendPalB
/// @param timeHoldA
/// @param timeAtoB
/// @param timeHoldB
/// @param timeBtoA
/// @param unused1
/// @param unused2
API_CALLABLE(SetActorPaletteSwapParams);

/// @evtapi
/// @param actorID
/// @param partIndex
API_CALLABLE(BattleCamTargetActorPart);

/// @evtapi
/// @param outLayer
/// @param outIsLight
API_CALLABLE(GetDarknessStatus);

/// @evtapi
/// @param cancelMode
API_CALLABLE(CancelEnemyTurn);

/// @evtapi
/// @param event
API_CALLABLE(DispatchEventPlayer);

extern EvtScript EVS_Mario_HandlePhase;
extern EvtScript EVS_Peach_HandlePhase;
extern EvtScript EVS_ExecuteMarioAction;
extern EvtScript EVS_ExecutePeachAction;
extern EvtScript EVS_Player_HandleEvent;
extern EvtScript EVS_PlayerFirstStrike;
extern EvtScript EVS_StartDefend;
extern EvtScript EVS_RunAwayStart;
extern EvtScript EVS_RunAwayFail;
extern EvtScript EVS_PlayerDies;
extern EvtScript EVS_Unused_EatItem;
extern EvtScript EVS_Unused_DrinkItem;
extern EvtScript EVS_UseLifeShroom;
extern EvtScript EVS_MerleeRunOut;
extern EvtScript EVS_MerleeAttackBonus;
extern EvtScript EVS_MerleeDefenseBonus;
extern EvtScript EVS_MerleeExpBonus;
extern EvtScript EVS_PlayerHappy;
extern EvtScript EVS_ApplyDizzyAttack;
extern EvtScript EVS_PlayerRegainAbility;
extern EvtScript EVS_UseMystery;
extern EvtScript EVS_PlaySleepHitFX;
extern EvtScript EVS_PlayDizzyHitFX;
extern EvtScript EVS_PlayParalyzeHitFX;
extern EvtScript EVS_PlayPoisonHitFX;
extern EvtScript EVS_PlayStopHitFX;
extern EvtScript EVS_PlayFreezeHitFX;
extern EvtScript EVS_PlayShrinkHitFX;
extern EvtScript EVS_ForceNextTarget;
extern EvtScript EVS_Enemy_Hit;
extern EvtScript EVS_Partner_RunAway;
extern EvtScript EVS_Partner_SpikeContact;
extern EvtScript EVS_Partner_BombetteSpikeContact;
extern EvtScript EVS_Partner_BurnContact;
extern EvtScript EVS_Partner_Recover;
extern EvtScript EVS_Partner_ShockHit;
extern EvtScript EVS_Partner_BurnHit;
extern EvtScript EVS_Partner_Hit;
extern EvtScript EVS_Partner_Drop;
extern EvtScript EVS_Partner_NoDamageHit;
extern EvtScript EVS_Partner_LakilesterHit;
extern EvtScript EVS_Enemy_HopToPos;
extern EvtScript EVS_Enemy_BurnHit;
extern EvtScript EVS_Enemy_ShockHit;
extern EvtScript EVS_Enemy_ShockHit_Impl;
extern EvtScript EVS_Partner_Celebrate;
extern EvtScript EVS_Enemy_NoDamageHit;
extern EvtScript EVS_Enemy_Death;
extern EvtScript EVS_Enemy_DeathWithoutRemove;
extern EvtScript EVS_Enemy_ScareAway;
extern EvtScript EVS_Enemy_SpinSmashHit;
extern EvtScript EVS_Enemy_FlipBackUp;
extern EvtScript EVS_Enemy_Knockback;
extern EvtScript EVS_Enemy_ReturnHome;
extern EvtScript EVS_Enemy_Recover;
extern EvtScript EVS_Enemy_HopHome;
extern EvtScript EVS_Enemy_AirLift;
extern EvtScript EVS_Enemy_BlowAway;
extern EvtScript Rumble_1;
extern EvtScript Rumble_2;
extern EvtScript Rumble_3;
extern EvtScript Rumble_4;
extern EvtScript Rumble_5;
extern EvtScript Rumble_6;
extern EvtScript Rumble_7;
extern EvtScript Rumble_Unused_1;
extern EvtScript Rumble_Unused_2;
extern EvtScript Rumble_Unused_3;
extern EvtScript Rumble_Unused_4;

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
