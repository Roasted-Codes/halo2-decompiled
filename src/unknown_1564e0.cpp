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
