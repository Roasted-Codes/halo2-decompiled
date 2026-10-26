// @flags /O2 /GL-
// Jacobian cursors and the word records written to the solver schema stream.
#include <xmmintrin.h>
struct s_linear_jacobian_31c530
{
	__m128 linear, angular_a, angular_b;
	s_linear_jacobian_31c530 *offset(long index);
};
struct s_angular_jacobian_31c520
{
	__m128 a, b;
};
struct s_angular_cursor_31c520 : s_angular_jacobian_31c520
{
	s_angular_cursor_31c520 *offset(long index);
};
struct s_schema_output_31f5e0
{
	void *jacobian;
	unsigned long *schema;
};
struct s_schema_pair_31f5e0 { unsigned long a, b; };
typedef void (__cdecl *solver_callback_320290)();
struct s_schema_cursors_31e740
{
	__m128 *jacobian;
	unsigned char *schema;
};
struct s_schema_header_31e770
{
	unsigned long opcode;
	__m128 *jacobian;
	long result_offset;
	long body_a;
	long body_b;
	long body_b_offset;
};
struct s_schema_input_31e770 { long body_a, body_b; };
typedef char assert_angular_jacobian_31c520[sizeof(s_angular_jacobian_31c520) == 32 ? 1 : -1];
typedef char assert_linear_jacobian_31c530[sizeof(s_linear_jacobian_31c530) == 48 ? 1 : -1];
typedef char assert_schema_header_31e770[sizeof(s_schema_header_31e770) == 24 ? 1 : -1];

// @retail 0x31c520
s_angular_cursor_31c520 *s_angular_cursor_31c520::offset(long index)
{
	return this + index;
}
// @retail 0x31c530
s_linear_jacobian_31c530 *s_linear_jacobian_31c530::offset(long index)
{
	return this + index;
}
// @retail 0x31f5e0
void __cdecl function_31f5e0(s_schema_pair_31f5e0 const *pair, s_schema_output_31f5e0 *output)
{
	s_schema_pair_31f5e0 values = *pair;
	unsigned long *schema = output->schema;
	void *jacobian = output->jacobian;
	schema[3] = values.a;
	schema[4] = values.b;
	schema[1] = (unsigned long)jacobian;
	schema[0] = 0x11801;
	schema[2] = 0;
	schema[5] = 0;
	output->schema = schema + 6;
}
// @retail 0x320290
void *__cdecl function_320290(solver_callback_320290 callback, long bytes,
	void const *input, s_schema_output_31f5e0 *output)
{
	unsigned long *schema = output->schema;
	schema[0] = ((bytes + 8) << 8) | 0x2000e;
	schema[1] = (unsigned long)callback;
	unsigned char *payload = (unsigned char *)(schema + 2);
	output->schema = (unsigned long *)(payload + bytes);
	return payload;
}
// @retail 0x31e740
void __cdecl function_31e740(float factor, __m128 const *value, s_schema_cursors_31e740 const *output, long index)
{
	(output->jacobian - index * 3)->m128_f32[3] = factor * value->m128_f32[3];
}
// @retail 0x31e770
void __cdecl function_31e770(s_schema_input_31e770 const *input, s_schema_cursors_31e740 *output, long result_offset, long body_b_offset)
{
	s_schema_header_31e770 *schema = (s_schema_header_31e770 *)output->schema;
	__m128 *jacobian = output->jacobian;
	long a = input->body_a;
	long b = input->body_b;
	schema->body_a = a;
	schema->result_offset = result_offset;
	schema->body_b = b;
	schema->body_b_offset = body_b_offset;
	schema->opcode = 0x11801;
	schema->jacobian = jacobian;
	output->schema = (unsigned char *)(schema + 1);
}
