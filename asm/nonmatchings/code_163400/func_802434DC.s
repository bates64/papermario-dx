.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_802434DC
/* 163D3C 802434DC 3C028016 */  lui       $v0, 0x8016
/* 163D40 802434E0 24429D50 */  addiu     $v0, $v0, -0x62b0
/* 163D44 802434E4 00042140 */  sll       $a0, $a0, 5
/* 163D48 802434E8 00822021 */  addu      $a0, $a0, $v0
/* 163D4C 802434EC 9083001C */  lbu       $v1, 0x1c($a0)
/* 163D50 802434F0 14600005 */  bnez      $v1, .L80243508
/* 163D54 802434F4 28620010 */   slti     $v0, $v1, 0x10
/* 163D58 802434F8 90820000 */  lbu       $v0, ($a0)
/* 163D5C 802434FC 304200FB */  andi      $v0, $v0, 0xfb
/* 163D60 80243500 A0820000 */  sb        $v0, ($a0)
/* 163D64 80243504 28620010 */  slti      $v0, $v1, 0x10
.L80243508:
/* 163D68 80243508 10400008 */  beqz      $v0, .L8024352C
/* 163D6C 8024350C 00031040 */   sll      $v0, $v1, 1
/* 163D70 80243510 3C038025 */  lui       $v1, 0x8025
/* 163D74 80243514 00621821 */  addu      $v1, $v1, $v0
/* 163D78 80243518 84639C3C */  lh        $v1, -0x63c4($v1)
/* 163D7C 8024351C 8CE20000 */  lw        $v0, ($a3)
/* 163D80 80243520 00431021 */  addu      $v0, $v0, $v1
/* 163D84 80243524 03E00008 */  jr        $ra
/* 163D88 80243528 ACE20000 */   sw       $v0, ($a3)
.L8024352C:
/* 163D8C 8024352C 3C028025 */  lui       $v0, 0x8025
/* 163D90 80243530 84429C5A */  lh        $v0, -0x63a6($v0)
/* 163D94 80243534 8CE30000 */  lw        $v1, ($a3)
/* 163D98 80243538 00621821 */  addu      $v1, $v1, $v0
/* 163D9C 8024353C ACE30000 */  sw        $v1, ($a3)
/* 163DA0 80243540 90820000 */  lbu       $v0, ($a0)
/* 163DA4 80243544 304200F7 */  andi      $v0, $v0, 0xf7
/* 163DA8 80243548 03E00008 */  jr        $ra
/* 163DAC 8024354C A0820000 */   sb       $v0, ($a0)
