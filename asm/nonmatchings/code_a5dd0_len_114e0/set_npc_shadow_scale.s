.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel set_npc_shadow_scale
/* A9000 80112900 3C028007 */  lui       $v0, %hi(gGameStatusPtr)
/* A9004 80112904 8C42419C */  lw        $v0, %lo(gGameStatusPtr)($v0)
/* A9008 80112908 44851000 */  mtc1      $a1, $f2
/* A900C 8011290C 80420070 */  lb        $v0, 0x70($v0)
/* A9010 80112910 44862000 */  mtc1      $a2, $f4
/* A9014 80112914 1440000A */  bnez      $v0, .L80112940
/* A9018 80112918 00000000 */   nop      
/* A901C 8011291C 3C014522 */  lui       $at, 0x4522
/* A9020 80112920 34218000 */  ori       $at, $at, 0x8000
/* A9024 80112924 44810000 */  mtc1      $at, $f0
/* A9028 80112928 00000000 */  nop       
/* A902C 8011292C 46001003 */  div.s     $f0, $f2, $f0
/* A9030 80112930 3C018015 */  lui       $at, 0x8015
/* A9034 80112934 D422F968 */  ldc1      $f2, -0x698($at)
/* A9038 80112938 08044A57 */  j         .L8011295C
/* A903C 8011293C 46000021 */   cvt.d.s  $f0, $f0
.L80112940:
/* A9040 80112940 3C014561 */  lui       $at, 0x4561
/* A9044 80112944 44810000 */  mtc1      $at, $f0
/* A9048 80112948 00000000 */  nop       
/* A904C 8011294C 46001003 */  div.s     $f0, $f2, $f0
/* A9050 80112950 3C018015 */  lui       $at, 0x8015
/* A9054 80112954 D422F970 */  ldc1      $f2, -0x690($at)
/* A9058 80112958 46000021 */  cvt.d.s   $f0, $f0
.L8011295C:
/* A905C 8011295C 46201081 */  sub.d     $f2, $f2, $f0
/* A9060 80112960 462010A0 */  cvt.s.d   $f2, $f2
/* A9064 80112964 E482001C */  swc1      $f2, 0x1c($a0)
/* A9068 80112968 C480001C */  lwc1      $f0, 0x1c($a0)
/* A906C 8011296C 3C018015 */  lui       $at, 0x8015
/* A9070 80112970 D422F978 */  ldc1      $f2, -0x688($at)
/* A9074 80112974 46000021 */  cvt.d.s   $f0, $f0
/* A9078 80112978 4622003C */  c.lt.d    $f0, $f2
/* A907C 8011297C 00000000 */  nop       
/* A9080 80112980 45000006 */  bc1f      .L8011299C
/* A9084 80112984 00000000 */   nop      
/* A9088 80112988 3C013C23 */  lui       $at, 0x3c23
/* A908C 8011298C 3421D70A */  ori       $at, $at, 0xd70a
/* A9090 80112990 44810000 */  mtc1      $at, $f0
/* A9094 80112994 00000000 */  nop       
/* A9098 80112998 E480001C */  swc1      $f0, 0x1c($a0)
.L8011299C:
/* A909C 8011299C 3C014270 */  lui       $at, 0x4270
/* A90A0 801129A0 44810000 */  mtc1      $at, $f0
/* A90A4 801129A4 00000000 */  nop       
/* A90A8 801129A8 4604003C */  c.lt.s    $f0, $f4
/* A90AC 801129AC 00000000 */  nop       
/* A90B0 801129B0 45000005 */  bc1f      .L801129C8
/* A90B4 801129B4 00000000 */   nop      
/* A90B8 801129B8 C480001C */  lwc1      $f0, 0x1c($a0)
/* A90BC 801129BC 46000000 */  add.s     $f0, $f0, $f0
/* A90C0 801129C0 03E00008 */  jr        $ra
/* A90C4 801129C4 E4800024 */   swc1     $f0, 0x24($a0)
.L801129C8:
/* A90C8 801129C8 C480001C */  lwc1      $f0, 0x1c($a0)
/* A90CC 801129CC 03E00008 */  jr        $ra
/* A90D0 801129D0 E4800024 */   swc1     $f0, 0x24($a0)
