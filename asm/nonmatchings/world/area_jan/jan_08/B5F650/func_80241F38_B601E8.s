.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80241F38_B601E8
/* B601E8 80241F38 27BDFFB0 */  addiu     $sp, $sp, -0x50
/* B601EC 80241F3C AFB20038 */  sw        $s2, 0x38($sp)
/* B601F0 80241F40 0080902D */  daddu     $s2, $a0, $zero
/* B601F4 80241F44 AFBF0048 */  sw        $ra, 0x48($sp)
/* B601F8 80241F48 AFB50044 */  sw        $s5, 0x44($sp)
/* B601FC 80241F4C AFB40040 */  sw        $s4, 0x40($sp)
/* B60200 80241F50 AFB3003C */  sw        $s3, 0x3c($sp)
/* B60204 80241F54 AFB10034 */  sw        $s1, 0x34($sp)
/* B60208 80241F58 AFB00030 */  sw        $s0, 0x30($sp)
/* B6020C 80241F5C 8E510148 */  lw        $s1, 0x148($s2)
/* B60210 80241F60 86240008 */  lh        $a0, 8($s1)
/* B60214 80241F64 0C00EABB */  jal       get_npc_unsafe
/* B60218 80241F68 00A0802D */   daddu    $s0, $a1, $zero
/* B6021C 80241F6C 8E43000C */  lw        $v1, 0xc($s2)
/* B60220 80241F70 0240202D */  daddu     $a0, $s2, $zero
/* B60224 80241F74 8C650000 */  lw        $a1, ($v1)
/* B60228 80241F78 0C0B1EAF */  jal       get_variable
/* B6022C 80241F7C 0040A82D */   daddu    $s5, $v0, $zero
/* B60230 80241F80 AFA00010 */  sw        $zero, 0x10($sp)
/* B60234 80241F84 8E2300D0 */  lw        $v1, 0xd0($s1)
/* B60238 80241F88 8C630030 */  lw        $v1, 0x30($v1)
/* B6023C 80241F8C AFA30014 */  sw        $v1, 0x14($sp)
/* B60240 80241F90 8E2300D0 */  lw        $v1, 0xd0($s1)
/* B60244 80241F94 8C63001C */  lw        $v1, 0x1c($v1)
/* B60248 80241F98 AFA30018 */  sw        $v1, 0x18($sp)
/* B6024C 80241F9C 8E2300D0 */  lw        $v1, 0xd0($s1)
/* B60250 80241FA0 8C630024 */  lw        $v1, 0x24($v1)
/* B60254 80241FA4 AFA3001C */  sw        $v1, 0x1c($sp)
/* B60258 80241FA8 8E2300D0 */  lw        $v1, 0xd0($s1)
/* B6025C 80241FAC 8C630028 */  lw        $v1, 0x28($v1)
/* B60260 80241FB0 27B40010 */  addiu     $s4, $sp, 0x10
/* B60264 80241FB4 AFA30020 */  sw        $v1, 0x20($sp)
/* B60268 80241FB8 8E2300D0 */  lw        $v1, 0xd0($s1)
/* B6026C 80241FBC 3C014282 */  lui       $at, 0x4282
/* B60270 80241FC0 44810000 */  mtc1      $at, $f0
/* B60274 80241FC4 8C63002C */  lw        $v1, 0x2c($v1)
/* B60278 80241FC8 0040982D */  daddu     $s3, $v0, $zero
/* B6027C 80241FCC E7A00028 */  swc1      $f0, 0x28($sp)
/* B60280 80241FD0 A7A0002C */  sh        $zero, 0x2c($sp)
/* B60284 80241FD4 16000005 */  bnez      $s0, .L80241FEC
/* B60288 80241FD8 AFA30024 */   sw       $v1, 0x24($sp)
/* B6028C 80241FDC 8E2200B0 */  lw        $v0, 0xb0($s1)
/* B60290 80241FE0 30420004 */  andi      $v0, $v0, 4
/* B60294 80241FE4 10400020 */  beqz      $v0, .L80242068
/* B60298 80241FE8 00000000 */   nop      
.L80241FEC:
/* B6029C 80241FEC 2404F7FF */  addiu     $a0, $zero, -0x801
/* B602A0 80241FF0 AE400070 */  sw        $zero, 0x70($s2)
/* B602A4 80241FF4 A6A0008E */  sh        $zero, 0x8e($s5)
/* B602A8 80241FF8 8E2200CC */  lw        $v0, 0xcc($s1)
/* B602AC 80241FFC 8EA30000 */  lw        $v1, ($s5)
/* B602B0 80242000 8C420000 */  lw        $v0, ($v0)
/* B602B4 80242004 00641824 */  and       $v1, $v1, $a0
/* B602B8 80242008 AEA30000 */  sw        $v1, ($s5)
/* B602BC 8024200C AEA20028 */  sw        $v0, 0x28($s5)
/* B602C0 80242010 8E2200D0 */  lw        $v0, 0xd0($s1)
/* B602C4 80242014 8C420034 */  lw        $v0, 0x34($v0)
/* B602C8 80242018 54400005 */  bnel      $v0, $zero, .L80242030
/* B602CC 8024201C 2402FDFF */   addiu    $v0, $zero, -0x201
/* B602D0 80242020 34620200 */  ori       $v0, $v1, 0x200
/* B602D4 80242024 2403FFF7 */  addiu     $v1, $zero, -9
/* B602D8 80242028 0809080E */  j         .L80242038
/* B602DC 8024202C 00431024 */   and      $v0, $v0, $v1
.L80242030:
/* B602E0 80242030 00621024 */  and       $v0, $v1, $v0
/* B602E4 80242034 34420008 */  ori       $v0, $v0, 8
.L80242038:
/* B602E8 80242038 AEA20000 */  sw        $v0, ($s5)
/* B602EC 8024203C 8E2200B0 */  lw        $v0, 0xb0($s1)
/* B602F0 80242040 30420004 */  andi      $v0, $v0, 4
/* B602F4 80242044 10400007 */  beqz      $v0, .L80242064
/* B602F8 80242048 24020063 */   addiu    $v0, $zero, 0x63
/* B602FC 8024204C AE420070 */  sw        $v0, 0x70($s2)
/* B60300 80242050 AE400074 */  sw        $zero, 0x74($s2)
/* B60304 80242054 8E2200B0 */  lw        $v0, 0xb0($s1)
/* B60308 80242058 2403FFFB */  addiu     $v1, $zero, -5
/* B6030C 8024205C 00431024 */  and       $v0, $v0, $v1
/* B60310 80242060 AE2200B0 */  sw        $v0, 0xb0($s1)
.L80242064:
/* B60314 80242064 AE20006C */  sw        $zero, 0x6c($s1)
.L80242068:
/* B60318 80242068 8E420070 */  lw        $v0, 0x70($s2)
/* B6031C 8024206C 2842001E */  slti      $v0, $v0, 0x1e
/* B60320 80242070 10400009 */  beqz      $v0, .L80242098
/* B60324 80242074 00000000 */   nop      
/* B60328 80242078 8E22006C */  lw        $v0, 0x6c($s1)
/* B6032C 8024207C 14400006 */  bnez      $v0, .L80242098
/* B60330 80242080 00000000 */   nop      
/* B60334 80242084 0C09061C */  jal       func_80241870_B5FB20
/* B60338 80242088 0240202D */   daddu    $a0, $s2, $zero
/* B6033C 8024208C 10400002 */  beqz      $v0, .L80242098
/* B60340 80242090 2402001E */   addiu    $v0, $zero, 0x1e
/* B60344 80242094 AE420070 */  sw        $v0, 0x70($s2)
.L80242098:
/* B60348 80242098 8E430070 */  lw        $v1, 0x70($s2)
/* B6034C 8024209C 2C620064 */  sltiu     $v0, $v1, 0x64
/* B60350 802420A0 10400048 */  beqz      $v0, .L802421C4
/* B60354 802420A4 00031080 */   sll      $v0, $v1, 2
/* B60358 802420A8 3C018024 */  lui       $at, %hi(D_80247670)
/* B6035C 802420AC 00220821 */  addu      $at, $at, $v0
/* B60360 802420B0 8C227670 */  lw        $v0, %lo(D_80247670)($at)
/* B60364 802420B4 00400008 */  jr        $v0
/* B60368 802420B8 00000000 */   nop      
/* B6036C 802420BC 0240202D */  daddu     $a0, $s2, $zero
/* B60370 802420C0 0260282D */  daddu     $a1, $s3, $zero
/* B60374 802420C4 0C012568 */  jal       func_800495A0
/* B60378 802420C8 0280302D */   daddu    $a2, $s4, $zero
/* B6037C 802420CC 0240202D */  daddu     $a0, $s2, $zero
/* B60380 802420D0 0260282D */  daddu     $a1, $s3, $zero
/* B60384 802420D4 0C0125AE */  jal       func_800496B8
/* B60388 802420D8 0280302D */   daddu    $a2, $s4, $zero
/* B6038C 802420DC 08090871 */  j         .L802421C4
/* B60390 802420E0 00000000 */   nop      
/* B60394 802420E4 0240202D */  daddu     $a0, $s2, $zero
/* B60398 802420E8 0260282D */  daddu     $a1, $s3, $zero
/* B6039C 802420EC 0C090515 */  jal       jan_08_UnkNpcAIFunc4
/* B603A0 802420F0 0280302D */   daddu    $a2, $s4, $zero
/* B603A4 802420F4 0240202D */  daddu     $a0, $s2, $zero
/* B603A8 802420F8 0260282D */  daddu     $a1, $s3, $zero
/* B603AC 802420FC 0C090529 */  jal       func_802414A4_B5F754
/* B603B0 80242100 0280302D */   daddu    $a2, $s4, $zero
/* B603B4 80242104 08090871 */  j         .L802421C4
/* B603B8 80242108 00000000 */   nop      
/* B603BC 8024210C 0240202D */  daddu     $a0, $s2, $zero
/* B603C0 80242110 0260282D */  daddu     $a1, $s3, $zero
/* B603C4 80242114 0C01278F */  jal       func_80049E3C
/* B603C8 80242118 0280302D */   daddu    $a2, $s4, $zero
/* B603CC 8024211C 0240202D */  daddu     $a0, $s2, $zero
/* B603D0 80242120 0260282D */  daddu     $a1, $s3, $zero
/* B603D4 80242124 0C0127B3 */  jal       func_80049ECC
/* B603D8 80242128 0280302D */   daddu    $a2, $s4, $zero
/* B603DC 8024212C 08090871 */  j         .L802421C4
/* B603E0 80242130 00000000 */   nop      
/* B603E4 80242134 0240202D */  daddu     $a0, $s2, $zero
/* B603E8 80242138 0260282D */  daddu     $a1, $s3, $zero
/* B603EC 8024213C 0C0127DF */  jal       func_80049F7C
/* B603F0 80242140 0280302D */   daddu    $a2, $s4, $zero
/* B603F4 80242144 0240202D */  daddu     $a0, $s2, $zero
/* B603F8 80242148 0260282D */  daddu     $a1, $s3, $zero
/* B603FC 8024214C 0C012849 */  jal       func_8004A124
/* B60400 80242150 0280302D */   daddu    $a2, $s4, $zero
/* B60404 80242154 08090871 */  j         .L802421C4
/* B60408 80242158 00000000 */   nop      
/* B6040C 8024215C 0240202D */  daddu     $a0, $s2, $zero
/* B60410 80242160 0260282D */  daddu     $a1, $s3, $zero
/* B60414 80242164 0C0128FA */  jal       func_8004A3E8
/* B60418 80242168 0280302D */   daddu    $a2, $s4, $zero
/* B6041C 8024216C 08090871 */  j         .L802421C4
/* B60420 80242170 00000000 */   nop      
/* B60424 80242174 0C09059A */  jal       jan_08_UnkNpcAIFunc6
/* B60428 80242178 0240202D */   daddu    $a0, $s2, $zero
/* B6042C 8024217C 0C0905B5 */  jal       jan_08_UnkNpcAIFunc7
/* B60430 80242180 0240202D */   daddu    $a0, $s2, $zero
/* B60434 80242184 8E430070 */  lw        $v1, 0x70($s2)
/* B60438 80242188 24020020 */  addiu     $v0, $zero, 0x20
/* B6043C 8024218C 1462000D */  bne       $v1, $v0, .L802421C4
/* B60440 80242190 00000000 */   nop      
/* B60444 80242194 0C0905D1 */  jal       jan_08_UnkNpcAIFunc8
/* B60448 80242198 0240202D */   daddu    $a0, $s2, $zero
/* B6044C 8024219C 8E430070 */  lw        $v1, 0x70($s2)
/* B60450 802421A0 24020021 */  addiu     $v0, $zero, 0x21
/* B60454 802421A4 14620007 */  bne       $v1, $v0, .L802421C4
/* B60458 802421A8 00000000 */   nop      
/* B6045C 802421AC 0C090607 */  jal       jan_08_UnkNpcAIFunc5
/* B60460 802421B0 0240202D */   daddu    $a0, $s2, $zero
/* B60464 802421B4 08090871 */  j         .L802421C4
/* B60468 802421B8 00000000 */   nop      
/* B6046C 802421BC 0C0129CF */  jal       func_8004A73C
/* B60470 802421C0 0240202D */   daddu    $a0, $s2, $zero
.L802421C4:
/* B60474 802421C4 8FBF0048 */  lw        $ra, 0x48($sp)
/* B60478 802421C8 8FB50044 */  lw        $s5, 0x44($sp)
/* B6047C 802421CC 8FB40040 */  lw        $s4, 0x40($sp)
/* B60480 802421D0 8FB3003C */  lw        $s3, 0x3c($sp)
/* B60484 802421D4 8FB20038 */  lw        $s2, 0x38($sp)
/* B60488 802421D8 8FB10034 */  lw        $s1, 0x34($sp)
/* B6048C 802421DC 8FB00030 */  lw        $s0, 0x30($sp)
/* B60490 802421E0 0000102D */  daddu     $v0, $zero, $zero
/* B60494 802421E4 03E00008 */  jr        $ra
/* B60498 802421E8 27BD0050 */   addiu    $sp, $sp, 0x50
/* B6049C 802421EC 00000000 */  nop       
