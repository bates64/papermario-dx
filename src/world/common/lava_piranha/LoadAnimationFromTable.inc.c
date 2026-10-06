typedef struct VineBuffer {
    u8* data;
    u32 capacity;
} VineBuffer;

API_CALLABLE(LoadAnimationFromTable) {
    static const VineBuffer buffers[NUM_VINES] = {
        [VINE_0] = { D_80200000, sizeof(D_80200000) },
        [VINE_1] = { D_80204000, sizeof(D_80204000) },
        [VINE_2] = { D_80207000, sizeof(D_80207000) },
        [VINE_3] = { D_8020A000, sizeof(D_8020A000) },
    };
    Bytecode* args = script->ptrReadPos;
    s32 type = evt_get_variable(script, *args++);
    s32 index = evt_get_variable(script, *args++);
    u32 start;
    u32 end;
    u32 size;

    ASSERT_MSG((u32)type < ARRAY_COUNT(buffers), "Invalid vine buffer %ld", type);
    ASSERT_MSG((u32)index < ARRAY_COUNT(VineAnimationsDmaTable) / 3, "Invalid vine animation %ld", index);
    start = (u32)VineAnimationsDmaTable[3 * index + 0];
    end = (u32)VineAnimationsDmaTable[3 * index + 1];
    size = end - start;
    ASSERT_MSG(end > start && size <= buffers[type].capacity,
        "Vine animation %ld (%lu bytes) does not fit buffer %ld", index, size, type);

    dma_copy((u8*) start, (u8*) end, buffers[type].data);
    return ApiStatus_DONE2;
}
