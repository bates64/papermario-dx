.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel update_starpoints_display
/* 16EC9C 802403BC 27BDFF70 */  addiu     $sp, $sp, -0x90
/* 16ECA0 802403C0 3C0B800E */  lui       $t3, %hi(gBattleStatus)
/* 16ECA4 802403C4 256BC070 */  addiu     $t3, $t3, %lo(gBattleStatus)
/* 16ECA8 802403C8 AFBF007C */  sw        $ra, 0x7c($sp)
/* 16ECAC 802403CC AFBE0078 */  sw        $fp, 0x78($sp)
/* 16ECB0 802403D0 AFB70074 */  sw        $s7, 0x74($sp)
/* 16ECB4 802403D4 AFB60070 */  sw        $s6, 0x70($sp)
/* 16ECB8 802403D8 AFB5006C */  sw        $s5, 0x6c($sp)
/* 16ECBC 802403DC AFB40068 */  sw        $s4, 0x68($sp)
/* 16ECC0 802403E0 AFB30064 */  sw        $s3, 0x64($sp)
/* 16ECC4 802403E4 AFB20060 */  sw        $s2, 0x60($sp)
/* 16ECC8 802403E8 AFB1005C */  sw        $s1, 0x5c($sp)
/* 16ECCC 802403EC AFB00058 */  sw        $s0, 0x58($sp)
/* 16ECD0 802403F0 F7B60088 */  sdc1      $f22, 0x88($sp)
/* 16ECD4 802403F4 F7B40080 */  sdc1      $f20, 0x80($sp)
/* 16ECD8 802403F8 8D620000 */  lw        $v0, ($t3)
/* 16ECDC 802403FC 30420001 */  andi      $v0, $v0, 1
/* 16ECE0 80240400 1040016E */  beqz      $v0, .L802409BC
/* 16ECE4 80240404 00000000 */   nop      
/* 16ECE8 80240408 8D620004 */  lw        $v0, 4($t3)
/* 16ECEC 8024040C 30420001 */  andi      $v0, $v0, 1
/* 16ECF0 80240410 1440001D */  bnez      $v0, .L80240488
/* 16ECF4 80240414 240500CA */   addiu    $a1, $zero, 0xca
/* 16ECF8 80240418 3C036666 */  lui       $v1, 0x6666
/* 16ECFC 8024041C 34636667 */  ori       $v1, $v1, 0x6667
/* 16ED00 80240420 91650078 */  lbu       $a1, 0x78($t3)
/* 16ED04 80240424 24020124 */  addiu     $v0, $zero, 0x124
/* 16ED08 80240428 3C01802A */  lui       $at, 0x802a
/* 16ED0C 8024042C AC22DA40 */  sw        $v0, -0x25c0($at)
/* 16ED10 80240430 240200C4 */  addiu     $v0, $zero, 0xc4
/* 16ED14 80240434 00052E00 */  sll       $a1, $a1, 0x18
/* 16ED18 80240438 00052603 */  sra       $a0, $a1, 0x18
/* 16ED1C 8024043C 00830018 */  mult      $a0, $v1
/* 16ED20 80240440 3C01802A */  lui       $at, 0x802a
/* 16ED24 80240444 AC22DA44 */  sw        $v0, -0x25bc($at)
/* 16ED28 80240448 24020006 */  addiu     $v0, $zero, 6
/* 16ED2C 8024044C 3C01802A */  lui       $at, 0x802a
/* 16ED30 80240450 AC22DA48 */  sw        $v0, -0x25b8($at)
/* 16ED34 80240454 00052FC3 */  sra       $a1, $a1, 0x1f
/* 16ED38 80240458 00006010 */  mfhi      $t4
/* 16ED3C 8024045C 000C1883 */  sra       $v1, $t4, 2
/* 16ED40 80240460 00651823 */  subu      $v1, $v1, $a1
/* 16ED44 80240464 00031080 */  sll       $v0, $v1, 2
/* 16ED48 80240468 00431021 */  addu      $v0, $v0, $v1
/* 16ED4C 8024046C 00021040 */  sll       $v0, $v0, 1
/* 16ED50 80240470 00822023 */  subu      $a0, $a0, $v0
/* 16ED54 80240474 00042600 */  sll       $a0, $a0, 0x18
/* 16ED58 80240478 00042603 */  sra       $a0, $a0, 0x18
/* 16ED5C 8024047C 3C01802A */  lui       $at, 0x802a
/* 16ED60 80240480 0809014B */  j         .L8024052C
/* 16ED64 80240484 AC24DA4C */   sw       $a0, -0x25b4($at)
.L80240488:
/* 16ED68 80240488 3C08802A */  lui       $t0, 0x802a
/* 16ED6C 8024048C 2508DA40 */  addiu     $t0, $t0, -0x25c0
/* 16ED70 80240490 3C0A802A */  lui       $t2, 0x802a
/* 16ED74 80240494 254ADA48 */  addiu     $t2, $t2, -0x25b8
/* 16ED78 80240498 8D060000 */  lw        $a2, ($t0)
/* 16ED7C 8024049C 8D430000 */  lw        $v1, ($t2)
/* 16ED80 802404A0 00A62823 */  subu      $a1, $a1, $a2
/* 16ED84 802404A4 14600002 */  bnez      $v1, .L802404B0
/* 16ED88 802404A8 00A3001A */   div      $zero, $a1, $v1
/* 16ED8C 802404AC 0007000D */  break     7
.L802404B0:
/* 16ED90 802404B0 2401FFFF */   addiu    $at, $zero, -1
/* 16ED94 802404B4 14610004 */  bne       $v1, $at, .L802404C8
/* 16ED98 802404B8 3C018000 */   lui      $at, 0x8000
/* 16ED9C 802404BC 14A10002 */  bne       $a1, $at, .L802404C8
/* 16EDA0 802404C0 00000000 */   nop      
/* 16EDA4 802404C4 0006000D */  break     6
.L802404C8:
/* 16EDA8 802404C8 00002812 */   mflo     $a1
/* 16EDAC 802404CC 3C07802A */  lui       $a3, 0x802a
/* 16EDB0 802404D0 24E7DA44 */  addiu     $a3, $a3, -0x25bc
/* 16EDB4 802404D4 8CE40000 */  lw        $a0, ($a3)
/* 16EDB8 802404D8 24020078 */  addiu     $v0, $zero, 0x78
/* 16EDBC 802404DC 00441023 */  subu      $v0, $v0, $a0
/* 16EDC0 802404E0 14600002 */  bnez      $v1, .L802404EC
/* 16EDC4 802404E4 0043001A */   div      $zero, $v0, $v1
/* 16EDC8 802404E8 0007000D */  break     7
.L802404EC:
/* 16EDCC 802404EC 2401FFFF */   addiu    $at, $zero, -1
/* 16EDD0 802404F0 14610004 */  bne       $v1, $at, .L80240504
/* 16EDD4 802404F4 3C018000 */   lui      $at, 0x8000
/* 16EDD8 802404F8 14410002 */  bne       $v0, $at, .L80240504
/* 16EDDC 802404FC 00000000 */   nop      
/* 16EDE0 80240500 0006000D */  break     6
.L80240504:
/* 16EDE4 80240504 00001012 */   mflo     $v0
/* 16EDE8 80240508 2463FFFF */  addiu     $v1, $v1, -1
/* 16EDEC 8024050C AD430000 */  sw        $v1, ($t2)
/* 16EDF0 80240510 00C53021 */  addu      $a2, $a2, $a1
/* 16EDF4 80240514 00822021 */  addu      $a0, $a0, $v0
/* 16EDF8 80240518 AD060000 */  sw        $a2, ($t0)
/* 16EDFC 8024051C 1C600003 */  bgtz      $v1, .L8024052C
/* 16EE00 80240520 ACE40000 */   sw       $a0, ($a3)
/* 16EE04 80240524 24020001 */  addiu     $v0, $zero, 1
/* 16EE08 80240528 AD420000 */  sw        $v0, ($t2)
.L8024052C:
/* 16EE0C 8024052C 3C028028 */  lui       $v0, 0x8028
/* 16EE10 80240530 804209F4 */  lb        $v0, 0x9f4($v0)
/* 16EE14 80240534 1040000F */  beqz      $v0, .L80240574
/* 16EE18 80240538 24050001 */   addiu    $a1, $zero, 1
/* 16EE1C 8024053C 3C048028 */  lui       $a0, 0x8028
/* 16EE20 80240540 248409F5 */  addiu     $a0, $a0, 0x9f5
/* 16EE24 80240544 80830000 */  lb        $v1, ($a0)
/* 16EE28 80240548 28620009 */  slti      $v0, $v1, 9
/* 16EE2C 8024054C 14400004 */  bnez      $v0, .L80240560
/* 16EE30 80240550 2862000D */   slti     $v0, $v1, 0xd
/* 16EE34 80240554 50400002 */  beql      $v0, $zero, .L80240560
/* 16EE38 80240558 A0800000 */   sb       $zero, ($a0)
/* 16EE3C 8024055C 0000282D */  daddu     $a1, $zero, $zero
.L80240560:
/* 16EE40 80240560 3C038028 */  lui       $v1, 0x8028
/* 16EE44 80240564 246309F5 */  addiu     $v1, $v1, 0x9f5
/* 16EE48 80240568 90620000 */  lbu       $v0, ($v1)
/* 16EE4C 8024056C 24420001 */  addiu     $v0, $v0, 1
/* 16EE50 80240570 A0620000 */  sb        $v0, ($v1)
.L80240574:
/* 16EE54 80240574 10A00111 */  beqz      $a1, .L802409BC
/* 16EE58 80240578 00000000 */   nop      
/* 16EE5C 8024057C 3C038028 */  lui       $v1, 0x8028
/* 16EE60 80240580 246309F0 */  addiu     $v1, $v1, 0x9f0
/* 16EE64 80240584 9162007A */  lbu       $v0, 0x7a($t3)
/* 16EE68 80240588 C4600000 */  lwc1      $f0, ($v1)
/* 16EE6C 8024058C 3C013FF0 */  lui       $at, 0x3ff0
/* 16EE70 80240590 44811800 */  mtc1      $at, $f3
/* 16EE74 80240594 44801000 */  mtc1      $zero, $f2
/* 16EE78 80240598 3C013F80 */  lui       $at, 0x3f80
/* 16EE7C 8024059C 4481B000 */  mtc1      $at, $f22
/* 16EE80 802405A0 46000021 */  cvt.d.s   $f0, $f0
/* 16EE84 802405A4 46220001 */  sub.d     $f0, $f0, $f2
/* 16EE88 802405A8 44801000 */  mtc1      $zero, $f2
/* 16EE8C 802405AC 2442FFFF */  addiu     $v0, $v0, -1
/* 16EE90 802405B0 A162007A */  sb        $v0, 0x7a($t3)
/* 16EE94 802405B4 46200020 */  cvt.s.d   $f0, $f0
/* 16EE98 802405B8 4602003E */  c.le.s    $f0, $f2
/* 16EE9C 802405BC 00000000 */  nop       
/* 16EEA0 802405C0 45000036 */  bc1f      .L8024069C
/* 16EEA4 802405C4 E4600000 */   swc1     $f0, ($v1)
/* 16EEA8 802405C8 81620079 */  lb        $v0, 0x79($t3)
/* 16EEAC 802405CC 1840000D */  blez      $v0, .L80240604
/* 16EEB0 802405D0 00000000 */   nop      
/* 16EEB4 802405D4 91620078 */  lbu       $v0, 0x78($t3)
/* 16EEB8 802405D8 24420001 */  addiu     $v0, $v0, 1
/* 16EEBC 802405DC A1620078 */  sb        $v0, 0x78($t3)
/* 16EEC0 802405E0 00021600 */  sll       $v0, $v0, 0x18
/* 16EEC4 802405E4 00021603 */  sra       $v0, $v0, 0x18
/* 16EEC8 802405E8 28420065 */  slti      $v0, $v0, 0x65
/* 16EECC 802405EC 14400002 */  bnez      $v0, .L802405F8
/* 16EED0 802405F0 24020064 */   addiu    $v0, $zero, 0x64
/* 16EED4 802405F4 A1620078 */  sb        $v0, 0x78($t3)
.L802405F8:
/* 16EED8 802405F8 91620079 */  lbu       $v0, 0x79($t3)
/* 16EEDC 802405FC 2442FFFF */  addiu     $v0, $v0, -1
/* 16EEE0 80240600 A1620079 */  sb        $v0, 0x79($t3)
.L80240604:
/* 16EEE4 80240604 81630079 */  lb        $v1, 0x79($t3)
/* 16EEE8 80240608 58600001 */  blezl     $v1, .L80240610
/* 16EEEC 8024060C 24030001 */   addiu    $v1, $zero, 1
.L80240610:
/* 16EEF0 80240610 44830000 */  mtc1      $v1, $f0
/* 16EEF4 80240614 00000000 */  nop       
/* 16EEF8 80240618 46800020 */  cvt.s.w   $f0, $f0
/* 16EEFC 8024061C 8162007A */  lb        $v0, 0x7a($t3)
/* 16EF00 80240620 3C013FF0 */  lui       $at, 0x3ff0
/* 16EF04 80240624 44811800 */  mtc1      $at, $f3
/* 16EF08 80240628 44801000 */  mtc1      $zero, $f2
/* 16EF0C 8024062C 44822000 */  mtc1      $v0, $f4
/* 16EF10 80240630 00000000 */  nop       
/* 16EF14 80240634 46802120 */  cvt.s.w   $f4, $f4
/* 16EF18 80240638 46002103 */  div.s     $f4, $f4, $f0
/* 16EF1C 8024063C 46002021 */  cvt.d.s   $f0, $f4
/* 16EF20 80240640 3C028028 */  lui       $v0, 0x8028
/* 16EF24 80240644 244209F0 */  addiu     $v0, $v0, 0x9f0
/* 16EF28 80240648 4622003C */  c.lt.d    $f0, $f2
/* 16EF2C 8024064C 00000000 */  nop       
/* 16EF30 80240650 45000005 */  bc1f      .L80240668
/* 16EF34 80240654 E4440000 */   swc1     $f4, ($v0)
/* 16EF38 80240658 3C013F80 */  lui       $at, 0x3f80
/* 16EF3C 8024065C 44810000 */  mtc1      $at, $f0
/* 16EF40 80240660 00000000 */  nop       
/* 16EF44 80240664 E4400000 */  swc1      $f0, ($v0)
.L80240668:
/* 16EF48 80240668 C4400000 */  lwc1      $f0, ($v0)
/* 16EF4C 8024066C 3C014018 */  lui       $at, 0x4018
/* 16EF50 80240670 44811800 */  mtc1      $at, $f3
/* 16EF54 80240674 44801000 */  mtc1      $zero, $f2
/* 16EF58 80240678 46000021 */  cvt.d.s   $f0, $f0
/* 16EF5C 8024067C 4620103C */  c.lt.d    $f2, $f0
/* 16EF60 80240680 00000000 */  nop       
/* 16EF64 80240684 45000006 */  bc1f      .L802406A0
/* 16EF68 80240688 3C036666 */   lui      $v1, 0x6666
/* 16EF6C 8024068C 3C0140C0 */  lui       $at, 0x40c0
/* 16EF70 80240690 44810000 */  mtc1      $at, $f0
/* 16EF74 80240694 00000000 */  nop       
/* 16EF78 80240698 E4400000 */  swc1      $f0, ($v0)
.L8024069C:
/* 16EF7C 8024069C 3C036666 */  lui       $v1, 0x6666
.L802406A0:
/* 16EF80 802406A0 34636667 */  ori       $v1, $v1, 0x6667
/* 16EF84 802406A4 91620078 */  lbu       $v0, 0x78($t3)
/* 16EF88 802406A8 00021600 */  sll       $v0, $v0, 0x18
/* 16EF8C 802406AC 00022603 */  sra       $a0, $v0, 0x18
/* 16EF90 802406B0 00830018 */  mult      $a0, $v1
/* 16EF94 802406B4 0000882D */  daddu     $s1, $zero, $zero
/* 16EF98 802406B8 3C12802A */  lui       $s2, 0x802a
/* 16EF9C 802406BC 8E52DA40 */  lw        $s2, -0x25c0($s2)
/* 16EFA0 802406C0 3C15802A */  lui       $s5, 0x802a
/* 16EFA4 802406C4 8EB5DA44 */  lw        $s5, -0x25bc($s5)
/* 16EFA8 802406C8 000217C3 */  sra       $v0, $v0, 0x1f
/* 16EFAC 802406CC 00006010 */  mfhi      $t4
/* 16EFB0 802406D0 000C1883 */  sra       $v1, $t4, 2
/* 16EFB4 802406D4 00621823 */  subu      $v1, $v1, $v0
/* 16EFB8 802406D8 00031600 */  sll       $v0, $v1, 0x18
/* 16EFBC 802406DC 0002B603 */  sra       $s6, $v0, 0x18
/* 16EFC0 802406E0 00031080 */  sll       $v0, $v1, 2
/* 16EFC4 802406E4 00431021 */  addu      $v0, $v0, $v1
/* 16EFC8 802406E8 00021040 */  sll       $v0, $v0, 1
/* 16EFCC 802406EC 00822023 */  subu      $a0, $a0, $v0
/* 16EFD0 802406F0 00042600 */  sll       $a0, $a0, 0x18
/* 16EFD4 802406F4 00042603 */  sra       $a0, $a0, 0x18
/* 16EFD8 802406F8 1AC00039 */  blez      $s6, .L802407E0
/* 16EFDC 802406FC AFA40050 */   sw       $a0, 0x50($sp)
/* 16EFE0 80240700 3C1E8008 */  lui       $fp, 0x8008
/* 16EFE4 80240704 27DE0FF0 */  addiu     $fp, $fp, 0xff0
/* 16EFE8 80240708 3C178010 */  lui       $s7, 0x8010
/* 16EFEC 8024070C 26F74BEC */  addiu     $s7, $s7, 0x4bec
/* 16EFF0 80240710 3C14802A */  lui       $s4, 0x802a
/* 16EFF4 80240714 2694EFE8 */  addiu     $s4, $s4, -0x1018
/* 16EFF8 80240718 3C13802A */  lui       $s3, 0x802a
/* 16EFFC 8024071C 2673EFC0 */  addiu     $s3, $s3, -0x1040
.L80240720:
/* 16F000 80240720 8E700000 */  lw        $s0, ($s3)
/* 16F004 80240724 0C05122C */  jal       get_menu_icon_script
/* 16F008 80240728 0200202D */   daddu    $a0, $s0, $zero
/* 16F00C 8024072C 105E0004 */  beq       $v0, $fp, .L80240740
/* 16F010 80240730 0200202D */   daddu    $a0, $s0, $zero
/* 16F014 80240734 0C0511FF */  jal       set_menu_icon_script
/* 16F018 80240738 03C0282D */   daddu    $a1, $fp, $zero
/* 16F01C 8024073C 0200202D */  daddu     $a0, $s0, $zero
.L80240740:
/* 16F020 80240740 0C05128B */  jal       clear_icon_flags
/* 16F024 80240744 24050002 */   addiu    $a1, $zero, 2
/* 16F028 80240748 0200202D */  daddu     $a0, $s0, $zero
/* 16F02C 8024074C 0240282D */  daddu     $a1, $s2, $zero
/* 16F030 80240750 0C051261 */  jal       set_icon_render_pos
/* 16F034 80240754 02A0302D */   daddu    $a2, $s5, $zero
/* 16F038 80240758 0C0511EA */  jal       draw_icon_0
/* 16F03C 8024075C 0200202D */   daddu    $a0, $s0, $zero
/* 16F040 80240760 8E900000 */  lw        $s0, ($s4)
/* 16F044 80240764 0C05122C */  jal       get_menu_icon_script
/* 16F048 80240768 0200202D */   daddu    $a0, $s0, $zero
/* 16F04C 8024076C 10570004 */  beq       $v0, $s7, .L80240780
/* 16F050 80240770 0200202D */   daddu    $a0, $s0, $zero
/* 16F054 80240774 0C0511FF */  jal       set_menu_icon_script
/* 16F058 80240778 02E0282D */   daddu    $a1, $s7, $zero
/* 16F05C 8024077C 0200202D */  daddu     $a0, $s0, $zero
.L80240780:
/* 16F060 80240780 0C05128B */  jal       clear_icon_flags
/* 16F064 80240784 24050002 */   addiu    $a1, $zero, 2
/* 16F068 80240788 0200202D */  daddu     $a0, $s0, $zero
/* 16F06C 8024078C 0240282D */  daddu     $a1, $s2, $zero
/* 16F070 80240790 0C051261 */  jal       set_icon_render_pos
/* 16F074 80240794 26A6FFFB */   addiu    $a2, $s5, -5
/* 16F078 80240798 0C0511EA */  jal       draw_icon_0
/* 16F07C 8024079C 0200202D */   daddu    $a0, $s0, $zero
/* 16F080 802407A0 3C0141A0 */  lui       $at, 0x41a0
/* 16F084 802407A4 44810000 */  mtc1      $at, $f0
/* 16F088 802407A8 00000000 */  nop       
/* 16F08C 802407AC 4600B002 */  mul.s     $f0, $f22, $f0
/* 16F090 802407B0 00000000 */  nop       
/* 16F094 802407B4 26940004 */  addiu     $s4, $s4, 4
/* 16F098 802407B8 44921000 */  mtc1      $s2, $f2
/* 16F09C 802407BC 00000000 */  nop       
/* 16F0A0 802407C0 468010A0 */  cvt.s.w   $f2, $f2
/* 16F0A4 802407C4 46001081 */  sub.s     $f2, $f2, $f0
/* 16F0A8 802407C8 26310001 */  addiu     $s1, $s1, 1
/* 16F0AC 802407CC 0236102A */  slt       $v0, $s1, $s6
/* 16F0B0 802407D0 4600118D */  trunc.w.s $f6, $f2
/* 16F0B4 802407D4 44123000 */  mfc1      $s2, $f6
/* 16F0B8 802407D8 1440FFD1 */  bnez      $v0, .L80240720
/* 16F0BC 802407DC 26730004 */   addiu    $s3, $s3, 4
.L802407E0:
/* 16F0C0 802407E0 2A22000A */  slti      $v0, $s1, 0xa
/* 16F0C4 802407E4 10400013 */  beqz      $v0, .L80240834
/* 16F0C8 802407E8 00111880 */   sll      $v1, $s1, 2
/* 16F0CC 802407EC 3C02802A */  lui       $v0, 0x802a
/* 16F0D0 802407F0 2442EFE8 */  addiu     $v0, $v0, -0x1018
/* 16F0D4 802407F4 00629021 */  addu      $s2, $v1, $v0
/* 16F0D8 802407F8 3C02802A */  lui       $v0, 0x802a
/* 16F0DC 802407FC 2442EFC0 */  addiu     $v0, $v0, -0x1040
/* 16F0E0 80240800 00628021 */  addu      $s0, $v1, $v0
/* 16F0E4 80240804 24050002 */  addiu     $a1, $zero, 2
.L80240808:
/* 16F0E8 80240808 8E040000 */  lw        $a0, ($s0)
/* 16F0EC 8024080C 26100004 */  addiu     $s0, $s0, 4
/* 16F0F0 80240810 0C051280 */  jal       set_icon_flags
/* 16F0F4 80240814 26310001 */   addiu    $s1, $s1, 1
/* 16F0F8 80240818 24050002 */  addiu     $a1, $zero, 2
/* 16F0FC 8024081C 8E440000 */  lw        $a0, ($s2)
/* 16F100 80240820 0C051280 */  jal       set_icon_flags
/* 16F104 80240824 26520004 */   addiu    $s2, $s2, 4
/* 16F108 80240828 2A22000A */  slti      $v0, $s1, 0xa
/* 16F10C 8024082C 1440FFF6 */  bnez      $v0, .L80240808
/* 16F110 80240830 24050002 */   addiu    $a1, $zero, 2
.L80240834:
/* 16F114 80240834 3C014160 */  lui       $at, 0x4160
/* 16F118 80240838 44810000 */  mtc1      $at, $f0
/* 16F11C 8024083C 00000000 */  nop       
/* 16F120 80240840 4600B002 */  mul.s     $f0, $f22, $f0
/* 16F124 80240844 00000000 */  nop       
/* 16F128 80240848 3C01802A */  lui       $at, 0x802a
/* 16F12C 8024084C C422DA44 */  lwc1      $f2, -0x25bc($at)
/* 16F130 80240850 468010A0 */  cvt.s.w   $f2, $f2
/* 16F134 80240854 3C02800E */  lui       $v0, 0x800e
/* 16F138 80240858 8C42C074 */  lw        $v0, -0x3f8c($v0)
/* 16F13C 8024085C 46001080 */  add.s     $f2, $f2, $f0
/* 16F140 80240860 3C12802A */  lui       $s2, 0x802a
/* 16F144 80240864 8E52DA40 */  lw        $s2, -0x25c0($s2)
/* 16F148 80240868 30420001 */  andi      $v0, $v0, 1
/* 16F14C 8024086C 4600118D */  trunc.w.s $f6, $f2
/* 16F150 80240870 44153000 */  mfc1      $s5, $f6
/* 16F154 80240874 1040001D */  beqz      $v0, .L802408EC
/* 16F158 80240878 00000000 */   nop      
/* 16F15C 8024087C 8FAC0050 */  lw        $t4, 0x50($sp)
/* 16F160 80240880 1180001B */  beqz      $t4, .L802408F0
/* 16F164 80240884 0000202D */   daddu    $a0, $zero, $zero
/* 16F168 80240888 24050004 */  addiu     $a1, $zero, 4
/* 16F16C 8024088C 2646FF9C */  addiu     $a2, $s2, -0x64
/* 16F170 80240890 2402006E */  addiu     $v0, $zero, 0x6e
/* 16F174 80240894 AFA20014 */  sw        $v0, 0x14($sp)
/* 16F178 80240898 2402000C */  addiu     $v0, $zero, 0xc
/* 16F17C 8024089C AFA20018 */  sw        $v0, 0x18($sp)
/* 16F180 802408A0 24020078 */  addiu     $v0, $zero, 0x78
/* 16F184 802408A4 AFA2001C */  sw        $v0, 0x1c($sp)
/* 16F188 802408A8 24020140 */  addiu     $v0, $zero, 0x140
/* 16F18C 802408AC AFA20044 */  sw        $v0, 0x44($sp)
/* 16F190 802408B0 240200F0 */  addiu     $v0, $zero, 0xf0
/* 16F194 802408B4 26A7FFFB */  addiu     $a3, $s5, -5
/* 16F198 802408B8 AFA00010 */  sw        $zero, 0x10($sp)
/* 16F19C 802408BC AFA00020 */  sw        $zero, 0x20($sp)
/* 16F1A0 802408C0 AFA00024 */  sw        $zero, 0x24($sp)
/* 16F1A4 802408C4 AFA00028 */  sw        $zero, 0x28($sp)
/* 16F1A8 802408C8 AFA0002C */  sw        $zero, 0x2c($sp)
/* 16F1AC 802408CC AFA00030 */  sw        $zero, 0x30($sp)
/* 16F1B0 802408D0 AFA00034 */  sw        $zero, 0x34($sp)
/* 16F1B4 802408D4 AFA00038 */  sw        $zero, 0x38($sp)
/* 16F1B8 802408D8 AFA0003C */  sw        $zero, 0x3c($sp)
/* 16F1BC 802408DC AFA00040 */  sw        $zero, 0x40($sp)
/* 16F1C0 802408E0 AFA20048 */  sw        $v0, 0x48($sp)
/* 16F1C4 802408E4 0C03D4B8 */  jal       draw_box
/* 16F1C8 802408E8 AFA0004C */   sw       $zero, 0x4c($sp)
.L802408EC:
/* 16F1CC 802408EC 8FAC0050 */  lw        $t4, 0x50($sp)
.L802408F0:
/* 16F1D0 802408F0 19800024 */  blez      $t4, .L80240984
/* 16F1D4 802408F4 0000882D */   daddu    $s1, $zero, $zero
/* 16F1D8 802408F8 3C148008 */  lui       $s4, 0x8008
/* 16F1DC 802408FC 269410C8 */  addiu     $s4, $s4, 0x10c8
/* 16F1E0 80240900 3C014120 */  lui       $at, 0x4120
/* 16F1E4 80240904 4481A000 */  mtc1      $at, $f20
/* 16F1E8 80240908 3C13802A */  lui       $s3, 0x802a
/* 16F1EC 8024090C 2673F010 */  addiu     $s3, $s3, -0xff0
.L80240910:
/* 16F1F0 80240910 8E700000 */  lw        $s0, ($s3)
/* 16F1F4 80240914 0C05122C */  jal       get_menu_icon_script
/* 16F1F8 80240918 0200202D */   daddu    $a0, $s0, $zero
/* 16F1FC 8024091C 10540004 */  beq       $v0, $s4, .L80240930
/* 16F200 80240920 0200202D */   daddu    $a0, $s0, $zero
/* 16F204 80240924 0C0511FF */  jal       set_menu_icon_script
/* 16F208 80240928 0280282D */   daddu    $a1, $s4, $zero
/* 16F20C 8024092C 0200202D */  daddu     $a0, $s0, $zero
.L80240930:
/* 16F210 80240930 0C05128B */  jal       clear_icon_flags
/* 16F214 80240934 24050002 */   addiu    $a1, $zero, 2
/* 16F218 80240938 0200202D */  daddu     $a0, $s0, $zero
/* 16F21C 8024093C 0240282D */  daddu     $a1, $s2, $zero
/* 16F220 80240940 0C051261 */  jal       set_icon_render_pos
/* 16F224 80240944 02A0302D */   daddu    $a2, $s5, $zero
/* 16F228 80240948 0C0511EA */  jal       draw_icon_0
/* 16F22C 8024094C 0200202D */   daddu    $a0, $s0, $zero
/* 16F230 80240950 4614B082 */  mul.s     $f2, $f22, $f20
/* 16F234 80240954 00000000 */  nop       
/* 16F238 80240958 44920000 */  mtc1      $s2, $f0
/* 16F23C 8024095C 00000000 */  nop       
/* 16F240 80240960 46800020 */  cvt.s.w   $f0, $f0
/* 16F244 80240964 46020001 */  sub.s     $f0, $f0, $f2
/* 16F248 80240968 4600018D */  trunc.w.s $f6, $f0
/* 16F24C 8024096C 44123000 */  mfc1      $s2, $f6
/* 16F250 80240970 8FAC0050 */  lw        $t4, 0x50($sp)
/* 16F254 80240974 26310001 */  addiu     $s1, $s1, 1
/* 16F258 80240978 022C102A */  slt       $v0, $s1, $t4
/* 16F25C 8024097C 1440FFE4 */  bnez      $v0, .L80240910
/* 16F260 80240980 26730004 */   addiu    $s3, $s3, 4
.L80240984:
/* 16F264 80240984 2A22000A */  slti      $v0, $s1, 0xa
/* 16F268 80240988 1040000C */  beqz      $v0, .L802409BC
/* 16F26C 8024098C 00111080 */   sll      $v0, $s1, 2
/* 16F270 80240990 3C03802A */  lui       $v1, 0x802a
/* 16F274 80240994 2463F010 */  addiu     $v1, $v1, -0xff0
/* 16F278 80240998 00438021 */  addu      $s0, $v0, $v1
.L8024099C:
/* 16F27C 8024099C 8E040000 */  lw        $a0, ($s0)
/* 16F280 802409A0 24050002 */  addiu     $a1, $zero, 2
/* 16F284 802409A4 26100004 */  addiu     $s0, $s0, 4
/* 16F288 802409A8 0C051280 */  jal       set_icon_flags
/* 16F28C 802409AC 26310001 */   addiu    $s1, $s1, 1
/* 16F290 802409B0 2A22000A */  slti      $v0, $s1, 0xa
/* 16F294 802409B4 1440FFF9 */  bnez      $v0, .L8024099C
/* 16F298 802409B8 00000000 */   nop      
.L802409BC:
/* 16F29C 802409BC 8FBF007C */  lw        $ra, 0x7c($sp)
/* 16F2A0 802409C0 8FBE0078 */  lw        $fp, 0x78($sp)
/* 16F2A4 802409C4 8FB70074 */  lw        $s7, 0x74($sp)
/* 16F2A8 802409C8 8FB60070 */  lw        $s6, 0x70($sp)
/* 16F2AC 802409CC 8FB5006C */  lw        $s5, 0x6c($sp)
/* 16F2B0 802409D0 8FB40068 */  lw        $s4, 0x68($sp)
/* 16F2B4 802409D4 8FB30064 */  lw        $s3, 0x64($sp)
/* 16F2B8 802409D8 8FB20060 */  lw        $s2, 0x60($sp)
/* 16F2BC 802409DC 8FB1005C */  lw        $s1, 0x5c($sp)
/* 16F2C0 802409E0 8FB00058 */  lw        $s0, 0x58($sp)
/* 16F2C4 802409E4 D7B60088 */  ldc1      $f22, 0x88($sp)
/* 16F2C8 802409E8 D7B40080 */  ldc1      $f20, 0x80($sp)
/* 16F2CC 802409EC 03E00008 */  jr        $ra
/* 16F2D0 802409F0 27BD0090 */   addiu    $sp, $sp, 0x90
