#include "unknown_11c920.h"
#include "globals.h"
#include "engine_peer.h"
#include "unknown_19ec40.h"
#include "unknown_2420a0.h"
#include "game_engine_events.h"

// @flags /O2 /arch:SSE /Gr

bool function_15b2f0();
long function_cbd50(long unit_index, short weapon_index);
short function_101280(long object_index);
bool function_138880();
bool function_138860();
void function_15fe70(long player_index);
bool function_244680(long team, long unit_index);
void __stdcall function_a7810(dword mask);
struct s_242ef1 { point3f const *field_0; };
long function_242ef0(s_242ef1 point, long team);
struct s_team_entry;
s_team_entry *function_15e410(short team);
void function_242ba0(long marker_index, long object_index, long player_index);
void function_197210(long player_index, long value14, long value10);
void function_242e00(long player_index, long team);
void function_242660(long object_index, bool flag);
void function_2430a0(long player_index, bool flag);

static inline bool slot_flag_clear_2403b0(s_slot_table *table, long team)
{
	return !(table->flags[team] & 1);
}

// score 190 (was 190): frame 0x3c agrees; object-pool reload, completion
// flag stores and final predicate layout differ. Scoring team word 187
// (three-point gain rejected), long 214; blocked long/byte 190/190; existing
// flag helper force-inline 190; returned point 199; marker bits 190; option
// scope 190. Original body and helper declaration retained.
// Earlier 190 (was 190): pool reload and separate completion stores remain;
// pool reload and separate completion stores remain;
// Earlier: pool reload and separate completion stores remain;
// read-only unit/type result 190/190; scoring team at call 226; completion event prepared first 193;
// marker/slot entry lifetimes 190/190; success-result predicate 193; type result plus event preparation 193.
// Read-only helper input 190; table reference 190; native team parameter 190; result-first predicate 192;
// flag byte sample 190; direct capped result 190; cap and table reference 190; option guard order 190. Pool
// reload and separate completion stores remain.
// Earlier 190 (was 190): Cached pool base and merged completion stores remain.
// Native player record 190; scoring-team field binding 190; both 190;
// increment counter binding 202; decrement binding 190; both counters 202;
// marker-team value 194; native player with both counters 202.
// Earlier 190 (was 190): cached pool, merged completion stores and flag-result materialization remain.
// Predicate long/short/byte/signed-byte returns 189/190/190/190;
// byte predicate input 190; byte input with long/short/byte results 189/190/190.
// Both one-point gains rejected; original predicate and body restored.
// Earlier 190 (was 190): cached pool base, merged completion stores and predicate result remain.
// Cached pool base and merged completion stores remain.
// cached pool, merged completion stores and flag-result materialization remain.
// cached pool base, merged completion stores and predicate result remain.
// Earlier: Cached pool base and merged completion stores remain.
// Earlier: cached pool, merged completion stores and flag-result materialization remain.
// Earlier: cached pool base, merged completion stores and predicate result remain.
// Native unit/weapon/both header references 190/190/190; external carried-index,
// selected-slot or both field bindings 190/190/190; initializer return used directly 311;
// external options record reference 190.
// pool-data reload, completion stores and final predicate layout still differ.
// permission result 190; fallback permission scope 190; present-unit scope 190
// eligible-weapon scope 190; present-slot scope 190; present-marker scope 190
// unit/weapon scopes 190; option once 190.
// Earlier 190 (was 190): frame 0x3c agrees; cached pool base, merged completion stores and predicate layout remain.
// Negative-three addition 190; default-NONE/explicit-arm team results 191/190; reversed completion
// bit order 190; in-place limit 190; two-use stored-short ticks 190; limit plus stored ticks 190;
// default-NONE team plus negative-three addition 191. Opening body and existing helper restored.
// Round 144: native flag-bit object by value with bool/byte/short/long results 190/190/190/192;
// native flag-bit object pointer with the same result widths 190/190/190/192. All restored;
// protected-reader pool reuse and merged completion stores remain.
// frame 0x3c agrees; cached pool base, merged completion stores and predicate layout remain.
// Round 364: Fresh player/unit/slot reads 254/190/271; player-unit/player-slot/
// unit-slot/all three 254/329/271/329; unit-index field at each use 195.
// Round 366: Team-first existing predicate with original/const/native-team/both inputs 190 each;
// long/short/byte/signed-byte results 189/190/190/190. One-point reduction rejected.
// Event initialization between completion bits 183; initialize/first bit/cause/second bit 163;
// first bit/initialize/cause/second bit 183; both preparation steps first 193. Separate event
// buffers 196/160/183/193. Seven-point forms rejected; raw 163/160 regress the instruction
// sequence or frame (0x60), so all restored.
// Earlier: frame 0x3c agrees; cached pool base, merged completion stores and predicate layout remain.
// Native flag-array and actual flag-element reference predicate inputs, each
// with logical/complement extraction: bool results 190, long results 189;
// all eight restored, one-point gains below threshold.
// noinline 101280 190; noinline 15b2f0 190; noinline 138880 190; noinline 138860 190; noinline 15fe70 190;
// noinline 244680 190; noinline 197210 190; noinline 242660 190. All restored.
// Round 167: Plain descending notification-mask loop 187 (three-point gain dropped);
// with completion initialization between bits / preparation before the second bit /
// initialization before both bits 240/251/240; independent event buffers 193, with
// the first two interleaves 240/251; existing bitfields plus first interleave 240.
// Loop remains rolled; extra branches and event/store sequencing regress. All restored.
// Complete eligibility bool/byte/short/long results 190/190/190/190;
// default-false reader-gate results 190/190/190/190. Pool reload and completion stores remain.
// Slot/limit/ticks/marker/unit/weapon home names and scalar/all combinations
// 190 each (fast); original body restored.
// Complete entry carried-unit value 221; with short slot/clock-first product/both
// 239/221/239; word teams alone/slot/product/all 207/223/207/223 (fast).
// Original unit observations, counter arithmetic, stores and reader contracts restored.
// @retail 0x2403b0
void __stdcall function_2403b0(long player_index)
{
	s_event event;
	point3f position;
	if (g_4e6948->mode == 4 || !function_15b2f0())
		return;
	byte *player = g_4e8c24->data + (player_index & 0xffff) * 0x21c;
	long unit_index = *(long *)(player + 0x2c);
	if (unit_index == NONE)
		return;
	byte *unit = *(byte **)(g_4e0300->data + (unit_index & 0xffff) * 12 + 8);
	long weapon_index = function_cbd50(unit_index, *(signed char *)(unit + 0x212));
	if (*(short *)(unit + 0x1fc) != NONE || weapon_index == NONE || (short)weapon_index == NONE ||
		function_101280(weapon_index) != 1 || *((byte *)g_4e6948 + 0x1128))
		return;
	byte *weapon = *(byte **)(g_4e0300->data + (weapon_index & 0xffff) * 12 + 8);
	long slot = *(short *)(weapon + 0x17e);
	if (slot == NONE)
		return;
	if (!g_55e4d0[g_4e9ae8->engine_index]->p35(player_index, 1) && !function_138880())
		function_15fe70(player_index);
	if (g_4e6948->mode_180 == 9 && !(g_51ec80->flags[slot] & 8))
	{
		signed char team = *(signed char *)(player + 0xc0);
		if (team == NONE)
			return;
		if (function_244680(team, *(long *)(player + 0x2c)))
		{
			if (g_51ec80->e[slot] == NONE)
			{
				game_engine_event_initialize_inline(&event, 10, 14);
				game_engine_event_set_cause_player(player_index, &event);
				function_19eb90(&event);
			}
			long limit = (short)*(short *)((byte *)g_4e6948 + 0x244) * g_510c54->field_2_3;
			long ticks = g_51ec80->e[slot] + 1;
			if (ticks > limit)
				ticks = limit;
			g_51ec80->e[slot] = (short)ticks;
			if ((short)ticks == limit)
			{
				g_51ec80->flags[slot] |= 8;
				g_51ec80->flags[slot] |= 1;
				game_engine_event_initialize_inline(&event, 10, 15);
				game_engine_event_set_cause_player(player_index, &event);
				function_19eb90(&event);
				function_a7810(0x200);
				function_a7810(0x100);
				return;
			}
		}
		else
		{
			long ticks = g_51ec80->e[slot] - 3;
			if (ticks <= NONE)
				ticks = NONE;
			g_51ec80->e[slot] = (short)ticks;
		}
		function_a7810(0x100);
		return;
	}
	function_b9dd0(*(long *)(player + 0x2c), &position);
	s_242ef1 point = { &position };
	long marker = function_242ef0(point, *(signed char *)(player + 0xc0));
	if (marker == NONE)
		return;
	bool blocked = false;
	if ((g_4e6948->flags22c & 8) && *(long *)((byte *)g_4e6948 + 0x240) != 1 && *(long *)((byte *)g_4e6948 + 0x240) != 2 && g_4e6948->mode_180 != 9)
	{
		signed char team = *(signed char *)(player + 0xc0);
		if (!function_15e410(team) || !slot_flag_clear_2403b0(g_51ec80, team))
			blocked = true;
	}
	if (blocked)
		function_2430a0(player_index, true);
	else if (function_138860())
	{
		if (g_4e6948->mode_180 == 9)
			function_242ba0(marker, weapon_index, player_index);
		else
		{
			short team = (short)slot == 8 ? NONE : (short)slot;
			function_197210(player_index, 1, slot);
			function_242e00(player_index, team);
			function_242660(weapon_index, false);
		}
	}
}
