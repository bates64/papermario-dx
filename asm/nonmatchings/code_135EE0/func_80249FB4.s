.set noat # allow manual use of $at
.set noreorder # don't insert nops after branches

.include "include/macro.inc"

glabel func_80249FB4
/* 13D2F4 80249FB4 8D250000 */  lw    $a1, ($t1)
/* 13D2F8 80249FB8 25440001 */  addiu $a0, $t2, 1
/* 13D2FC 80249FBC 25660001 */  addiu $a2, $t3, 1
/* 13D300 80249FC0 00A0182D */  daddu $v1, $a1, $zero
/* 13D304 80249FC4 8FAB00B4 */  lw    $t3, 0xb4($sp)
/* 13D308 80249FC8 24A50008 */  addiu $a1, $a1, 8
/* 13D30C 80249FCC 014B1021 */  addu  $v0, $t2, $t3
/* 13D310 80249FD0 8FAA00B0 */  lw    $t2, 0xb0($sp)
/* 13D314 80249FD4 8FAB00B8 */  lw    $t3, 0xb8($sp)
/* 13D318 80249FD8 2447FFFF */  addiu $a3, $v0, -1
/* 13D31C 80249FDC 014B1021 */  addu  $v0, $t2, $t3
/* 13D320 80249FE0 2448FFFF */  addiu $t0, $v0, -1
/* 13D324 80249FE4 3C02E700 */  lui   $v0, 0xe700
/* 13D328 80249FE8 AD250000 */  sw    $a1, ($t1)
/* 13D32C 80249FEC AC620000 */  sw    $v0, ($v1)
/* 13D330 80249FF0 1C800002 */  bgtz  $a0, .L80249FFC
/* 13D334 80249FF4 AC600004 */   sw    $zero, 4($v1)
/* 13D338 80249FF8 24040001 */  addiu $a0, $zero, 1
.L80249FFC:
/* 13D33C 80249FFC 58C00001 */  blezl $a2, .L8024A004
/* 13D340 8024A000 24060001 */   addiu $a2, $zero, 1
.L8024A004:
/* 13D344 8024A004 18E00129 */  blez  $a3, .L8024A4AC
/* 13D348 8024A008 00000000 */   nop   
/* 13D34C 8024A00C 19000127 */  blez  $t0, .L8024A4AC
/* 13D350 8024A010 2882013F */   slti  $v0, $a0, 0x13f
/* 13D354 8024A014 10400125 */  beqz  $v0, .L8024A4AC
/* 13D358 8024A018 28C200EF */   slti  $v0, $a2, 0xef
/* 13D35C 8024A01C 10400123 */  beqz  $v0, .L8024A4AC
/* 13D360 8024A020 28E2013F */   slti  $v0, $a3, 0x13f
/* 13D364 8024A024 50400001 */  beql  $v0, $zero, .L8024A02C
/* 13D368 8024A028 2407013F */   addiu $a3, $zero, 0x13f
.L8024A02C:
/* 13D36C 8024A02C 290200EF */  slti  $v0, $t0, 0xef
/* 13D370 8024A030 50400001 */  beql  $v0, $zero, .L8024A038
/* 13D374 8024A034 240800EF */   addiu $t0, $zero, 0xef
.L8024A038:
/* 13D378 8024A038 3C014080 */  lui   $at, 0x4080
/* 13D37C 8024A03C 44812000 */  mtc1  $at, $f4
/* 13D380 8024A040 44840000 */  mtc1  $a0, $f0
/* 13D384 8024A044 00000000 */  nop   
/* 13D388 8024A048 46800020 */  cvt.s.w $f0, $f0
/* 13D38C 8024A04C 46040002 */  mul.s $f0, $f0, $f4
/* 13D390 8024A050 00000000 */  nop   
/* 13D394 8024A054 24A20008 */  addiu $v0, $a1, 8
/* 13D398 8024A058 44861000 */  mtc1  $a2, $f2
/* 13D39C 8024A05C 00000000 */  nop   
/* 13D3A0 8024A060 468010A0 */  cvt.s.w $f2, $f2
/* 13D3A4 8024A064 3C04ED00 */  lui   $a0, 0xed00
/* 13D3A8 8024A068 46041082 */  mul.s $f2, $f2, $f4
/* 13D3AC 8024A06C 00000000 */  nop   
/* 13D3B0 8024A070 AD220000 */  sw    $v0, ($t1)
/* 13D3B4 8024A074 4600018D */  trunc.w.s $f6, $f0
/* 13D3B8 8024A078 44023000 */  mfc1  $v0, $f6
/* 13D3BC 8024A07C 00000000 */  nop   
/* 13D3C0 8024A080 30420FFF */  andi  $v0, $v0, 0xfff
/* 13D3C4 8024A084 00021300 */  sll   $v0, $v0, 0xc
/* 13D3C8 8024A088 4600118D */  trunc.w.s $f6, $f2
/* 13D3CC 8024A08C 44033000 */  mfc1  $v1, $f6
/* 13D3D0 8024A090 44871000 */  mtc1  $a3, $f2
/* 13D3D4 8024A094 00000000 */  nop   
/* 13D3D8 8024A098 468010A0 */  cvt.s.w $f2, $f2
/* 13D3DC 8024A09C 46041082 */  mul.s $f2, $f2, $f4
/* 13D3E0 8024A0A0 00000000 */  nop   
/* 13D3E4 8024A0A4 30630FFF */  andi  $v1, $v1, 0xfff
/* 13D3E8 8024A0A8 00641825 */  or    $v1, $v1, $a0
/* 13D3EC 8024A0AC 00431025 */  or    $v0, $v0, $v1
/* 13D3F0 8024A0B0 44880000 */  mtc1  $t0, $f0
/* 13D3F4 8024A0B4 00000000 */  nop   
/* 13D3F8 8024A0B8 46800020 */  cvt.s.w $f0, $f0
/* 13D3FC 8024A0BC 46040002 */  mul.s $f0, $f0, $f4
/* 13D400 8024A0C0 00000000 */  nop   
/* 13D404 8024A0C4 ACA20000 */  sw    $v0, ($a1)
/* 13D408 8024A0C8 4600118D */  trunc.w.s $f6, $f2
/* 13D40C 8024A0CC 44023000 */  mfc1  $v0, $f6
/* 13D410 8024A0D0 00000000 */  nop   
/* 13D414 8024A0D4 30420FFF */  andi  $v0, $v0, 0xfff
/* 13D418 8024A0D8 00021300 */  sll   $v0, $v0, 0xc
/* 13D41C 8024A0DC 4600018D */  trunc.w.s $f6, $f0
/* 13D420 8024A0E0 44033000 */  mfc1  $v1, $f6
/* 13D424 8024A0E4 00000000 */  nop   
/* 13D428 8024A0E8 30630FFF */  andi  $v1, $v1, 0xfff
/* 13D42C 8024A0EC 00431025 */  or    $v0, $v0, $v1
/* 13D430 8024A0F0 3C038027 */  lui   $v1, 0x8027
/* 13D434 8024A0F4 806300D4 */  lb    $v1, 0xd4($v1)
/* 13D438 8024A0F8 ACA20004 */  sw    $v0, 4($a1)
/* 13D43C 8024A0FC 24020003 */  addiu $v0, $zero, 3
/* 13D440 8024A100 1462002A */  bne   $v1, $v0, .L8024A1AC
/* 13D444 8024A104 24020001 */   addiu $v0, $zero, 1
/* 13D448 8024A108 3C038027 */  lui   $v1, 0x8027
/* 13D44C 8024A10C 8C6305E0 */  lw    $v1, 0x5e0($v1)
/* 13D450 8024A110 14620026 */  bne   $v1, $v0, .L8024A1AC
/* 13D454 8024A114 00000000 */   nop   
/* 13D458 8024A118 3C118027 */  lui   $s1, 0x8027
/* 13D45C 8024A11C 263104C8 */  addiu $s1, $s1, 0x4c8
/* 13D460 8024A120 8E220000 */  lw    $v0, ($s1)
/* 13D464 8024A124 1840000E */  blez  $v0, .L8024A160
/* 13D468 8024A128 24420001 */   addiu $v0, $v0, 1
/* 13D46C 8024A12C 3C108027 */  lui   $s0, 0x8027
/* 13D470 8024A130 261005E8 */  addiu $s0, $s0, 0x5e8
/* 13D474 8024A134 8FAB00AC */  lw    $t3, 0xac($sp)
/* 13D478 8024A138 8E040040 */  lw    $a0, 0x40($s0)
/* 13D47C 8024A13C 8FAA00B0 */  lw    $t2, 0xb0($sp)
/* 13D480 8024A140 25650116 */  addiu $a1, $t3, 0x116
/* 13D484 8024A144 0C051261 */  jal   set_icon_render_pos
/* 13D488 8024A148 2546000E */   addiu $a2, $t2, 0xe
/* 13D48C 8024A14C 8E040040 */  lw    $a0, 0x40($s0)
/* 13D490 8024A150 0C0511F8 */  jal   func_801447E0
/* 13D494 8024A154 00000000 */   nop   
/* 13D498 8024A158 8E220000 */  lw    $v0, ($s1)
/* 13D49C 8024A15C 24420001 */  addiu $v0, $v0, 1
.L8024A160:
/* 13D4A0 8024A160 00021840 */  sll   $v1, $v0, 1
/* 13D4A4 8024A164 00621821 */  addu  $v1, $v1, $v0
/* 13D4A8 8024A168 00031880 */  sll   $v1, $v1, 2
/* 13D4AC 8024A16C 3C028027 */  lui   $v0, 0x8027
/* 13D4B0 8024A170 00431021 */  addu  $v0, $v0, $v1
/* 13D4B4 8024A174 904204D0 */  lbu   $v0, 0x4d0($v0)
/* 13D4B8 8024A178 1040000C */  beqz  $v0, .L8024A1AC
/* 13D4BC 8024A17C 00000000 */   nop   
/* 13D4C0 8024A180 3C108027 */  lui   $s0, 0x8027
/* 13D4C4 8024A184 261005E8 */  addiu $s0, $s0, 0x5e8
/* 13D4C8 8024A188 8FAB00AC */  lw    $t3, 0xac($sp)
/* 13D4CC 8024A18C 8E040044 */  lw    $a0, 0x44($s0)
/* 13D4D0 8024A190 8FAA00B0 */  lw    $t2, 0xb0($sp)
/* 13D4D4 8024A194 25650116 */  addiu $a1, $t3, 0x116
/* 13D4D8 8024A198 0C051261 */  jal   set_icon_render_pos
/* 13D4DC 8024A19C 25460092 */   addiu $a2, $t2, 0x92
/* 13D4E0 8024A1A0 8E040044 */  lw    $a0, 0x44($s0)
/* 13D4E4 8024A1A4 0C0511F8 */  jal   func_801447E0
/* 13D4E8 8024A1A8 00000000 */   nop   
.L8024A1AC:
/* 13D4EC 8024A1AC 3C038027 */  lui   $v1, 0x8027
/* 13D4F0 8024A1B0 8C6305E4 */  lw    $v1, 0x5e4($v1)
/* 13D4F4 8024A1B4 8FA600AC */  lw    $a2, 0xac($sp)
/* 13D4F8 8024A1B8 50600001 */  beql  $v1, $zero, .L8024A1C0
/* 13D4FC 8024A1BC 24C60009 */   addiu $a2, $a2, 9
.L8024A1C0:
/* 13D500 8024A1C0 8FAB00B0 */  lw    $t3, 0xb0($sp)
/* 13D504 8024A1C4 2402005B */  addiu $v0, $zero, 0x5b
/* 13D508 8024A1C8 AFA20014 */  sw    $v0, 0x14($sp)
/* 13D50C 8024A1CC 24020022 */  addiu $v0, $zero, 0x22
/* 13D510 8024A1D0 AFA20018 */  sw    $v0, 0x18($sp)
/* 13D514 8024A1D4 240200FF */  addiu $v0, $zero, 0xff
/* 13D518 8024A1D8 AFA2001C */  sw    $v0, 0x1c($sp)
/* 13D51C 8024A1DC 24020001 */  addiu $v0, $zero, 1
/* 13D520 8024A1E0 AFA00010 */  sw    $zero, 0x10($sp)
/* 13D524 8024A1E4 14620004 */  bne   $v1, $v0, .L8024A1F8