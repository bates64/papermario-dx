#include "common.h"
#include "model.h"


s32 test_ray_zones(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX, f32* hitY, f32* hitZ,
                   f32* hitDepth, f32* nx, f32* ny, f32* nz);
s32 test_ray_colliders(s32 ignoreFlags, f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX,
                       f32* hitY, f32* hitZ, f32* hitDepth, f32* hitNx, f32* hitNy, f32* hitNz);

/// Test a general ray from a given starting position and direction against all entities.
/// If one is hit, returns the position and normal of the hit and the length along the ray on the output params.
/// All output params are invalid when a value of `NO_COLLIDER` is returned.
/// @param startX origin x position of the ray
/// @param startY origin y position of the ray
/// @param startZ origin z position of the ray
/// @param dirX normalized x direction of the ray
/// @param dirY normalized y direction of the ray
/// @param dirZ normalized z direction of the ray
/// @param[out] hitX normalized x position of the hit
/// @param[out] hitY normalized y position of the hit
/// @param[out] hitZ normalized z position of the hit
/// @param[in,out] hitDepth as input, maximum length of the ray; as output, distance along the ray of the hit
/// @param[out] hitNx x normal direction of the hit
/// @param[out] hitNy y normal direction of the hit
/// @param[out] hitNz z normal direction of the hit
/// @returns entity index or `NO_COLLIDER` is none is hit
s32 test_ray_entities(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX, f32* hitY, f32* hitZ,
                      f32* hitDepth, f32* hitNx, f32* hitNy, f32* hitNz);
