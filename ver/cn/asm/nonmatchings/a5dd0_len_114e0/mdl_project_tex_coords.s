.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Generated by spimdisasm 1.11.1 */

glabel mdl_project_tex_coords
/* B15EC 8011A70C 27BDFF68 */  addiu     $sp, $sp, -0x98
/* B15F0 8011A710 AFB40058 */  sw        $s4, 0x58($sp)
/* B15F4 8011A714 00A0A02D */  daddu     $s4, $a1, $zero
/* B15F8 8011A718 AFB00048 */  sw        $s0, 0x48($sp)
/* B15FC 8011A71C 00C0802D */  daddu     $s0, $a2, $zero
/* B1600 8011A720 AFB5005C */  sw        $s5, 0x5C($sp)
/* B1604 8011A724 00E0A82D */  daddu     $s5, $a3, $zero
/* B1608 8011A728 AFBF0060 */  sw        $ra, 0x60($sp)
/* B160C 8011A72C AFB30054 */  sw        $s3, 0x54($sp)
/* B1610 8011A730 AFB20050 */  sw        $s2, 0x50($sp)
/* B1614 8011A734 AFB1004C */  sw        $s1, 0x4C($sp)
/* B1618 8011A738 F7BE0090 */  sdc1      $f30, 0x90($sp)
/* B161C 8011A73C F7BC0088 */  sdc1      $f28, 0x88($sp)
/* B1620 8011A740 F7BA0080 */  sdc1      $f26, 0x80($sp)
/* B1624 8011A744 F7B80078 */  sdc1      $f24, 0x78($sp)
/* B1628 8011A748 F7B60070 */  sdc1      $f22, 0x70($sp)
/* B162C 8011A74C F7B40068 */  sdc1      $f20, 0x68($sp)
/* B1630 8011A750 0C0464FC */  jal       get_model_list_index_from_tree_index
/* B1634 8011A754 3084FFFF */   andi     $a0, $a0, 0xFFFF
/* B1638 8011A758 0C046444 */  jal       get_model_from_list_index
/* B163C 8011A75C 0040202D */   daddu    $a0, $v0, $zero
/* B1640 8011A760 8C420008 */  lw        $v0, 0x8($v0)
/* B1644 8011A764 240600DF */  addiu     $a2, $zero, 0xDF
/* B1648 8011A768 8C420004 */  lw        $v0, 0x4($v0)
/* B164C 8011A76C 24050001 */  addiu     $a1, $zero, 0x1
/* B1650 8011A770 8C420000 */  lw        $v0, 0x0($v0)
.LIQUE_8011A774:
/* B1654 8011A774 90430000 */  lbu       $v1, 0x0($v0)
/* B1658 8011A778 10660004 */  beq       $v1, $a2, .LIQUE_8011A78C
/* B165C 8011A77C 8C440004 */   lw       $a0, 0x4($v0)
/* B1660 8011A780 1465FFFC */  bne       $v1, $a1, .LIQUE_8011A774
/* B1664 8011A784 24420008 */   addiu    $v0, $v0, 0x8
/* B1668 8011A788 AFA4001C */  sw        $a0, 0x1C($sp)
.LIQUE_8011A78C:
/* B166C 8011A78C 8FA2001C */  lw        $v0, 0x1C($sp)
/* B1670 8011A790 84430000 */  lh        $v1, 0x0($v0)
/* B1674 8011A794 84440010 */  lh        $a0, 0x10($v0)
/* B1678 8011A798 44838000 */  mtc1      $v1, $f16
/* B167C 8011A79C 00000000 */  nop
/* B1680 8011A7A0 46808420 */  cvt.s.w   $f16, $f16
/* B1684 8011A7A4 44842000 */  mtc1      $a0, $f4
/* B1688 8011A7A8 00000000 */  nop
/* B168C 8011A7AC 46802120 */  cvt.s.w   $f4, $f4
/* B1690 8011A7B0 46048032 */  c.eq.s    $f16, $f4
/* B1694 8011A7B4 84430004 */  lh        $v1, 0x4($v0)
/* B1698 8011A7B8 84440008 */  lh        $a0, 0x8($v0)
/* B169C 8011A7BC 44839000 */  mtc1      $v1, $f18
/* B16A0 8011A7C0 00000000 */  nop
/* B16A4 8011A7C4 468094A0 */  cvt.s.w   $f18, $f18
/* B16A8 8011A7C8 4484A000 */  mtc1      $a0, $f20
/* B16AC 8011A7CC 00000000 */  nop
/* B16B0 8011A7D0 4680A520 */  cvt.s.w   $f20, $f20
/* B16B4 8011A7D4 8443000A */  lh        $v1, 0xA($v0)
/* B16B8 8011A7D8 84440014 */  lh        $a0, 0x14($v0)
/* B16BC 8011A7DC 4483B000 */  mtc1      $v1, $f22
/* B16C0 8011A7E0 00000000 */  nop
/* B16C4 8011A7E4 4680B5A0 */  cvt.s.w   $f22, $f22
/* B16C8 8011A7E8 44845000 */  mtc1      $a0, $f10
/* B16CC 8011A7EC 00000000 */  nop
/* B16D0 8011A7F0 468052A0 */  cvt.s.w   $f10, $f10
/* B16D4 8011A7F4 E7B60038 */  swc1      $f22, 0x38($sp)
/* B16D8 8011A7F8 84430018 */  lh        $v1, 0x18($v0)
/* B16DC 8011A7FC 8444001A */  lh        $a0, 0x1A($v0)
/* B16E0 8011A800 44830000 */  mtc1      $v1, $f0
/* B16E4 8011A804 00000000 */  nop
/* B16E8 8011A808 46800020 */  cvt.s.w   $f0, $f0
/* B16EC 8011A80C 4484E000 */  mtc1      $a0, $f28
/* B16F0 8011A810 00000000 */  nop
/* B16F4 8011A814 4680E720 */  cvt.s.w   $f28, $f28
/* B16F8 8011A818 E7BC0024 */  swc1      $f28, 0x24($sp)
/* B16FC 8011A81C 84430020 */  lh        $v1, 0x20($v0)
/* B1700 8011A820 84440024 */  lh        $a0, 0x24($v0)
/* B1704 8011A824 4483C000 */  mtc1      $v1, $f24
/* B1708 8011A828 00000000 */  nop
/* B170C 8011A82C 4680C620 */  cvt.s.w   $f24, $f24
/* B1710 8011A830 44843000 */  mtc1      $a0, $f6
/* B1714 8011A834 00000000 */  nop
/* B1718 8011A838 468031A0 */  cvt.s.w   $f6, $f6
/* B171C 8011A83C 84430028 */  lh        $v1, 0x28($v0)
/* B1720 8011A840 8444002A */  lh        $a0, 0x2A($v0)
/* B1724 8011A844 4483D000 */  mtc1      $v1, $f26
/* B1728 8011A848 00000000 */  nop
/* B172C 8011A84C 4680D6A0 */  cvt.s.w   $f26, $f26
/* B1730 8011A850 4484B000 */  mtc1      $a0, $f22
/* B1734 8011A854 00000000 */  nop
/* B1738 8011A858 4680B5A0 */  cvt.s.w   $f22, $f22
/* B173C 8011A85C E7B60028 */  swc1      $f22, 0x28($sp)
/* B1740 8011A860 9053000C */  lbu       $s3, 0xC($v0)
/* B1744 8011A864 9052000D */  lbu       $s2, 0xD($v0)
/* B1748 8011A868 9051000E */  lbu       $s1, 0xE($v0)
/* B174C 8011A86C 4503002E */  bc1tl     .LIQUE_8011A928
/* B1750 8011A870 46069081 */   sub.s    $f2, $f18, $f6
/* B1754 8011A874 46188081 */  sub.s     $f2, $f16, $f24
/* B1758 8011A878 46048381 */  sub.s     $f14, $f16, $f4
/* B175C 8011A87C 4600A201 */  sub.s     $f8, $f20, $f0
/* B1760 8011A880 460E1083 */  div.s     $f2, $f2, $f14
/* B1764 8011A884 46081002 */  mul.s     $f0, $f2, $f8
/* B1768 8011A888 00000000 */  nop
/* B176C 8011A88C 460A9301 */  sub.s     $f12, $f18, $f10
/* B1770 8011A890 460C1282 */  mul.s     $f10, $f2, $f12
/* B1774 8011A894 00000000 */  nop
/* B1778 8011A898 461AA101 */  sub.s     $f4, $f20, $f26
/* B177C 8011A89C 46069181 */  sub.s     $f6, $f18, $f6
/* B1780 8011A8A0 46040001 */  sub.s     $f0, $f0, $f4
/* B1784 8011A8A4 46065281 */  sub.s     $f10, $f10, $f6
/* B1788 8011A8A8 460A0003 */  div.s     $f0, $f0, $f10
/* B178C 8011A8AC E7A00040 */  swc1      $f0, 0x40($sp)
/* B1790 8011A8B0 46006002 */  mul.s     $f0, $f12, $f0
/* B1794 8011A8B4 00000000 */  nop
/* B1798 8011A8B8 C7B60038 */  lwc1      $f22, 0x38($sp)
/* B179C 8011A8BC 461CB101 */  sub.s     $f4, $f22, $f28
/* B17A0 8011A8C0 46041082 */  mul.s     $f2, $f2, $f4
/* B17A4 8011A8C4 00000000 */  nop
/* B17A8 8011A8C8 46004201 */  sub.s     $f8, $f8, $f0
/* B17AC 8011A8CC 460E4783 */  div.s     $f30, $f8, $f14
/* B17B0 8011A8D0 4610F182 */  mul.s     $f6, $f30, $f16
/* B17B4 8011A8D4 00000000 */  nop
/* B17B8 8011A8D8 C7BC0028 */  lwc1      $f28, 0x28($sp)
/* B17BC 8011A8DC 461CB001 */  sub.s     $f0, $f22, $f28
/* B17C0 8011A8E0 C7B60040 */  lwc1      $f22, 0x40($sp)
/* B17C4 8011A8E4 4612B202 */  mul.s     $f8, $f22, $f18
/* B17C8 8011A8E8 00000000 */  nop
/* B17CC 8011A8EC 46001081 */  sub.s     $f2, $f2, $f0
/* B17D0 8011A8F0 460A1683 */  div.s     $f26, $f2, $f10
/* B17D4 8011A8F4 461A6302 */  mul.s     $f12, $f12, $f26
/* B17D8 8011A8F8 00000000 */  nop
/* B17DC 8011A8FC 4612D082 */  mul.s     $f2, $f26, $f18
/* B17E0 8011A900 00000000 */  nop
/* B17E4 8011A904 460C2101 */  sub.s     $f4, $f4, $f12
/* B17E8 8011A908 460E2603 */  div.s     $f24, $f4, $f14
/* B17EC 8011A90C 4610C002 */  mul.s     $f0, $f24, $f16
/* B17F0 8011A910 00000000 */  nop
/* B17F4 8011A914 4606A181 */  sub.s     $f6, $f20, $f6
/* B17F8 8011A918 46083181 */  sub.s     $f6, $f6, $f8
/* B17FC 8011A91C C7BC0038 */  lwc1      $f28, 0x38($sp)
/* B1800 8011A920 08046A74 */  j         .LIQUE_8011A9D0
/* B1804 8011A924 4600E001 */   sub.s    $f0, $f28, $f0
.LIQUE_8011A928:
/* B1808 8011A928 460A9381 */  sub.s     $f14, $f18, $f10
/* B180C 8011A92C 4600A201 */  sub.s     $f8, $f20, $f0
/* B1810 8011A930 460E1083 */  div.s     $f2, $f2, $f14
/* B1814 8011A934 46081002 */  mul.s     $f0, $f2, $f8
/* B1818 8011A938 00000000 */  nop
/* B181C 8011A93C 46048301 */  sub.s     $f12, $f16, $f4
/* B1820 8011A940 460C1282 */  mul.s     $f10, $f2, $f12
/* B1824 8011A944 00000000 */  nop
/* B1828 8011A948 461AA101 */  sub.s     $f4, $f20, $f26
/* B182C 8011A94C 46188181 */  sub.s     $f6, $f16, $f24
/* B1830 8011A950 46040001 */  sub.s     $f0, $f0, $f4
/* B1834 8011A954 46065281 */  sub.s     $f10, $f10, $f6
/* B1838 8011A958 460A0783 */  div.s     $f30, $f0, $f10
/* B183C 8011A95C 461E6002 */  mul.s     $f0, $f12, $f30
/* B1840 8011A960 00000000 */  nop
/* B1844 8011A964 4610F182 */  mul.s     $f6, $f30, $f16
/* B1848 8011A968 00000000 */  nop
/* B184C 8011A96C C7B60038 */  lwc1      $f22, 0x38($sp)
/* B1850 8011A970 C7BC0024 */  lwc1      $f28, 0x24($sp)
/* B1854 8011A974 461CB101 */  sub.s     $f4, $f22, $f28
/* B1858 8011A978 46041082 */  mul.s     $f2, $f2, $f4
/* B185C 8011A97C 00000000 */  nop
/* B1860 8011A980 46004201 */  sub.s     $f8, $f8, $f0
/* B1864 8011A984 460E4203 */  div.s     $f8, $f8, $f14
/* B1868 8011A988 E7A80040 */  swc1      $f8, 0x40($sp)
/* B186C 8011A98C 46124202 */  mul.s     $f8, $f8, $f18
/* B1870 8011A990 00000000 */  nop
/* B1874 8011A994 C7BC0028 */  lwc1      $f28, 0x28($sp)
/* B1878 8011A998 461CB001 */  sub.s     $f0, $f22, $f28
/* B187C 8011A99C 46001081 */  sub.s     $f2, $f2, $f0
/* B1880 8011A9A0 460A1603 */  div.s     $f24, $f2, $f10
/* B1884 8011A9A4 46186302 */  mul.s     $f12, $f12, $f24
/* B1888 8011A9A8 00000000 */  nop
/* B188C 8011A9AC 4610C002 */  mul.s     $f0, $f24, $f16
/* B1890 8011A9B0 00000000 */  nop
/* B1894 8011A9B4 460C2101 */  sub.s     $f4, $f4, $f12
/* B1898 8011A9B8 460E2683 */  div.s     $f26, $f4, $f14
/* B189C 8011A9BC 4612D082 */  mul.s     $f2, $f26, $f18
/* B18A0 8011A9C0 00000000 */  nop
/* B18A4 8011A9C4 4606A181 */  sub.s     $f6, $f20, $f6
/* B18A8 8011A9C8 46083181 */  sub.s     $f6, $f6, $f8
/* B18AC 8011A9CC 4600B001 */  sub.s     $f0, $f22, $f0
.LIQUE_8011A9D0:
/* B18B0 8011A9D0 E7A6002C */  swc1      $f6, 0x2C($sp)
/* B18B4 8011A9D4 46020501 */  sub.s     $f20, $f0, $f2
/* B18B8 8011A9D8 0280202D */  daddu     $a0, $s4, $zero
/* B18BC 8011A9DC 27A50018 */  addiu     $a1, $sp, 0x18
/* B18C0 8011A9E0 27A6001C */  addiu     $a2, $sp, 0x1C
/* B18C4 8011A9E4 27A70020 */  addiu     $a3, $sp, 0x20
/* B18C8 8011A9E8 0C046902 */  jal       mdl_get_vertex_count
/* B18CC 8011A9EC AFB50010 */   sw       $s5, 0x10($sp)
/* B18D0 8011A9F0 8FA20018 */  lw        $v0, 0x18($sp)
/* B18D4 8011A9F4 1840006E */  blez      $v0, .LIQUE_8011ABB0
/* B18D8 8011A9F8 0000282D */   daddu    $a1, $zero, $zero
/* B18DC 8011A9FC 44809000 */  mtc1      $zero, $f18
/* B18E0 8011AA00 3C013FE0 */  lui       $at, (0x3FE00000 >> 16)
/* B18E4 8011AA04 44818800 */  mtc1      $at, $f17
/* B18E8 8011AA08 44808000 */  mtc1      $zero, $f16
.LIQUE_8011AA0C:
/* B18EC 8011AA0C 8FA3001C */  lw        $v1, 0x1C($sp)
/* B18F0 8011AA10 84620000 */  lh        $v0, 0x0($v1)
/* B18F4 8011AA14 44823000 */  mtc1      $v0, $f6
/* B18F8 8011AA18 00000000 */  nop
/* B18FC 8011AA1C 468031A0 */  cvt.s.w   $f6, $f6
/* B1900 8011AA20 84620002 */  lh        $v0, 0x2($v1)
/* B1904 8011AA24 84630004 */  lh        $v1, 0x4($v1)
/* B1908 8011AA28 44827000 */  mtc1      $v0, $f14
/* B190C 8011AA2C 00000000 */  nop
/* B1910 8011AA30 468073A0 */  cvt.s.w   $f14, $f14
/* B1914 8011AA34 44836000 */  mtc1      $v1, $f12
/* B1918 8011AA38 00000000 */  nop
/* B191C 8011AA3C 46806320 */  cvt.s.w   $f12, $f12
/* B1920 8011AA40 1200001C */  beqz      $s0, .LIQUE_8011AAB4
/* B1924 8011AA44 46003286 */   mov.s    $f10, $f6
/* B1928 8011AA48 C6040000 */  lwc1      $f4, 0x0($s0)
/* B192C 8011AA4C 46062102 */  mul.s     $f4, $f4, $f6
/* B1930 8011AA50 00000000 */  nop
/* B1934 8011AA54 C60A0010 */  lwc1      $f10, 0x10($s0)
/* B1938 8011AA58 460E5282 */  mul.s     $f10, $f10, $f14
/* B193C 8011AA5C 00000000 */  nop
/* B1940 8011AA60 C6000020 */  lwc1      $f0, 0x20($s0)
/* B1944 8011AA64 460C0002 */  mul.s     $f0, $f0, $f12
/* B1948 8011AA68 00000000 */  nop
/* B194C 8011AA6C C6020008 */  lwc1      $f2, 0x8($s0)
/* B1950 8011AA70 46061082 */  mul.s     $f2, $f2, $f6
/* B1954 8011AA74 00000000 */  nop
/* B1958 8011AA78 C6080018 */  lwc1      $f8, 0x18($s0)
/* B195C 8011AA7C 460E4202 */  mul.s     $f8, $f8, $f14
/* B1960 8011AA80 00000000 */  nop
/* B1964 8011AA84 C6060028 */  lwc1      $f6, 0x28($s0)
/* B1968 8011AA88 460C3182 */  mul.s     $f6, $f6, $f12
/* B196C 8011AA8C 00000000 */  nop
/* B1970 8011AA90 460A2100 */  add.s     $f4, $f4, $f10
/* B1974 8011AA94 46081080 */  add.s     $f2, $f2, $f8
/* B1978 8011AA98 46002100 */  add.s     $f4, $f4, $f0
/* B197C 8011AA9C 46061080 */  add.s     $f2, $f2, $f6
/* B1980 8011AAA0 C6000030 */  lwc1      $f0, 0x30($s0)
/* B1984 8011AAA4 46002280 */  add.s     $f10, $f4, $f0
/* B1988 8011AAA8 C6000038 */  lwc1      $f0, 0x38($s0)
/* B198C 8011AAAC 08046AAE */  j         .LIQUE_8011AAB8
/* B1990 8011AAB0 46001180 */   add.s    $f6, $f2, $f0
.LIQUE_8011AAB4:
/* B1994 8011AAB4 46006186 */  mov.s     $f6, $f12
.LIQUE_8011AAB8:
/* B1998 8011AAB8 460AF002 */  mul.s     $f0, $f30, $f10
/* B199C 8011AABC 00000000 */  nop
/* B19A0 8011AAC0 460AC082 */  mul.s     $f2, $f24, $f10
/* B19A4 8011AAC4 00000000 */  nop
/* B19A8 8011AAC8 C7B60040 */  lwc1      $f22, 0x40($sp)
/* B19AC 8011AACC 4606B102 */  mul.s     $f4, $f22, $f6
/* B19B0 8011AAD0 00000000 */  nop
/* B19B4 8011AAD4 4606D182 */  mul.s     $f6, $f26, $f6
/* B19B8 8011AAD8 00000000 */  nop
/* B19BC 8011AADC 46040000 */  add.s     $f0, $f0, $f4
/* B19C0 8011AAE0 46061080 */  add.s     $f2, $f2, $f6
/* B19C4 8011AAE4 C7BC002C */  lwc1      $f28, 0x2C($sp)
/* B19C8 8011AAE8 461C0100 */  add.s     $f4, $f0, $f28
/* B19CC 8011AAEC 4612203C */  c.lt.s    $f4, $f18
/* B19D0 8011AAF0 00000000 */  nop
/* B19D4 8011AAF4 45000004 */  bc1f      .LIQUE_8011AB08
/* B19D8 8011AAF8 46141080 */   add.s    $f2, $f2, $f20
/* B19DC 8011AAFC 46002021 */  cvt.d.s   $f0, $f4
/* B19E0 8011AB00 08046AC8 */  j         .LIQUE_8011AB20
/* B19E4 8011AB04 46300001 */   sub.d    $f0, $f0, $f16
.LIQUE_8011AB08:
/* B19E8 8011AB08 4604903C */  c.lt.s    $f18, $f4
/* B19EC 8011AB0C 00000000 */  nop
/* B19F0 8011AB10 45000004 */  bc1f      .LIQUE_8011AB24
/* B19F4 8011AB14 00000000 */   nop
/* B19F8 8011AB18 46002021 */  cvt.d.s   $f0, $f4
/* B19FC 8011AB1C 46300000 */  add.d     $f0, $f0, $f16
.LIQUE_8011AB20:
/* B1A00 8011AB20 46200120 */  cvt.s.d   $f4, $f0
.LIQUE_8011AB24:
/* B1A04 8011AB24 4612103C */  c.lt.s    $f2, $f18
/* B1A08 8011AB28 00000000 */  nop
/* B1A0C 8011AB2C 45000004 */  bc1f      .LIQUE_8011AB40
/* B1A10 8011AB30 00000000 */   nop
/* B1A14 8011AB34 46001021 */  cvt.d.s   $f0, $f2
/* B1A18 8011AB38 08046AD6 */  j         .LIQUE_8011AB58
/* B1A1C 8011AB3C 46300001 */   sub.d    $f0, $f0, $f16
.LIQUE_8011AB40:
/* B1A20 8011AB40 4602903C */  c.lt.s    $f18, $f2
/* B1A24 8011AB44 00000000 */  nop
/* B1A28 8011AB48 45000004 */  bc1f      .LIQUE_8011AB5C
/* B1A2C 8011AB4C 00000000 */   nop
/* B1A30 8011AB50 46001021 */  cvt.d.s   $f0, $f2
/* B1A34 8011AB54 46300000 */  add.d     $f0, $f0, $f16
.LIQUE_8011AB58:
/* B1A38 8011AB58 462000A0 */  cvt.s.d   $f2, $f0
.LIQUE_8011AB5C:
/* B1A3C 8011AB5C 8FA3001C */  lw        $v1, 0x1C($sp)
/* B1A40 8011AB60 4600258D */  trunc.w.s $f22, $f4
/* B1A44 8011AB64 4402B000 */  mfc1      $v0, $f22
/* B1A48 8011AB68 00000000 */  nop
/* B1A4C 8011AB6C A4620008 */  sh        $v0, 0x8($v1)
/* B1A50 8011AB70 A073000C */  sb        $s3, 0xC($v1)
/* B1A54 8011AB74 8FA4001C */  lw        $a0, 0x1C($sp)
/* B1A58 8011AB78 4600158D */  trunc.w.s $f22, $f2
/* B1A5C 8011AB7C 4402B000 */  mfc1      $v0, $f22
/* B1A60 8011AB80 00000000 */  nop
/* B1A64 8011AB84 A462000A */  sh        $v0, 0xA($v1)
/* B1A68 8011AB88 A092000D */  sb        $s2, 0xD($a0)
/* B1A6C 8011AB8C 8FA2001C */  lw        $v0, 0x1C($sp)
/* B1A70 8011AB90 24A50001 */  addiu     $a1, $a1, 0x1
/* B1A74 8011AB94 A051000E */  sb        $s1, 0xE($v0)
/* B1A78 8011AB98 8FA2001C */  lw        $v0, 0x1C($sp)
/* B1A7C 8011AB9C 8FA30018 */  lw        $v1, 0x18($sp)
/* B1A80 8011ABA0 24420010 */  addiu     $v0, $v0, 0x10
/* B1A84 8011ABA4 00A3182A */  slt       $v1, $a1, $v1
/* B1A88 8011ABA8 1460FF98 */  bnez      $v1, .LIQUE_8011AA0C
/* B1A8C 8011ABAC AFA2001C */   sw       $v0, 0x1C($sp)
.LIQUE_8011ABB0:
/* B1A90 8011ABB0 8FBF0060 */  lw        $ra, 0x60($sp)
/* B1A94 8011ABB4 8FB5005C */  lw        $s5, 0x5C($sp)
/* B1A98 8011ABB8 8FB40058 */  lw        $s4, 0x58($sp)
/* B1A9C 8011ABBC 8FB30054 */  lw        $s3, 0x54($sp)
/* B1AA0 8011ABC0 8FB20050 */  lw        $s2, 0x50($sp)
/* B1AA4 8011ABC4 8FB1004C */  lw        $s1, 0x4C($sp)
/* B1AA8 8011ABC8 8FB00048 */  lw        $s0, 0x48($sp)
/* B1AAC 8011ABCC D7BE0090 */  ldc1      $f30, 0x90($sp)
/* B1AB0 8011ABD0 D7BC0088 */  ldc1      $f28, 0x88($sp)
/* B1AB4 8011ABD4 D7BA0080 */  ldc1      $f26, 0x80($sp)
/* B1AB8 8011ABD8 D7B80078 */  ldc1      $f24, 0x78($sp)
/* B1ABC 8011ABDC D7B60070 */  ldc1      $f22, 0x70($sp)
/* B1AC0 8011ABE0 D7B40068 */  ldc1      $f20, 0x68($sp)
/* B1AC4 8011ABE4 03E00008 */  jr        $ra
/* B1AC8 8011ABE8 27BD0098 */   addiu    $sp, $sp, 0x98