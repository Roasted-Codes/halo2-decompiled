// @flags /O2 /GL-
// Havok solver callbacks. Accumulator prefix through the four inverse-mass
// terms at +0x30; no claim about the complete accumulator extent.
#include <xmmintrin.h>
struct lane_a_accumulator_prefix
{
	float state[12];
	float inverse_mass[4];
};
struct lane_a_mass_restore
{
	float saved[8];
	float scale_a;
	float scale_b;
	lane_a_accumulator_prefix *a;
	lane_a_accumulator_prefix *b;
};

// score 6 (was 6): three x87 products still load their operands in reverse order.
// Uniform compound, scale-first and mass-first forms 6; two index loops 14;
// retained pointers 44; retained scales 38; group scales 34; pointer ranges 71;
// per-product scale, input and result locals 14.
// Scalar member/index accessors, their compound and forced forms 6 each;
// read-only record and record/member form 6 each.
// @retail 0x315280
void __cdecl lane_a_scale_masses(void *, lane_a_mass_restore *record)
{
	record->a->inverse_mass[0] = record->scale_a * record->a->inverse_mass[0];
	record->a->inverse_mass[1] = record->scale_a * record->a->inverse_mass[1];
	record->a->inverse_mass[2] *= record->scale_a;
	record->a->inverse_mass[3] = record->scale_a * record->a->inverse_mass[3];
	record->b->inverse_mass[0] *= record->scale_b;
	record->b->inverse_mass[1] *= record->scale_b;
	record->b->inverse_mass[2] *= record->scale_b;
	record->b->inverse_mass[3] *= record->scale_b;
}

// @retail 0x3152f0
void __cdecl lane_a_restore_masses(void *, lane_a_mass_restore *record)
{
	record->a->inverse_mass[0] = record->saved[0];
	record->a->inverse_mass[1] = record->saved[1];
	record->a->inverse_mass[2] = record->saved[2];
	record->a->inverse_mass[3] = record->saved[3];
	record->b->inverse_mass[0] = record->saved[4];
	record->b->inverse_mass[1] = record->saved[5];
	record->b->inverse_mass[2] = record->saved[6];
	record->b->inverse_mass[3] = record->saved[7];
}

