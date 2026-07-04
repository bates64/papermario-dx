#include "common.h"

API_CALLABLE(GetDist2D) {
    Bytecode* args = script->ptrReadPos;
    Bytecode outVar = *args++;
    f32 ax = evt_get_float_variable(script, *args++);
    f32 ay = evt_get_float_variable(script, *args++);
    f32 bx = evt_get_float_variable(script, *args++);
    f32 by = evt_get_float_variable(script, *args++);

    evt_set_float_variable(script, outVar, dist2D(ax, ay, bx, by));

    return ApiStatus_DONE2;
}

API_CALLABLE(GetDist3D) {
    Bytecode* args = script->ptrReadPos;
    Bytecode outVar = *args++;
    s32 ax = evt_get_variable(script, *args++);
    s32 ay = evt_get_variable(script, *args++);
    s32 az = evt_get_variable(script, *args++);
    s32 bx = evt_get_variable(script, *args++);
    s32 by = evt_get_variable(script, *args++);
    s32 bz = evt_get_variable(script, *args++);
    f32 dx = ax - bx;
    f32 dy = ay - by;
    f32 dz = az - bz;

    evt_set_variable(script, outVar, sqrtf(SQ(dx) + SQ(dy) + SQ(dz)));

    return ApiStatus_DONE2;
}

API_CALLABLE(ClampAngleInt) {
    Bytecode* args = script->ptrReadPos;
    Bytecode inOutVar = *args++;
    s32 angle = evt_get_variable(script, inOutVar);

    evt_set_variable(script, inOutVar, clamp_angle(angle));

    return ApiStatus_DONE2;
}

API_CALLABLE(ClampAngleFloat) {
    Bytecode* args = script->ptrReadPos;
    Bytecode inOutVar = *args++;
    f32 angle = evt_get_float_variable(script, inOutVar);

    evt_set_float_variable(script, inOutVar, clamp_angle(angle));

    return ApiStatus_DONE2;
}

API_CALLABLE(AddVectorPolar) {
    Bytecode* args = script->ptrReadPos;

    Bytecode xVar = *args++;
    Bytecode yVar = *args++;

    f32 x = evt_get_float_variable(script, xVar);
    f32 y = evt_get_float_variable(script, yVar);
    f32 r = evt_get_float_variable(script, *args++);
    f32 theta = evt_get_float_variable(script, *args++);

    add_vec2D_polar(&x, &y, r, theta);

    evt_set_float_variable(script, xVar, x);
    evt_set_float_variable(script, yVar, y);

    return ApiStatus_DONE2;
}

API_CALLABLE(GetAngleBetweenPoints) {
    Bytecode* args = script->ptrReadPos;
    Bytecode outVar = *args++;
    f32 x1 = evt_get_float_variable(script, *args++);
    f32 z1 = evt_get_float_variable(script, *args++);
    f32 x2 = evt_get_float_variable(script, *args++);
    f32 z2 = evt_get_float_variable(script, *args++);
    f32 angle = atan2(x1, z1, x2, z2);

    evt_set_variable(script, outVar, angle);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetFloatAngleClamped) {
    Bytecode* args = script->ptrReadPos;
    Bytecode outVar = *args++;
    f32 x1 = evt_get_float_variable(script, *args++);
    f32 z1 = evt_get_float_variable(script, *args++);
    f32 x2 = evt_get_float_variable(script, *args++);
    f32 z2 = evt_get_float_variable(script, *args++);
    f32 angle = clamp_angle(atan2(x1, z1, x2, z2));

    evt_set_float_variable(script, outVar, angle);
    return ApiStatus_DONE2;
}

API_CALLABLE(RandInt) {
    Bytecode* args = script->ptrReadPos;

    s32 max = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    evt_set_variable(script, outVar, rand_int(max));

    return ApiStatus_DONE2;
}

enum {
    LERP_VAR_0 = 0x0, // (out float) cur
    LERP_VAR_1 = 0x1, // (out bool) in-progress
    LERP_VAR_B = 0xB, // mode
    LERP_VAR_C = 0xC, // start
    LERP_VAR_D = 0xD, // end
    LERP_VAR_E = 0xE, // elapsed
    LERP_VAR_F = 0xF, // duration
};

// args: start, end, duration, EasingType
API_CALLABLE(MakeLerp) {
    Bytecode* ptrReadPos = script->ptrReadPos;

    script->varTable[LERP_VAR_C] = evt_get_variable(script, *ptrReadPos++); // start
    script->varTable[LERP_VAR_D] = evt_get_variable(script, *ptrReadPos++); // end
    script->varTable[LERP_VAR_F] = evt_get_variable(script, *ptrReadPos++); // duration
    script->varTable[LERP_VAR_B] = evt_get_variable(script, *ptrReadPos++); // easing type
    script->varTable[LERP_VAR_E] = 0; // elapsed

    return ApiStatus_DONE2;
}

API_CALLABLE(UpdateLerp) {
    evt_set_variable(script, LocalVar(LERP_VAR_0), update_lerp(
        script->varTable[LERP_VAR_B],
        script->varTable[LERP_VAR_C],
        script->varTable[LERP_VAR_D],
        script->varTable[LERP_VAR_E],
        script->varTable[LERP_VAR_F]
    ));

    if (script->varTable[LERP_VAR_E] >= script->varTable[LERP_VAR_F]) {
        script->varTable[LERP_VAR_1] = false; // finished
    } else {
        script->varTable[LERP_VAR_1] = true; // lerping
    }
    script->varTable[LERP_VAR_E]++;

    return ApiStatus_DONE2;
}

API_CALLABLE(CosInterpMinMax) {
    Bytecode* args = script->ptrReadPos;
    s32 outVarTime = *args++;
    s32 time = evt_get_variable(script, outVarTime);
    s32 outValue = *args++;
    f32 min = evt_get_float_variable(script, *args++);
    f32 max = evt_get_float_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);
    s32 onlyOnce = evt_get_variable(script, *args++);
    f32 phaseOffset = (evt_get_float_variable(script, *args++) / 180.0f) * PI;
    f32 delta = (max - min) / 2;

    if (onlyOnce && duration < time) {
        time = duration;
        evt_set_variable(script, outVarTime, duration);
    }

    evt_set_float_variable(script, outValue,
        (min + delta) // average value
        - (delta * cos_rad(((time * PI) / duration) + phaseOffset))); // perturbation

    return ApiStatus_DONE2;
}

// precomputes a natural cubic spline through `pathPositions` to be used by `sample_spline_path`
void calc_spline_path(s32 num, f32* normalizedLengths, Vec3f* pathPositions, Vec3f* outVectors) {
    f32* lenBuf = heap_malloc(num * sizeof(f32));
    Vec3f* vecBuf = heap_malloc(num * sizeof(Vec3f));
    s32 i;

    // compute the distance of each vector along the path and map to the range [0,1]
    normalizedLengths[0] = 0.0f;
    for (i = 1; i < num; i++) {
        f32 dx = pathPositions[i].x - pathPositions[i-1].x;
        f32 dy = pathPositions[i].y - pathPositions[i-1].y;
        f32 dz = pathPositions[i].z - pathPositions[i-1].z;
        f32 length = sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
        normalizedLengths[i] = normalizedLengths[i-1] + length;
    }
    for (i = 1; i < num; i++) {
        normalizedLengths[i] /= normalizedLengths[num-1];
    }

    // end points
    outVectors[0].x = 0.0f;
    outVectors[0].y = 0.0f;
    outVectors[0].z = 0.0f;
    outVectors[num-1].x = 0.0f;
    outVectors[num-1].y = 0.0f;
    outVectors[num-1].z = 0.0f;

    for (i = 0; i < num - 1; i++) {
        lenBuf[i] = normalizedLengths[i+1] - normalizedLengths[i];
        vecBuf[i+1].x = (pathPositions[i+1].x - pathPositions[i].x) / lenBuf[i];
        vecBuf[i+1].y = (pathPositions[i+1].y - pathPositions[i].y) / lenBuf[i];
        vecBuf[i+1].z = (pathPositions[i+1].z - pathPositions[i].z) / lenBuf[i];
    }

    // n = 1
    outVectors[1].x = vecBuf[2].x - vecBuf[1].x;
    outVectors[1].y = vecBuf[2].y - vecBuf[1].y;
    outVectors[1].z = vecBuf[2].z - vecBuf[1].z;
    vecBuf[1].x = 2.0f * (normalizedLengths[2] - normalizedLengths[0]);
    vecBuf[1].y = 2.0f * (normalizedLengths[2] - normalizedLengths[0]);
    vecBuf[1].z = 2.0f * (normalizedLengths[2] - normalizedLengths[0]);

    // 1 < n < N - 2
    for (i = 1; i < num - 2; i++) {
        f32 sx = lenBuf[i] / vecBuf[i].x;
        f32 sy = lenBuf[i] / vecBuf[i].y;
        f32 sz = lenBuf[i] / vecBuf[i].z;
        outVectors[i+1].x = (vecBuf[i+2].x - vecBuf[i+1].x) - outVectors[i].x * sx;
        outVectors[i+1].y = (vecBuf[i+2].y - vecBuf[i+1].y) - outVectors[i].y * sy;
        outVectors[i+1].z = (vecBuf[i+2].z - vecBuf[i+1].z) - outVectors[i].z * sz;
        vecBuf[i+1].x = 2.0f * (normalizedLengths[i+2] - normalizedLengths[i]) - lenBuf[i] * sx;
        vecBuf[i+1].y = 2.0f * (normalizedLengths[i+2] - normalizedLengths[i]) - lenBuf[i] * sy;
        vecBuf[i+1].z = 2.0f * (normalizedLengths[i+2] - normalizedLengths[i]) - lenBuf[i] * sz;
    }

    // n = N - 2
    outVectors[num-2].x -= (lenBuf[num-2] * outVectors[num-1].x);
    outVectors[num-2].y -= (lenBuf[num-2] * outVectors[num-1].y);
    outVectors[num-2].z -= (lenBuf[num-2] * outVectors[num-1].z);

    for (i = num - 2; i > 0; i--) {
        outVectors[i].x = (outVectors[i].x - (lenBuf[i] * outVectors[i+1].x)) / vecBuf[i].x;
        outVectors[i].y = (outVectors[i].y - (lenBuf[i] * outVectors[i+1].y)) / vecBuf[i].y;
        outVectors[i].z = (outVectors[i].z - (lenBuf[i] * outVectors[i+1].z)) / vecBuf[i].z;
    }

    heap_free(lenBuf);
    heap_free(vecBuf);
}

void sample_spline_path(f32 alpha, Vec3f* outPos, s32 numVectors, f32* normalizedLengths, Vec3f* pathPoints, Vec3f* vectors) {
    s32 limit = numVectors - 1;
    f32 curLength;
    f32 curProgress;
    f32 ax, ay, az, bx, by, bz, dx, dy, dz;
    s32 i;

    // binary search the normalized length table
    for (i = 0; i < limit;) {
        s32 searchIdx = (i + limit) / 2;

        if (normalizedLengths[searchIdx] < alpha) {
            i = searchIdx + 1;
        } else {
            limit = searchIdx;
        }
    }

    if (i > 0) {
        i--;
    }

    curLength = normalizedLengths[i+1] - normalizedLengths[i];
    curProgress = alpha - normalizedLengths[i];

    dx = (pathPoints[i+1].x - pathPoints[i].x) / curLength;
    ax = (((vectors[i+1].x - vectors[i].x) * curProgress / curLength) + (3.0f * vectors[i].x)) * curProgress;
    bx = dx - (((2.0f * vectors[i].x) + vectors[i+1].x) * curLength);
    outPos->x = ((ax + bx) * curProgress) + pathPoints[i].x;

    dy = (pathPoints[i+1].y - pathPoints[i].y) / curLength;
    ay = (((vectors[i+1].y - vectors[i].y) * curProgress / curLength) + (3.0f * vectors[i].y)) * curProgress;
    by = dy - (((2.0f * vectors[i].y) + vectors[i+1].y) * curLength);
    outPos->y = ((ay + by) * curProgress) + pathPoints[i].y;

    dz = (pathPoints[i+1].z - pathPoints[i].z) / curLength;
    az = (((vectors[i+1].z - vectors[i].z) * curProgress / curLength) + (3.0f * vectors[i].z)) * curProgress;
    bz = dz - (((2.0f * vectors[i].z) + vectors[i+1].z) * curLength);
    outPos->z = ((az + bz) * curProgress) + pathPoints[i].z;
}

API_CALLABLE(LoadPath) {
    Bytecode* args = script->ptrReadPos;
    s32 time = evt_get_variable(script, *args++);
    Vec3f* vectorList = (Vec3f*) evt_get_variable(script, *args++);
    s32 numVectors = evt_get_variable(script, *args++);
    s32 easingType = evt_get_variable(script, *args++);
    Path* path = heap_malloc(sizeof(*path));

    script->varTablePtr[15] = path;
    path->numVectors = numVectors;
    path->lengths = heap_malloc(numVectors * sizeof(f32));
    path->staticVectorList = vectorList;
    path->vectors = heap_malloc(numVectors * sizeof(Vec3f));
    calc_spline_path(path->numVectors, path->lengths, path->staticVectorList, path->vectors);

    path->timeElapsed = 0;
    path->timeLeft = time - 1;
    path->easingType = easingType;

    return ApiStatus_DONE2;
}

API_CALLABLE(GetNextPathPos) {
    Path* path = script->varTablePtr[15];
    Vec3f pos;
    f32 alpha;
    f32 diff;

    switch (path->easingType) {
        case EASING_LINEAR:
            alpha = 1.0f / path->timeLeft * path->timeElapsed;
            break;
        case EASING_QUADRATIC_IN:
            alpha = 1.0f / SQ(path->timeLeft) * SQ(path->timeElapsed);
            break;
        case EASING_QUADRATIC_OUT:
            diff = path->timeLeft - path->timeElapsed;
            alpha = 1.0f - (SQ(diff) / SQ(path->timeLeft));
            break;
        case EASING_COS_IN_OUT:
            alpha = (1.0f - cos_rad((PI / path->timeLeft) * path->timeElapsed)) * 0.5f;
            break;
        default:
            alpha = 0.0f;
            break;
    }

    sample_spline_path(alpha, &pos, path->numVectors, path->lengths, path->staticVectorList, path->vectors);
    script->varTable[1] = FLOAT_TO_FIXED(pos.x);
    script->varTable[2] = FLOAT_TO_FIXED(pos.y);
    script->varTable[3] = FLOAT_TO_FIXED(pos.z);

    if (path->timeElapsed < path->timeLeft) {
        path->timeElapsed = path->timeElapsed + 1;
        script->varTable[0] = 1;
    } else {
        heap_free(path->lengths);
        heap_free(path->vectors);
        heap_free(script->varTablePtr[15]);
        script->varTable[0] = 0;
    }

    return ApiStatus_DONE2;
}

f32 sin_lookup_table[] = {
    0.000000f, 0.017452f, 0.034899f, 0.052336f, 0.069756f, 0.087156f, 0.104528f, 0.121869f,
    0.139173f, 0.156434f, 0.173648f, 0.190809f, 0.207912f, 0.224951f, 0.241922f, 0.258819f,
    0.275637f, 0.292372f, 0.309017f, 0.325568f, 0.342020f, 0.358368f, 0.374607f, 0.390731f,
    0.406737f, 0.422618f, 0.438371f, 0.453990f, 0.469472f, 0.484810f, 0.500000f, 0.515038f,
    0.529919f, 0.544639f, 0.559193f, 0.573576f, 0.587785f, 0.601815f, 0.615661f, 0.629320f,
    0.642788f, 0.656059f, 0.669131f, 0.681998f, 0.694658f, 0.707107f, 0.719340f, 0.731354f,
    0.743145f, 0.754710f, 0.766044f, 0.777146f, 0.788011f, 0.798636f, 0.809017f, 0.819152f,
    0.829038f, 0.838671f, 0.848048f, 0.857167f, 0.866025f, 0.874620f, 0.882948f, 0.891007f,
    0.898794f, 0.906308f, 0.913545f, 0.920505f, 0.927184f, 0.933580f, 0.939693f, 0.945519f,
    0.951057f, 0.956305f, 0.961262f, 0.965926f, 0.970296f, 0.974370f, 0.978148f, 0.981627f,
    0.984808f, 0.987688f, 0.990268f, 0.992546f, 0.994522f, 0.996195f, 0.997564f, 0.998630f,
    0.999391f, 0.999848f, 1.000000f,
};

u32 calc_vector_rot_impl(f32 dx, f32 dy) {
    // use trig identity to get sin(theta) = dy / hypot
    f32 sinAngle = abs(dy) / length2D(dx, dy);
    u16 minAngle = 0;
    u16 maxAngle = 90;
    u16 ret;
    u16 i;

    // obtain theta from value of sin(theta) via lookup table with one entry per angle
    // binary search needs 7 iterations because the table has 91 entries and 2^7 > 91 > 2^6
    for (i = 0; i < 7; i++) {
        u16 midAngle = minAngle + ((maxAngle - minAngle) / 2);

        if (sin_lookup_table[midAngle] < sinAngle) {
            minAngle = midAngle;
        } else {
            maxAngle = midAngle;
        }
    }

    // choose whichever is closer
    if (fabsf(sin_lookup_table[minAngle] - sinAngle) < fabsf(sin_lookup_table[maxAngle] - sinAngle)) {
        ret = minAngle;
    } else {
        ret = maxAngle;
    }

    if (dx < 0.0f && dy >= 0.0f) {
        ret = 180 - ret;
    }

    if (dx < 0.0f && dy < 0.0f) {
        ret += 180;
    }

    if (dx >= 0.0f && dy < 0.0f) {
        ret = 360 - ret;
    }

    return ret;
}

API_CALLABLE(CalcActorRotation) {
    Bytecode* args = script->ptrReadPos;
    Bytecode outVar = *args++;
    s32 x1 = evt_get_variable(script, *args++);
    s32 y1 = evt_get_variable(script, *args++);
    s32 x2 = evt_get_variable(script, *args++);
    s32 y2 = evt_get_variable(script, *args++);
    s32 dx = x2 - x1;
    s32 dy = y2 - y1;

    if ((dx != 0) || (dy != 0)) {
        evt_set_variable(script, outVar, calc_vector_rot_impl(dx, dy) - 90);
    }

    return ApiStatus_DONE2;
}
