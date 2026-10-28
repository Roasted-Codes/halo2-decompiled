// @flags /O2 /Ob1 /arch:SSE /Gr
/* UNKNOWN_1564E0.CPP: the Bink playback functions with float arithmetic
(unknown_01e930.cpp holds the rest). Retail builds them with SSE: the
remaining ticks convert and scale through cvtsi2ss/mulss, and the sound
callback selects its volume through a movss stack slot. */

#include "unknown_11c920.h"
#include "globals.h"
#include "unknown_01e930.h"
#include "slot_handler.h"

static __forceinline long real_to_long(real value);

/* per-track sound settings for the Bink sound callback */
struct s_bink_sound_track
{
	dword unknown00;
	real volume;
	byte unknown08[0x18];
};

s_bink_sound_track g_4e9300[8];

// @retail 0x1564e0
long bink_playback_ticks_remaining(void)
{
	s_bink_movie *movie = (s_bink_movie *)g_4e9188.movie;
	long result = 0;

	if (movie)
	{
		dword remaining = movie->frames - movie->frame_number;
		dword milliseconds = movie->frame_rate_divisor * movie->frames * 1000 / movie->frame_rate;
		real seconds;
		real ticks;

		milliseconds = milliseconds * remaining / (movie->frames > 1 ? movie->frames : 1);
		seconds = (long)milliseconds * 0.001f;
		ticks = seconds * 30.0f;
		result = real_to_long(ticks);
		result = result > 0 ? result : 0;
	}
	return result;
}

/* the Bink sound callback: a track's volume */
// @retail 0x156b30
real __stdcall function_156b30(long track, long type)
{
	real result = 0.0f;

	if (type == 0x3000577)
		result = g_4e9300[track].volume;
	return result;
}

/* the screen rectangles (unknown_0167a0.cpp) */
struct short_rect
{
	short v0, v1, v2, v3;
};

struct short_rect_pair
{
	short_rect a, b;
};

struct s_unknown_485a88
{
    byte flag;
    short_rect_pair rects;
};
extern s_unknown_485a88 g_unknown_485a88;
#define g_485a8a (g_unknown_485a88.rects)
extern byte g_4c1a18;

struct s_bink_vertex
{
	real x;
	real y;
	real u;
	real v;
	dword color;
};


void __stdcall function_35b90(void *material);
void __stdcall function_363a0(void *vertices);
void __stdcall function_1e930(long a);

// score 64 (was 64): Frame 0x64 and retail length recovered with SSE playback ownership
// Frame 0x64 and retail length recovered with SSE playback ownership
// and centered-first rectangle selection; fullscreen word loads, vertex conversion/loop homes remain.
// Earlier form used x87 conversions at frame 0x68. SSE body 103; direct screen fields 98;
// centered-first 75; UV stores first 94; long ordinal 117; short corner 114; vertex storage first
// 103; named bounds 103. Four-component publication orders uvxy/xyuv/uxvy/xuyv 65/73/75/74;
// real conditional arms 38, exact-only one-use/cast forms restored. Plain centered-first 75.
// Round 223: native edge defaults 116; all-long edges 77; independent corner 75;
// two-use side predicates 85; output cursor 75; defaults/wide/cursor with predicates
// 121/82/85. Position branches 73; UV then position branches 66; all branch stores
// 65; UV then position branch stores 64 (plain, kept). Rectangle result 106; native
// vertex initializer 109; rectangle with position branches in either store order
// 54/64, match-only record forms restored. Fullscreen word loads and loop homes remain.
// Complete independent short screen inputs 108; with native UV/position branches 119;
// input scalars plus native cursor 107/119; unsigned bounded ordinals 108/119/107/119.
// These shrink the frame to 0x58; original aggregate frame 0x64 and body restored.
// Coupled edge/input-rectangle/output-array lexical identities, seven subsets and complete edge declaration
// order: 64/64/64/64/64/64/64/64. Fullscreen word loads and vertex/loop homes remain
// original identities and declarations restored.
// @retail 0x156960
void function_156960(void)
{
	short_rect screen = g_485a8a.a;
	short left, right, top, bottom;
	s_bink_vertex vertices[4];

	if (!(g_4e9188.flags & 0x10))
	{
		short screen_width = screen.v3 - screen.v1;
		short screen_height = screen.v2 - screen.v0;

		left = (screen_width - g_4e9188.width) / 2;
		right = (screen_width + g_4e9188.width) / 2;
		top = (screen_height - g_4e9188.height) / 2;
		bottom = (screen_height + g_4e9188.height) / 2;
	}
	else
	{
		right = screen.v3;
		left = screen.v1;
		bottom = screen.v2;
		top = screen.v0;
	}

	for (short i = 0; i < 4; i++)
	{
		long corner = i + 1;

		if (corner & 2)
			vertices[i].u = g_4e9188.width;
		else
			vertices[i].u = 0.0f;
		if (i > 1)
			vertices[i].v = g_4e9188.height;
		else
			vertices[i].v = 0.0f;
		if (corner & 2)
			vertices[i].x = right;
		else
			vertices[i].x = left;
		if (i > 1)
			vertices[i].y = bottom;
		else
			vertices[i].y = top;
		vertices[i].color = 0xffffffff;
	}

	function_35b90(g_4e9188.material);
	function_363a0(vertices);
	if (g_4c1a18)
	{
		function_1e930(1);
		g_4c1a18 = 0;
	}
}
