#include "common.h"
#include "model.h"


s32 test_ray_zones(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX, f32* hitY, f32* hitZ,
                   f32* hitDepth, f32* nx, f32* ny, f32* nz);
s32 test_ray_colliders(s32 ignoreFlags, f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX,
                       f32* hitY, f32* hitZ, f32* hitDepth, f32* hitNx, f32* hitNy, f32* hitNz);

/// Test a general ray from a given starting position and direction against all entities.
/// If one is hit, returns the position and normal of the hit and the length along the ray
/// via the output parameters. All output parameters are invalid when `NO_COLLIDER` is returned.
///
/// `startX`/`startY`/`startZ` are the ray origin. `dirX`/`dirY`/`dirZ` are the normalized
/// ray direction. `hitX`/`hitY`/`hitZ` receive the hit position. `hitNx`/`hitNy`/`hitNz`
/// receive the hit normal. `hitDepth` is both input (maximum ray length) and output (distance
/// to the hit).
///
/// Returns entity index or `NO_COLLIDER` if none is hit.
s32 test_ray_entities(f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX, f32* hitY, f32* hitZ,
                      f32* hitDepth, f32* hitNx, f32* hitNy, f32* hitNz);
