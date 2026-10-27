#include "unknown_11c920.h"
#include "globals.h"
#include "engine_peer.h"
#include "unknown_157450.h"
#include "game_engine_events.h"
#include "slot_handler.h"

// @flags /O2 /arch:SSE /Gr

struct s_transition_player_iterator
{
	byte *player;
	s_record_pool *data;
	long datum_index;
	long absolute_index;
};

void __stdcall function_a7810(dword mask);
void function_b58c0(long index, dword mask);
bool player_iterator_next(long *iterator);
void function_157ae0();
long function_15b330(bool teams);
void function_15b3a0(long player_or_team, bool value);
void function_15fe50(long value);
void function_15ba00();
void function_15dd10();
void function_15c6f0();
void function_196430();
void function_196390();
void function_19eb90(s_event *event);
extern byte g_510ca1;
long function_158e90(long team);
bool function_158eb0();
bool function_158f50();
long function_23f260(long mode, long player_index, long value);
long function_23f360(long team, long mode);
void game_results_set_player_score(long index, long axis, short button);
void game_results_set_team_score(long index, long value, char button);
void function_1968b0(long index, long team, long counter, long value);
void function_15be20();
void function_23f000();
void function_159ac0();
void __stdcall function_15ae70(s_netgame_entry_state *entries);
void function_162de0();
void teleporters_update();
bool function_15eb20(long player_index);
void function_15b270(long player_index);
void __stdcall function_15bb20(long player_index);
void function_161f30(long player_index);
void function_162a30(long player_index);
bool function_161e10(long team);
void function_15ba90(long team);
void function_15c000();
void function_15ba20();
void function_23f6e0();
void function_15ebd0();
void function_15ece0();
void function_15ed60();
bool function_158a50(long player_index);
static __forceinline long real_to_long(real value);

PRIVATE inline long transition_local_player_next_15c150(long index)
{
	long result = NONE;
	for (long i = index == NONE ? 0 : index + 1; i < 4; ++i)
	{
		if (g_4e8c20->entries[i] != NONE)
		{
			result = i;
			break;
		}
	}
	return result;
}


// score 196 (was 196): delayed EBP save, team-byte home and word slot spill.
// Frame 0x1c agrees; delayed EBP save, teams-byte home and word local-slot spill remain.
// Earlier: delayed EBP save, team-byte home and word slot spill.
// Cursor player 253; count at loop tail 199; both 257; signed/unsigned
// word team counters 248; tail count plus word team counter 252.
// early EBP save, teams byte home and local-slot spill differ;
// unsigned count 242; short count 249; byte team 248; shared crowded with word slot 248; indexed fade with word slot 196.
// early EBP save, team-byte home and local-slot spill remain.
// Shared iterator 196; typed pooled player 196; native team bitfield 196; all three 196;
// direct four-slot traversal 351; with shared types 351; with native bitfield 351; all 351.
// delayed EBP save, team-byte home and word local-slot spill remain.
// Earlier 196 (was 196): early EBP save, team-byte home and local-slot spill remain.
// Earlier 196 (was 196): delayed EBP save, team-byte home and word local-slot spill remain.
// Per-use first-loop datum 196; short/byte/word teams predicates 196/196/196; datum plus short teams 196;
// shared entry/callback getters 196/196; both getters with per-use datum 196, all plain-confirmed.
// early EBP save, team-byte home and local-slot spill differ.
// Complete iterator/cursor clear 263/263; word/byte population 250/245;
// live pool ordinal 241; unsigned datum 196; complete iterator with ordinal 264; plus byte population 244.
// Earlier 196 (was 196): delayed EBP save, team-byte home and word local-slot spill remain.
// Early/late/both snapshot record references 196/196/196; late pooled-player reference 196;
// native fade reference with word slot 196; player and fade references 196; first-branch
// short rate 196; both snapshot references plus player/rate 196, all plain-confirmed.
// delayed EBP save, missing team-byte home and local-slot spill remain.
// Signed/unsigned byte local slots 244/244; each with indexed fade 244/244;
// signed-byte population 197 (plain 197), signed-byte team 248;
// signed-byte population/slot 245; unsigned-byte slot with signed-byte team 244.
// Timer final-store/result-first/conditional/increment-first 254/254/254/254;
// final-store/result-first with crowded result 254/256; each with complete live state 254/254.
// Round 143: complete per-use state receiver 196; with tail count/shared crowded/both
// 199/248/252. Team admission in body/condition 247/264; with per-use state 247/264.
// All original code restored; delayed EBP save, team-byte and word-slot homes remain.
// delayed EBP save, missing team-byte home and the local-player slot spill
// remain. Retail keeps the local-player index 32-bit throughout (cmp ebp, -1; ebp*4 fade index)
// and stores the masked team bit to a stack byte; with a 32-bit index the body is 997 bytes.
// Tried: cursor player 253; count at loop tail 199; both 257; signed/unsigned word team counters
// 248; tail count plus word team counter 252; unsigned count 242; short count 249; byte team 248;
// shared crowded with word slot 248; indexed fade with word slot 196; shared iterator 196; typed
// pooled player 196; native team bitfield 196; all three 196; direct four-slot traversal 351; with
// shared types 351; with native bitfield 351; all 351; per-use first-loop datum 196; short/byte/word
// teams predicates 196/196/196; datum plus short teams 196; shared entry/callback getters 196/196;
// both getters with per-use datum 196; complete iterator/cursor clear 263/263; word/byte population
// 250/245; live pool ordinal 241; unsigned datum 196; complete iterator with ordinal 264; plus byte
// population 244; early/late/both snapshot record references 196/196/196; late pooled-player
// reference 196; native fade reference with word slot 196; player and fade references 196;
// first-branch short rate 196; both snapshot references plus player/rate 196; signed/unsigned byte
// local slots 244/244; each with indexed fade 244/244; signed-byte population 197; signed-byte team
// 248; signed-byte population/slot 245; unsigned-byte slot with signed-byte team 244. Round 71:
// long local-player index 263 (997 bytes); existing player getter in both loops 196 (identical
// code); long index with the getter 263; long index with a byte team value 263; long index with
// the fade indexed through the globals array 263.

// Round 227: Private slot search sentinel-plus-one start 193; short return 196; short input 199; both
// short 199; simple start with short return/input/both 193/193/193 (three-point gains dropped);
// terminating candidate scan 230. Existing helper restored.
// Round 167: Native unsigned-word private search input/return/both 199/196/199;
// return/result 250, input/return/result 254, input/ordinal 263,
// input/return/ordinal 263, all native word 263. All restored; delayed EBP
// save, teams-byte home and local-slot spill remain.
// Existing search table pointer/const pointer/reference/const reference 196/196/196/196;
// actual entries pointer/const pointer/array/const array 196/196/196/196. Original helper restored.
// Count/unit index/team/local slot/fade/unit home names and two combined groups
// 196 each (fast; reduced-image callee caveat).
// Round 178: Complete fade-step terms with ternary/branch/saturate/update outputs 196/277/212/196;
// the same four with a native full-width local slot 263/251/263/263. Original graph restored;
// delayed EBP save, teams-byte and word-slot homes remain.
// @retail 0x15c150
void function_15c150()
{
	if (g_55e4d0[g_4e9ae8->engine_index])
	{
		function_15be20();
		function_23f000();
		function_159ac0();
		function_15ae70((s_netgame_entry_state *)((byte *)g_4e9ae8 + 0x7dc));
		function_162de0();
		if (g_4e6948->mode != 4) teleporters_update();
		s_transition_player_iterator iterator;
		iterator.data = g_4e8c24;
		iterator.datum_index = NONE;
		iterator.absolute_index = NONE;
		long count = 0;
		while (player_iterator_next((long *)&iterator))
		{
			long index = iterator.datum_index;
			++count;
#pragma inline_depth(0)
			if (!function_15eb20(index))
#pragma inline_depth()
			{
				byte *player = g_4e8c24->data + (index & 0xffff) * 0x21c;
				long unit_index = *(long *)(player + 0x2c);
				if (unit_index != NONE)
				{
					byte *unit = *(byte **)(g_4e0300->data + (unit_index & 0xffff) * 12 + 8);
					*(real *)(unit + 0xf0) = 0.0f;
				}
			}
			function_15b270(index);
			function_15bb20(index);
			function_161f30(index);
			g_55e4d0[g_4e9ae8->engine_index]->p15(index);
			function_162a30(index);
		}
		s_mp_globals *globals = g_4e9ae8;
		*(long *)((byte *)globals + 0xc0c) = count > 8;
		if (count > 8) *(word *)((byte *)globals + 0xc10) |= 1;
		else *((byte *)globals + 0xc10) &= ~1;
		if (g_55e4d0[globals->engine_index])
		{
			bool teams = (*((byte *)g_4e6948 + 0x184) & 1) != 0;
			if (teams)
				for (long team = 0; team < 8; ++team)
					if (function_161e10(team)) function_15ba90(team);
		}
		g_55e4d0[globals->engine_index]->p18();
		if (g_4e6948->mode != 4)
		{
			function_15c000();
			function_15ba20();
			function_23f6e0();
		}
		function_15ebd0();
		function_15ece0();
		function_15ed60();
		globals = g_4e9ae8;
		if (g_55e4d0[globals->engine_index] && globals->w6c == 1 &&
			(g_4e6948->mode == 4 || globals->lc04 == 1))
			*(short *)((byte *)globals + 0xfa) = 0;
		else ++*(short *)((byte *)globals + 0xfa);
		for (word local = transition_local_player_next_15c150(NONE); local != (word)NONE;
			local = transition_local_player_next_15c150(local))
		{
			long index = NONE;
			if (local != (word)NONE)
				index = g_4e8c20->entries[local];
			if (index != NONE)
			{
				byte *player = g_4e8c24->data + (index & 0xffff) * 0x21c;
				real *fade = (real *)((byte *)globals + 0xe4 + local * 4);
				if (*(short *)((byte *)globals + 0xfa) > g_510c54->field_2_3 * 4)
				{
					real value = *fade + 1.0f / (real)g_510c54->field_2_3;
					*fade = value < 1.0f ? value : 1.0f;
				}
				else if (*(long *)(player + 0x2c) == NONE && *(long *)(player + 0x170) <= 0 && function_158a50(index))
				{
					real value = *fade + 1.0f / (real)g_510c54->field_2_3;
					*fade = value < 1.0f ? value : 1.0f;
				}
				else
				{
					if ((!(*((byte *)globals + 0xf4) & (1 << local)) && *(long *)(player + 0x2c) != NONE) ||
						(*(long *)(player + 0x2c) == NONE && !function_158a50(index) &&
						(g_510c54->game_time - *(long *)((byte *)globals + 0x70) < 0 ? 0 : g_510c54->game_time - *(long *)((byte *)globals + 0x70)) > g_510c54->field_2_3))
					{
						if (g_510c54->game_time > real_to_long((real)g_510c54->field_2_3 * 1.5f))
						{
							real value = *fade - 3.0f / (real)g_510c54->field_2_3;
							*fade = value < 0.0f ? 0.0f : value;
						}
					}
				}
			}
		}
	}
}

PRIVATE __forceinline s_mp_globals *transition_start_time_set(s_mp_globals *globals, long time)
{
	*(long *)((byte *)globals + 0x70) = time;
	return globals;
}

// score 5 (was 5): the game options pointer is kept in ebp where retail keeps it in ebx.
// @retail 0x15c550
void function_15c550()
{
	s_mp_globals *globals = g_4e9ae8;
	long requested = globals->lc04;
	if (requested != globals->w6c)
	{
		switch (requested)
		{
		case 3:
			++globals->w6e;
			function_a7810(8);
			*(long *)((byte *)globals + 0xc00) = g_510c54->field_2_3;
			break;
		case 2:
			if (game_engine_get_statborg())
				game_engine_get_statborg()->valid = false;
			if (g_4e6948->mode != 4 && g_510ca0)
				g_510ca1 = true;
			*(long *)((byte *)globals + 0xc00) = g_510c54->field_2_3 * 5;
			break;
		case 1:
			function_157ae0();
			if (game_engine_get_statborg())
				game_engine_get_statborg()->valid = true;
			globals = transition_start_time_set(g_4e9ae8, g_510c54->game_time);
			if (g_4e6948->mode != 4)
			{
				s_game_options_view *options = g_4e6948;
				s_transition_player_iterator iterator;
				iterator.data = g_4e8c24;
				iterator.absolute_index = NONE;
				iterator.datum_index = NONE;
				while (player_iterator_next((long *)&iterator))
				{
					long index = iterator.datum_index & 0xffff;
					long lives = options->value1b8;
					*(short *)(iterator.player + 0x1ac) = (short)(lives ? lives : NONE);
					if (g_55e4d0[globals->engine_index])
					{
						long entity = globals->slots[(short)index];
						if (entity != NONE)
							function_b58c0(entity, 0x20);
					}
					iterator.player[2] |= 8;
				}
			}
			break;
		}
		g_55e4d0[globals->engine_index]->p36(globals->lc04);
		globals = g_4e9ae8;
		globals->w6c = (short)globals->lc04;
		if (g_55e4d0[globals->engine_index] && globals->value24 != NONE)
			function_b58c0(globals->value24, 2);
	}
}

// @retail 0x15ca10
void function_15ca10()
{
	s_mp_globals *globals = g_4e9ae8;
	if (g_55e4d0[globals->engine_index] && g_4e6948->mode != 4)
	{
		if (!g_4e6948->flag1128)
		{
			switch (globals->w6c)
			{
			case 3:
				if (--*(long *)((byte *)globals + 0xc00) <= 0)
				{
					function_15fe50(1);
					*(dword *)globals |= 0x20;
				}
				break;
			case 2:
				if (--*(long *)((byte *)globals + 0xc00) <= 0)
				{
					if ((short)globals->w6e < 31)
						function_15fe50(3);
					else
						function_15ba00();
				}
				break;
			}
			function_15c550();
		}
		else if (!globals->bc08)
		{
			globals->bc08 = true;
			function_a7810(4);
			if (globals->w6c == 1)
			{
				if (globals->lc04 == 1)
				{
					function_15b3a0(function_15b330(false), 0);
					globals = g_4e9ae8;
				}
				if (globals->lc04 != 1)
					function_15c550();
			}
			function_15dd10();
			s_event event;
			game_engine_event_initialize_inline(&event, 0, 0x13);
			function_19eb90(&event);
			if (g_510ca0 && !g_510cb1)
			{
				if (game_engine_get_statborg())
					game_engine_get_statborg()->valid = false;
				g_510ca1 = false;
				function_15c6f0();
				function_196430();
				g_510ca1 = true;
				function_196390();
			}
		}
	}
}

PRIVATE __forceinline byte *transition_statistics(s_mp_globals *globals)
{
	byte *result = NULL;
	if (g_55e4d0[globals->engine_index])
		result = (byte *)globals + 0x304;
	return result;
}

// @retail 0x15c6f0
void function_15c6f0()
{
	s_mp_globals *globals = g_4e9ae8;
	if (function_x340af0())
	{
		bool preserve = function_158eb0();
		dword teams = 0;
		for (long i = 0; i < 16; ++i)
		{
			globals = g_4e9ae8;
			if (i != NONE && i >= 0 && i < g_4e8c24->high_water_index)
			{
				byte *player = g_4e8c24->data + i * g_4e8c24->size;
				short salt = *(short *)player;
				char team = *(char *)(player + 0xc0);
				if (salt && team != NONE)
				{
					long index = (salt << 16) | i;
					byte *statistics = transition_statistics(globals);
					short score = *(short *)(statistics + (index & 0xffff) * 0x1c + 6);
					long mode = 0;
					if (g_4e6948->flag1128)
						mode = 1;
					long value = function_23f260(mode, index, NONE) / 2;
					game_results_set_player_score(i, score, (short)value);
					if (!(player[2] & 2))
					{
						long player_team = *(char *)(player + 0xc0);
						if (player_team != NONE)
						{
							function_1968b0(i, player_team, 3, 1);
							if (!preserve && function_158e90(player_team) == 0)
								function_1968b0(i, *(char *)(player + 0xc0), 4, 1);
						}
					}
					if (*(char *)(player + 0xc0) != NONE && !((word)teams & (1 << *(char *)(player + 0xc0))))
					{
						globals = g_4e9ae8;
						statistics = transition_statistics(globals);
						score = *(short *)(statistics + 0x1c6 + *(char *)(player + 0xc0) * 0x12);
						bool flag = g_4e6948->flag1128;
						value = function_23f360(*(char *)(player + 0xc0), flag != 0) / 2;
						game_results_set_team_score(*(char *)(player + 0xc0), score, (char)value);
						teams |= 1 << *(char *)(player + 0xc0);
					}
				}
			}
		}
	}
	else
	{
		bool preserve = function_158f50();
		for (long i = 0; i < 16; ++i)
		{
			globals = g_4e9ae8;
			if (i != NONE && i >= 0 && i < g_4e8c24->high_water_index)
			{
				byte *player = g_4e8c24->data + i * g_4e8c24->size;
				short salt = *(short *)player;
				if (salt && *(char *)(player + 0xc0) != NONE)
				{
					long index = (salt << 16) | i;
					byte *statistics = transition_statistics(globals);
					short score = *(short *)(statistics + (index & 0xffff) * 0x1c + 6);
					bool flag = g_4e6948->flag1128;
					long value = function_23f260(flag != 0, index, NONE) / 2;
					game_results_set_player_score(i, score, (short)value);
					if (!(player[2] & 2))
					{
						function_1968b0(i, NONE, 3, 1);
						if (!preserve)
						{
							bool flag = g_4e6948->flag1128;

							if (function_23f260(flag != 0, index, NONE) / 2 == 0)
								function_1968b0(i, NONE, 4, 1);
						}
					}
				}
			}
		}
	}
}
