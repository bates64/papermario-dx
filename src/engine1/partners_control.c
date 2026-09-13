#include "common_structs.h"
#include "world/partners.h"
#include "world/partners_internal.h"
#include "macros.h"

enum PartnerCommands {
    PARTNER_CMD_NONE                = 0,
    PARTNER_CMD_CLEAR               = 1,
    PARTNER_CMD_INSTA_SWITCH        = 2, // skips put away / take out scripts. assumes valid current partner.
    PARTNER_CMD_SWITCH              = 3, // assumes valid current partner.
    PARTNER_CMD_PUT_AWAY            = 4, // switches to null partner.
    PARTNER_CMD_INSTA_PUT_AWAY      = 5,
    PARTNER_CMD_TAKE_OUT            = 6, // assumes no current partner.
    PARTNER_CMD_INSTA_TAKE_OUT      = 7,
    PARTNER_CMD_USE_ABILITY         = 8,
    PARTNER_CMD_RESET               = 9,
    PARTNER_CMD_ABORT               = 10,
};

BSS s32 PartnerSpawnMode;
BSS Evt* PartnerCurrentScript;
BSS s32 PartnerCurrentScriptID;
BSS b32 PartnerCommandPending;
BSS s32 NextPartnerID;
BSS s32 NextPartnerCommand;
BSS s32 CurPartnerCommand;

BSS s32 CommandSubstate;

void init_partner_commands(void) {
    PartnerCommandPending = false;
    NextPartnerCommand = PARTNER_CMD_NONE;
}

void suspend_partner_commands(void) {
    if (does_script_exist(PartnerCurrentScriptID)) {
        kill_script_by_ID(PartnerCurrentScriptID);
    }
}

void resume_partner_commands(void) {
    if (does_script_exist(PartnerCurrentScriptID)) {
        kill_script_by_ID(PartnerCurrentScriptID);
    }

    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
    PartnerCurrentScript->owner2.npc = gPartnerNpc;
    PartnerCurrentScriptID = PartnerCurrentScript->id;
    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;

    NextPartnerCommand = PARTNER_CMD_CLEAR;
}

void process_partner_commands(void) {
    PlayerData* playerData = &gPlayerData;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (partnerStatus->inputDisabledCount == 0) {
        partnerStatus->stickX = gGameStatusPtr->stickX[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->stickY = gGameStatusPtr->stickY[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->curButtons = gGameStatusPtr->curButtons[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->pressedButtons = gGameStatusPtr->pressedButtons[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->heldButtons = gGameStatusPtr->heldButtons[gGameStatusPtr->multiplayerEnabled];
    } else {
        partnerStatus->stickX = 0;
        partnerStatus->stickY = 0;
        partnerStatus->curButtons = 0;
        partnerStatus->pressedButtons = 0;
        partnerStatus->heldButtons = 0;
    }

    if (playerStatus->animFlags & PA_FLAG_INTERRUPT_USE_PARTNER) {
        playerStatus->animFlags &= ~PA_FLAG_INTERRUPT_USE_PARTNER;
        partnerStatus->pressedButtons |= (BUTTON_B | BUTTON_C_DOWN);
        playerStatus->animFlags |= PA_FLAG_FORCED_PARTNER_ABILITY_END;
    }

    if (NextPartnerCommand != PARTNER_CMD_NONE) {
        CurPartnerCommand = NextPartnerCommand;
        CommandSubstate = 0;
        NextPartnerCommand = PARTNER_CMD_NONE;
    }

    if (CurPartnerCommand >= PARTNER_CMD_INSTA_SWITCH) {
        if (CurPartnerCommand != PARTNER_CMD_USE_ABILITY) {
            PartnerSpawnMode = PARTNER_SPAWN_NONE;
        }
    }

    switch (CurPartnerCommand) {
        case PARTNER_CMD_NONE:
            break;
        case PARTNER_CMD_SWITCH:
            PartnerSpawnMode = PARTNER_SPAWN_SWITCH;
            switch (CommandSubstate) {
                case 0: // put away current partner
                    disable_player_input();
                    sfx_play_sound(SOUND_PARTNER_PUT_AWAY);
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->putAway, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CommandSubstate = 1;
                    set_time_freeze_mode(TIME_FREEZE_PARTIAL);
                    break;
                case 1: // free old partner and create new one
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    set_time_freeze_mode(TIME_FREEZE_NONE);
                    partner_free_npc();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    sfx_play_sound(SOUND_PARTNER_GET_OUT);
                    ActivePartner->init(gPartnerNpc);
                    CommandSubstate = 2;
                    // fallthrough
                case 2: // take out new partner
                    PartnerCurrentScript = start_script(ActivePartner->takeOut, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CommandSubstate = 3;
                    set_time_freeze_mode(TIME_FREEZE_PARTIAL);
                    break;
                case 3: // resume normal partner behaviour
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    enable_player_input();
                    set_time_freeze_mode(TIME_FREEZE_NONE);
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_SWITCH:
            PartnerSpawnMode = PARTNER_SPAWN_SWITCH;
            switch (CommandSubstate) {
                case 0:
                    kill_script_by_ID(PartnerCurrentScriptID);
                    CommandSubstate = 1;
                    // fallthrough
                case 1:
                    partner_free_npc();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    gPartnerNpc->pos.x = SavedPartnerPos.x;
                    gPartnerNpc->pos.y = SavedPartnerPos.y;
                    gPartnerNpc->pos.z = SavedPartnerPos.z;
                    gPartnerNpc->jumpVel = 0.0f;
                    gPartnerNpc->scale.x = 1.0f;
                    gPartnerNpc->scale.y = 1.0f;
                    gPartnerNpc->scale.z = 1.0f;
                    ActivePartner->init(gPartnerNpc);
                    CommandSubstate = 2;
                    // fallthrough
                case 2:
                    CommandSubstate = 3;
                    break;
                case 3:
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_PUT_AWAY:
            switch (CommandSubstate) {
                case 0: // put away current partner
                    disable_player_input();
                    sfx_play_sound(SOUND_PARTNER_PUT_AWAY);
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->putAway, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CommandSubstate = 1;
                    break;
                case 1: // free old partner and resume game
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    partner_free_npc();
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_PUT_AWAY:
            if (CommandSubstate == 0) {
                kill_script_by_ID(PartnerCurrentScriptID);
                partner_free_npc();
                CurPartnerCommand = PARTNER_CMD_CLEAR;
                playerData->curPartner = CurrentPartnerID = NextPartnerID;
                break;
            }
            break;
        case PARTNER_CMD_TAKE_OUT:
            switch (CommandSubstate) {
                case 0: // create the new partner
                    disable_player_input();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    ActivePartner->init(gPartnerNpc);
                    CommandSubstate = 1;
                    // fallthrough
                case 1: // take out new partner
                    PartnerCurrentScript = start_script(ActivePartner->takeOut, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CommandSubstate = 2;
                    break;
                case 2: // resume standard partner behaviour
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_TAKE_OUT:
            PartnerSpawnMode = PARTNER_SPAWN_INSTA;
            switch (CommandSubstate) {
                case 0:
                    disable_player_input();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    gPartnerNpc->pos.x = SavedPartnerPos.x;
                    gPartnerNpc->pos.y = SavedPartnerPos.y;
                    gPartnerNpc->pos.z = SavedPartnerPos.z;
                    gPartnerNpc->jumpVel = 0.0f;
                    gPartnerNpc->scale.x = 1.0f;
                    gPartnerNpc->scale.y = 1.0f;
                    gPartnerNpc->scale.z = 1.0f;
                    ActivePartner->init(gPartnerNpc);
                    CommandSubstate = 1;
                    break;
                case 1:
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    gPartnerNpc->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_USE_ABILITY:
            switch (CommandSubstate) {
                case 0:
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->useAbility, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CommandSubstate = 1;
                    break;
                case 1:
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_RESET:
            PartnerSpawnMode = PARTNER_SPAWN_RESET;
            switch (CommandSubstate) {
                case 0:
                    disable_player_input();
                    ActivePartner->init(gPartnerNpc);
                    CommandSubstate = 1;
                    // fallthrough
                case 1:
                    CommandSubstate = 2;
                    break;
                case 2:
                    if (partnerStatus->partnerActionState != 1) {
                        SavedPartnerPos.x = playerStatus->pos.x;
                        SavedPartnerPos.y = playerStatus->pos.y;
                        SavedPartnerPos.z = playerStatus->pos.z;
                        PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                        PartnerCurrentScript->owner2.npc = gPartnerNpc;
                        PartnerCurrentScriptID = PartnerCurrentScript->id;
                        PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    }
                    enable_player_input();
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_ABORT:
            if (CommandSubstate == 0) {
                if (does_script_exist(PartnerCurrentScriptID)) {
                    kill_script_by_ID(PartnerCurrentScriptID);
                }
                CommandSubstate = 1;
            }
            break;
        case PARTNER_CMD_CLEAR:
            CurPartnerCommand = PARTNER_CMD_NONE;
            PartnerCommandPending = false;
            if (PartnerSpawnMode != PARTNER_SPAWN_SWITCH) {
                PartnerSpawnMode = PARTNER_SPAWN_NONE;
            }
            break;
    }
}

void switch_to_partner(s32 partnerID) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_TAKE_OUT;
            SavedPartnerPos.x = playerStatus->pos.x;
            SavedPartnerPos.y = playerStatus->pos.y;
            SavedPartnerPos.z = playerStatus->pos.z;
        }
    }
}

void partner_init_after_battle(s32 partnerID) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;
        partnerStatus->partnerActionState = 0;
        partnerStatus->shouldResumeAbility = false;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_INSTA_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_TAKE_OUT;
            SavedPartnerPos.x = playerStatus->pos.x;
            SavedPartnerPos.y = playerStatus->pos.y;
            SavedPartnerPos.z = playerStatus->pos.z;
        }
    }
}

void partner_switch_to_partner_instant(s32 partnerID) {
    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_INSTA_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_INSTA_TAKE_OUT;
        }
    }
}

s32 partner_use_ability(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (!is_starting_conversation()
        && ActivePartner != nullptr
        && (ActivePartner->canUseAbility == nullptr || ActivePartner->canUseAbility(gPartnerNpc)))
    {
        if (gGameStatusPtr->multiplayerEnabled && (partnerStatus->curButtons & BUTTON_B)) {
            sfx_play_sound(SOUND_MENU_ERROR);
        } else if (CurrentPartnerID != PARTNER_NONE) {
            PartnerCommandPending = true;
            NextPartnerCommand = PARTNER_CMD_USE_ABILITY;
            process_partner_commands();
            return true;
        }
    }
    return false;
}

s32 partner_can_open_world_menus(void) {
    if (ActivePartner != nullptr
        && ActivePartner->canPlayerOpenMenus != nullptr
        && !ActivePartner->canPlayerOpenMenus(gPartnerNpc)
    ) {
        return false;
    }
    return true;
}

s32 partner_can_use_ability(void) {
    if (ActivePartner->canUseAbility != nullptr && !ActivePartner->canUseAbility(gPartnerNpc)) {
        return true;
    }
    return false;
}

void partner_reset_data(void) {
    mem_clear(&gPartnerStatus, sizeof(gPartnerStatus));
    get_worker(create_worker_frontUI(process_partner_commands, nullptr));

    PartnerCommandPending = true;
    NextPartnerCommand = PARTNER_CMD_RESET;
    CurrentPartnerID = gPlayerData.curPartner;

    if (gGameStatusPtr->keepUsingPartnerOnMapChange) {
        gPartnerStatus.partnerActionState = PARTNER_ACTION_USE;
        gGameStatusPtr->keepUsingPartnerOnMapChange = false;
    }

    ActivePartner = nullptr;
    SavedPartnerPos.x = gPlayerStatus.pos.x;
    SavedPartnerPos.y = gPlayerStatus.pos.y;
    SavedPartnerPos.z = gPlayerStatus.pos.z;

    if (CurrentPartnerID == PARTNER_NONE) {
        NextPartnerCommand = PARTNER_CMD_CLEAR;
    } else {
        create_partner_npc();
        gPartnerNpc->scale.x = 1.0f;
        gPartnerNpc->scale.y = 1.0f;
        gPartnerNpc->scale.z = 1.0f;
        process_partner_commands();
    }
}

void partner_kill_ability_script(void) {
    NextPartnerCommand = PARTNER_CMD_ABORT;

    if (does_script_exist(PartnerCurrentScriptID)) {
        kill_script_by_ID(PartnerCurrentScriptID);
    }
}

void partner_suspend_ability_script(void) {
    if (CurrentPartnerID != PARTNER_NONE) {
        if (does_script_exist(PartnerCurrentScriptID)) {
            suspend_all_script(PartnerCurrentScriptID);
        }
    }
}

void partner_resume_ability_script(void) {
    if (CurrentPartnerID != PARTNER_NONE) {
        if (does_script_exist(PartnerCurrentScriptID)) {
            resume_all_script(PartnerCurrentScriptID);
        }
    }
}

void partner_enable_input(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    partnerStatus->inputDisabledCount--;
    if (partnerStatus->inputDisabledCount < 0) {
        partnerStatus->inputDisabledCount = 0;
    }
}

void partner_disable_input(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    partnerStatus->inputDisabledCount++;
}
