// @flags /O2 /Ob1 /arch:SSE /Gr
/* UNKNOWN_249E20.CPP: lookups in the structure bsp's audibility data.
   Decompiled by lane F: 0x18c3b0 calls them with register arguments. */

#include "unknown_11c920.h"
#include <string.h>
#include "unknown_249e20.h"

// @retail 0x249e20
long function_249e20(s_structure_bsp_view *bsp, long index)
{
	long result = NONE;

	if (index != NONE && bsp->audibility_count > 0)
	{
		s_structure_audibility *audibility = bsp->audibility;
		for (long i = 0; i < audibility->cluster_count; i++)
		{
			if (audibility->clusters[i] == index)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

// score 9 (was 9): audibility load before saved-register/index setup remains;
// tried entry row first 31f; entry row after result 31f; second category default 29f; explicit absence results 42f;
// complete category selection 37f; native row domain 9f; native stride domain 9f; read only word table 9f;
// direct table fields 44f; direct row expressions 38f.
// entry saves/index load and audibility EDI allocation differ;
// shared bit test/read-only bits 9/9; second-arm cursor 44; category loops
// indexed/shared test/cursor/mask 58/58/46/45; final result selection 37.
// @retail 0x249e60
long function_249e60(long cluster_index, s_structure_bsp_view *bsp, long index)
{
	long result = NONE;

	if (bsp->audibility_count > 0)
	{
		long row = 2 * index;
		dword *bits = bsp->audibility->bits;
		long stride = (bsp->cluster_count + 31) >> 5;

		if (bits[stride * row + (cluster_index >> 5)] & (1 << (cluster_index & 0x1f)))
		{
			result = 0;
		}
		else if (bits[stride * (row + 1) + (cluster_index >> 5)] & (1 << (cluster_index & 0x1f)))
		{
			result = 1;
		}
	}
	return result;
}

/* ---- lane O: the values kept for each pair of clusters ---- */

/* the index of the pair (a, b), a < b, in a triangular table of n clusters */
static inline long cluster_pair_index(long a, long b, long n)
{
	return (n - 1) * a - (a + 1) * a / 2 + b - 1;
}

static inline long cluster_minimum(long a, long b)
{
	long result = b;

	if (a <= b)
		result = a;
	return result;
}

static inline long cluster_maximum(long a, long b)
{
	long result = b;

	if (a > b)
		result = a;
	return result;
}

/* the byte the bsp keeps for a pair of clusters (bit 7: audible, the rest
   a distance) */
// @retail 0x249ed0
byte function_249ed0(short cluster_a, short cluster_b, s_structure_bsp_view *bsp)
{
	if (cluster_a != cluster_b)
	{
		if (cluster_a > cluster_b)
		{
			short swap = cluster_a;

			cluster_a = cluster_b;
			cluster_b = swap;
		}
		return bsp->cluster_pair_values[(bsp->cluster_count - 1) * cluster_a - (cluster_a + 1) * cluster_a / 2 + cluster_b - 1];
	}

	return 0;
}

/* true when sound carries between two clusters */
// @retail 0x249c20
bool function_249c20(s_structure_bsp_view *bsp, long cluster_a, long cluster_b)
{
	bool result = false;

	if (cluster_a != cluster_b)
	{
		if (bsp->audibility_count > 0)
		{
			dword *bits = bsp->audibility->cluster_pair_bits;
			long low = cluster_minimum(cluster_a, cluster_b);
			long high = cluster_maximum(cluster_a, cluster_b);
			long index = cluster_pair_index(low, high, bsp->cluster_count);

			result = (bits[index >> 5] & (1 << (index & 0x1f))) != 0;
		}
		else
		{
			result = function_249ed0((short)cluster_a, (short)cluster_b, bsp) >> 7;
		}
	}
	return result;
}

/* the two rows of cluster bits of an index (512 bits each at most) */
// @retail 0x249c90
void function_249c90(dword *bits_a, s_structure_bsp_view *bsp, long index, dword *bits_b)
{
	if (bsp->audibility_count > 0)
	{
		s_structure_audibility *audibility = bsp->audibility;
		long row = 2 * index;
		long count = (bsp->cluster_count + 31) >> 5;
		dword *source_b = audibility->bits + count * (row + 1);
		dword *source_a = audibility->bits + count * row;

		memcpy(bits_a, source_a, count * sizeof(dword));
		memcpy(bits_b, source_b, ((bsp->cluster_count + 31) >> 5) * sizeof(dword));
	}
	else
	{
		memset(bits_a, 0, 0x40);
		memset(bits_b, 0, 0x40);
	}
}

/* the row of door bits of an index (128 bits at most) */
// @retail 0x249d10
void function_249d10(s_structure_bsp_view *bsp, dword *bits, long index)
{
	if (bsp->audibility_count > 0)
	{
		s_structure_audibility *audibility = bsp->audibility;

		if (audibility->door_count > 0)
		{
			long count = (audibility->door_count + 31) >> 5;

			memcpy(bits, audibility->door_bits + count * index, count * sizeof(dword));
		}
	}
	else
	{
		memset(bits, 0, 0x10);
	}
}

/* the distance sound travels between two clusters */
#pragma optimize("s", on)
// score 65 (was 65): entry constants, branch saves and returns differ; reported 182 includes eleven fill bytes.

// score 65 (was 65): No frame; entry zero/default constants and branch-only saves differ.
// Minimum/maximum/both first-input results 65/65/65; minimum/maximum/both return paths 63/66/63;
// conditional extrema 63; byte sample with first-input extrema 75. Sub-four gains and
// matched-neighbor losses rejected.
// entry constants, branch-only record saves and native sample/return ownership differ; eleven fill bytes.
// entry constants, branch saves and returns differ; reported 182 includes eleven fill bytes.
// Maximum sentinel first 88; interior interval first 82 kept; integer sample 88; read-only audibility 88;
// ordered cluster parameters 91; named pair index/range 88/88; direct fallback 84; both boundaries 82.
// Unequal-cluster scope 81; fallback first 81; total result assignment 82; zero/upper
// result defaults 80/80; word/short samples 76/76; native count observation 82.
// Existing minimum/maximum/both/index force-inline declarations 82/82/82/82;
// fallback inline/noinline 82/82; extrema before receiver 81 (below gate); high before low 82.
// Named fraction/span-first/bounds-after-sample/bounds-before-table 82/82/82/82;
// full/final interpolation expressions 82/82; native endpoint tests with/without fraction 85/85.
// Sample offset long/short/word 78/65/77; direct receiver 65 kept; table-operation first 65;
// explicit endpoint results 79; word-path returns 65; shared index row parts 76.
// Direct receiver: plain 65; active 171 bytes unchanged, raw differing rows remain 65.
// Wrapped byte offset/native byte pair/record receiver 78/81/80; byte endpoints 83;
// zero/upper defaults with byte offset 75/78; fraction/production exits 78/79. Entry constants and branch saves remain.
// Fallback masked byte/word/long/dword carriers 78/78/78/78;
// lower field observations 77; produced span 65;
// both bound fields 77; byte sample with direct bounds 83.
// Direct short/long/word offset 66/76/76; record reference 76; table pointer 65; distance scalar names 65; record/short offset 65; byte record sample 82.
// @retail 0x249d60
real function_249d60(s_structure_bsp_view *bsp, long cluster_a, long cluster_b)
{
	real local_0 = 255.0f;
	if (cluster_a == cluster_b)
		local_0 = 0.0f;
	else if (bsp->audibility_count > 0)
	{
		long low = cluster_minimum(cluster_a, cluster_b);
		long high = cluster_maximum(cluster_a, cluster_b);
		word value = bsp->audibility->cluster_pair_distances[cluster_pair_index(low, high, bsp->cluster_count)];
		if (value > 0 && value < 0xff)
		{
			real local_1 = bsp->audibility->distance_lower;
			real local_2 = bsp->audibility->distance_upper;
			local_0 = (real)(value - 1) * (1.0f / 253.0f);
			local_2 -= local_1;
			local_0 *= local_2;
			local_0 += local_1;
		}
		else
			local_0 = value ? 256.0f : 0.0f;
	}
	else
		local_0 = (real)(function_249ed0((short)cluster_a, (short)cluster_b, bsp) & ~0x80) * (256.0f / 127.0f);
	return local_0;
}
#pragma optimize("", on)
