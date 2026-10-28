// @flags /O2 /Ob1 /GL-
#include "constraint_helpers_314090.h"
#include <stddef.h>
#include <float.h>
#include <math.h>

typedef char snapshot3_size[(sizeof(c_component_joint_snapshot_3) == 0x40) ? 1 : -1];
typedef char snapshot4_size[(sizeof(c_component_joint_snapshot_4) == 0x30) ? 1 : -1];
typedef char snapshot5_size[(sizeof(c_component_joint_snapshot_5) == 0xa0) ? 1 : -1];
typedef char motion_description_size[(sizeof(s_314320) == 0x14) ? 1 : -1];
typedef char motion_object_size[(sizeof(c_314710) == 0x60) ? 1 : -1];
typedef char motion_distance_offset[(offsetof(motion_limits_view_314450, distance_a) == 0x50) ? 1 : -1];
typedef char ball_results_offset[(offsetof(ball_socket_view_314090, results) == 0x40) ? 1 : -1];
typedef char spring_results_offset[(offsetof(spring_view_314830, results) == 0x44) ? 1 : -1];
typedef char prismatic_results_offset[(offsetof(prismatic_view_314b80, results) == 0xac) ? 1 : -1];

// @retail 0x3140c0
c_component_joint_snapshot_4::c_component_joint_snapshot_4()
{
	pivot_a = _mm_setzero_ps();
	pivot_b = _mm_setzero_ps();
}
// @retail 0x314860
c_component_joint_snapshot_3::c_component_joint_snapshot_3()
{
	pivot_a = _mm_setzero_ps();
	pivot_b = _mm_setzero_ps();
	length = 0.0f;
}
// Score 12: the compiler moves the frame's zero/identity stores ahead of the
// five preceding vector clears. All offsets, values and the base call agree.
// Stop here: the remaining difference is instruction scheduling.
// @retail 0x314bb0
c_component_joint_snapshot_5::c_component_joint_snapshot_5()
{
	pivot_a = _mm_setzero_ps();
	pivot_b = _mm_setzero_ps();
	axis_a = _mm_setzero_ps();
	axis_b = _mm_setzero_ps();
	perpendicular_b = _mm_setzero_ps();
	frame_b[0] = _mm_setzero_ps();
	frame_b[1] = _mm_setzero_ps();
	frame_b[2] = _mm_setzero_ps();
	frame_b[0].m128_f32[0] = 1.0f;
	frame_b[1].m128_f32[1] = 1.0f;
	frame_b[2].m128_f32[2] = 1.0f;
	minimum = -FLT_MAX;
	maximum = FLT_MAX;
	friction = 0.0f;
}
// @retail 0x3141c0
void c_component_joint_reader_4::read(c_component_joint_snapshot_4 *output)
{
	((lane_a_constraint *)this)->export_base((lane_a_constraint_description *)output);
	ball_socket_view_314090 const *object = (ball_socket_view_314090 const *)this;
	output->pivot_a = object->pivot_a;
	output->pivot_b = object->pivot_b;
}
// @retail 0x3142f0
void ball_socket_view_314090::import_description(c_component_joint_snapshot_4 const *description)
{
	((lane_a_constraint *)this)->import_base((lane_a_constraint_description const *)description);
	pivot_a = description->pivot_a;
	pivot_b = description->pivot_b;
}
// @retail 0x3141b0
lane_a_solver_result *ball_socket_view_314090::runtime() { return results; }
// @retail 0x3141f0
void ball_socket_view_314090::info(lane_a_constraint_info *output) const
{
	output->maximum = 0;
	output->result_bytes = 0x24;
	output->op_bytes = 0x90;
	output->result_count = 3;
}
// @retail 0x314980
void spring_view_314830::export_description(c_component_joint_snapshot_3 *description) const
{
	((lane_a_constraint const *)this)->export_base((lane_a_constraint_description *)description);
	description->pivot_a = pivot_a;
	description->pivot_b = pivot_b;
	description->length = length;
}
// @retail 0x314b50
void spring_view_314830::import_description(c_component_joint_snapshot_3 const *description)
{
	((lane_a_constraint *)this)->import_base((lane_a_constraint_description const *)description);
	pivot_a = description->pivot_a;
	pivot_b = description->pivot_b;
	length = description->length;
}
// @retail 0x314950
lane_a_solver_result *spring_view_314830::runtime() { return results; }
// @retail 0x314960
bool_result_2da7f0 spring_view_314830::valid() const
{
	if (length <= 0.0f) return false;
	return true;
}
// @retail 0x3149b0
void spring_view_314830::info(lane_a_constraint_info *output) const
{
	output->maximum = 0;
	output->result_bytes = 0x1c;
	output->op_bytes = 0x30;
	output->result_count = 1;
}
// Score 9: the virtual-table load is scheduled before the last vector copies;
// retail reads it after loading the final scalar. The 126-byte extent and
// field copies agree. The virtual call still uses the valid() slot at +0x1c.
// @retail 0x314cd0
void prismatic_view_314b80::import_fields(c_component_joint_snapshot_5 const *description)
{
	pivot_a = description->pivot_a;
	pivot_b = description->pivot_b;
	axis_a = description->axis_a;
	axis_b = description->axis_b;
	minimum = description->minimum;
	maximum = description->maximum;
	perpendicular_b = description->perpendicular_b;
	frame_b[0] = description->frame_b[0];
	frame_b[1] = description->frame_b[1];
	frame_b[2] = description->frame_b[2];
	friction = description->friction;
	((lane_a_constraint *)this)->valid();
}
// @retail 0x314d50
void prismatic_view_314b80::export_description(c_component_joint_snapshot_5 *description) const
{
	((lane_a_constraint const *)this)->export_base((lane_a_constraint_description *)description);
	description->pivot_a = pivot_a;
	description->pivot_b = pivot_b;
	description->axis_a = axis_a;
	description->axis_b = axis_b;
	description->minimum = minimum;
	description->maximum = maximum;
	description->perpendicular_b = perpendicular_b;
	description->frame_b[0] = frame_b[0];
	description->frame_b[1] = frame_b[1];
	description->frame_b[2] = frame_b[2];
	description->friction = friction;
}
// @retail 0x314fa0
void prismatic_view_314b80::import_description(c_component_joint_snapshot_5 const *description)
{
	((lane_a_constraint *)this)->import_base((lane_a_constraint_description const *)description);
	import_fields(description);
}
// @retail 0x314cc0
lane_a_solver_result *prismatic_view_314b80::runtime() { return results; }
// @retail 0x314dd0
void prismatic_view_314b80::info(lane_a_constraint_info *output) const
{
	output->maximum = 0;
	output->result_bytes = 0x40;
	output->op_bytes = 0x120;
	output->result_count = 7;
}
// @retail 0x314320
s_314320::s_314320()
{
	*(float *)&field_0 = -1.0f;
	field_4 = 0.01f;
	field_8 = 0.005f;
	field_c = 0.1f;
	field_10 = 0.2f;
}
// @retail 0x314450
void s_314450::function_314450(s_314320 *output)
{
	motion_limits_view_314450 const *object = (motion_limits_view_314450 const *)this;
	output->field_4 = object->distance_a;
	output->field_8 = object->angle_a;
	output->field_c = object->distance_b;
	output->field_10 = object->angle_b;
	output->field_0 = *(long const *)&object->radius_squared;
}
// @retail 0x314480
void s_314450::function_314480(s_314320 const *input)
{
	motion_limits_view_314450 *object = (motion_limits_view_314450 *)this;
	object->distance_a = input->field_4;
	object->angle_a = input->field_8;
	object->distance_b = input->field_c;
	object->angle_b = input->field_10;
	object->radius_squared = *(float const *)&input->field_0;
}

// Serialization callbacks use the standard cdecl convention.
// @retail 0x314090
void __cdecl export_ball_socket_314090(c_component_joint_reader_4 *object, c_component_joint_snapshot_4 *description)
{ object->read(description); }
// @retail 0x3140a0
void __cdecl import_ball_socket_3140a0(ball_socket_view_314090 *object, c_component_joint_snapshot_4 const *description)
{ object->import_description(description); }
// @retail 0x314350
void __cdecl export_motion_limits_314350(s_314450 *object, s_314320 *description)
{ object->function_314450(description); }
// @retail 0x314360
void __cdecl import_motion_limits_314360(s_314450 *object, s_314320 const *description)
{ object->function_314480(description); }
// @retail 0x314830
void __cdecl export_spring_314830(spring_view_314830 *object, c_component_joint_snapshot_3 *description)
{ object->export_description(description); }
// @retail 0x314840
void __cdecl import_spring_314840(spring_view_314830 *object, c_component_joint_snapshot_3 const *description)
{ object->import_description(description); }
// @retail 0x314b80
void __cdecl export_prismatic_314b80(prismatic_view_314b80 *object, c_component_joint_snapshot_5 *description)
{ object->export_description(description); }
// @retail 0x314b90
void __cdecl import_prismatic_314b90(prismatic_view_314b80 *object, c_component_joint_snapshot_5 const *description)
{ object->import_description(description); }

static __forceinline float dot3_314e00(__m128 a, __m128 b)
{
	__m128 product = _mm_mul_ps(a, b);
	__m128 y = _mm_shuffle_ps(product, product, 0x55);
	__m128 z = _mm_shuffle_ps(product, product, 0xaa);
	y = _mm_add_ss(y, product);
	z = _mm_add_ss(z, y);
	float value;
	_mm_store_ss(&value, z);
	return value;
}
// @retail 0x314e00
bool_result_2da7f0 prismatic_view_314b80::valid() const
{
	if (!(fabs(fabs(dot3_314e00(axis_b, perpendicular_b))) < 1.0e-5f)) return false;
	if (!(fabs(dot3_314e00(perpendicular_b, perpendicular_b) - 1.0f) < 1.0e-5f)) return false;
	if (!(fabs(dot3_314e00(axis_b, axis_b) - 1.0f) < 1.0e-5f)) return false;
	if (minimum > maximum) return false;
	return true;
}

struct motion_frame_3144b0
{
	byte unknown00[0x30];
	__m128 rotation;
	byte unknown40[0x70];
	__m128 position;
};
struct motion_body_3144b0
{
	byte unknown00[0x3c];
	motion_frame_3144b0 *frame;
};
static __forceinline float length4_squared_3144b0(__m128 delta)
{
	__m128 squared = _mm_mul_ps(delta, delta);
	__m128 sum = _mm_add_ps(_mm_shuffle_ps(squared, squared, 0x4e), squared);
	sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, 0xb1));
	float value;
	_mm_store_ss(&value, sum);
	return value;
}
// @retail 0x3144b0
s_1d1870 c_314710::function_3144b0(void *body)
{
	motion_limits_view_314450 *limits = (motion_limits_view_314450 *)this;
	motion_body_3144b0 *input = (motion_body_3144b0 *)body;
	__m128 delta = _mm_sub_ps(limits->position_a, input->frame->position);
	float distance_squared = dot3_314e00(delta, delta);
	__m128 rotation = input->frame->rotation;
	float angle_squared = length4_squared_3144b0(_mm_sub_ps(limits->rotation_a, rotation));
	if (distance_squared < limits->distance_a * limits->distance_a &&
		angle_squared * limits->radius_squared < limits->angle_a * limits->angle_a)
		return true;
	limits->rotation_a = rotation;
	limits->position_a = input->frame->position;
	return false;
}
// @retail 0x314580
s_1d1870 c_314710::function_314580(void *body)
{
	motion_limits_view_314450 *limits = (motion_limits_view_314450 *)this;
	motion_body_3144b0 *input = (motion_body_3144b0 *)body;
	__m128 delta = _mm_sub_ps(limits->position_b, input->frame->position);
	float distance_squared = dot3_314e00(delta, delta);
	__m128 rotation = input->frame->rotation;
	float angle_squared = length4_squared_3144b0(_mm_sub_ps(limits->rotation_b, rotation));
	if (distance_squared < limits->distance_b * limits->distance_b &&
		angle_squared * limits->radius_squared < limits->angle_b * limits->angle_b)
		return true;
	limits->rotation_b = rotation;
	limits->position_b = input->frame->position;
	return false;
}
// @retail 0x3155f0
void contact_sizes_3155f0::get_sizes(lane_b_constraint_sizes *sizes)
{
	lane_b_contact_constraint_prefix::get_sizes(sizes);
	sizes->op_bytes += 0x28;
}
// @retail 0x315720
void contact_sizes_315720::get_sizes(lane_b_constraint_sizes *sizes)
{
	lane_b_contact_constraint_prefix::get_sizes(sizes);
	sizes->op_bytes += 0x88;
}
