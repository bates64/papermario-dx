.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80265D44
/* 194624 80265D44 3C03800E */  lui       $v1, %hi(gBattleStatus)
/* 194628 80265D48 2463C070 */  addiu     $v1, $v1, %lo(gBattleStatus)
/* 19462C 80265D4C 8C6600D8 */  lw        $a2, 0xd8($v1)
/* 194630 80265D50 8CC201F4 */  lw        $v0, 0x1f4($a2)
/* 194634 80265D54 8C450094 */  lw        $a1, 0x94($v0)
/* 194638 80265D58 14A00006 */  bnez      $a1, .L80265D74
/* 19463C 80265D5C 0000102D */   daddu    $v0, $zero, $zero
/* 194640 80265D60 03E00008 */  jr        $ra
/* 194644 80265D64 00000000 */   nop      
.L80265D68:
/* 194648 80265D68 8CA70004 */  lw        $a3, 4($a1)
/* 19464C 80265D6C 03E00008 */  jr        $ra
/* 194650 80265D70 00E0102D */   daddu    $v0, $a3, $zero
.L80265D74:
/* 194654 80265D74 8C620004 */  lw        $v0, 4($v1)
/* 194658 80265D78 30420040 */  andi      $v0, $v0, 0x40
/* 19465C 80265D7C 14400022 */  bnez      $v0, .L80265E08
/* 194660 80265D80 0000382D */   daddu    $a3, $zero, $zero
/* 194664 80265D84 3C028011 */  lui       $v0, %hi(gPlayerData)
/* 194668 80265D88 2442F290 */  addiu     $v0, $v0, %lo(gPlayerData)
/* 19466C 80265D8C 80420002 */  lb        $v0, 2($v0)
/* 194670 80265D90 28420006 */  slti      $v0, $v0, 6
/* 194674 80265D94 10400009 */  beqz      $v0, .L80265DBC
/* 194678 80265D98 24020001 */   addiu    $v0, $zero, 1
/* 19467C 80265D9C 50820001 */  beql      $a0, $v0, .L80265DA4
/* 194680 80265DA0 2404001A */   addiu    $a0, $zero, 0x1a
.L80265DA4:
/* 194684 80265DA4 24020012 */  addiu     $v0, $zero, 0x12
/* 194688 80265DA8 50820001 */  beql      $a0, $v0, .L80265DB0
/* 19468C 80265DAC 24040016 */   addiu    $a0, $zero, 0x16
.L80265DB0:
/* 194690 80265DB0 2402001C */  addiu     $v0, $zero, 0x1c
/* 194694 80265DB4 50820001 */  beql      $a0, $v0, .L80265DBC
/* 194698 80265DB8 2404001D */   addiu    $a0, $zero, 0x1d
.L80265DBC:
/* 19469C 80265DBC 80C30210 */  lb        $v1, 0x210($a2)
/* 1946A0 80265DC0 24020009 */  addiu     $v0, $zero, 9
/* 1946A4 80265DC4 1462000C */  bne       $v1, $v0, .L80265DF8
/* 1946A8 80265DC8 24020004 */   addiu    $v0, $zero, 4
/* 1946AC 80265DCC 24020001 */  addiu     $v0, $zero, 1
/* 1946B0 80265DD0 50820001 */  beql      $a0, $v0, .L80265DD8
/* 1946B4 80265DD4 2404001A */   addiu    $a0, $zero, 0x1a
.L80265DD8:
/* 1946B8 80265DD8 24020012 */  addiu     $v0, $zero, 0x12
/* 1946BC 80265DDC 50820001 */  beql      $a0, $v0, .L80265DE4
/* 1946C0 80265DE0 24040016 */   addiu    $a0, $zero, 0x16
.L80265DE4:
/* 1946C4 80265DE4 2402001C */  addiu     $v0, $zero, 0x1c
/* 1946C8 80265DE8 50820001 */  beql      $a0, $v0, .L80265DF0
/* 1946CC 80265DEC 2404001D */   addiu    $a0, $zero, 0x1d
.L80265DF0:
/* 1946D0 80265DF0 80C30210 */  lb        $v1, 0x210($a2)
/* 1946D4 80265DF4 24020004 */  addiu     $v0, $zero, 4
.L80265DF8:
/* 1946D8 80265DF8 14620003 */  bne       $v1, $v0, .L80265E08
/* 1946DC 80265DFC 24020012 */   addiu    $v0, $zero, 0x12
/* 1946E0 80265E00 50820001 */  beql      $a0, $v0, .L80265E08
/* 1946E4 80265E04 24040018 */   addiu    $a0, $zero, 0x18
.L80265E08:
/* 1946E8 80265E08 8CA20000 */  lw        $v0, ($a1)
/* 1946EC 80265E0C 1040000B */  beqz      $v0, .L80265E3C
/* 1946F0 80265E10 24030001 */   addiu    $v1, $zero, 1
/* 1946F4 80265E14 8CA20000 */  lw        $v0, ($a1)
.L80265E18:
/* 1946F8 80265E18 14430002 */  bne       $v0, $v1, .L80265E24
/* 1946FC 80265E1C 00000000 */   nop      
/* 194700 80265E20 8CA70004 */  lw        $a3, 4($a1)
.L80265E24:
/* 194704 80265E24 1044FFD0 */  beq       $v0, $a0, .L80265D68
/* 194708 80265E28 00000000 */   nop      
/* 19470C 80265E2C 24A50008 */  addiu     $a1, $a1, 8
/* 194710 80265E30 8CA20000 */  lw        $v0, ($a1)
/* 194714 80265E34 1440FFF8 */  bnez      $v0, .L80265E18
/* 194718 80265E38 00000000 */   nop      
.L80265E3C:
/* 19471C 80265E3C 03E00008 */  jr        $ra
/* 194720 80265E40 00E0102D */   daddu    $v0, $a3, $zero
