.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80057C54
/* 33054 80057C54 27BDFFE8 */  addiu     $sp, $sp, -0x18
/* 33058 80057C58 308400FF */  andi      $a0, $a0, 0xff
/* 3305C 80057C5C 00041140 */  sll       $v0, $a0, 5
/* 33060 80057C60 3C038008 */  lui       $v1, 0x8008
/* 33064 80057C64 8C638E54 */  lw        $v1, -0x71ac($v1)
/* 33068 80057C68 00441023 */  subu      $v0, $v0, $a0
/* 3306C 80057C6C AFBF0010 */  sw        $ra, 0x10($sp)
/* 33070 80057C70 8C63001C */  lw        $v1, 0x1c($v1)
/* 33074 80057C74 00021080 */  sll       $v0, $v0, 2
/* 33078 80057C78 00621821 */  addu      $v1, $v1, $v0
/* 3307C 80057C7C 8C650064 */  lw        $a1, 0x64($v1)
/* 33080 80057C80 8C620068 */  lw        $v0, 0x68($v1)
/* 33084 80057C84 00A2102A */  slt       $v0, $a1, $v0
/* 33088 80057C88 14400017 */  bnez      $v0, .L80057CE8
/* 3308C 80057C8C 00000000 */   nop      
/* 33090 80057C90 3C028008 */  lui       $v0, 0x8008
/* 33094 80057C94 24428181 */  addiu     $v0, $v0, -0x7e7f
/* 33098 80057C98 90420000 */  lbu       $v0, ($v0)
/* 3309C 80057C9C 14400008 */  bnez      $v0, .L80057CC0
/* 330A0 80057CA0 00000000 */   nop      
/* 330A4 80057CA4 8463004E */  lh        $v1, 0x4e($v1)
/* 330A8 80057CA8 3C028008 */  lui       $v0, 0x8008
/* 330AC 80057CAC 84428EE0 */  lh        $v0, -0x7120($v0)
/* 330B0 80057CB0 00620018 */  mult      $v1, $v0
/* 330B4 80057CB4 00004012 */  mflo      $t0
/* 330B8 80057CB8 08015F3F */  j         .L80057CFC
/* 330BC 80057CBC 00081040 */   sll      $v0, $t0, 1
.L80057CC0:
/* 330C0 80057CC0 8462004C */  lh        $v0, 0x4c($v1)
/* 330C4 80057CC4 8463004E */  lh        $v1, 0x4e($v1)
/* 330C8 80057CC8 00021040 */  sll       $v0, $v0, 1
/* 330CC 80057CCC 3C018008 */  lui       $at, 0x8008
/* 330D0 80057CD0 00220821 */  addu      $at, $at, $v0
/* 330D4 80057CD4 84228E60 */  lh        $v0, -0x71a0($at)
/* 330D8 80057CD8 00620018 */  mult      $v1, $v0
/* 330DC 80057CDC 00004012 */  mflo      $t0
/* 330E0 80057CE0 08015F3F */  j         .L80057CFC
/* 330E4 80057CE4 00081040 */   sll      $v0, $t0, 1
.L80057CE8:
/* 330E8 80057CE8 84640050 */  lh        $a0, 0x50($v1)
/* 330EC 80057CEC 8466005A */  lh        $a2, 0x5a($v1)
/* 330F0 80057CF0 0C016001 */  jal       func_80058004
/* 330F4 80057CF4 94670058 */   lhu      $a3, 0x58($v1)
/* 330F8 80057CF8 00021400 */  sll       $v0, $v0, 0x10
.L80057CFC:
/* 330FC 80057CFC 00021403 */  sra       $v0, $v0, 0x10
/* 33100 80057D00 8FBF0010 */  lw        $ra, 0x10($sp)
/* 33104 80057D04 03E00008 */  jr        $ra
/* 33108 80057D08 27BD0018 */   addiu    $sp, $sp, 0x18
