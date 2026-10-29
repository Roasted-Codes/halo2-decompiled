// @flags /O2 /Gr /arch:SSE
#include "unknown_2551c0.h"
#include "globals.h"
#include "swarm.h"

struct s_28dab1
{
	byte field_0[0x18];
	long field_18;
};

struct s_28dab2
{
	byte field_0[0x2e];
	short field_2e;
};

long function_1e4990(long arg_0);
long function_28dbd0(long arg_0, long arg_1, long arg_2, s_28dab2 const *arg_3, bool arg_4);
void __stdcall swarm_delete(long arg_0);

// score 44 (was 44): the tag pointer is in esi where retail keeps it in edi (the NONE result in
// the other one), and retail keeps the loop limit in ebx with a cmovg and spills the creature
// definition index, where ours keeps the index in ebx and spills the limit (a branch, no cmov).
// Tried: declaration order, the result split from the allocation, the comparison against the
// variable, the goto, the limit's width 53 or worse; retail's store order with the count read once
// 53; tag pointer declared before the result 44; flag byte in a local 44; nested tag test 44;
// locals at the top 53; the record pointer before the tag-field read (retail's head, not its
// limit): ternary 79, `count = 10; if (field > 0) count = field;` 56 (cmovg into ebp), 65 with an
// else tail, after the stores 81; requested count 74; nonpositive bound replaced 97; explicit bound
// arms 44; sampled object flags 44; guarded tag-field reference 97; immutable record receiver 44;
// completed count 51; immutable receiver and bound 44; point setters first/second/both 83/88/92;
// tag/placement references 44/44; plain while 44; equality termination 45; completed-count field
// reference 44; inline call-boundary declarations 44; the swarm type and getter 44, with retail's
// store order 53, the swarm pointer first 95 (72 with retail's order); the loop counter's zero
// before the stores 108.
// @retail 0x28dab0
long __stdcall function_28dab0(long arg_0, s_28dab2 const *arg_1)
{
	long local_0 = NONE;
	s_28dab1 *local_1 = (s_28dab1 *)g_4e3b44[arg_0 & 0xffff].bytes;
	if ((*(byte *)function_1e4990(arg_0) & 1) && local_1->field_18 != NONE)
	{
		local_0 = record_pool_allocate(g_5044c8);
		if (local_0 != NONE)
		{
			long local_2 = local_1->field_18;
			s_swarm *local_3 = swarm_get(local_0);
			local_3->gather_position_valid = false;
			local_3->spawn_slot_reference = true;
			local_3->creature_count = 0;
			local_3->initial_creature_count = 0;
			local_3->event_count = 0;
			local_3->actor_index = NONE;
			local_3->first_creature_index = NONE;
			local_3->position = *g_468788;
			local_3->gather_position = *g_468788;
			short local_4 = arg_1->field_2e > 0 ? arg_1->field_2e : 10;
			for (short local_5 = 0; local_5 < local_4; local_5++)
				function_28dbd0(local_0, arg_0, local_2, arg_1, local_5 == 0);
			if (local_3->creature_count <= 0)
			{
				swarm_delete(local_0);
				local_0 = NONE;
				goto local_6;
			}
			local_3->initial_creature_count = local_3->creature_count;
		}
	}
local_6:
	return local_0;
}
