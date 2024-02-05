#include "common.h"
#include "ld_addrs.h"
#include "dx/debug_menu.h"

extern Addr sprite_shading_profiles_data_ROM_START;

/// Packed equivalent of SpriteShadingLightSource as baked into the ROM, smaller due to packed position vector
typedef struct PackedShadingLightSource {
    /* 0x00 */ s8 flags;
    /* 0x01 */ Color_RGB8 rgb;
    /* 0x04 */ Vec3s pos;
    /* 0x0A */ f32 falloff;
    /* 0x0E */ s8 unk_14;
    /* 0x0F */ char pad_0F[0x1];
} __attribute__((packed)) PackedShadingLightSource; // size = 0x10

/// Packed equivalent of SpriteShadingProfile as baked into the ROM
typedef struct PackedShadingProfile {
    /* 0x00 */ u8 count;
    /* 0x01 */ char pad_01[0x1];
    /* 0x02 */ Color_RGB8 ambientColor;
    /* 0x05 */ u8 ambientPower;
    /* 0x06 */ PackedShadingLightSource sources[7];
    /* 0x76 */ char pad_86[0xA];
} __attribute__((packed)) PackedShadingProfile; // size = 0x100

s32 ShadingOffsetsBuffer[2];
PackedShadingProfile PackedShadingData;

API_CALLABLE(SetSpriteShading) {
    Bytecode* args = script->ptrReadPos;
    s32 profileID = evt_get_variable(script, *args++);
    s32 shadingGroupOffset = (profileID >> 0x10) * 8;
    s32 shadingProfileOffset = (profileID & 0xFFFF) * 4;
    SpriteShadingProfile* profile;
    s32 romBase;
    s32 groupProfiles;
    s32 groupStart;
    s32 profileStart;
    s32 dataOffset;
    s32 i;

    if (profileID == SHADING_NONE) {
        return ApiStatus_DONE2;
    }

    // load shading group data
    romBase = (s32)sprite_shading_profiles_ROM_START;
    dma_copy((u8*)shadingGroupOffset + romBase, (u8*)shadingGroupOffset + romBase + 8, ShadingOffsetsBuffer);

    // load offset to shading data
    romBase = (s32)sprite_shading_profiles_ROM_START + shadingProfileOffset;
    groupStart = ShadingOffsetsBuffer[0];
    groupProfiles = ShadingOffsetsBuffer[1];
    dma_copy((u8*)groupProfiles + romBase, (u8*)groupProfiles + romBase + 4, ShadingOffsetsBuffer);

    // load shading profile
    profileStart = ShadingOffsetsBuffer[0];
    dataOffset = (s32)sprite_shading_profiles_data_ROM_START + groupStart + profileStart;
    dma_copy((u8*) dataOffset, (u8*) dataOffset + sizeof(PackedShadingData), &PackedShadingData);

    profile = gSpriteShadingProfile;
    profile->ambientColor.r = PackedShadingData.ambientColor.r;
    profile->ambientColor.g = PackedShadingData.ambientColor.g;
    profile->ambientColor.b = PackedShadingData.ambientColor.b;
    profile->ambientPower = PackedShadingData.ambientPower;

    for (i = 0; i < PackedShadingData.count; i++) {
        SpriteShadingLightSource* source = &gSpriteShadingProfile->sources[i];
        source->flags = PackedShadingData.sources[i].flags;
        source->rgb.r = PackedShadingData.sources[i].rgb.r;
        source->rgb.g = PackedShadingData.sources[i].rgb.g;
        source->rgb.b = PackedShadingData.sources[i].rgb.b;
        source->pos.x = PackedShadingData.sources[i].pos.x;
        source->pos.y = PackedShadingData.sources[i].pos.y;
        source->pos.z = PackedShadingData.sources[i].pos.z;
        source->falloff = PackedShadingData.sources[i].falloff;
        source->unk_14 = PackedShadingData.sources[i].unk_14;
    }
    gSpriteShadingProfile->flags |= SPR_SHADING_FLAG_ENABLED;

    return ApiStatus_DONE2;
}

API_CALLABLE(EnableSpriteShading) {
    Bytecode* args = script->ptrReadPos;
    s32 enabled = evt_get_variable(script, *args++);

    if (enabled) {
        gSpriteShadingProfile->flags |= SPR_SHADING_FLAG_ENABLED;
    } else {
        gSpriteShadingProfile->flags &= ~SPR_SHADING_FLAG_ENABLED;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(GetDemoState) {
    evt_set_variable(script, *script->ptrReadPos, gGameStatusPtr->demoState);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoPressButton) {
    gGameStatusPtr->demoButtonInput |= evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoReleaseButton) {
    gGameStatusPtr->demoButtonInput &= ~evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoSetButtons) {
    gGameStatusPtr->demoButtonInput = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoJoystickRadial) {
    Bytecode* args = script->ptrReadPos;
    f32 mag = evt_get_float_variable(script, *args++);
    f32 ang = evt_get_float_variable(script, *args++);

    gGameStatus.demoStickX = mag * sin_deg(ang);
    gGameStatus.demoStickY = mag * cos_deg(ang);

    return ApiStatus_DONE2;
}

API_CALLABLE(DemoJoystickXY) {
    Bytecode* args = script->ptrReadPos;
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);

    gGameStatus.demoStickX = x;
    gGameStatus.demoStickY = y;

    return ApiStatus_DONE2;
}
