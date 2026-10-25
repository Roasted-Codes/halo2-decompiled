// @flags /O2 /arch:SSE /Gr
#include "projection_storage.h"
#include "unknown_11c920.h"
#include "camera_storage.h"
#include "unknown_0259d0.h"
#include "unknown_030290.h"
#include <math.h>
#include <string.h>

real function_30bf0(vector3f *arg_0);

struct s_501e0
{
    point3f field_0;
    real field_c;
    real field_10;
    dword field_14;
};

static __forceinline void world_vector_to_view(real arg_0, vector3f const *arg_1, vector3f *arg_2)
{
    real local_0 = arg_1->i;
    real local_1 = arg_1->j;
    real local_2 = arg_1->k;
    if (arg_0 != 1.f)
    {
        local_0 = arg_0 * local_0;
        local_1 = arg_0 * local_1;
        local_2 = arg_0 * local_2;
    }
    for (long component = 0; component < 3; ++component)
        arg_2->n[component] = g_4b9e14.forward.n[component] * local_2 + g_4b9e14.up.n[component] * local_1 + g_4b9e14.right.n[component] * local_0;
}

// score 255 (was 255): frame 0x20 versus 0x14 and transform coefficient/result registers differ.
// Global optimization off 961; depth zero 555; frame pointer 300;
// input-first products 255; k/j/i transform output 272.
// score 227 (was 255): frame 0x18 versus 0x14; coefficient/result registers and tail differ.
// Offset/transform/blend loops 315/291/255; paired loops 237; depth bounds 237; both 227.
// Paired loops with blend/unsigned/in-place 236/237/287;
// scoped bounds 230; literal zero 227; bound scalar homes 227 (plain).
// @retail 0x501e0
void function_501e0(s_501e0 const *arg_0, bool arg_1, s_501e0 *arg_2)
{
    real local_14 = 0.f;
    vector3f local_0;
    vector3f local_1;
    for (long component = 0; component < 3; ++component)
    {
        local_0.n[component] = arg_0[0].field_0.n[component] - g_4b9da0.n[component];
        local_1.n[component] = arg_0[1].field_0.n[component] - g_4b9da0.n[component];
    }
    vector3f local_2;
    vector3f local_3;
    world_vector_to_view(g_4b9e14.scale, &local_0, &local_2);
    world_vector_to_view(g_4b9e14.scale, &local_1, &local_3);
    real first_depth_limit = local_2.k * local_2.k * 4.f;
    real second_depth_limit = local_3.k * local_3.k * 4.f;
    if (local_2.k < 0.f && local_3.k < 0.f &&
        first_depth_limit > local_2.i * local_2.i &&
        first_depth_limit > local_2.j * local_2.j &&
        second_depth_limit > local_3.i * local_3.i &&
        second_depth_limit > local_3.j * local_3.j)
    {
        real local_4 = local_14 - local_2.k;
        real local_5 = local_14 - local_3.k;
        real local_6;
        if (arg_1)
            local_6 = 1.f / (local_5 + local_4);
        else
        {
            local_4 = 1.f;
            local_5 = 1.f;
            local_6 = 0.5f;
        }
        arg_2->field_0.x = (arg_0[1].field_0.x * local_4 + arg_0[0].field_0.x * local_5) * local_6;
        arg_2->field_0.y = (arg_0[1].field_0.y * local_4 + arg_0[0].field_0.y * local_5) * local_6;
        arg_2->field_0.z = (arg_0[1].field_0.z * local_4 + arg_0[0].field_0.z * local_5) * local_6;
        arg_2->field_c = (arg_0[1].field_c + arg_0[0].field_c) * 0.5f;
        arg_2->field_10 = (arg_0[1].field_10 + arg_0[0].field_10) * 0.5f;
        arg_2->field_14 = arg_0[0].field_14;
        if (arg_1)
        {
            real local_7 = (local_3.i * local_4 - local_2.i * local_5) * 2.f;
            real local_8 = (local_3.j * local_4 - local_2.j * local_5) * 2.f;
            real local_9 = local_8 * local_8 + local_7 * local_7;
            if (local_9 >= 0.f)
                arg_2->field_c = (real)(sqrt(local_9) * arg_2->field_c * local_6);
        }
        else
        {
            vector3f local_10;
            local_10.i = arg_0[1].field_0.x - arg_0[0].field_0.x;
            local_10.j = arg_0[1].field_0.y - arg_0[0].field_0.y;
            local_10.k = arg_0[1].field_0.z - arg_0[0].field_0.z;
            real local_11 = function_30bf0(&local_10);
            real local_12 = g_4b9dac.j * local_10.j;
            local_12 = g_4b9dac.k * local_10.k + local_12;
            local_12 += local_10.i * g_4b9dac.i;
            real local_13 = 1.f - local_12 * local_12;
            local_13 = local_13 < 0.f ? 0.f : local_13 > 1.f ? 1.f : local_13;
            arg_2->field_c = (real)(sqrt(local_13) * arg_2->field_c * local_11);
        }
    }
    else
    {
        memset(arg_2, 0, sizeof(*arg_2));
    }
}
