#ifndef CONSTRAINT_HELPERS_314090_H
#define CONSTRAINT_HELPERS_314090_H
#include "lane_b_constraint_dependencies.h"

// Description layouts follow the retail constructors and import/export copies.
// The base occupies twelve bytes, followed by aligned vector fields.
struct c_component_joint_snapshot_3 : lane_b_rigid_constraint_description
{
	__m128 pivot_a, pivot_b;
	float length;
	c_component_joint_snapshot_3();
};
struct c_component_joint_snapshot_4 : lane_b_rigid_constraint_description
{
	__m128 pivot_a, pivot_b;
	c_component_joint_snapshot_4();
};
struct c_component_joint_snapshot_5 : lane_b_rigid_constraint_description
{
	__m128 pivot_a, pivot_b, axis_a, axis_b, perpendicular_b;
	__m128 frame_b[3];
	float minimum, maximum, friction;
	c_component_joint_snapshot_5();
};
struct c_component_joint_reader_4
{
	void read(c_component_joint_snapshot_4 *output);
};

// Non-owning views: the shared constraint prefix is accessed through its
// existing type, without inventing another virtual table for these objects.
struct ball_socket_view_314090
{
	byte base[0x20];
	__m128 pivot_a, pivot_b;
	lane_a_solver_result results[3];
	lane_a_solver_result *runtime();
	void import_description(c_component_joint_snapshot_4 const *description);
	void info(lane_a_constraint_info *output) const;
};
struct spring_view_314830
{
	byte base[0x20];
	__m128 pivot_a, pivot_b;
	float length;
	lane_a_solver_result results[1];
	lane_a_solver_result *runtime();
	bool_result_2da7f0 valid() const;
	void export_description(c_component_joint_snapshot_3 *description) const;
	void import_description(c_component_joint_snapshot_3 const *description);
	void info(lane_a_constraint_info *output) const;
};
struct prismatic_view_314b80
{
	byte base[0x20];
	__m128 pivot_a, pivot_b, axis_a, axis_b, perpendicular_b;
	__m128 frame_b[3];
	float minimum, maximum, friction;
	lane_a_solver_result results[7];
	lane_a_solver_result *runtime();
	bool_result_2da7f0 valid() const;
	void import_fields(c_component_joint_snapshot_5 const *description);
	void export_description(c_component_joint_snapshot_5 *description) const;
	void import_description(c_component_joint_snapshot_5 const *description);
	void info(lane_a_constraint_info *output) const;
};

struct s_314320 : lane_b_constraint_aggregate
{
	long field_0;
	real field_4, field_8, field_c, field_10;
	s_314320();
};
struct s_314450
{
	void function_314450(s_314320 *output);
	void function_314480(s_314320 const *input);
};
struct motion_limits_view_314450
{
	byte base[8];
	float radius_squared;
	byte unknown0c[4];
	__m128 position_a, rotation_a, position_b, rotation_b;
	float distance_a, angle_a, distance_b, angle_b;
};

struct s_1d1870
{
	char field_0;
	s_1d1870() {}
	s_1d1870(bool value) : field_0(value) {}
};
class hkEntity;
class c_314710 : public c_a
{
public:
	byte field_8[0x58];
	c_314710(hkEntity *entity);
	s_1d1870 function_3144b0(void *body);
	s_1d1870 function_314580(void *body);
};
struct contact_sizes_3155f0 : lane_b_contact_constraint_prefix
{
	void get_sizes(lane_b_constraint_sizes *sizes);
};
struct contact_sizes_315720 : lane_b_contact_constraint_prefix
{
	void get_sizes(lane_b_constraint_sizes *sizes);
};
#endif
