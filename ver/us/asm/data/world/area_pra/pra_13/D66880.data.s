.include "macro.inc"

.section .data

dlabel D_802422A0_D66880
.word 0x00000000, 0x001E002D, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00630000

dlabel D_802422CC_D668AC
.word 0x00000000

dlabel D_802422D0_D668B0
.word 0x00000000

dlabel D_802422D4_D668B4
.word 0x00000024, 0x00000002, 0xFE363C89, 0xFE363C81, 0x00000043, 0x00000001, ShowKeyChoicePopup, 0x00000024, 0x00000002, 0xFE363C8A, 0xFE363C80, 0x00000014, 0x00000001, 0xFE363C80, 0x00000016, 0x00000001, 0x00000000, 0x00000016, 0x00000001, 0xFFFFFFFF, 0x0000001C, 0x00000000, 0x00000043, 0x00000002, RemoveKeyItemAt, 0xFE363C81, 0x00000043, 0x00000004, GetPlayerPos, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000043, 0x00000004, pra_13_AddPlayerHandsOffset, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000042, 0x00000002, 0xFE363C80, 0x00050000, 0x00000043, 0x00000007, MakeItemEntity, 0xFE363C80, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000001, 0x00000000, 0x00000043, 0x00000002, SetPlayerAnimation, 0x00060005, 0x00000008, 0x00000001, 0x0000001E, 0x00000043, 0x00000002, SetPlayerAnimation, 0x00010002, 0x00000043, 0x00000002, RemoveItemEntity, 0xFE363C80, 0x00000023, 0x00000000, 0x00000043, 0x00000002, func_802411A0_D65780, 0xFE363C8A, 0x00000043, 0x00000001, CloseChoicePopup, 0x00000048, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000, 0x00000043, 0x00000002, func_802411D8_D657B8, 0xFE363C80, 0x0000004E, 0x00000006, D_802422D4_D668B4, 0x00000010, 0x00000000, D_80243720, 0x00000000, 0x00000001, 0x00000043, 0x00000002, func_8024114C_D6572C, 0xFE363C80, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242468_D66A48
.word 0x00000024, 0x00000002, 0xFE363C89, 0xFE363C81, 0x00000043, 0x00000001, ShowConsumableChoicePopup, 0x00000024, 0x00000002, 0xFE363C8A, 0xFE363C80, 0x00000014, 0x00000001, 0xFE363C80, 0x00000016, 0x00000001, 0x00000000, 0x00000016, 0x00000001, 0xFFFFFFFF, 0x0000001C, 0x00000000, 0x00000043, 0x00000002, RemoveItemAt, 0xFE363C81, 0x00000043, 0x00000004, GetPlayerPos, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000043, 0x00000004, pra_13_AddPlayerHandsOffset, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000043, 0x00000007, MakeItemEntity, 0xFE363C80, 0xFE363C83, 0xFE363C84, 0xFE363C85, 0x00000001, 0x00000000, 0x00000043, 0x00000002, SetPlayerAnimation, 0x00060005, 0x00000008, 0x00000001, 0x0000001E, 0x00000043, 0x00000002, SetPlayerAnimation, 0x00010002, 0x00000043, 0x00000002, RemoveItemEntity, 0xFE363C80, 0x00000023, 0x00000000, 0x00000043, 0x00000002, func_802411A0_D65780, 0xFE363C8A, 0x00000043, 0x00000001, CloseChoicePopup, 0x00000048, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000, 0x00000043, 0x00000002, func_80241274_D65854, 0xFE363C80, 0x0000004E, 0x00000006, D_80242468_D66A48, 0x00000010, 0x00000000, pra_13_802438E8, 0x00000000, 0x00000001, 0x00000043, 0x00000002, func_8024114C_D6572C, 0xFE363C80, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_802425EC_D66BCC
.word 0x00000043, 0x00000005, MakeLerp, 0x00000000, 0x00000B40, 0x00000028, 0x00000004, 0x00000003, 0x00000001, 0x00000001, 0x00000043, 0x00000001, UpdateLerp, 0x00000043, 0x00000005, SetNpcRotation, 0xFE363C84, 0x00000000, 0xFE363C80, 0x00000000, 0x00000008, 0x00000001, 0x00000001, 0x0000000A, 0x00000002, 0xFE363C81, 0x00000001, 0x00000004, 0x00000001, 0x00000001, 0x00000013, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_8024267C_D66C5C
.word 0x00000043, 0x00000002, GetEntryID, 0xFE363C80, 0x0000000A, 0x00000002, 0xFE363C80, 0x00000002, 0x0000000C, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000002, DisablePlayerInput, 0x00000001, 0x00000008, 0x00000001, 0x0000000A, 0x00000043, 0x00000003, SetNpcYaw, 0x00000000, 0x0000005A, 0x00000056, 0x00000000, 0x00000043, 0x00000002, SetPlayerSpeed, 0xF24A8280, 0x00000043, 0x00000004, PlayerMoveTo, 0x000001B8, 0xFFFFFFBA, 0x00000000, 0x00000057, 0x00000000, 0x00000008, 0x00000001, 0x0000000F, 0x00000043, 0x00000005, GetNpcPos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000009, SetCamProperties, 0x00000000, 0xF24A8E80, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0xF24FF280, 0xF24AAA80, 0xF24A5E80, 0x00000043, 0x00000006, SpeakToPlayer, 0x00000000, 0x0001002B, 0x0001002B, 0x00000000, 0x00120139, 0x00000043, 0x00000006, SpeakToPlayer, 0x00000001, 0x0003000E, 0x00030003, 0x00000000, 0x0012013A, 0x00000043, 0x00000003, ResetCam, 0x00000000, 0xF24A9280, 0x00000043, 0x00000004, PanToTarget, 0x00000000, 0x00000000, 0x00000000, 0x00000056, 0x00000000, 0x00000043, 0x00000005, GetNpcPos, 0x00000000, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000005, SetNpcPos, 0x00000000, 0x00000000, 0xFFFFFC18, 0x00000000, 0x00000043, 0x00000004, pra_13_PlayBigSmokePuff, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000005, SetNpcPos, 0x00000002, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000004, PlaySoundAtNpc, 0x00000002, 0x000002CD, 0x00000000, 0x00000043, 0x00000004, SetNpcFlagBits, 0x00000002, 0x00000100, 0x00000001, 0x00000024, 0x00000002, 0xFE363C84, 0x00000002, 0x00000043, 0x00000003, SetNpcYaw, 0x00000002, 0x0000005A, 0x00000046, 0x00000001, D_802425EC_D66BCC, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000002, 0x004E0004, 0x00000043, 0x00000004, SetNpcFlagBits, 0x00000002, 0x00000100, 0x00000001, 0x00000043, 0x00000005, NpcMoveTo, 0x00000002, 0x000001AE, 0xFFFFFFBA, 0x0000000F, 0x00000057, 0x00000000, 0x00000056, 0x00000000, 0x00000043, 0x00000005, GetNpcPos, 0x00000001, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000004, pra_13_PlayBigSmokePuff, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000005, SetNpcPos, 0x00000001, 0x00000185, 0x00000000, 0xFFFFFFC3, 0x00000043, 0x00000005, SetNpcPos, 0x00000003, 0xFE363C80, 0xFE363C81, 0xFE363C82, 0x00000043, 0x00000004, PlaySoundAtNpc, 0x00000003, 0x000002CD, 0x00000000, 0x00000043, 0x00000004, SetNpcFlagBits, 0x00000001, 0x01000100, 0x00000001, 0x00000043, 0x00000004, SetNpcFlagBits, 0x00000003, 0x00000100, 0x00000001, 0x00000024, 0x00000002, 0xFE363C84, 0x00000003, 0x00000043, 0x00000003, SetNpcYaw, 0x00000003, 0x0000005A, 0x00000046, 0x00000001, D_802425EC_D66BCC, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000003, 0x004E0004, 0x00000043, 0x00000004, SetNpcFlagBits, 0x00000003, 0x00000100, 0x00000001, 0x00000043, 0x00000005, NpcMoveTo, 0x00000003, 0x000001A4, 0xFFFFFFBA, 0x0000000F, 0x00000057, 0x00000000, 0x00000008, 0x00000001, 0x00000023, 0x00000043, 0x00000002, StartBossBattle, 0x00000003, 0x00000013, 0x00000000, 0x00000013, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242A70_D67050
.word 0x00000043, 0x00000005, SetNpcPos, 0x00000002, 0x00000190, 0x00000000, 0xFFFFFFBA, 0x00000043, 0x00000005, SetNpcPos, 0x00000003, 0x00000172, 0x00000000, 0xFFFFFFBA, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000002, 0x004E0002, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000003, 0x004E0002, 0x0000004D, 0x00000001, 0x00000000, 0x00000043, 0x00000002, SetTimeFreezeMode, 0x00000001, 0x00000043, 0x00000005, SetNpcPos, 0x00000001, 0x00000000, 0xFFFFFC18, 0x00000000, 0x00000008, 0x00000001, 0x0000000A, 0x00000043, 0x00000006, SpeakToPlayer, 0x00000002, 0x004E0005, 0x004E0002, 0x00000000, 0x0012013B, 0x00000008, 0x00000001, 0x0000000A, 0x00000043, 0x00000004, InterpNpcYaw, 0x00000002, 0x0000010E, 0x00000000, 0x00000043, 0x00000004, InterpNpcYaw, 0x00000003, 0x0000010E, 0x00000000, 0x00000008, 0x00000001, 0x0000000F, 0x00000056, 0x00000000, 0x00000043, 0x00000004, PlaySoundAtNpc, 0x00000002, 0x000002CB, 0x00000000, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000002, 0x004E0004, 0x00000043, 0x00000005, NpcMoveTo, 0x00000002, 0x00000000, 0xFFFFFFBA, 0x0000002D, 0x00000043, 0x00000005, SetNpcPos, 0x00000002, 0x00000000, 0xFFFFFC18, 0x00000000, 0x00000057, 0x00000000, 0x00000043, 0x00000004, PlaySoundAtNpc, 0x00000003, 0x000002CB, 0x00000000, 0x00000043, 0x00000003, SetNpcAnimation, 0x00000003, 0x004E0004, 0x00000043, 0x00000005, NpcMoveTo, 0x00000003, 0xFFFFFFE2, 0xFFFFFFBA, 0x0000002D, 0x00000043, 0x00000005, SetNpcPos, 0x00000003, 0xFFFFFFE2, 0xFFFFFC18, 0x00000000, 0x00000024, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000002, SetTimeFreezeMode, 0x00000000, 0x0000004D, 0x00000001, 0x0000000B, 0x00000043, 0x00000002, DisablePlayerInput, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242CA0_D67280
.word 0x00000043, 0x00000004, SetNpcFlagBits, 0xFFFFFFFF, 0x10000000, 0x00000001, 0x00000043, 0x00000003, SetNpcAnimation, 0xFFFFFFFF, 0x00010002, 0x00000043, 0x00000002, GetEntryID, 0xFE363C80, 0x0000000A, 0x00000002, 0xFE363C80, 0x00000002, 0x0000000C, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000005, SetNpcPos, 0xFFFFFFFF, 0x00000177, 0x00000000, 0xFFFFFFC5, 0x00000013, 0x00000000, 0x00000012, 0x00000000, 0x0000000A, 0x00000002, 0xF8406152, 0x00000001, 0x0000000C, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000005, SetNpcPos, 0xFFFFFFFF, 0x000001D1, 0x00000000, 0xFFFFFFC5, 0x00000043, 0x00000004, InterpNpcYaw, 0xFFFFFFFF, 0x0000010E, 0x00000000, 0x00000013, 0x00000000, 0x00000013, 0x00000000, 0x00000013, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242DA4_D67384
.word 0x00000043, 0x00000003, BindNpcIdle, 0xFFFFFFFF, D_8024267C_D66C5C, 0x00000043, 0x00000003, BindNpcDefeat, 0xFFFFFFFF, D_80242A70_D67050, 0x00000043, 0x00000004, SetNpcFlagBits, 0xFFFFFFFF, 0x10000000, 0x00000001, 0x00000043, 0x00000002, GetEntryID, 0xFE363C80, 0x0000000A, 0x00000002, 0xFE363C80, 0x00000002, 0x0000000C, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000005, SetNpcPos, 0xFFFFFFFF, 0x00000159, 0x00000000, 0xFFFFFFC5, 0x0000003E, 0x00000002, 0x00000010, 0xFE363C8A, 0x00000043, 0x00000001, func_802413D0_D659B0, 0x00000013, 0x00000000, 0x00000012, 0x00000000, 0x0000000A, 0x00000002, 0xF8406152, 0x00000001, 0x0000000C, 0x00000002, 0xF5DE0180, 0x0000004F, 0x00000043, 0x00000005, SetNpcPos, 0xFFFFFFFF, 0x000001B3, 0x00000000, 0xFFFFFFC5, 0x0000003E, 0x00000002, 0x00000010, 0xFE363C8A, 0x00000043, 0x00000001, func_802413D0_D659B0, 0x00000013, 0x00000000, 0x00000013, 0x00000000, 0x00000013, 0x00000000, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242EDC_D674BC
.word 0x00000043, 0x00000004, SetNpcFlagBits, 0xFFFFFFFF, 0x10000000, 0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242F04_D674E4
.word 0x00000043, 0x00000004, SetNpcFlagBits, 0xFFFFFFFF, 0x10000000, 0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000000

dlabel D_80242F2C_D6750C
.word 0x00000000, D_802422A0_D66880, 0x00000000, 0xC47A0000, 0x00000000, 0x00604D0D, D_80242CA0_D67280, 0x00000000, 0x00000000, 0x0000005A, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00030003, 0x00030005, 0x00030005, 0x00030005, 0x00030005, 0x00030005, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

dlabel D_8024311C_D676FC
.word 0x00000001, D_802422A0_D66880, 0x00000000, 0xC47A0000, 0x00000000, 0x00E40D0C, D_80242DA4_D67384, 0x00000000, 0x00000000, 0x0000005A, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00030003, 0x00030005, 0x00030005, 0x00030005, 0x00030005, 0x00030005, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00030000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, D_802422A0_D66880, 0x00000000, 0xC47A0000, 0x00000000, 0x00E40D09, D_80242EDC_D674BC, 0x00000000, 0x00000000, 0x0000010E, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x004E0002, 0x004E0003, 0x004E0004, 0x004E0004, 0x004E0002, 0x004E0002, 0x004E000A, 0x004E000A, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000003, D_802422A0_D66880, 0x00000000, 0xC47A0000, 0x00000000, 0x00E40D09, D_80242F04_D674E4, 0x00000000, 0x00000000, 0x0000010E, 0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00007FFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x004E0002, 0x004E0003, 0x004E0004, 0x004E0004, 0x004E0002, 0x004E0002, 0x004E000A, 0x004E000A, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x004E0002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, D_80242F2C_D6750C, 0x21020001, 0x00000003, D_8024311C_D676FC, 0x21020001, 0x00000000, 0x00000000, 0x00000000
