.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_8005BB34
/* 36F34 8005BB34 27BDFFC0 */  addiu     $sp, $sp, -0x40
/* 36F38 8005BB38 F7BE0038 */  sdc1      $f30, 0x38($sp)
/* 36F3C 8005BB3C F7BC0030 */  sdc1      $f28, 0x30($sp)
/* 36F40 8005BB40 F7BA0028 */  sdc1      $f26, 0x28($sp)
/* 36F44 8005BB44 F7B80020 */  sdc1      $f24, 0x20($sp)
/* 36F48 8005BB48 F7B60018 */  sdc1      $f22, 0x18($sp)
/* 36F4C 8005BB4C F7B40010 */  sdc1      $f20, 0x10($sp)
/* 36F50 8005BB50 C4800030 */  lwc1      $f0, 0x30($a0)
/* 36F54 8005BB54 44801000 */  mtc1      $zero, $f2
/* 36F58 8005BB58 00000000 */  nop
/* 36F5C 8005BB5C 46020032 */  c.eq.s    $f0, $f2
/* 36F60 8005BB60 00000000 */  nop
/* 36F64 8005BB64 4500000B */  bc1f      .L8005BB94
/* 36F68 8005BB68 00000000 */   nop
/* 36F6C 8005BB6C C4800034 */  lwc1      $f0, 0x34($a0)
/* 36F70 8005BB70 46020032 */  c.eq.s    $f0, $f2
/* 36F74 8005BB74 00000000 */  nop
/* 36F78 8005BB78 45000006 */  bc1f      .L8005BB94
/* 36F7C 8005BB7C 00000000 */   nop
/* 36F80 8005BB80 C4800038 */  lwc1      $f0, 0x38($a0)
/* 36F84 8005BB84 46020032 */  c.eq.s    $f0, $f2
/* 36F88 8005BB88 00000000 */  nop
/* 36F8C 8005BB8C 45010167 */  bc1t      .L8005C12C
/* 36F90 8005BB90 0000102D */   daddu    $v0, $zero, $zero
.L8005BB94:
/* 36F94 8005BB94 8C820000 */  lw        $v0, ($a0)
/* 36F98 8005BB98 3C01800A */  lui       $at, %hi(D_800A2040)
/* 36F9C 8005BB9C C43A2040 */  lwc1      $f26, %lo(D_800A2040)($at)
/* 36FA0 8005BBA0 C4400000 */  lwc1      $f0, ($v0)
/* 36FA4 8005BBA4 4600D001 */  sub.s     $f0, $f26, $f0
/* 36FA8 8005BBA8 E7A00008 */  swc1      $f0, 8($sp)
/* 36FAC 8005BBAC C48A0030 */  lwc1      $f10, 0x30($a0)
/* 36FB0 8005BBB0 46005082 */  mul.s     $f2, $f10, $f0
/* 36FB4 8005BBB4 00000000 */  nop
/* 36FB8 8005BBB8 3C01800A */  lui       $at, %hi(D_800A2044)
/* 36FBC 8005BBBC C43C2044 */  lwc1      $f28, %lo(D_800A2044)($at)
/* 36FC0 8005BBC0 C4400004 */  lwc1      $f0, 4($v0)
/* 36FC4 8005BBC4 4600E601 */  sub.s     $f24, $f28, $f0
/* 36FC8 8005BBC8 C4880034 */  lwc1      $f8, 0x34($a0)
/* 36FCC 8005BBCC 3C01800A */  lui       $at, %hi(D_800A2048)
/* 36FD0 8005BBD0 C4322048 */  lwc1      $f18, %lo(D_800A2048)($at)
/* 36FD4 8005BBD4 46184102 */  mul.s     $f4, $f8, $f24
/* 36FD8 8005BBD8 00000000 */  nop
/* 36FDC 8005BBDC E7B20000 */  swc1      $f18, ($sp)
/* 36FE0 8005BBE0 C4400008 */  lwc1      $f0, 8($v0)
/* 36FE4 8005BBE4 46009581 */  sub.s     $f22, $f18, $f0
/* 36FE8 8005BBE8 C4860038 */  lwc1      $f6, 0x38($a0)
/* 36FEC 8005BBEC 46163002 */  mul.s     $f0, $f6, $f22
/* 36FF0 8005BBF0 00000000 */  nop
/* 36FF4 8005BBF4 8C830004 */  lw        $v1, 4($a0)
/* 36FF8 8005BBF8 46041080 */  add.s     $f2, $f2, $f4
/* 36FFC 8005BBFC 8C850008 */  lw        $a1, 8($a0)
/* 37000 8005BC00 8482003C */  lh        $v0, 0x3c($a0)
/* 37004 8005BC04 1040007E */  beqz      $v0, .L8005BE00
/* 37008 8005BC08 46001500 */   add.s    $f20, $f2, $f0
/* 3700C 8005BC0C 4480F000 */  mtc1      $zero, $f30
/* 37010 8005BC10 00000000 */  nop
/* 37014 8005BC14 461EA03C */  c.lt.s    $f20, $f30
/* 37018 8005BC18 00000000 */  nop
/* 3701C 8005BC1C 45030143 */  bc1tl     .L8005C12C
/* 37020 8005BC20 0000102D */   daddu    $v0, $zero, $zero
/* 37024 8005BC24 3C01800A */  lui       $at, %hi(D_800A204C)
/* 37028 8005BC28 C430204C */  lwc1      $f16, %lo(D_800A204C)($at)
/* 3702C 8005BC2C 46105002 */  mul.s     $f0, $f10, $f16
/* 37030 8005BC30 00000000 */  nop
/* 37034 8005BC34 3C01800A */  lui       $at, %hi(D_800A2050)
/* 37038 8005BC38 C42E2050 */  lwc1      $f14, %lo(D_800A2050)($at)
/* 3703C 8005BC3C 460E4102 */  mul.s     $f4, $f8, $f14
/* 37040 8005BC40 00000000 */  nop
/* 37044 8005BC44 3C01800A */  lui       $at, %hi(D_800A2054)
/* 37048 8005BC48 C42C2054 */  lwc1      $f12, %lo(D_800A2054)($at)
/* 3704C 8005BC4C 460C3082 */  mul.s     $f2, $f6, $f12
/* 37050 8005BC50 00000000 */  nop
/* 37054 8005BC54 46040000 */  add.s     $f0, $f0, $f4
/* 37058 8005BC58 46020000 */  add.s     $f0, $f0, $f2
/* 3705C 8005BC5C 4600F03E */  c.le.s    $f30, $f0
/* 37060 8005BC60 00000000 */  nop
/* 37064 8005BC64 45010131 */  bc1t      .L8005C12C
/* 37068 8005BC68 0000102D */   daddu    $v0, $zero, $zero
/* 3706C 8005BC6C C4880014 */  lwc1      $f8, 0x14($a0)
/* 37070 8005BC70 460E4102 */  mul.s     $f4, $f8, $f14
/* 37074 8005BC74 00000000 */  nop
/* 37078 8005BC78 C4820010 */  lwc1      $f2, 0x10($a0)
/* 3707C 8005BC7C 460C1002 */  mul.s     $f0, $f2, $f12
/* 37080 8005BC80 00000000 */  nop
/* 37084 8005BC84 46104202 */  mul.s     $f8, $f8, $f16
/* 37088 8005BC88 00000000 */  nop
/* 3708C 8005BC8C 46101082 */  mul.s     $f2, $f2, $f16
/* 37090 8005BC90 00000000 */  nop
/* 37094 8005BC94 46002101 */  sub.s     $f4, $f4, $f0
/* 37098 8005BC98 C486000C */  lwc1      $f6, 0xc($a0)
/* 3709C 8005BC9C 460C3002 */  mul.s     $f0, $f6, $f12
/* 370A0 8005BCA0 00000000 */  nop
/* 370A4 8005BCA4 460E3182 */  mul.s     $f6, $f6, $f14
/* 370A8 8005BCA8 00000000 */  nop
/* 370AC 8005BCAC C7B20008 */  lwc1      $f18, 8($sp)
/* 370B0 8005BCB0 46049102 */  mul.s     $f4, $f18, $f4
/* 370B4 8005BCB4 00000000 */  nop
/* 370B8 8005BCB8 46080001 */  sub.s     $f0, $f0, $f8
/* 370BC 8005BCBC 4600C002 */  mul.s     $f0, $f24, $f0
/* 370C0 8005BCC0 00000000 */  nop
/* 370C4 8005BCC4 46061081 */  sub.s     $f2, $f2, $f6
/* 370C8 8005BCC8 4602B082 */  mul.s     $f2, $f22, $f2
/* 370CC 8005BCCC 00000000 */  nop
/* 370D0 8005BCD0 46002100 */  add.s     $f4, $f4, $f0
/* 370D4 8005BCD4 46022100 */  add.s     $f4, $f4, $f2
/* 370D8 8005BCD8 461E203C */  c.lt.s    $f4, $f30
/* 370DC 8005BCDC 00000000 */  nop
/* 370E0 8005BCE0 45010112 */  bc1t      .L8005C12C
/* 370E4 8005BCE4 00000000 */   nop
/* 370E8 8005BCE8 C48A0020 */  lwc1      $f10, 0x20($a0)
/* 370EC 8005BCEC 460E5002 */  mul.s     $f0, $f10, $f14
/* 370F0 8005BCF0 00000000 */  nop
/* 370F4 8005BCF4 C488001C */  lwc1      $f8, 0x1c($a0)
/* 370F8 8005BCF8 460C4102 */  mul.s     $f4, $f8, $f12
/* 370FC 8005BCFC 00000000 */  nop
/* 37100 8005BD00 46105282 */  mul.s     $f10, $f10, $f16
/* 37104 8005BD04 00000000 */  nop
/* 37108 8005BD08 46104202 */  mul.s     $f8, $f8, $f16
/* 3710C 8005BD0C 00000000 */  nop
/* 37110 8005BD10 C4620000 */  lwc1      $f2, ($v1)
/* 37114 8005BD14 4602D081 */  sub.s     $f2, $f26, $f2
/* 37118 8005BD18 46040001 */  sub.s     $f0, $f0, $f4
/* 3711C 8005BD1C 46001082 */  mul.s     $f2, $f2, $f0
/* 37120 8005BD20 00000000 */  nop
/* 37124 8005BD24 C4860018 */  lwc1      $f6, 0x18($a0)
/* 37128 8005BD28 460C3002 */  mul.s     $f0, $f6, $f12
/* 3712C 8005BD2C 00000000 */  nop
/* 37130 8005BD30 460E3182 */  mul.s     $f6, $f6, $f14
/* 37134 8005BD34 00000000 */  nop
/* 37138 8005BD38 C4640004 */  lwc1      $f4, 4($v1)
/* 3713C 8005BD3C 4604E101 */  sub.s     $f4, $f28, $f4
/* 37140 8005BD40 460A0001 */  sub.s     $f0, $f0, $f10
/* 37144 8005BD44 46002102 */  mul.s     $f4, $f4, $f0
/* 37148 8005BD48 00000000 */  nop
/* 3714C 8005BD4C C7B20000 */  lwc1      $f18, ($sp)
/* 37150 8005BD50 46064201 */  sub.s     $f8, $f8, $f6
/* 37154 8005BD54 C4600008 */  lwc1      $f0, 8($v1)
/* 37158 8005BD58 46009001 */  sub.s     $f0, $f18, $f0
/* 3715C 8005BD5C 46080002 */  mul.s     $f0, $f0, $f8
/* 37160 8005BD60 00000000 */  nop
/* 37164 8005BD64 46041080 */  add.s     $f2, $f2, $f4
/* 37168 8005BD68 46001080 */  add.s     $f2, $f2, $f0
/* 3716C 8005BD6C 461E103C */  c.lt.s    $f2, $f30
/* 37170 8005BD70 00000000 */  nop
/* 37174 8005BD74 450100ED */  bc1t      .L8005C12C
/* 37178 8005BD78 00000000 */   nop
/* 3717C 8005BD7C C48A002C */  lwc1      $f10, 0x2c($a0)
/* 37180 8005BD80 460E5002 */  mul.s     $f0, $f10, $f14
/* 37184 8005BD84 00000000 */  nop
/* 37188 8005BD88 C4880028 */  lwc1      $f8, 0x28($a0)
/* 3718C 8005BD8C 460C4102 */  mul.s     $f4, $f8, $f12
/* 37190 8005BD90 00000000 */  nop
/* 37194 8005BD94 46105282 */  mul.s     $f10, $f10, $f16
/* 37198 8005BD98 00000000 */  nop
/* 3719C 8005BD9C 46104202 */  mul.s     $f8, $f8, $f16
/* 371A0 8005BDA0 00000000 */  nop
/* 371A4 8005BDA4 C4A20000 */  lwc1      $f2, ($a1)
/* 371A8 8005BDA8 4602D081 */  sub.s     $f2, $f26, $f2
/* 371AC 8005BDAC 46040001 */  sub.s     $f0, $f0, $f4
/* 371B0 8005BDB0 46001082 */  mul.s     $f2, $f2, $f0
/* 371B4 8005BDB4 00000000 */  nop
/* 371B8 8005BDB8 C4860024 */  lwc1      $f6, 0x24($a0)
/* 371BC 8005BDBC 460C3002 */  mul.s     $f0, $f6, $f12
/* 371C0 8005BDC0 00000000 */  nop
/* 371C4 8005BDC4 460E3182 */  mul.s     $f6, $f6, $f14
/* 371C8 8005BDC8 00000000 */  nop
/* 371CC 8005BDCC C4A40004 */  lwc1      $f4, 4($a1)
/* 371D0 8005BDD0 4604E101 */  sub.s     $f4, $f28, $f4
/* 371D4 8005BDD4 460A0001 */  sub.s     $f0, $f0, $f10
/* 371D8 8005BDD8 46002102 */  mul.s     $f4, $f4, $f0
/* 371DC 8005BDDC 00000000 */  nop
/* 371E0 8005BDE0 46064201 */  sub.s     $f8, $f8, $f6
/* 371E4 8005BDE4 C4A00008 */  lwc1      $f0, 8($a1)
/* 371E8 8005BDE8 46009001 */  sub.s     $f0, $f18, $f0
/* 371EC 8005BDEC 46080002 */  mul.s     $f0, $f0, $f8
/* 371F0 8005BDF0 00000000 */  nop
/* 371F4 8005BDF4 46041080 */  add.s     $f2, $f2, $f4
/* 371F8 8005BDF8 08017000 */  j         .L8005C000
/* 371FC 8005BDFC 46001080 */   add.s    $f2, $f2, $f0
.L8005BE00:
/* 37200 8005BE00 3C01800A */  lui       $at, %hi(D_800A204C)
/* 37204 8005BE04 C430204C */  lwc1      $f16, %lo(D_800A204C)($at)
/* 37208 8005BE08 46105002 */  mul.s     $f0, $f10, $f16
/* 3720C 8005BE0C 00000000 */  nop
/* 37210 8005BE10 3C01800A */  lui       $at, %hi(D_800A2050)
/* 37214 8005BE14 C42E2050 */  lwc1      $f14, %lo(D_800A2050)($at)
/* 37218 8005BE18 460E4102 */  mul.s     $f4, $f8, $f14
/* 3721C 8005BE1C 00000000 */  nop
/* 37220 8005BE20 3C01800A */  lui       $at, %hi(D_800A2054)
/* 37224 8005BE24 C42C2054 */  lwc1      $f12, %lo(D_800A2054)($at)
/* 37228 8005BE28 460C3082 */  mul.s     $f2, $f6, $f12
/* 3722C 8005BE2C 00000000 */  nop
/* 37230 8005BE30 46040000 */  add.s     $f0, $f0, $f4
/* 37234 8005BE34 46020000 */  add.s     $f0, $f0, $f2
/* 37238 8005BE38 46140002 */  mul.s     $f0, $f0, $f20
/* 3723C 8005BE3C 00000000 */  nop
/* 37240 8005BE40 4480F000 */  mtc1      $zero, $f30
/* 37244 8005BE44 00000000 */  nop
/* 37248 8005BE48 4600F03E */  c.le.s    $f30, $f0
/* 3724C 8005BE4C 00000000 */  nop
/* 37250 8005BE50 450100B6 */  bc1t      .L8005C12C
/* 37254 8005BE54 0000102D */   daddu    $v0, $zero, $zero
/* 37258 8005BE58 C4880014 */  lwc1      $f8, 0x14($a0)
/* 3725C 8005BE5C 460E4002 */  mul.s     $f0, $f8, $f14
/* 37260 8005BE60 00000000 */  nop
/* 37264 8005BE64 C4840010 */  lwc1      $f4, 0x10($a0)
/* 37268 8005BE68 460C2082 */  mul.s     $f2, $f4, $f12
/* 3726C 8005BE6C 00000000 */  nop
/* 37270 8005BE70 46104202 */  mul.s     $f8, $f8, $f16
/* 37274 8005BE74 00000000 */  nop
/* 37278 8005BE78 46102102 */  mul.s     $f4, $f4, $f16
/* 3727C 8005BE7C 00000000 */  nop
/* 37280 8005BE80 46020001 */  sub.s     $f0, $f0, $f2
/* 37284 8005BE84 C486000C */  lwc1      $f6, 0xc($a0)
/* 37288 8005BE88 460C3082 */  mul.s     $f2, $f6, $f12
/* 3728C 8005BE8C 00000000 */  nop
/* 37290 8005BE90 460E3182 */  mul.s     $f6, $f6, $f14
/* 37294 8005BE94 00000000 */  nop
/* 37298 8005BE98 C7B20008 */  lwc1      $f18, 8($sp)
/* 3729C 8005BE9C 46009002 */  mul.s     $f0, $f18, $f0
/* 372A0 8005BEA0 00000000 */  nop
/* 372A4 8005BEA4 46081081 */  sub.s     $f2, $f2, $f8
/* 372A8 8005BEA8 4602C082 */  mul.s     $f2, $f24, $f2
/* 372AC 8005BEAC 00000000 */  nop
/* 372B0 8005BEB0 46062101 */  sub.s     $f4, $f4, $f6
/* 372B4 8005BEB4 4604B102 */  mul.s     $f4, $f22, $f4
/* 372B8 8005BEB8 00000000 */  nop
/* 372BC 8005BEBC 46020000 */  add.s     $f0, $f0, $f2
/* 372C0 8005BEC0 46040000 */  add.s     $f0, $f0, $f4
/* 372C4 8005BEC4 46140002 */  mul.s     $f0, $f0, $f20
/* 372C8 8005BEC8 00000000 */  nop
/* 372CC 8005BECC 461E003C */  c.lt.s    $f0, $f30
/* 372D0 8005BED0 00000000 */  nop
/* 372D4 8005BED4 45010095 */  bc1t      .L8005C12C
/* 372D8 8005BED8 00000000 */   nop
/* 372DC 8005BEDC C48A0020 */  lwc1      $f10, 0x20($a0)
/* 372E0 8005BEE0 460E5002 */  mul.s     $f0, $f10, $f14
/* 372E4 8005BEE4 00000000 */  nop
/* 372E8 8005BEE8 C488001C */  lwc1      $f8, 0x1c($a0)
/* 372EC 8005BEEC 460C4102 */  mul.s     $f4, $f8, $f12
/* 372F0 8005BEF0 00000000 */  nop
/* 372F4 8005BEF4 46105282 */  mul.s     $f10, $f10, $f16
/* 372F8 8005BEF8 00000000 */  nop
/* 372FC 8005BEFC 46104202 */  mul.s     $f8, $f8, $f16
/* 37300 8005BF00 00000000 */  nop
/* 37304 8005BF04 C4620000 */  lwc1      $f2, ($v1)
/* 37308 8005BF08 4602D081 */  sub.s     $f2, $f26, $f2
/* 3730C 8005BF0C 46040001 */  sub.s     $f0, $f0, $f4
/* 37310 8005BF10 46001082 */  mul.s     $f2, $f2, $f0
/* 37314 8005BF14 00000000 */  nop
/* 37318 8005BF18 C4860018 */  lwc1      $f6, 0x18($a0)
/* 3731C 8005BF1C 460C3002 */  mul.s     $f0, $f6, $f12
/* 37320 8005BF20 00000000 */  nop
/* 37324 8005BF24 460E3182 */  mul.s     $f6, $f6, $f14
/* 37328 8005BF28 00000000 */  nop
/* 3732C 8005BF2C C4640004 */  lwc1      $f4, 4($v1)
/* 37330 8005BF30 4604E101 */  sub.s     $f4, $f28, $f4
/* 37334 8005BF34 460A0001 */  sub.s     $f0, $f0, $f10
/* 37338 8005BF38 46002102 */  mul.s     $f4, $f4, $f0
/* 3733C 8005BF3C 00000000 */  nop
/* 37340 8005BF40 C7B20000 */  lwc1      $f18, ($sp)
/* 37344 8005BF44 46064201 */  sub.s     $f8, $f8, $f6
/* 37348 8005BF48 C4600008 */  lwc1      $f0, 8($v1)
/* 3734C 8005BF4C 46009001 */  sub.s     $f0, $f18, $f0
/* 37350 8005BF50 46080002 */  mul.s     $f0, $f0, $f8
/* 37354 8005BF54 00000000 */  nop
/* 37358 8005BF58 46041080 */  add.s     $f2, $f2, $f4
/* 3735C 8005BF5C 46001080 */  add.s     $f2, $f2, $f0
/* 37360 8005BF60 46141082 */  mul.s     $f2, $f2, $f20
/* 37364 8005BF64 00000000 */  nop
/* 37368 8005BF68 461E103C */  c.lt.s    $f2, $f30
/* 3736C 8005BF6C 00000000 */  nop
/* 37370 8005BF70 4501006E */  bc1t      .L8005C12C
/* 37374 8005BF74 00000000 */   nop
/* 37378 8005BF78 C48A002C */  lwc1      $f10, 0x2c($a0)
/* 3737C 8005BF7C 460E5002 */  mul.s     $f0, $f10, $f14
/* 37380 8005BF80 00000000 */  nop
/* 37384 8005BF84 C4880028 */  lwc1      $f8, 0x28($a0)
/* 37388 8005BF88 460C4102 */  mul.s     $f4, $f8, $f12
/* 3738C 8005BF8C 00000000 */  nop
/* 37390 8005BF90 46105282 */  mul.s     $f10, $f10, $f16
/* 37394 8005BF94 00000000 */  nop
/* 37398 8005BF98 46104202 */  mul.s     $f8, $f8, $f16
/* 3739C 8005BF9C 00000000 */  nop
/* 373A0 8005BFA0 C4A20000 */  lwc1      $f2, ($a1)
/* 373A4 8005BFA4 4602D081 */  sub.s     $f2, $f26, $f2
/* 373A8 8005BFA8 46040001 */  sub.s     $f0, $f0, $f4
/* 373AC 8005BFAC 46001082 */  mul.s     $f2, $f2, $f0
/* 373B0 8005BFB0 00000000 */  nop
/* 373B4 8005BFB4 C4860024 */  lwc1      $f6, 0x24($a0)
/* 373B8 8005BFB8 460C3002 */  mul.s     $f0, $f6, $f12
/* 373BC 8005BFBC 00000000 */  nop
/* 373C0 8005BFC0 460E3182 */  mul.s     $f6, $f6, $f14
/* 373C4 8005BFC4 00000000 */  nop
/* 373C8 8005BFC8 C4A40004 */  lwc1      $f4, 4($a1)
/* 373CC 8005BFCC 4604E101 */  sub.s     $f4, $f28, $f4
/* 373D0 8005BFD0 460A0001 */  sub.s     $f0, $f0, $f10
/* 373D4 8005BFD4 46002102 */  mul.s     $f4, $f4, $f0
/* 373D8 8005BFD8 00000000 */  nop
/* 373DC 8005BFDC 46064201 */  sub.s     $f8, $f8, $f6
/* 373E0 8005BFE0 C4A00008 */  lwc1      $f0, 8($a1)
/* 373E4 8005BFE4 46009001 */  sub.s     $f0, $f18, $f0
/* 373E8 8005BFE8 46080002 */  mul.s     $f0, $f0, $f8
/* 373EC 8005BFEC 00000000 */  nop
/* 373F0 8005BFF0 46041080 */  add.s     $f2, $f2, $f4
/* 373F4 8005BFF4 46001080 */  add.s     $f2, $f2, $f0
/* 373F8 8005BFF8 46141082 */  mul.s     $f2, $f2, $f20
/* 373FC 8005BFFC 00000000 */  nop
.L8005C000:
/* 37400 8005C000 461E103C */  c.lt.s    $f2, $f30
/* 37404 8005C004 00000000 */  nop
/* 37408 8005C008 45030048 */  bc1tl     .L8005C12C
/* 3740C 8005C00C 0000102D */   daddu    $v0, $zero, $zero
/* 37410 8005C010 C4860030 */  lwc1      $f6, 0x30($a0)
/* 37414 8005C014 3C01800A */  lui       $at, %hi(D_800A204C)
/* 37418 8005C018 C420204C */  lwc1      $f0, %lo(D_800A204C)($at)
/* 3741C 8005C01C 46003182 */  mul.s     $f6, $f6, $f0
/* 37420 8005C020 00000000 */  nop
/* 37424 8005C024 C4820034 */  lwc1      $f2, 0x34($a0)
/* 37428 8005C028 3C01800A */  lui       $at, %hi(D_800A2050)
/* 3742C 8005C02C C4202050 */  lwc1      $f0, %lo(D_800A2050)($at)
/* 37430 8005C030 46001082 */  mul.s     $f2, $f2, $f0
/* 37434 8005C034 00000000 */  nop
/* 37438 8005C038 C4840038 */  lwc1      $f4, 0x38($a0)
/* 3743C 8005C03C 3C01800A */  lui       $at, %hi(D_800A2054)
/* 37440 8005C040 C4202054 */  lwc1      $f0, %lo(D_800A2054)($at)
/* 37444 8005C044 46002102 */  mul.s     $f4, $f4, $f0
/* 37448 8005C048 00000000 */  nop
/* 3744C 8005C04C 3C01800A */  lui       $at, %hi(D_800A2064)
/* 37450 8005C050 C4282064 */  lwc1      $f8, %lo(D_800A2064)($at)
/* 37454 8005C054 46023180 */  add.s     $f6, $f6, $f2
/* 37458 8005C058 44800000 */  mtc1      $zero, $f0
/* 3745C 8005C05C 00000000 */  nop
/* 37460 8005C060 4608003E */  c.le.s    $f0, $f8
/* 37464 8005C064 00000000 */  nop
/* 37468 8005C068 45000007 */  bc1f      .L8005C088
/* 3746C 8005C06C 46043180 */   add.s    $f6, $f6, $f4
/* 37470 8005C070 4600A007 */  neg.s     $f0, $f20
/* 37474 8005C074 46060003 */  div.s     $f0, $f0, $f6
/* 37478 8005C078 4600403E */  c.le.s    $f8, $f0
/* 3747C 8005C07C 00000000 */  nop
/* 37480 8005C080 4501002A */  bc1t      .L8005C12C
/* 37484 8005C084 0000102D */   daddu    $v0, $zero, $zero
.L8005C088:
/* 37488 8005C088 4600A007 */  neg.s     $f0, $f20
/* 3748C 8005C08C 3C01800A */  lui       $at, %hi(D_800A204C)
/* 37490 8005C090 C422204C */  lwc1      $f2, %lo(D_800A204C)($at)
/* 37494 8005C094 46060003 */  div.s     $f0, $f0, $f6
/* 37498 8005C098 46001082 */  mul.s     $f2, $f2, $f0
/* 3749C 8005C09C 00000000 */  nop
/* 374A0 8005C0A0 3C01800A */  lui       $at, %hi(D_800A2050)
/* 374A4 8005C0A4 C42A2050 */  lwc1      $f10, %lo(D_800A2050)($at)
/* 374A8 8005C0A8 46005282 */  mul.s     $f10, $f10, $f0
/* 374AC 8005C0AC 00000000 */  nop
/* 374B0 8005C0B0 3C01800A */  lui       $at, %hi(D_800A2040)
/* 374B4 8005C0B4 C42C2040 */  lwc1      $f12, %lo(D_800A2040)($at)
/* 374B8 8005C0B8 3C01800A */  lui       $at, %hi(D_800A2054)
/* 374BC 8005C0BC C4282054 */  lwc1      $f8, %lo(D_800A2054)($at)
/* 374C0 8005C0C0 C4840030 */  lwc1      $f4, 0x30($a0)
/* 374C4 8005C0C4 C4860038 */  lwc1      $f6, 0x38($a0)
/* 374C8 8005C0C8 46004202 */  mul.s     $f8, $f8, $f0
/* 374CC 8005C0CC 00000000 */  nop
/* 374D0 8005C0D0 3C01800A */  lui       $at, %hi(D_800A2064)
/* 374D4 8005C0D4 E4202064 */  swc1      $f0, %lo(D_800A2064)($at)
/* 374D8 8005C0D8 3C01800A */  lui       $at, %hi(D_800A2044)
/* 374DC 8005C0DC C4202044 */  lwc1      $f0, %lo(D_800A2044)($at)
/* 374E0 8005C0E0 24020001 */  addiu     $v0, $zero, 1
/* 374E4 8005C0E4 3C01800A */  lui       $at, %hi(D_800A2068)
/* 374E8 8005C0E8 E4242068 */  swc1      $f4, %lo(D_800A2068)($at)
/* 374EC 8005C0EC 46026300 */  add.s     $f12, $f12, $f2
/* 374F0 8005C0F0 C4840034 */  lwc1      $f4, 0x34($a0)
/* 374F4 8005C0F4 3C01800A */  lui       $at, %hi(D_800A2048)
/* 374F8 8005C0F8 C4222048 */  lwc1      $f2, %lo(D_800A2048)($at)
/* 374FC 8005C0FC 460A0000 */  add.s     $f0, $f0, $f10
/* 37500 8005C100 3C01800A */  lui       $at, %hi(D_800A2070)
/* 37504 8005C104 E4262070 */  swc1      $f6, %lo(D_800A2070)($at)
/* 37508 8005C108 3C01800A */  lui       $at, %hi(D_800A206C)
/* 3750C 8005C10C E424206C */  swc1      $f4, %lo(D_800A206C)($at)
/* 37510 8005C110 46081080 */  add.s     $f2, $f2, $f8
/* 37514 8005C114 3C01800A */  lui       $at, %hi(D_800A2058)
/* 37518 8005C118 E42C2058 */  swc1      $f12, %lo(D_800A2058)($at)
/* 3751C 8005C11C 3C01800A */  lui       $at, %hi(D_800A205C)
/* 37520 8005C120 E420205C */  swc1      $f0, %lo(D_800A205C)($at)
/* 37524 8005C124 3C01800A */  lui       $at, %hi(D_800A2060)
/* 37528 8005C128 E4222060 */  swc1      $f2, %lo(D_800A2060)($at)
.L8005C12C:
/* 3752C 8005C12C D7BE0038 */  ldc1      $f30, 0x38($sp)
/* 37530 8005C130 D7BC0030 */  ldc1      $f28, 0x30($sp)
/* 37534 8005C134 D7BA0028 */  ldc1      $f26, 0x28($sp)
/* 37538 8005C138 D7B80020 */  ldc1      $f24, 0x20($sp)
/* 3753C 8005C13C D7B60018 */  ldc1      $f22, 0x18($sp)
/* 37540 8005C140 D7B40010 */  ldc1      $f20, 0x10($sp)
/* 37544 8005C144 03E00008 */  jr        $ra
/* 37548 8005C148 27BD0040 */   addiu    $sp, $sp, 0x40