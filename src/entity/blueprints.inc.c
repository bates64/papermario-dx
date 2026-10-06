#include "common.h"

#define ENTITY_BLUEPRINT(name, overlay) \
    EntityBlueprint Entity_##name = { overlay, "EntityImpl_" #name }

ENTITY_BLUEPRINT(SavePoint, "SaveBlock");

ENTITY_BLUEPRINT(RedSwitch, "Switch");
ENTITY_BLUEPRINT(BlueSwitch, "Switch");
ENTITY_BLUEPRINT(HugeBlueSwitch, "Switch");
ENTITY_BLUEPRINT(GreenStompSwitch, "Switch");

ENTITY_BLUEPRINT(ShatteringHammer1Block, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringHammer2Block, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringHammer3Block, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringHammer1BlockTiny, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringHammer2BlockTiny, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringHammer3BlockTiny, "ShatteringBlock");
ENTITY_BLUEPRINT(ShatteringBrickBlock, "ShatteringBlock");

ENTITY_BLUEPRINT(InertYellowBlock, "Block");
ENTITY_BLUEPRINT(InertRedBlock, "Block");
ENTITY_BLUEPRINT(BrickBlock, "Block");
ENTITY_BLUEPRINT(MulticoinBlock, "Block");
ENTITY_BLUEPRINT(Hammer1Block, "Block");
ENTITY_BLUEPRINT(Hammer1BlockWideX, "Block");
ENTITY_BLUEPRINT(Hammer1BlockWideZ, "Block");
ENTITY_BLUEPRINT(Hammer1BlockTiny, "Block");
ENTITY_BLUEPRINT(Hammer2Block, "Block");
ENTITY_BLUEPRINT(Hammer2BlockWideX, "Block");
ENTITY_BLUEPRINT(Hammer2BlockWideZ, "Block");
ENTITY_BLUEPRINT(Hammer2BlockTiny, "Block");
ENTITY_BLUEPRINT(Hammer3Block, "Block");
ENTITY_BLUEPRINT(Hammer3BlockWideX, "Block");
ENTITY_BLUEPRINT(Hammer3BlockWideZ, "Block");
ENTITY_BLUEPRINT(Hammer3BlockTiny, "Block");
ENTITY_BLUEPRINT(PushBlock, "Block");
ENTITY_BLUEPRINT(PowBlock, "Block");

ENTITY_BLUEPRINT(YellowBlock, "ItemBlock");
ENTITY_BLUEPRINT(HiddenYellowBlock, "ItemBlock");
ENTITY_BLUEPRINT(RedBlock, "ItemBlock");
ENTITY_BLUEPRINT(HiddenRedBlock, "ItemBlock");
ENTITY_BLUEPRINT(TriggerBlock, "ItemBlock");
ENTITY_BLUEPRINT(HitGroundedYellowBlock, "ItemBlock");
ENTITY_BLUEPRINT(HitFloatingYellowBlock, "ItemBlock");
ENTITY_BLUEPRINT(HitRedBlock, "ItemBlock");

ENTITY_BLUEPRINT(HeartBlockFrame, "HeartBlock");
ENTITY_BLUEPRINT(HeartBlockContent, "HeartBlock");
ENTITY_BLUEPRINT(HeartBlock, "HeartBlock");

ENTITY_BLUEPRINT(SuperBlock, "SuperBlock");
ENTITY_BLUEPRINT(SuperBlockContent, "SuperBlock");
ENTITY_BLUEPRINT(UltraBlock, "SuperBlock");
ENTITY_BLUEPRINT(UltraBlockContent, "SuperBlock");

ENTITY_BLUEPRINT(ScriptSpring, "SimpleSpring");
ENTITY_BLUEPRINT(SimpleSpring, "SimpleSpring");
ENTITY_BLUEPRINT(HiddenPanel, "HiddenPanel");
ENTITY_BLUEPRINT(GiantChest, "Chest");
ENTITY_BLUEPRINT(Chest, "Chest");
ENTITY_BLUEPRINT(WoodenCrate, "WoodenCrate");
ENTITY_BLUEPRINT(BlueWarpPipe, "BlueWarpPipe");
ENTITY_BLUEPRINT(Signpost, "Signpost");

ENTITY_BLUEPRINT(Padlock, "Padlock");
ENTITY_BLUEPRINT(PadlockRedFrame, "Padlock");
ENTITY_BLUEPRINT(PadlockRedFace, "Padlock");
ENTITY_BLUEPRINT(PadlockBlueFace, "Padlock");
ENTITY_BLUEPRINT(BoardedFloor, "BoardedFloor");
ENTITY_BLUEPRINT(BombableRock, "BombableRock");
ENTITY_BLUEPRINT(BombableRockWide, "BombableRock");

ENTITY_BLUEPRINT(Tweester, "Tweester");
ENTITY_BLUEPRINT(StarBoxLauncher, "StarBoxLauncher");

ENTITY_BLUEPRINT(CymbalPlant, "CymbalPlant");
ENTITY_BLUEPRINT(PinkFlower, "PinkFlower");
ENTITY_BLUEPRINT(PinkFlowerLight, "PinkFlower");
ENTITY_BLUEPRINT(SpinningFlower, "SpinningFlower");

ENTITY_BLUEPRINT(BellbellPlant, "BellbellPlant");
ENTITY_BLUEPRINT(TrumpetPlant, "TrumpetPlant");
ENTITY_BLUEPRINT(Munchlesia, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaReset, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaGrab, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaEnvelop, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaBeginChew, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaChewing, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaSpitOut, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaReset1, "Munchlesia");
ENTITY_BLUEPRINT(MunchlesiaReset2, "Munchlesia");

ENTITY_BLUEPRINT(ArrowSign, "ArrowSign");

#undef ENTITY_BLUEPRINT
