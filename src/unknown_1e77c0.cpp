// @flags /O2 /Gr
/* UNKNOWN_1E77C0.CPP: recording a unit request in its player's local state
   (the e6900 callee) */

#include "unknown_11c920.h"
#include "globals.h"
#include <string.h>
#include <xmmintrin.h>

/* a player (g_4e8c24, 0x21c bytes): +0x28 is its local player slot */
struct s_player_request_view
{
	byte unknown00[0x28];
	short local_player_index;
	byte unknown2a[2];
	long unit_index;
	byte unknown30[0xc0 - 0x30];
	char team;
	byte unknownc1[0x21c - 0xc1];
};

struct s_time_entry
{
	long time;
	short a;
	short b;
};

struct s_request_transition
{
	short state;
	short ticks;
};

/* a local player's state in g_51e9c0 (src/player_request_state.cpp), 0x1b0 bytes:
   the four last unit requests at +0x150 */
struct s_local_player_state_view
{
	s_request_transition transitions[32];
	byte unknown080[0x150 - 0x80];
	s_time_entry requests[4];
	dword request_flags[8];
	long version;
	byte field_194;
	byte field_195;
	byte field_196;
	byte field_197;
	byte timer198;
	byte timer199;
	byte timer19a;
	byte field_19b;
	byte unknown19c[0x1b0 - 0x19c];
};

struct s_unknown_1e6a40;
extern s_unknown_1e6a40 *g_51e9c0;

void function_1e6980(s_time_entry *entries, short a, byte b);
bool function_1e7ab0(long local_index, long type);
bool function_1e83c0(long local_index, long type);

// @retail 0x1e8f60
void function_1e8f60(long player_index)
{
	s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
	long index = player->local_player_index;
	if (index != NONE)
		((s_local_player_state_view *)g_51e9c0)[index].field_195 = (byte)g_510c54->field_2_3;
}

// @retail 0x1e9070
void function_1e9070(long player_index)
{
	s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
	long index = player->local_player_index;
	if (index != NONE)
		((s_local_player_state_view *)g_51e9c0)[index].field_19b = (byte)g_510c54->field_2_3;
}

struct s_request_screen_bounds
{
	short top, left, bottom, right;
};



PRIVATE inline long next_request_player(long current)
{
	long result = NONE;
	long start;
	if (current == NONE)
		start = 0;
	else
		start = current + 1;
	for (long index = start; index < 4; index++)
	{
		if (g_4e8c20->entries[index] != NONE)
		{
			result = index;
			break;
		}
	}
	return result;
}

PRIVATE inline void set_request_flag(long local_index, byte flag)
{
	long player_index = local_index == NONE ? NONE : g_4e8c20->entries[local_index];
	if (player_index != NONE)
	{
		s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
		long index = player->local_player_index;
		if (index != NONE)
		{
			s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[index];
			byte flags = state->field_194;
			state->field_194 = flags | flag;
		}
	}
}

// @retail 0x1e7800
void function_1e7800(void)
{
	for (long index = next_request_player(NONE); index != NONE; index = next_request_player(index))
		set_request_flag(index, 1);
}

// @retail 0x1e78b0
void function_1e78b0(void)
{
	for (long index = next_request_player(NONE); index != NONE; index = next_request_player(index))
		set_request_flag(index, 2);
}

// @retail 0x1e7960
void function_1e7960(void)
{
	for (long index = next_request_player(NONE); index != NONE; index = next_request_player(index))
		set_request_flag(index, 4);
}

struct s_entry_420
{
	long value;
	word field_04;
	word limit;
	word field_08;
	short duration;
	byte field_0c[8];
};

struct s_table_420
{
	byte field_00[0x420];
	long count;
	s_entry_420 *entries;
};

inline s_entry_420 *entry_420_get(long index)
{
	s_entry_420 *result = NULL;
	s_table_420 *table = (s_table_420 *)g_510c94;
	if (table && index >= 0 && index < table->count)
		result = &table->entries[index];
	return result;
}

// @retail 0x1e8cb0
long function_1e8cb0(long index)
{
	long result = 0;
	s_entry_420 *entry = NULL;
	s_table_420 *table = (s_table_420 *)g_510c94;
	if (table && index >= 0 && index < table->count)
	{
		/* the table is read a second time for the lookup (retail does; with one read the index lands in another register) */
		s_table_420 *entry_table = (s_table_420 *)g_510c94;
		entry = &entry_table->entries[index];
	}
	if (entry)
		result = entry->value;
	return result;
}

// @retail 0x1e8d50
s_entry_420 *function_1e8d50(long index)
{
	s_entry_420 *result = NULL;
	s_table_420 *table = (s_table_420 *)g_510c94;
	if (table && index >= 0 && index < table->count)
	{
		/* the table is read a second time for the lookup (retail does; with one read the index lands in another register) */
		s_table_420 *entry_table = (s_table_420 *)g_510c94;
		result = &entry_table->entries[index];
	}
	return result;
}

// @retail 0x1e77c0
void function_1e77c0(long player_index, long type, byte result)
{
	s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);

	if (player->local_player_index != NONE)
		function_1e6980(((s_local_player_state_view *)g_51e9c0)[player->local_player_index].requests, (short)type, result);
}

// @retail 0x1e69d0
bool function_1e69d0(s_time_entry *entries, long type, long age_limit)
{
	long now = g_510c54->game_time;
	bool result = false;
	long i = 0;
	do
	{
		if ((word)entries[i].a == type && now - entries[i].time < age_limit)
		{
			result = true;
			break;
		}
		i++;
	} while (i < 4);
	return result;
}

struct s_flag_pair
{
	dword low;
	dword high;
};

// @retail 0x1e6a00
void function_1e6a00(long value, s_flag_pair *flags, long index)
{
	bool high = (bool)(((dword)value >> 1) & 1);
	if (value & 1)
		flags->low |= 1 << index;
	else
		flags->low &= ~(1 << index);
	if (high)
		flags->high |= 1 << index;
	else
		flags->high &= ~(1 << index);
}

// @retail 0x1e7a10
bool function_1e7a10(long player, long index)
{
	bool result = false;
	if (player != NONE)
	{
		s_flag_pair *flags = (s_flag_pair *)((byte *)g_51e9c0 + player * 0x1b0 + 0x170);
		long value = ((flags->high & (1 << index)) ? 2 : 0) + ((flags->low & (1 << index)) ? 1 : 0);
		result = value == 3;
	}
	return result;
}

// @retail 0x1e7a60
long function_1e7a60(long player, long index)
{
	long result = 0;
	if (player != NONE)
	{
		s_flag_pair *flags = (s_flag_pair *)((byte *)g_51e9c0 + player * 0x1b0 + 0x170);
		result = ((flags->high & (1 << index)) ? 2 : 0) + ((flags->low & (1 << index)) ? 1 : 0);
	}
	return result;
}

struct s_request_source
{
	byte field_00[0x1c];
	dword flags;
	byte field_20;
	byte field_21[7];
	short type;
	byte value;
	byte field_2b;
	long id;
	byte field_30[0x2c];
};

struct s_request_state
{
	word type;
	word field_02;
	long id;
	short count;
	short field_0a;
	short value;
};

// @retail 0x1e8ce0
void function_1e8ce0(s_request_state *state, s_request_source *source)
{
	short type = source->type;
	long stored_type = state->type;
	long const &incoming_type = (long)type;
	if (incoming_type != stored_type || source->id != state->id)
	{
		state->type = type;
		state->id = source->id;
		state->value = source->value;
		state->count = 0;
		state->field_0a = 0;
	}
	if (state->type == 1 || state->type == 3 || state->type == 4 || state->type == 5 || state->type == 6)
	{
		if (source->flags & 8)
			state->count++;
	}
}

struct s_request_object
{
	byte field_000[0xaa];
	byte type;
	byte field_0ab[0x138 - 0xab];
	short team;
	byte field_13a[0x1fc - 0x13a];
	short field_1fc;
	byte field_1fe[0x216 - 0x1fe];
	byte field_216;
};

struct s_request_object_header
{
	byte field_00[8];
	s_request_object *object;
};

bool function_1df560(short team_a, short team_b);

// score 47 (was 47): retail keeps the scaled index in EAX and reads the field
// as [eax+esi+0x28], and loads the table pointer after the index is scaled;
// ours materialises the record pointer in EBX and reads [ebx+0x28].
// Ours gives the state EAX for the final call's `state + 0x140` argument
// (`add eax, 0x140`), so the record moves to EBX; retail keeps the record in
// EAX and passes `lea eax, [edx+0x140]`. Tried: state declared first 47; a
// previous-request pointer 47; the state as a byte offset 47; no record
// local, a fresh one for the unit 52; the copies without `current` 47.
// Also tried: the unit index in a local (before or after the copies) 47; a short
// local index 58; the player as an array element 47; an early return 47; the
// local index read again for the state 58; the unit tests in one condition 47;
// the local index read without the player local (before or after it) 47; the
// player table in a local 47; the request pointer as an early local 64; the
// counter through a byte local 47.
// @retail 0x1e6b00
void function_1e6b00(long player_index, s_request_source *source)
{
	s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
	long index = player->local_player_index;
	if (index != NONE)
	{
		s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[index];
		s_request_source *current = (s_request_source *)((byte *)state + 0x88);
		*(s_request_source *)((byte *)state + 0xe4) = *current;
		*current = *source;
		if (player->unit_index != NONE)
		{
			s_request_object *unit = ((s_request_object_header *)g_4e0300->data)[player->unit_index & 0xffff].object;
			if (unit->field_1fc == NONE && source->field_20 != 0xff && source->field_20 != unit->field_216)
			{
				state->field_197++;
				state->field_196 = (byte)(g_510c54->field_2_3 * 2);
			}
		}
		function_1e8ce0((s_request_state *)((byte *)state + 0x140), source);
	}
}

// score 51 (was 51): index EBX/mask EBP priority, repeated output load and low/high store order remain.
// retail keeps the index in EBX and the mask in EBP (ours
// the other way round), loads the output pointer once above the last test and
// stores the low flag word first in the inlined update. Without the read
// barrier: high word through the pair and low word through the state array 51
// (retail's load order and `mov eax, mask; and eax, low`); both through the
// pair 77, both through the state array 77-80, mask local / term order /
// `21 == index` / limit or next locals / swapped arms 51-52.
// Earlier: retail saves the pointer argument in EBX and shifts the mask in EBP.
// Round 129: flag view declared after both value terms read from the array 77 (state
// moves to EAX); unsigned index 51; explicit else arm 51; constant update before the output
// stores 54; `limit > 0` 51. Screened: array/element-address flag views, the transition
// slot for the recursion, a next-value local, the absent-entry arm last, output stores
// swapped, call before the stores, all 45-78 in screen terms (base 45).
// score 51 (was 51): index/mask roles and the output join remain; tested completion
// with separate/state/ticks/both stores 116/112/114/120; shared setter variants
// 83/111/108/109. Original early-result body restored.
// index/mask registers and the repeated output load remain.
// Declared paired-word view with mixed/pair/array/mirrored reads 51/77/80/77;
// paired snapshot before/after pointer lifetime and low-first snapshot 115/115/115;
// paired snapshot with one shifted mask 85.
// Early dependency predicate, native signed ordinal, both, native recursive slot, predicate/slot all 51;
// request value advanced in place alone/with native ordinal 58/58; adjacent recursive ordinal 51.
// @retail 0x1e8d80
bool __stdcall function_1e8d80(long index, s_local_player_state_view *state, s_entry_420 *entry, s_request_transition *output)
{
	s_flag_pair *flags = (s_flag_pair *)((byte *)state + 0x170);
	long value = ((flags->high & (1 << index)) ? 2 : 0) + ((state->request_flags[0] & (1 << index)) ? 1 : 0);
	if (index == 21)
		function_1e8d80(22, state, entry_420_get(22), (s_request_transition *)((byte *)state + 0x58));
	if (!entry)
	{
		output->state = 4;
		output->ticks = g_510c54->field_2_3 * 5;
		return false;
	}
	if (entry->limit != 0 && entry->limit <= 3)
	{
		if (value + 1 >= entry->limit)
		{
			output->state = 5;
			output->ticks = 0;
			function_1e6a00(3, flags, index);
			return true;
		}
		output->state = 4;
		output->ticks = g_510c54->field_2_3 * entry->duration;
		function_1e6a00(value + 1, flags, index);
		return false;
	}
	output->state = 4;
	output->ticks = g_510c54->field_2_3 * entry->duration;
	return false;
}

// @retail 0x1e8fa0
void function_1e8fa0(long player_index, long object_index, byte kind)
{
	s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
	s_request_object *object = ((s_request_object_header *)g_4e0300->data)[object_index & 0xffff].object;
	long local_index = player->local_player_index;
	if (local_index != NONE && ((1 << object->type) & 3) && function_1df560(player->team, object->team))
	{
		s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[local_index];
		byte type = kind & 0x3f;
		if (type == 0x15 || type == 0x16)
			state->timer198 = (byte)g_510c54->field_2_3;
		else if (type == 3)
			state->timer199 = (byte)g_510c54->field_2_3;
		else if ((type >= 5 && type <= 0x13) || (type >= 0x27 && type <= 0x28))
			state->timer19a = (byte)g_510c54->field_2_3;
	}
}

struct s_parent_seat_object
{
	long definition_index;
	byte field_4[0x14 - 4];
	long parent_index;
	byte field_18[0x1fc - 0x18];
	short seat_index;
};

struct s_parent_seat_header
{
	short salt;
	byte flags;
	byte type;
	byte field_4[4];
	s_parent_seat_object *object;
};

struct s_parent_seat
{
	dword : 2;
	dword enabled : 1;
	dword : 29;
	byte field_4[0xb0 - 4];
};

struct s_parent_seat_definition
{
	byte field_0[0x1cc];
	s_parent_seat *seats;
	byte field_1d0[0x21a - 0x1d0];
	short type;
};

// @retail 0x1e8eb0
bool function_1e8eb0(long object_index, long type, bool any_nonzero)
{
	s_parent_seat_header *headers = (s_parent_seat_header *)g_4e0300->data;
	s_parent_seat_object *object = headers[object_index & 0xffff].object;
	bool result = false;
	const long *type_reference = &type;
	const bool *any_reference = &any_nonzero;
	if (object->parent_index != NONE && object->seat_index != NONE)
	{
		short seat_index = object->seat_index;
		s_parent_seat_header *parent = &headers[object->parent_index & 0xffff];
		if ((1 << parent->type) & 2)
		{
			s_parent_seat_definition *definition = (s_parent_seat_definition *)g_4e3b44[parent->object->definition_index & 0xffff].bytes;
			if (TEST_FIELD_BIT(definition->seats[seat_index].enabled))
			{
				if (definition->type == *type_reference || (*any_reference && definition->type != 0))
					result = true;
			}
		}
	}
	return result;
}

struct s_request_profile
{
	__int64 field_0[0x128 / 8];
	dword flags[8];
	byte field_148[0x1e0 - 0x148];
};

// score 108 (was 108): aligned frame 0x1e8 agrees; player/version registers and flag reads differ.
// Default profile 164; early memset 150; unsigned version 143; aligned byte prefix 180;
// unsigned local index 143; aligned dword prefix 180; common bits 370; separate tick reset 335.
// All use ordinary player data and native loops; original profile and body retained.
// A plain 32-entry loop of `ticks = 0; state = function_1e7a10(local_index, i) ? 5 : 0;` gives retail's
// per-element flag reloads and bool select but stays rolled (337, 357 bytes): with if/else, a
// pointer local, a bool local, short/int/unsigned/do/while counters, an inline transition helper,
// inline/forceinline on 0x1e7a10 alike; noinline 373; the four-way body calling it 154.
// @retail 0x1e73b0
void function_1e73b0()
{
	for (long local_index = next_request_player(NONE); local_index != NONE;
		local_index = next_request_player(local_index))
	{
		long player_index = local_index == NONE ? NONE : g_4e8c20->entries[local_index];
		if (player_index != NONE)
		{
			s_player_request_view *player = (s_player_request_view *)(*(byte *volatile *)&g_4e8c24->data + (player_index & 0xffff) * 0x21c);
			long profile_index = *(long *)((byte *)player + 0x24);
			if (profile_index != NONE)
			{
				s_request_profile profile;
				long version;
				s_player_slot *slot = &g_54e8e0[profile_index];
				if (slot && (*(byte *)slot & 0x10))
				{
					profile = *(s_request_profile *)((byte *)slot + 0x18);
					version = *(long *)((byte *)slot + 0x1f8);
				}
				else
				{
					memset(&profile, 0, sizeof(profile));
					version = NONE;
				}
				s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[local_index];
				memcpy(state->request_flags, profile.flags, sizeof(profile.flags));
				state->version = version;
				dword flags0 = state->request_flags[0];
                dword flags1 = state->request_flags[1];
                for (long i = 2; i - 2 < 32; i += 4)
				{
					{
						s_request_transition *transition = &state->transitions[(i - 2)];
						transition->ticks = 0;
						long value = ((flags1 & (1 << (i - 2))) ? 2 : 0) + ((flags0 & (1 << (i - 2))) ? 1 : 0);
						transition->state = value == 3 ? 5 : 0;
					}
					{
						s_request_transition *transition = &state->transitions[(i - 1)];
						transition->ticks = 0;
						long value = ((flags1 & (1 << (i - 1))) ? 2 : 0) + ((flags0 & (1 << (i - 1))) ? 1 : 0);
						transition->state = value == 3 ? 5 : 0;
					}
					{
						s_request_transition *transition = &state->transitions[i];
						transition->ticks = 0;
						long value = ((flags1 & (1 << i)) ? 2 : 0) + ((flags0 & (1 << i)) ? 1 : 0);
						transition->state = value == 3 ? 5 : 0;
					}
					{
						s_request_transition *transition = &state->transitions[(i + 1)];
						transition->ticks = 0;
						long value = ((flags1 & (1 << (i + 1))) ? 2 : 0) + ((flags0 & (1 << (i + 1))) ? 1 : 0);
						transition->state = value == 3 ? 5 : 0;
					}
				}
			}
		}
	}
}

#include "unknown_1248b0.h"
#include <math.h>

struct s_weapon_status_magazine
{
 bool active;
 bool idle;
 short loaded;
 short loaded_maximum;
 short unloaded;
 short total_maximum;
};

struct s_weapon_status
{
 real value;
 real heat;
 bool flag8;
 bool flag9;
 byte unknown0a[2];
 real fraction;
 bool charging;
 bool target_available;
 bool target_charging;
 bool target_ready;
 real target_fraction;
 point3f target_position;
 short magazine_count;
 s_weapon_status_magazine magazines[2];
};

void function_100520(long weapon_index, s_weapon_status *status);
point3f *function_b9dd0(long object_index, point3f *result);
short function_c8860(long unit_index);
long function_cbd50(long unit_index, short weapon_index);
bool function_f42f0(long vehicle_index);
bool function_15eaf0(void);

PRIVATE inline real request_angle_delta(real angle, real previous)
{
 real delta = angle - previous;
 if (delta > 3.1415927410125732f) delta -= 6.2831854820251465f;
 if (delta < -3.1415927410125732f) delta += 6.2831854820251465f;
 return delta;
}

bool function_13cb40(void);
bool motion_sensor_enemy_vehicle_ahead(long local_player_index);
bool motion_sensor_enemy_nearby(long local_player_index);
long function_162fd0(long index);
bool voice_port_can_talk(long port);
bool function_100f00(long weapon_index);
bool function_100fd0(long weapon_index);
short function_101010(long weapon_index, short index);
struct s_object;
s_object *function_badc0(long object_index, dword type_mask);

struct s_unit_child_iterator
{
 long object_index;
 long unit_index;
 short seat_index;
 long next_index;
};
struct s_damage_object;
void function_d0590(s_unit_child_iterator *iterator, long object_index);
s_damage_object *function_d05c0(s_unit_child_iterator *iterator);

PRIVATE inline byte *request_unit(long object_index)
{
 return *(byte **)(g_4e0300->data + (object_index & 0xffff) * 12 + 8);
}

PRIVATE inline long request_weapon(s_player_request_view *player, bool secondary)
{
 long unit_index = player->unit_index;
 byte *unit = request_unit(unit_index);
 return function_cbd50(unit_index, *(signed char *)(unit + (secondary ? 0x213 : 0x212)));
}

long function_1469f0(real seconds);
// score 279 (was 279): frame 12 and the state/offset/cursor homes now agree; retail keeps the local
// index in eax (the player index register, reloaded after each call and passed to 0x1e83c0 in
// eax), ours puts it in edx, so the scratch registers rotate and 0x1e83c0's calls reload it,
// which also splits `++*elapsed` around the reload (retail `inc dword ptr [edi + 0x84]`).
// Round 57: the final loop's request test through the existing 0x1e7a10 (retail inlines it:
// `sete al; test al, al`, with g_51e9c0 re-read) 316 alone; with a long local index (retail's
// movsx load, 32-bit NONE test, offset spill) 319; with the selected-state cases in 0..4 order
// (case 4 falls into the final loop as in retail) and the countdown stores without short casts
// 275 fast / 279 plain, kept (frame 12; removes the hand-written copy of 0x1e7a10). Before that:
// cases in 0..4 order 293; casts alone 284; both 288. On the kept form: player read before the
// options pointer 275, index before options 280, short difficulty local 290, selected/elapsed
// declared first 275/275 (fast).
// Round 59 (fast control 280): campaign difficulty as a ternary short local 278; the same through a
// forceinline options helper 278 (still a 16-bit load); restricted through a short-parameter bool
// helper 280 (gives retail's movsx, bool arms inverted); difficulty through a campaign getter 283;
// restricted computed before the player 330 (player index moves to ecx). The local index stays in
// edx, so the restricted bool takes al where retail has cl.
// Earlier: frame 4 versus 12; early slot spill, state displacement and transition/flag homes remain.
// Earlier: Frame 4/12, early slot spill and state/transition/flag homes remain.
// Earlier: frame 4/12 and slot/state/transition/flag homes remain.
// frame four/twelve and slot/state/transition homes remain.
// Integer query 358; three/four indexed timers 342/342; three/four timer cursors 296/291;
// query with four/three indexed timers 361/361, four cursor timers 311.
// Reduced control 280; all restored.
// frame 4/12 and slot/state/transition/flag homes remain.
// Query, cancellation and execution separate inline/noinline declarations, individually
// and together, all 280 fast, tying the unchanged preview (full 279). All restored.
// First +0 is frame 4 versus retail 12; slot/state and final flag/transition carriers still differ.
// Native signed-word slot 283 fast/290 plain; full-width difficulty 308; shared elapsed 309;
// cooldown-first 296; fixed initial do scan 340; slot plus cooldown-first 281.
// frame 4/12 and slot/transition/flag homes remain; cooldown case first reaches retail length.
// Selected-state orders 01324/02134/03124/02314/03214/04213/04312/40123: 292/287/280/293/298/302/277/280 fast; last order 279 plain.
// Byte/word request value 298/293; missing-bit test 317; final byte scan 304 (fast control 293).
// frame 4 versus 12 and slot/state/flag homes remain.
// Restriction result 293; selection-field references 290; state reference 290;
// initial state gates 288; byte scan 319; gates with native slot 307 (plain).
// Shared state displacement late/early/direct flags/with native difficulty 347/353/347/359 fast;
// entry selected/shared transition/entry descriptor workspaces 280/280/280; native difficulty 286.
// Unchanged fast control 280 versus plain 279; all executable forms restored.
// Selected workspace orders entry/current/transition 285, current/entry/transition 287,
// transition/current/entry 280, entry/transition/current 285, transition/entry/current 280;
// promoted slot alone/with entry-first 291/296; final post-tested scan 280 (fast control 280). All restored.
// Round 187: admission exit 280; selection after timers 292; selection phase scope 280;
// native countdown results alone/with admission/with scope 317/317/317, with late selection 326;
// admission plus late scoped selection 292. Fast control 280; all restored.
// Current dispatch/query context: native current/elapsed/both fields 280/280/308 fast;
// byte/signed-byte restriction 280/280; nested restriction result 286; unsigned/signed-word
// initial scan 335/335. Reduced control 280, full baseline 279; real state layout and
// executable body restored.
// Round 188 unsigned state field, shared bitmap tests, forceinline table getter,
// their pairs/all, and noinline table getter: 280/295/280/295/280/295/295/341 (fast control 280).
// Round 167: Cooldown-first selected-case orders 41023/41203/41302/42013/42103/
// 42301/43012/43102 score 279/283/279/277/282/290/280/278 fast (control 280, full 279).
// Best gains at most three; original 40123 order restored; inherited score headers merged.
// Round 194: Complementary admission bool/byte/short/long 280/280/286/274; native rounded/timed/both countdown
// stores 279/284/284, both with complementary admission 284. Fast control 280; original body restored.
// Round 375: Shared active-state 2/3 actions with word/short/long/unsigned state
// 316/316/325/325; shared 1/2/3 actions 341/341/350/350 (fast control 280).
// Frame eight versus twelve; shorter bodies and initial slot spill remain; restored.
// Round 139: Shared request ordinal long/int/short/word 280/280/339/339 fast; those four with
// shared scan/selected transition workspace 280/280/339/339. Unchanged fast control 280 versus full
// 279; frame 4/12 and early slot/state/final-cursor homes remain. Original executable source, fixed
// scan bounds and state/call observations restored.
// Round 178: Paired zero chains for old selection/cooldowns/both/active clears/old+active/
// cooldowns+active/all/all opposite order 280/280/280/280/280/280/280/280 fast, control 280; full 279.
// Four-byte frame and slot/state/final-cursor homes persist; original stores restored.
// @retail 0x1e6bd0
void function_1e6bd0(long player_index)
{
 s_game_options_view *options = g_4e6948;
 s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
 long local_index = player->local_player_index;
 bool restricted = options->state == 1 && (options->difficulty == 3 || options->difficulty == 2);
 if (local_index != NONE && *((byte *)g_51e9c0 + 0x6c5) && !restricted)
 {
  s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[local_index];
  long *current = (long *)((byte *)state + 0x80);
  long *elapsed = (long *)((byte *)state + 0x84);
  long selected = *current;
  if (state->field_195 > 0) --state->field_195;
  if (state->field_196 > 0 && --state->field_196 == 0) state->field_197 = 0;
  if (state->timer198 > 0) --state->timer198;
  if (state->timer199 > 0) --state->timer199;
  if (state->timer19a > 0) --state->timer19a;
  if (state->field_19b > 0) --state->field_19b;
  for (long i = 0; i < 32; ++i)
  {
   s_request_transition *transition = &state->transitions[i];
   switch ((word)transition->state)
   {
   case 0:
   {
    if (selected == NONE || selected > i || i == 31)
     if (function_1e7ab0(local_index, i)) selected = i;
    break;
   }
   case 4:
   {
    if (--transition->ticks <= 0) { transition->ticks = 0; transition->state = 0; }
    break;
   }
   }
  }
  if (selected != NONE)
  {
   long old_current = *current;
   s_request_transition *transition = &state->transitions[selected];
   s_entry_420 *entry = entry_420_get(selected);
   if (selected != old_current)
   {
    if (old_current != NONE)
    {
     state->transitions[old_current].ticks = 0;
     state->transitions[old_current].state = 0;
    }
    *current = selected;
    *elapsed = 0;
   }
   switch ((word)transition->state)
   {
   case 0:
    transition->state = 1;
    transition->ticks = entry ? function_1469f0(*(real *)entry->field_0c) : 0;
    break;
   case 1:
    if (function_1e83c0(local_index, selected))
    {
     function_1e8d80(selected, state, entry, transition);
     *current = NONE;
    }
    else if (function_1e7ab0(local_index, selected))
    {
     if (--transition->ticks <= 0) { transition->state = 2; transition->ticks = 0; }
    }
    else
    {
     transition->state = 0;
     transition->ticks = 0;
     *current = NONE;
    }
    break;
   case 2:
    ++*elapsed;
    if (function_1e83c0(local_index, selected))
    {
     function_1e8d80(selected, state, entry, transition);
     *current = NONE;
     *elapsed = 0;
    }
    else if (!function_1e7ab0(local_index, selected))
    {
     transition->state = 3;
     transition->ticks = entry ? g_510c54->field_2_3 * entry->field_08 : 0;
    }
    break;
   case 3:
    ++*elapsed;
    if (function_1e83c0(local_index, selected))
    {
     function_1e8d80(selected, state, entry, transition);
     *current = NONE;
     *elapsed = 0;
    }
    else if (function_1e7ab0(local_index, selected))
    {
     transition->state = 2;
     transition->ticks = 0;
    }
    else if (--transition->ticks <= 0)
    {
     transition->ticks = 0;
     transition->state = 0;
     *current = NONE;
     *elapsed = 0;
    }
    break;
   case 4:
    if (--transition->ticks <= 0) { transition->ticks = 0; transition->state = 0; }
    break;
   }
  }
  for (long i = 0; i < 32; ++i)
  {
   if (i != *current)
   {
    if (!function_1e7a10(local_index, i))
    {
     switch (i)
     {
     case 15: case 17: case 18: case 23: case 30:
      if (function_1e83c0(local_index, i))
       function_1e8d80(i, state, entry_420_get(i), &state->transitions[i]);
      break;
     }
    }
   }
  }
 }
}

struct s_player_profile;
struct s_player_profile_settings;
void __stdcall player_slot_change_profile(long index, s_player_profile *settings, long profile_index);
void __stdcall player_slot_store_profile(long index, s_player_profile_settings *settings, long profile_index);

struct __declspec(align(8)) s_request_settings
{
	byte values[0x1e0];
};

struct s_request_profile_slot
{
	dword flags;
	byte field_4[0x18 - 4];
	s_request_settings settings;
	long profile_index;
	byte field_1fc[0xc70 - 0x1fc];
};

// Retail realigns the stack before the aligned request settings.
// @retail 0x1e75d0 standard
void __stdcall function_1e75d0(dword flush)
{
	__declspec(align(8)) s_request_settings settings;
	for (long index = next_request_player(NONE); index != NONE; index = next_request_player(index))
	{
		long player_index = index == NONE ? NONE : g_4e8c20->entries[index];
		if (player_index != NONE)
		{
			s_player_request_view *player = (s_player_request_view *)(g_4e8c24->data + (player_index & 0xffff) * 0x21c);
			long slot_index = *(long *)((byte *)player + 0x24);
			if (slot_index != NONE)
			{
				s_request_profile_slot *slot = (s_request_profile_slot *)g_54e8e0 + slot_index;
				long profile_index;
				if (slot && (slot->flags & 0x10))
				{
					settings = slot->settings;
					profile_index = slot->profile_index;
				}
				else
				{
					memset(&settings, 0, sizeof(settings));
					profile_index = NONE;
				}
				if (profile_index != NONE)
				{
					s_local_player_state_view *state = &((s_local_player_state_view *)g_51e9c0)[index];
					if (state->version == profile_index)
					{
						bool changed = false;
						int comparison = memcmp(settings.values + 0x128, state->request_flags, sizeof(state->request_flags));
						if (comparison != 0)
						{
							memcpy(settings.values + 0x128, state->request_flags, sizeof(state->request_flags));
							*((byte *)state + 0x19d) = 1;
							changed = true;
						}
						if (!flush)
						{
							if (changed)
								player_slot_change_profile(*(long *)((byte *)player + 0x24), (s_player_profile *)&settings, profile_index);
						}
						else if (*((byte *)state + 0x19d))
						{
							player_slot_store_profile(*(long *)((byte *)player + 0x24), (s_player_profile_settings *)&settings, profile_index);
							*((byte *)g_51e9c0 + index * 0x1b0 + 0x19d) = 0;
						}
					}
				}
			}
		}
	}
}
