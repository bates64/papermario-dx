.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel _heap_free
/* 461C 8002921C 14A00003 */  bnez      $a1, .L8002922C
/* 4620 80029220 00000000 */   nop      
.L80029224:
/* 4624 80029224 03E00008 */  jr        $ra
/* 4628 80029228 24020001 */   addiu    $v0, $zero, 1
.L8002922C:
/* 462C 8002922C 94A2FFF8 */  lhu       $v0, -8($a1)
/* 4630 80029230 1040FFFC */  beqz      $v0, .L80029224
/* 4634 80029234 24A6FFF0 */   addiu    $a2, $a1, -0x10
/* 4638 80029238 8CA7FFF0 */  lw        $a3, -0x10($a1)
/* 463C 8002923C 8CA5FFF4 */  lw        $a1, -0xc($a1)
/* 4640 80029240 00E0182D */  daddu     $v1, $a3, $zero
/* 4644 80029244 50600009 */  beql      $v1, $zero, .L8002926C
/* 4648 80029248 0080182D */   daddu    $v1, $a0, $zero
/* 464C 8002924C 94620008 */  lhu       $v0, 8($v1)
/* 4650 80029250 54400006 */  bnel      $v0, $zero, .L8002926C
/* 4654 80029254 0080182D */   daddu    $v1, $a0, $zero
/* 4658 80029258 8C670000 */  lw        $a3, ($v1)
/* 465C 8002925C 8C630004 */  lw        $v1, 4($v1)
/* 4660 80029260 24A20010 */  addiu     $v0, $a1, 0x10
/* 4664 80029264 00432821 */  addu      $a1, $v0, $v1
/* 4668 80029268 0080182D */  daddu     $v1, $a0, $zero
.L8002926C:
/* 466C 8002926C 8C640000 */  lw        $a0, ($v1)
/* 4670 80029270 10860007 */  beq       $a0, $a2, .L80029290
/* 4674 80029274 00C3102B */   sltu     $v0, $a2, $v1
/* 4678 80029278 1440000D */  bnez      $v0, .L800292B0
/* 467C 8002927C 00C0182D */   daddu    $v1, $a2, $zero
/* 4680 80029280 1080000A */  beqz      $a0, .L800292AC
/* 4684 80029284 0080182D */   daddu    $v1, $a0, $zero
/* 4688 80029288 0800A49B */  j         .L8002926C
/* 468C 8002928C 00000000 */   nop      
.L80029290:
/* 4690 80029290 94620008 */  lhu       $v0, 8($v1)
/* 4694 80029294 54400006 */  bnel      $v0, $zero, .L800292B0
/* 4698 80029298 00C0182D */   daddu    $v1, $a2, $zero
/* 469C 8002929C 0060302D */  daddu     $a2, $v1, $zero
/* 46A0 800292A0 8CC30004 */  lw        $v1, 4($a2)
/* 46A4 800292A4 24A20010 */  addiu     $v0, $a1, 0x10
/* 46A8 800292A8 00432821 */  addu      $a1, $v0, $v1
.L800292AC:
/* 46AC 800292AC 00C0182D */  daddu     $v1, $a2, $zero
.L800292B0:
/* 46B0 800292B0 0000102D */  daddu     $v0, $zero, $zero
/* 46B4 800292B4 AC670000 */  sw        $a3, ($v1)
/* 46B8 800292B8 AC650004 */  sw        $a1, 4($v1)
/* 46BC 800292BC 03E00008 */  jr        $ra
/* 46C0 800292C0 A4600008 */   sh       $zero, 8($v1)
