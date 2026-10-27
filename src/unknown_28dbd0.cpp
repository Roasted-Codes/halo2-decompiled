// @flags /O2 /Gr /arch:SSE
#include "unknown_2551c0.h"
#include "unknown_20fe20.h"
#include "globals.h"
#include <math.h>
#include "vector_products.h"
#include "normalize3d.h"

struct s_28dbd3
{
	long field_0;
	s_type_c3b527 field_4;
	real field_14;
	real field_18;
	long field_1c;
	byte field_20[0x10];
	long field_30;
};

struct s_28dbd0
{
	byte field_0[0x1c];
	point3f field_1c;
	vector3f field_28;
	vector3f field_34;
	vector3f field_40;
	byte field_4c[0x68];
	word field_b4;
	word field_b6;
	byte field_b8[0xc4 - 0xb8];
};

struct s_effect_owner;
struct s_object_ai_data;
struct s_28dab2;
void function_b7930(void *arg_0, long arg_1, long arg_2, s_effect_owner const *arg_3);
long __stdcall function_b7b40(void *arg_0);
void __stdcall function_b8540(long arg_0);
void function_141ce0(real arg_0, real arg_1, real arg_2, transform4x3f *arg_3);
long function_1e06b0(long arg_0);
void swarm_creature_initialize(s_object_ai_data *arg_0);
bool function_28e320(long arg_0, long arg_1);
void swarm_creature_reset_position(long arg_0, s_object_ai_data *arg_1);

__forceinline void function_28dbd2(real arg_0, vector3f *arg_1, vector3f *arg_2)
{
	real local_0 = (real)sin(arg_0);
	real local_1 = (real)cos(arg_0);
	real local_2 = dot3f(arg_1, arg_2) * (1.0f - local_1);
	vector3f local_3;
	cross3f(arg_2, arg_1, &local_3);
	vector3f_scale(arg_1, local_2, arg_1);
	vector3f_scale(&local_3, local_0, &local_3);
	vector3f_scale(arg_2, local_1, arg_2);
	arg_2->i = arg_2->i + arg_1->i - local_3.i;
	arg_2->j = arg_2->j + arg_1->j - local_3.j;
	arg_2->k = arg_2->k + arg_1->k - local_3.k;
}

__forceinline void function_28dbd4(s_type_c3b527 const *arg_0, point3f *arg_1)
{
	if (arg_0->output_index == NONE || !function_2104b0(arg_0->output_index, &arg_0->point, arg_1))
		*arg_1 = arg_0->point;
}

__forceinline s_object_ai_data *function_28dbd5(s_handler_object_view *arg_0)
{
	s_object_ai_data *local_1;
	if (!arg_0->flags134)
		local_1 = (s_object_ai_data *)((byte *)arg_0 + arg_0->ai_offset);
	else
		local_1 = NULL;
	return local_1;
}

// score 186 (was 186): Frame 0x11c versus 0x118 and rotation scalar homes remain.
// Frame 0x11c versus 0x118; request home is four bytes late and rotation scalar homes differ.
// 0x11c frame versus 0x118 and rotation scalar spills remain; cross before trig 234f, alignment before trig 234f, shared velocity scale 213f, plain rotation component loop 234f, global optimization off 549f.
// Frame 0x11c versus retail 0x118 and rotation cross scalar homes remain.
// Earlier: 0x11c frame versus 0x118 and rotation scalar spills remain; cross before trig 234f, alignment before trig 234f, shared velocity scale 213f, plain rotation component loop 234f, global optimization off 549f.
// frame 0x11c versus 0x118 and rotation cross homes remain;
// cross before trig 234f, alignment before trig 234f, shared velocity scale 213f, plain rotation component loop 234f, global optimization off 549f.
// Frame 0x11c versus 0x118; rotation cross scalar homes remain.
// frame 0x11c versus 0x118 and rotation cross homes;
// named request word 213; complete creation-stage scope 213; random arm first
// 284; shared rotation output setter 226; size optimization 563.
// rotation axis input first 213; rotation output first 213; native rotation input copy 250; cosine complement
// lifetime 226; separate creation result 319; creation value initialization 353; frame pointer 304; float
// consistency 512.
// Shared-cross scalar captures 226; axis value 293; post-trig alignment 234;
// launch-speed name 213; tilt name 213; jitter base value 231;
// two offset component loops 479; transform memcpy 213.
// frame 0x11c versus 0x118 and rotation scalar homes remain;
// in-place input scale 260; in-place cross scale 229; both scales 232;
// ordinary rotation inline 213; forced shared cross 213; output-pointer result 213;
// result plus forced cross 213; result plus both scales 232.
// frame 0x11c/0x118 and rotation cross homes remain; completed scalar outputs 226; output orders jik/kij/jki/kji/ikj 223/195/222/237/216; double angle 216; output-angle-axis helper 213 (fast).
// Earlier 213 (was 213): frame 0x11c versus 0x118 and rotation scalar homes remain;
// Earlier 213 (was 213): frame 0x11c/0x118 and rotation cross homes remain; completed scalar outputs 226; output orders jik/kij/jki/kji/ikj 223/195/222/237/216; double angle 216; output-angle-axis helper 213 (fast).
// Earlier at 213 (from 213): frame 0x11c versus 0x118 and rotation scalar homes remain;
// Earlier at 213 (from 213): frame 0x11c/0x118 and rotation cross homes remain; completed scalar outputs 226; output orders jik/kij/jki/kji/ikj 223/195/222/237/216; double angle 216; output-angle-axis helper 213 (fast).
// Earlier at 213 (was 213): frame 0x11c versus 0x118 and rotation scalar homes remain;
// Earlier at 213 (was 213): frame 0x11c/0x118 and rotation cross homes remain; completed scalar outputs 226; output orders jik/kij/jki/kji/ikj 223/195/222/237/216; double angle 216; output-angle-axis helper 213 (fast).
// rotation cross spills and the extra frame dword remain;
// sine-weighted cross products 226; cosine-plus-projection sums 226;
// axis projection products 226; cosine products 226; rotation-helper names 213;
// cross/projection lexical homes 213; sine/cosine products 227; launch-offset products 213.
// Consumed-axis projection 222; with cross scale 222; with direction scale 200;
// all three shared scales 186 plain; corresponding native loops 230/229/231/235.
// Direct named pooled flag field 186 plain; the consumed axis is dead after its sole call.
// Round 225: Native vector result pointer/pointer, value/pointer, pointer/value, value/value,
// reference/pointer, pointer/reference, reference/reference 296/372/325/409/296/296/296; distinct input/output
// 296. Frames 12c/134; original restored.
// Round 227: Distinct shared-scale cosine/projection/cross outputs 241/224/233; paired outputs
// 246/252/225; all three 246; all three with native component output loop 246. Original helper, body
// and includes restored.
// Complete axis+direction inputs: unchanged terms 324; cosine/projection/turn
// terms 305/319/324; cosine+projection 338; cosine+turn 303; projection+turn 312;
// all weighted terms 342. Original helper and request restored.
// Round 330: Paired double trig 244; double projection 244; both 244; double launch speed 244; launch/trig
// 321; launch/projection 316; all three 322; existing double velocity scaler 245. Exact-match-only forms
// restored; adjacent helpers retained.
// Round 173: Consumed-axis shared-scale orders projection/direction/cross 190,
// cross/projection/direction 227, cross/direction/projection 236, direction/projection/cross 248,
// direction/cross/projection 252; early cross 234; early alignment 235; cosine first 227. Frame
// 0x11c versus 0x118 and rotation cross homes remain; original helper and all calls restored.
// Round 175: Consumed-axis reference axis/direction/both 186/186/186;
// axis value with pointer/reference direction 308/308; double trig input with
// pointer/axis-reference/both-reference inputs 188/188/188. Original helper restored.
// Round 177: Consumed-axis complete output by assignment/aggregate 287/287; native returned output with
// pointer/reference axis 297/297; complete scalar/cross role names 186/186; early cross storage
// with original/named scalars 186/186. Frame 0x11c versus 0x118 persists; all original code restored.
// Round 243: Delayed-sine schedules 187/187/180/212/209/212/209; output loop 230; scalar
// trig contracts 227/187/224/191. The 180 form fixes frame only, gains six and is
// rejected; 209 fixes frame and request homes. Original helper and body restored.
// @retail 0x28dbd0
long function_28dbd0(long arg_0, long arg_1, long arg_2, s_28dab2 const *arg_3, bool arg_4)
{
	long local_1 = NONE;
	s_28dbd3 const *local_4 = (s_28dbd3 const *)arg_3;
	s_28dbd0 local_0;
	function_b7930(&local_0, arg_2, NONE, NULL);
	function_28dbd4(&local_4->field_4, &local_0.field_1c);
	if (local_4->field_1c & 4)
	{
		transform4x3f local_1;
		function_141ce0(local_4->field_14, local_4->field_18, 0.0f, &local_1);
		local_0.field_28 = local_1.forward;
		local_0.field_34 = local_1.up;
	}
	else
	{
		real local_1 = function_259d0(&g_4e7408->unknown0, __FILE__, __LINE__, -3.1415927f, 3.1415927f);
		vector3f local_2;
		local_2.i = (real)cos(local_1);
		local_2.j = (real)sin(local_1);
		local_2.k = 0.0f;
		if (local_4->field_1c & 2)
		{
			real local_3 = function_259d0(&g_4e7408->unknown0, __FILE__, __LINE__, 2.0f, 3.0f);
			real local_4 = function_259d0(&g_4e7408->unknown0, __FILE__, __LINE__, 0.2617994f, 1.5707964f);
			local_0.field_28 = local_2;
			vector3f local_5;
			cross3f(&local_2, g_4687b0, &local_5);
			function_28dbd2(local_4, &local_5, &local_2);
			local_0.field_1c.x += local_2.i * 0.1f;
			local_0.field_1c.y += local_2.j * 0.1f;
			local_0.field_1c.z += local_2.k * 0.1f;
			local_0.field_1c.x += g_4687b0->i * 0.1f;
			local_0.field_1c.y += g_4687b0->j * 0.1f;
			local_0.field_1c.z += g_4687b0->k * 0.1f;
			local_0.field_40.i = local_2.i * local_3;
			local_0.field_40.j = local_2.j * local_3;
			local_0.field_40.k = local_2.k * local_3;
		}
		else
		{
			if (!arg_4)
			{
				real local_3 = function_259d0(&g_4e7408->unknown0, __FILE__, __LINE__, -0.5f, 0.5f);
				real local_4 = function_259d0(&g_4e7408->unknown0, __FILE__, __LINE__, -0.5f, 0.5f);
				local_0.field_1c.x += local_3;
				local_0.field_1c.y += local_4;
			}
			local_0.field_28 = local_2;
		}
	}
	if (!local_4->field_30)
		*(long *)((byte *)&local_0 + 0xc) = function_1e06b0(arg_1);
	else
		*(long *)((byte *)&local_0 + 0xc) = local_4->field_30;
	local_0.field_b4 = 0;
	local_0.field_b6 = 0xb0;
	local_1 = function_b7b40(&local_0);
	if (local_1 != NONE)
	{
		s_handler_object_view *local_2 = handler_object_get(local_1);
		s_object_ai_data *local_3 = function_28dbd5(local_2);
		if (local_3)
		{
			swarm_creature_initialize(local_3);
			if (function_28e320(arg_0, local_1))
			{
				swarm_creature_reset_position(local_1, local_3);
				goto local_6;
			}
		}
		function_b8540(local_1);
		local_1 = NONE;
	}
local_6:
	return local_1;
}
