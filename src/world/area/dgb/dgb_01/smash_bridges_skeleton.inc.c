#include "dgb_01.h"

StaticAnimatorNode N(SmashBridgesNode121) = {
    .pos = { 225.0f, 255.0f, 0.0f },
};

StaticAnimatorNode N(SmashBridgesNode120) = {
    .displayList = N(D_8024C098_C09918),
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode N(SmashBridgesNode119) = {
    .displayList = N(D_8024C030_C098B0),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode120),
};

StaticAnimatorNode N(SmashBridgesNode118) = {
    .displayList = N(D_8024BFC8_C09848),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode119),
};

StaticAnimatorNode N(SmashBridgesNode117) = {
    .displayList = N(D_8024C2E0_C09B60),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode118),
};

StaticAnimatorNode N(SmashBridgesNode116) = {
    .displayList = N(D_8024C1F0_C09A70),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode117),
};

StaticAnimatorNode N(SmashBridgesNode115) = {
    .displayList = N(D_8024C100_C09980),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode116),
};

StaticAnimatorNode N(SmashBridgesNode114) = {
    .child = &N(SmashBridgesNode115),
};

StaticAnimatorNode N(SmashBridgesNode113) = {
    .displayList = N(D_8024C560_C09DE0),
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode N(SmashBridgesNode112) = {
    .displayList = N(D_8024C4C0_C09D40),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode113),
};

StaticAnimatorNode N(SmashBridgesNode111) = {
    .displayList = N(D_8024C420_C09CA0),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode112),
};

StaticAnimatorNode N(SmashBridgesNode110) = {
    .sibling = &N(SmashBridgesNode114),
    .child = &N(SmashBridgesNode111),
};

StaticAnimatorNode N(SmashBridgesNode109) = {
    .displayList = N(D_8024B770_C08FF0),
};

StaticAnimatorNode N(SmashBridgesNode108) = {
    .displayList = N(D_8024B8F8_C09178),
    .sibling = &N(SmashBridgesNode109),
};

StaticAnimatorNode N(SmashBridgesNode107) = {
    .displayList = N(D_8024BAA0_C09320),
    .sibling = &N(SmashBridgesNode108),
};

StaticAnimatorNode N(SmashBridgesNode106) = {
    .displayList = N(D_802515B0_C0EE30),
    .sibling = &N(SmashBridgesNode107),
};

StaticAnimatorNode N(SmashBridgesNode105) = {
    .displayList = N(D_80250168_C0D9E8),
    .sibling = &N(SmashBridgesNode106),
};

StaticAnimatorNode N(SmashBridgesNode104) = {
    .displayList = N(D_80250108_C0D988),
    .sibling = &N(SmashBridgesNode105),
};

StaticAnimatorNode N(SmashBridgesNode103) = {
    .displayList = N(D_80251798_C0F018),
    .sibling = &N(SmashBridgesNode104),
};

StaticAnimatorNode N(SmashBridgesNode102) = {
    .displayList = N(D_80250360_C0DBE0),
    .sibling = &N(SmashBridgesNode103),
};

StaticAnimatorNode N(SmashBridgesNode101) = {
    .displayList = N(D_80251710_C0EF90),
    .sibling = &N(SmashBridgesNode102),
};

StaticAnimatorNode N(SmashBridgesNode100) = {
    .displayList = N(D_802502F8_C0DB78),
    .sibling = &N(SmashBridgesNode101),
};

StaticAnimatorNode N(SmashBridgesNode099) = {
    .displayList = N(D_802516A8_C0EF28),
    .sibling = &N(SmashBridgesNode100),
};

StaticAnimatorNode N(SmashBridgesNode098) = {
    .displayList = N(D_80250290_C0DB10),
    .sibling = &N(SmashBridgesNode099),
};

StaticAnimatorNode N(SmashBridgesNode097) = {
    .displayList = N(D_80251638_C0EEB8),
    .sibling = &N(SmashBridgesNode098),
};

StaticAnimatorNode N(SmashBridgesNode096) = {
    .displayList = N(D_80250220_C0DAA0),
    .sibling = &N(SmashBridgesNode097),
};

StaticAnimatorNode N(SmashBridgesNode095) = {
    .sibling = &N(SmashBridgesNode110),
    .child = &N(SmashBridgesNode096),
};

StaticAnimatorNode N(SmashBridgesNode094) = {
    .displayList = N(D_8024FAB0_C0D330),
    .rot = { 0x0000, 0x1FFF, 0x8001 },
    .pos = { -315.0f, 2.0f, -139.0f },
};

StaticAnimatorNode N(SmashBridgesNode093) = {
    .displayList = N(D_8024FA18_C0D298),
    .rot = { 0x8001, 0x2AAA, 0x8001 },
    .pos = { -455.0f, 421.0f, -20.0f },
    .sibling = &N(SmashBridgesNode094),
};

StaticAnimatorNode N(SmashBridgesNode092) = {
    .displayList = N(D_8024F980_C0D200),
    .rot = { 0x8001, 0xE001, 0x0000 },
    .pos = { -385.0f, 2.0f, 169.0f },
    .sibling = &N(SmashBridgesNode093),
};

StaticAnimatorNode N(SmashBridgesNode091) = {
    .displayList = N(D_8024F8E8_C0D168),
    .rot = { 0x0000, 0x2AAA, 0x8001 },
    .pos = { -105.0f, 2.0f, -210.0f },
    .sibling = &N(SmashBridgesNode092),
};

StaticAnimatorNode N(SmashBridgesNode090) = {
    .displayList = N(D_8024F850_C0D0D0),
    .rot = { 0x0000, 0xEAAB, 0x8001 },
    .pos = { -5.0f, 2.0f, -180.0f },
    .sibling = &N(SmashBridgesNode091),
};

StaticAnimatorNode N(SmashBridgesNode089) = {
    .displayList = N(D_8024F7B8_C0D038),
    .rot = { 0x8001, 0x0AAA, 0x0000 },
    .pos = { -195.0f, 2.0f, 259.0f },
    .sibling = &N(SmashBridgesNode090),
};

StaticAnimatorNode N(SmashBridgesNode088) = {
    .displayList = N(D_8024F720_C0CFA0),
    .rot = { 0x8001, 0xD556, 0x8001 },
    .pos = { -65.0f, 2.0f, 189.0f },
    .sibling = &N(SmashBridgesNode089),
};

StaticAnimatorNode N(SmashBridgesNode087) = {
    .displayList = N(D_8024F688_C0CF08),
    .rot = { 0x8001, 0x0000, 0x0000 },
    .pos = { 275.0f, 2.0f, -129.0f },
    .sibling = &N(SmashBridgesNode088),
};

StaticAnimatorNode N(SmashBridgesNode086) = {
    .displayList = N(D_8024F5F0_C0CE70),
    .rot = { 0x0000, 0xF556, 0x8001 },
    .pos = { 195.0f, 421.0f, -40.0f },
    .sibling = &N(SmashBridgesNode087),
};

StaticAnimatorNode N(SmashBridgesNode085) = {
    .displayList = N(D_8024F558_C0CDD8),
    .rot = { 0x8001, 0x1555, 0x8001 },
    .pos = { 85.0f, 2.0f, 329.0f },
    .sibling = &N(SmashBridgesNode086),
};

StaticAnimatorNode N(SmashBridgesNode084) = {
    .displayList = N(D_8024F4C0_C0CD40),
    .rot = { 0x8001, 0x1555, 0x0000 },
    .pos = { 215.0f, 421.0f, 29.0f },
    .sibling = &N(SmashBridgesNode085),
};

StaticAnimatorNode N(SmashBridgesNode083) = {
    .sibling = &N(SmashBridgesNode095),
    .child = &N(SmashBridgesNode084),
};

StaticAnimatorNode N(SmashBridgesNode082) = {
    .displayList = N(D_8024F328_C0CBA8),
    .rot = { 0x8001, 0x0000, 0x0000 },
    .pos = { 8.0f, -23.0f, -49.0f },
};

StaticAnimatorNode N(SmashBridgesNode081) = {
    .displayList = N(D_8024F160_C0C9E0),
    .rot = { 0x0000, 0xF8E4, 0x8001 },
    .pos = { 73.0f, -23.0f, 20.0f },
    .sibling = &N(SmashBridgesNode082),
};

StaticAnimatorNode N(SmashBridgesNode080) = {
    .displayList = N(D_8024F1F8_C0CA78),
    .rot = { 0x8001, 0x0000, 0x0000 },
    .pos = { -1.0f, -23.0f, 49.0f },
    .sibling = &N(SmashBridgesNode081),
};

StaticAnimatorNode N(SmashBridgesNode079) = {
    .displayList = N(D_8024F290_C0CB10),
    .rot = { 0x8001, 0x0000, 0x8001 },
    .pos = { 18.0f, -23.0f, 0.0f },
    .sibling = &N(SmashBridgesNode080),
};

StaticAnimatorNode N(SmashBridgesNode078) = {
    .rot = { 0x0000, 0x1FFF, 0x0000 },
    .pos = { 61.0f, 47.0f, -31.0f },
    .child = &N(SmashBridgesNode079),
};

StaticAnimatorNode N(SmashBridgesNode077) = {
    .displayList = N(D_8024F3C0_C0CC40),
    .rot = { 0x8001, 0x0AAA, 0x0000 },
    .pos = { -415.0f, 21.0f, 20.0f },
    .sibling = &N(SmashBridgesNode078),
};

StaticAnimatorNode N(SmashBridgesNode076) = {
    .displayList = N(D_8024F0C8_C0C948),
    .rot = { 0x8001, 0xF8E4, 0x8001 },
    .pos = { 195.0f, 211.0f, -39.0f },
    .sibling = &N(SmashBridgesNode077),
};

StaticAnimatorNode N(SmashBridgesNode075) = {
    .displayList = N(D_8024F030_C0C8B0),
    .rot = { 0x8001, 0xF1C8, 0x8001 },
    .pos = { 95.0f, 210.0f, -30.0f },
    .sibling = &N(SmashBridgesNode076),
};

StaticAnimatorNode N(SmashBridgesNode074) = {
    .displayList = N(D_8024EF98_C0C818),
    .rot = { 0x8001, 0x1555, 0x8001 },
    .pos = { 115.0f, 211.0f, 39.0f },
    .sibling = &N(SmashBridgesNode075),
};

StaticAnimatorNode N(SmashBridgesNode073) = {
    .displayList = N(D_8024EF00_C0C780),
    .rot = { 0x8001, 0x0AAA, 0x8001 },
    .pos = { 215.0f, 211.0f, 39.0f },
    .sibling = &N(SmashBridgesNode074),
};

StaticAnimatorNode N(SmashBridgesNode072) = {
    .sibling = &N(SmashBridgesNode083),
    .child = &N(SmashBridgesNode073),
};

StaticAnimatorNode N(SmashBridgesNode071) = {
    .displayList = N(D_8024BEF8_C09778),
    .rot = { 0x0000, 0x0AAA, 0x0000 },
    .pos = { -375.0f, 2.0f, 0.0f },
};

StaticAnimatorNode N(SmashBridgesNode070) = {
    .displayList = N(D_8024BE60_C096E0),
    .rot = { 0x0000, 0xEAAB, 0x8001 },
    .pos = { -175.0f, 2.0f, -49.0f },
    .sibling = &N(SmashBridgesNode071),
};

StaticAnimatorNode N(SmashBridgesNode069) = {
    .displayList = N(D_8024BDC8_C09648),
    .rot = { 0x8001, 0x0000, 0x8001 },
    .pos = { 75.0f, 2.0f, -49.0f },
    .sibling = &N(SmashBridgesNode070),
};

StaticAnimatorNode N(SmashBridgesNode068) = {
    .sibling = &N(SmashBridgesNode072),
    .child = &N(SmashBridgesNode069),
};

StaticAnimatorNode N(SmashBridgesNode067) = {
    .sibling = &N(SmashBridgesNode121),
    .child = &N(SmashBridgesNode068),
};

StaticAnimatorNode N(SmashBridgesNode066) = {
    .displayList = N(D_8024DEF8_dgb_01),
};

StaticAnimatorNode N(SmashBridgesNode065) = {
    .displayList = N(D_8024E120_C0B9A0),
    .sibling = &N(SmashBridgesNode066),
};

StaticAnimatorNode N(SmashBridgesNode064) = {
    .displayList = N(D_8024E0A8_C0B928),
    .sibling = &N(SmashBridgesNode065),
};

StaticAnimatorNode N(SmashBridgesNode063) = {
    .displayList = N(D_8024E020_C0B8A0),
    .sibling = &N(SmashBridgesNode064),
};

StaticAnimatorNode N(SmashBridgesNode062) = {
    .displayList = N(D_8024DFA0_C0B820),
    .sibling = &N(SmashBridgesNode063),
};

StaticAnimatorNode N(SmashBridgesNode061) = {
    .displayList = N(D_8024E1A8_C0BA28),
    .sibling = &N(SmashBridgesNode062),
};

StaticAnimatorNode N(SmashBridgesNode060) = {
    .displayList = N(D_8024DD60_C0B5E0),
    .sibling = &N(SmashBridgesNode061),
};

StaticAnimatorNode N(SmashBridgesNode059) = {
    .displayList = N(D_8024DC50_C0B4D0),
    .sibling = &N(SmashBridgesNode060),
};

StaticAnimatorNode N(SmashBridgesNode058) = {
    .rot = { 0x0000, 0x0000, 0xEA9F },
    .pos = { -360.0f, 85.0f, -1.0f },
    .child = &N(SmashBridgesNode059),
};

StaticAnimatorNode N(SmashBridgesNode057) = {
    .displayList = N(D_8024ECB0_C0C530),
};

StaticAnimatorNode N(SmashBridgesNode056) = {
    .displayList = N(D_8024EE18_C0C698),
    .sibling = &N(SmashBridgesNode057),
};

StaticAnimatorNode N(SmashBridgesNode055) = {
    .rot = { 0xEAAB, 0x2E87, 0xF02E },
    .pos = { 35.0f, 316.0f, 36.0f },
    .sibling = &N(SmashBridgesNode058),
    .child = &N(SmashBridgesNode056),
};

StaticAnimatorNode N(SmashBridgesNode054) = {
    .displayList = N(D_80250720_C0DFA0),
};

StaticAnimatorNode N(SmashBridgesNode053) = {
    .displayList = N(D_80250910_C0E190),
    .sibling = &N(SmashBridgesNode054),
};

StaticAnimatorNode N(SmashBridgesNode052) = {
    .displayList = N(D_80250698_C0DF18),
    .sibling = &N(SmashBridgesNode053),
};

StaticAnimatorNode N(SmashBridgesNode051) = {
    .displayList = N(D_80250798_C0E018),
    .sibling = &N(SmashBridgesNode052),
};

StaticAnimatorNode N(SmashBridgesNode050) = {
    .displayList = N(D_80250820_C0E0A0),
    .sibling = &N(SmashBridgesNode051),
};

StaticAnimatorNode N(SmashBridgesNode049) = {
    .displayList = N(D_80250898_C0E118),
    .sibling = &N(SmashBridgesNode050),
};

StaticAnimatorNode N(SmashBridgesNode048) = {
    .rot = { 0xFC72, 0xFE27, 0x0000 },
    .pos = { 133.0f, 271.0f, 30.0f },
    .sibling = &N(SmashBridgesNode055),
    .child = &N(SmashBridgesNode049),
};

StaticAnimatorNode N(SmashBridgesNode047) = {
    .displayList = N(D_8024C918_C0A198),
    .pos = { 252.0f, 0.0f, 0.0f },
};

StaticAnimatorNode N(SmashBridgesNode046) = {
    .displayList = N(D_8024C998_C0A218),
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &N(SmashBridgesNode047),
};

StaticAnimatorNode N(SmashBridgesNode045) = {
    .displayList = N(D_8024C808_C0A088),
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &N(SmashBridgesNode046),
};

StaticAnimatorNode N(SmashBridgesNode044) = {
    .sibling = &N(SmashBridgesNode045),
};

StaticAnimatorNode N(SmashBridgesNode043) = {
    .rot = { 0x0000, 0x0000, 0xF60C },
    .pos = { -252.0f, 0.0f, 0.0f },
    .child = &N(SmashBridgesNode044),
};

StaticAnimatorNode N(SmashBridgesNode042) = {
    .rot = { 0x0000, 0x0000, 0x09F4 },
    .pos = { 253.0f, 285.0f, 86.0f },
    .child = &N(SmashBridgesNode043),
};

StaticAnimatorNode N(SmashBridgesNode041) = {
    .displayList = N(D_8024CAF0_C0A370),
    .sibling = &N(SmashBridgesNode042),
};

StaticAnimatorNode N(SmashBridgesNode040) = {
    .displayList = N(D_8024CC28_C0A4A8),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode041),
};

StaticAnimatorNode N(SmashBridgesNode039) = {
    .displayList = N(D_8024CB68_C0A3E8),
    .sibling = &N(SmashBridgesNode040),
};

StaticAnimatorNode N(SmashBridgesNode038) = {
    .displayList = N(D_8024CD98_C0A618),
    .sibling = &N(SmashBridgesNode039),
};

StaticAnimatorNode N(SmashBridgesNode037) = {
    .displayList = N(D_8024CD10_C0A590),
    .sibling = &N(SmashBridgesNode038),
};

StaticAnimatorNode N(SmashBridgesNode036) = {
    .displayList = N(D_8024CCA0_C0A520),
    .sibling = &N(SmashBridgesNode037),
};

StaticAnimatorNode N(SmashBridgesNode035) = {
    .displayList = N(D_8024CE08_C0A688),
    .sibling = &N(SmashBridgesNode036),
};

StaticAnimatorNode N(SmashBridgesNode034) = {
    .displayList = N(D_8024C670_C09EF0),
    .sibling = &N(SmashBridgesNode035),
};

StaticAnimatorNode N(SmashBridgesNode033) = {
    .sibling = &N(SmashBridgesNode048),
    .child = &N(SmashBridgesNode034),
};

StaticAnimatorNode N(SmashBridgesNode032) = {
    .displayList = N(D_8024D2B8_C0AB38),
};

StaticAnimatorNode N(SmashBridgesNode031) = {
    .displayList = N(D_8024D448_C0ACC8),
    .sibling = &N(SmashBridgesNode032),
};

StaticAnimatorNode N(SmashBridgesNode030) = {
    .displayList = N(D_8024D3C8_C0AC48),
    .sibling = &N(SmashBridgesNode031),
};

StaticAnimatorNode N(SmashBridgesNode029) = {
    .pos = { 105.0f, -8.0f, 87.0f },
    .child = &N(SmashBridgesNode030),
};

StaticAnimatorNode N(SmashBridgesNode028) = {
    .displayList = N(D_8024D580_C0AE00),
    .sibling = &N(SmashBridgesNode029),
};

StaticAnimatorNode N(SmashBridgesNode027) = {
    .displayList = N(D_8024D680_C0AF00),
    .sibling = &N(SmashBridgesNode028),
};

StaticAnimatorNode N(SmashBridgesNode026) = {
    .displayList = N(D_8024D828_C0B0A8),
    .sibling = &N(SmashBridgesNode027),
};

StaticAnimatorNode N(SmashBridgesNode025) = {
    .displayList = N(D_8024D788_C0B008),
    .sibling = &N(SmashBridgesNode026),
};

StaticAnimatorNode N(SmashBridgesNode024) = {
    .displayList = N(D_8024D700_C0AF80),
    .sibling = &N(SmashBridgesNode025),
};

StaticAnimatorNode N(SmashBridgesNode023) = {
    .displayList = N(D_8024D8D0_C0B150),
    .sibling = &N(SmashBridgesNode024),
};

StaticAnimatorNode N(SmashBridgesNode022) = {
    .displayList = N(D_8024D060_C0A8E0),
    .sibling = &N(SmashBridgesNode023),
};

StaticAnimatorNode N(SmashBridgesNode021) = {
    .rot = { 0x0000, 0x1FFF, 0x0000 },
    .pos = { 61.0f, 47.0f, -31.0f },
    .sibling = &N(SmashBridgesNode033),
    .child = &N(SmashBridgesNode022),
};

StaticAnimatorNode N(SmashBridgesNode020) = {
    .displayList = N(D_8024E6D8_C0BF58),
    .rot = { 0x038E, 0x0000, 0x18E3 },
    .pos = { -465.0f, 210.0f, -90.0f },
};

StaticAnimatorNode N(SmashBridgesNode019) = {
    .displayList = N(D_8024E5B0_C0BE30),
    .rot = { 0x0000, 0x18E3, 0x1555 },
    .pos = { -465.0f, 210.0f, 90.0f },
    .sibling = &N(SmashBridgesNode020),
};

StaticAnimatorNode N(SmashBridgesNode018) = {
    .displayList = N(D_8024E800_C0C080),
    .sibling = &N(SmashBridgesNode019),
};

StaticAnimatorNode N(SmashBridgesNode017) = {
    .displayList = N(D_8024EA60_C0C2E0),
    .sibling = &N(SmashBridgesNode018),
};

StaticAnimatorNode N(SmashBridgesNode016) = {
    .displayList = N(D_8024E9D8_C0C258),
    .sibling = &N(SmashBridgesNode017),
};

StaticAnimatorNode N(SmashBridgesNode015) = {
    .displayList = N(D_8024E968_C0C1E8),
    .sibling = &N(SmashBridgesNode016),
};

StaticAnimatorNode N(SmashBridgesNode014) = {
    .displayList = N(D_8024E8C0_C0C140),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(SmashBridgesNode015),
};

StaticAnimatorNode N(SmashBridgesNode013) = {
    .displayList = N(D_8024EAD0_C0C350),
    .sibling = &N(SmashBridgesNode014),
};

StaticAnimatorNode N(SmashBridgesNode012) = {
    .displayList = N(D_8024E4D8_C0BD58),
    .sibling = &N(SmashBridgesNode013),
};

StaticAnimatorNode N(SmashBridgesNode011) = {
    .pos = { 0.0f, -188.0f, 0.0f },
    .sibling = &N(SmashBridgesNode021),
    .child = &N(SmashBridgesNode012),
};

StaticAnimatorNode N(SmashBridgesNode010) = {
    .displayList = N(D_802510C8_C0E948),
    .pos = { -179.0f, 34.0f, 98.0f },
};

StaticAnimatorNode N(SmashBridgesNode009) = {
    .displayList = N(D_80250E88_C0E708),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(SmashBridgesNode010),
};

StaticAnimatorNode N(SmashBridgesNode008) = {
    .displayList = N(D_80251050_C0E8D0),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(SmashBridgesNode009),
};

StaticAnimatorNode N(SmashBridgesNode007) = {
    .displayList = N(D_80250FC8_C0E848),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(SmashBridgesNode008),
};

StaticAnimatorNode N(SmashBridgesNode006) = {
    .displayList = N(D_80250F40_C0E7C0),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(SmashBridgesNode007),
};

StaticAnimatorNode N(SmashBridgesNode005) = {
    .displayList = N(D_80250DE0_C0E660),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(SmashBridgesNode006),
};

StaticAnimatorNode N(SmashBridgesNode004) = {
    .rot = { 0xFB06, 0xC60C, 0 },
    .pos = { 179.0f, -34.0f, -98.0f },
    .child = &N(SmashBridgesNode005),
};

StaticAnimatorNode N(SmashBridgesNode003) = {
    .rot = { 0, 0xFA06, 0xC464 },
    .pos = { -245.0f, 196.0f, 21.0f },
    .sibling = &N(SmashBridgesNode011),
    .child = &N(SmashBridgesNode004),
};

StaticAnimatorNode N(SmashBridgesNode002) = {
    .sibling = &N(SmashBridgesNode067),
    .child = &N(SmashBridgesNode003),
};

StaticAnimatorNode N(SmashBridgesRoot) = {
    .child = &N(SmashBridgesNode002),
};

StaticAnimatorNode* N(SmashBridgesSkeleton)[] = {
    &N(SmashBridgesRoot),
        &N(SmashBridgesNode002),
            &N(SmashBridgesNode003),
                &N(SmashBridgesNode004),
                    &N(SmashBridgesNode005),
                    &N(SmashBridgesNode006),
                    &N(SmashBridgesNode007),
                    &N(SmashBridgesNode008),
                    &N(SmashBridgesNode009),
                    &N(SmashBridgesNode010),
            &N(SmashBridgesNode011),
                &N(SmashBridgesNode012),
                &N(SmashBridgesNode013),
                &N(SmashBridgesNode014),
                &N(SmashBridgesNode015),
                &N(SmashBridgesNode016),
                &N(SmashBridgesNode017),
                &N(SmashBridgesNode018),
                &N(SmashBridgesNode019),
                &N(SmashBridgesNode020),
            &N(SmashBridgesNode021),
                &N(SmashBridgesNode022),
                &N(SmashBridgesNode023),
                &N(SmashBridgesNode024),
                &N(SmashBridgesNode025),
                &N(SmashBridgesNode026),
                &N(SmashBridgesNode027),
                &N(SmashBridgesNode028),
                &N(SmashBridgesNode029),
                    &N(SmashBridgesNode030),
                    &N(SmashBridgesNode031),
                    &N(SmashBridgesNode032),
            &N(SmashBridgesNode033),
                &N(SmashBridgesNode034),
                &N(SmashBridgesNode035),
                &N(SmashBridgesNode036),
                &N(SmashBridgesNode037),
                &N(SmashBridgesNode038),
                &N(SmashBridgesNode039),
                &N(SmashBridgesNode040),
                &N(SmashBridgesNode041),
                &N(SmashBridgesNode042),
                    &N(SmashBridgesNode043),
                        &N(SmashBridgesNode044),
                        &N(SmashBridgesNode045),
                        &N(SmashBridgesNode046),
                        &N(SmashBridgesNode047),
            &N(SmashBridgesNode048),
                &N(SmashBridgesNode049),
                &N(SmashBridgesNode050),
                &N(SmashBridgesNode051),
                &N(SmashBridgesNode052),
                &N(SmashBridgesNode053),
                &N(SmashBridgesNode054),
            &N(SmashBridgesNode055),
                &N(SmashBridgesNode056),
                &N(SmashBridgesNode057),
            &N(SmashBridgesNode058),
                &N(SmashBridgesNode059),
                &N(SmashBridgesNode060),
                &N(SmashBridgesNode061),
                &N(SmashBridgesNode062),
                &N(SmashBridgesNode063),
                &N(SmashBridgesNode064),
                &N(SmashBridgesNode065),
                &N(SmashBridgesNode066),
        &N(SmashBridgesNode067),
            &N(SmashBridgesNode068),
                &N(SmashBridgesNode069),
                &N(SmashBridgesNode070),
                &N(SmashBridgesNode071),
            &N(SmashBridgesNode072),
                &N(SmashBridgesNode073),
                &N(SmashBridgesNode074),
                &N(SmashBridgesNode075),
                &N(SmashBridgesNode076),
                &N(SmashBridgesNode077),
                &N(SmashBridgesNode078),
                    &N(SmashBridgesNode079),
                    &N(SmashBridgesNode080),
                    &N(SmashBridgesNode081),
                    &N(SmashBridgesNode082),
            &N(SmashBridgesNode083),
                &N(SmashBridgesNode084),
                &N(SmashBridgesNode085),
                &N(SmashBridgesNode086),
                &N(SmashBridgesNode087),
                &N(SmashBridgesNode088),
                &N(SmashBridgesNode089),
                &N(SmashBridgesNode090),
                &N(SmashBridgesNode091),
                &N(SmashBridgesNode092),
                &N(SmashBridgesNode093),
                &N(SmashBridgesNode094),
            &N(SmashBridgesNode095),
                &N(SmashBridgesNode096),
                &N(SmashBridgesNode097),
                &N(SmashBridgesNode098),
                &N(SmashBridgesNode099),
                &N(SmashBridgesNode100),
                &N(SmashBridgesNode101),
                &N(SmashBridgesNode102),
                &N(SmashBridgesNode103),
                &N(SmashBridgesNode104),
                &N(SmashBridgesNode105),
                &N(SmashBridgesNode106),
                &N(SmashBridgesNode107),
                &N(SmashBridgesNode108),
                &N(SmashBridgesNode109),
            &N(SmashBridgesNode110),
                &N(SmashBridgesNode111),
                &N(SmashBridgesNode112),
                &N(SmashBridgesNode113),
            &N(SmashBridgesNode114),
                &N(SmashBridgesNode115),
                &N(SmashBridgesNode116),
                &N(SmashBridgesNode117),
                &N(SmashBridgesNode118),
                &N(SmashBridgesNode119),
                &N(SmashBridgesNode120),
        &N(SmashBridgesNode121),
    nullptr,
};
