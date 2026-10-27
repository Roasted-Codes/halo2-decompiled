// @flags /O2 /Ob1 /Gr
#include "unknown_11c920.h"
#include "unknown_058dd0.h"
#include <string.h>

struct s_session_search;
void function_72330(c_session_state_matchmaking *arg_0);
void function_72540(c_session_state_matchmaking *arg_0);
void function_72260(c_session_state_matchmaking *arg_0);
void function_72170(c_session_state_matchmaking *arg_0);
void function_90840(s_session_search *arg_0);
long function_66050(c_class_58d20 *arg_0, long arg_1);
long network_session_find_member(c_class_58d20 *arg_0, const s_session_member_identity *arg_1);
bool function_70d60(c_session_state_matchmaking *arg_0);
bool function_70ea0(c_session_state_matchmaking *arg_0);
bool function_71210(c_session_state_matchmaking *arg_0);
bool function_712d0(c_session_state_matchmaking *arg_0);
bool __stdcall function_71390(c_session_state_matchmaking *arg_0);
bool function_71480(c_session_state_matchmaking *arg_0);
bool __stdcall function_71730(c_session_state_matchmaking *arg_0);
bool __stdcall function_71d70(c_session_state_matchmaking *arg_0);
bool network_session_host_set_value49f8(c_class_58d20 *arg_0, long arg_1);

// score 182 (was 182): Frame 0x10 agrees; primary-session ESI joins and byte-return normalization remain.
// Earlier 182 (was 182): primary-session ESI joins and byte return normalization remain.
// Frame 0x10 agrees; primary-session ESI joins and byte normalization remain.
// Earlier: frame and length agree; primary-session EBP versus ESI, mode joins
// and final Boolean normalization differ; byte return result 182; word return result 275;
// long return result 258; unsigned return result 258; independent mode gates 243;
// mode flag else 243; member gates with retained frame 243; terminal gates with retained frame 243.
// Earlier: primary-session EBP/ESI joins and return normalization remain; signed-byte
// result and readiness, update, mode-value and two dispatch noinline declarations 185 each in the
// reduced image; unchanged preview 185 (full 182).
// primary-session join carrier and return normalization remain;
// secondary consumer scope / state phases / byte result after state / after sessions 182/182/185/185f;
// scoped dispatch / member receiver / both lifetimes / with dispatch 183/182/182/183f.
// Earlier: Primary-session join carriers and Boolean normalization remain. final existing state query 182; initial
// existing state query 182; both existing state queries 182; dispatch result accumulation 182; state
// queries and accumulation 182; result after owner capture 184; native state object receiver 182; native
// signed state and ordinal 182.
// primary-session ESI joins and canonical return normalization remain;
// low-bit / true-equality return 184/212; primary object reference 182, with those returns 184/212;
// owner plus primary references 182; primary reference with native dispatch / low-bit return 183/185.
// Earlier: primary-session ESI joins remain; actual search-status member cursor
// at its two consumers / at entry 182/182. Original byte-result body restored.
// Earlier: primary session join registers and result normalization remain; cleanup
// interval/exception-first/nested gate 202/234/202; initial/final/both state orders 186/182/186; native ready
// byte 182; secondary half-open range 182.
// primary-session ESI joins and return normalization remain.
// Tested dispatch results in cases 6..13 separately 209/209/209/209/209/208/207/206;
// all eight tested results 243. All original byte assignments restored.
// Initial/type/final direct field observations 182/182/182; initial+type/initial+final/type+final/all
// 182/182/182/182; all with the two-use secondary state 182. Original byte-result body restored.
// Round 189 positive result after direct inactive-reset exit: byte/bool 241/253; terminal-true
// before reset 241/253; retail case order 242/254; both interactions 242/254. Original shared exit
// and byte result restored.
// Inline live-state predicate at secondary/primary/both 227/223/227; existing live-state function
// at secondary/primary/both 227/223/227; mixed helper boundaries 227/227. All fast.
// Omit initial unused state store 226; omit final 219; phase result initialization 220; omit both
// 249; omit initial with phase result 239; omit final with phase result 248; omit both with phase
// result 265; member skip guard 182 (fast).
// Round 165: At-use owner/primary/secondary pointer fields and their three pairs/all
// 267/269/224/246/239/251/250; two-use optional-host state observation 182.
// Original pointer snapshots, local state stores and complete body restored.
// Round 140: four caller-only declarations tie 182 and are excluded diagnostics. Callee
// reset/member/value/search/host declarations 280/182/182/182/182; member plus value 182; reset plus host and
// all five 280. Reset forms lose matched callers; combined forms lose reduced controls. All declarations and
// executable code restored.
// Negative update-result bool/byte/short/long from entry 296/296/297/305;
// after the reset exit 307/307/292/299. Original positive byte-result body restored.
// On the byte-result graph: native owner/primary/secondary lexical homes, all
// pairs, all three, and complete role-correct workspaces 182 each (eight forms).
// Round 215: Coherent native byte/signed-byte virtual returns, each with byte/Boolean
// result storage and original/retail case order, 243/241/243/241 each. Manager caller
// loses its match in all eight; original Boolean contracts and complete body restored.
// Round 233: Dispatch success-only result stores, byte/bool 277/253;
// reversed captures, early terminal success, and both 277/253/277/253/277/253.
// Original result assignments, captures and both local state stores restored.
// Scalar state/index/host/first spill/last spill homes 182 each; paired spills,
// combined value homes, and all scalar homes 182 each (fast).
// Separate initial-state, type and final-state lifetimes in all seven combinations
// 182 each; all separate with retail case order 183. Original body restored.
// Excluded-state conjunction owns the failed arm at initial/final/both joins 182/182/182;
// each with Boolean result 243/243/243; both with physical case order at byte/Boolean
// result 183/241 (fast). Original positive readiness arms and byte result restored.
// Round 153: advancing member cursor on the retained byte graph 182; structured reset/active join indexed/cursor 182/182, native Boolean 243/243; successful-first join indexed/cursor 182/182, cursor Boolean 243. Original body and inherited state stores restored.
// @retail 0x706f0
bool c_session_state_matchmaking::update()
{
	byte local_3 = false;
	s_session_owner *local_0 = owner;
	c_class_58d20 *local_1 = local_0->session_a;
	c_class_58d20 *local_2 = local_0->session_b;
	long local_4 = local_1->state;
	if (!local_4 || function_058d90(local_1))
	{
		function_06df60(local_0, 0, 0, 0);
		mode = 1;
		goto local_done;
	}
	if (local_4 == 5 || local_4 == 6 || local_4 == 7 || local_4 == 8)
	{
		if (mode == 3)
		{
			if (!flag10)
				mode = 19;
			if (mode == 3)
			{
				if (!*(bool *)((byte *)this + 0x14))
					function_72330(this);
				if (mode == 3)
				{
					function_72540(this);
					if (mode == 3)
					{
						if (local_2->state > 2 && local_2->state <= 8)
						{
							for (long local_5 = 0; local_5 < local_2->member_count; local_5++)
							{
								if (local_2->members[local_5].unknown88 == 1 &&
									network_session_find_member(local_1,
										(const s_session_member_identity *)&local_2->members[local_5]) != NONE)
									mode = 5;
							}
						}
						if (mode == 3)
						{
							long local_6 = NONE;
							if (local_1->state > 2 && local_1->state <= 8)
								local_6 = local_1->value49c8;
							if (function_66050(local_1, local_6))
								mode = 7;
						}
					}
				}
			}
		}
		if (mode == 3)
			function_72260(this);
	}
	else
	{
		volatile long local_7 = local_4;
	}
	if (flag97c)
		function_90840((s_session_search *)&flag97c);
	function_72170(this);
	if (mode == 3)
	{
		switch (local_1->type)
		{
		case 6: local_3 = function_70d60(this); break;
		case 7: local_3 = function_70ea0(this); break;
		case 8: local_3 = function_71210(this); break;
		case 9: local_3 = function_712d0(this); break;
		case 10: local_3 = function_71480(this); break;
		case 11: local_3 = function_71730(this); break;
		case 12: local_3 = function_71d70(this); break;
		case 13: local_3 = function_71390(this); break;
		default: mode = 1; break;
		}
	}
	local_4 = local_1->type;
	if (local_4 != 7 && local_4 != 8 && local_4 != 9 && local_4 != 13 && flag97c)
		function_090c80(&flag97c);
	if (mode != 3 && mode != 2)
	{
		if (local_1->function_058d20())
			network_session_set_mode(local_1, 1);
		function_06df60(local_0, 1, 0, 0);
		local_3 = true;
	}
	local_4 = local_1->state;
	if (local_4 == 5 || local_4 == 6 || local_4 == 7 || local_4 == 8)
		network_session_host_set_value49f8(local_1, mode);
	else
	{
		volatile long local_8 = local_4;
	}
local_done:
	return local_3;
}
