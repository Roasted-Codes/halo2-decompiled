// @flags /O2 /arch:SSE /Gr
/* UNKNOWN_239B80.CPP: two-dimensional polygon helpers (convex hulls,
   clipping against lines and point-in-polygon tests over point2f
   arrays) */

#include "unknown_11c920.h"
#include "unknown_0259d0.h"
#include <float.h>
#include <string.h>

#define k_real_epsilon 0.0001f
#define MAXIMUM_POLYGON_POINTS 48

struct vector2f { real i, j; };

/* a line in the plane: points p with dot(n, p) == d */
struct plane2f
{
	vector2f n;
	real d;
};

PRIVATE __forceinline bool polygon_clip_intersection_23a430(plane2f const *plane,
	point2f const *first, point2f const *second, long count, short capacity, point2f *output)
{
	real dy = first->y - second->y;
	real dx = first->x - second->x;
	real denominator = plane->n.i * dx;
	denominator += plane->n.j * dy;
	if ((denominator < -0.0001f || denominator > 0.0001f) && count < capacity)
	{
		real fraction = (plane->n.j * first->y + plane->n.i * first->x - plane->d) / denominator;
		dx *= fraction;
		output->x = first->x - dx;
		dy *= fraction;
		output->y = first->y - dy;
		return true;
	}
	return false;
}

// score 101 (was 101): frame 0x618 agrees; result/cursor initialization and displacement/fraction SSE homes still differ.
// Earlier: frame 0x618 agrees; cursor/result initialization, delta XMM
// homes and extra fraction copies remain. X-first deltas 109; full denominator 103;
// scales before stores 101; first input record 207; Boolean helper result 101;
// aggregate intersection 152; capacity-first gate 108; native input count 153;
// intersection role names 101; output-first helper 101; count-result helper 101;
// x-first deltas with full denominator 107.
// Shared difference/projection/both 109/101/109; actual output cursor 256;
// difference/projection with output cursor 256/256; natural previous update 101; cursor with previous update 256.
// @retail 0x23a430
short function_23a430(short count, point2f const *points, plane2f const *plane,
	real epsilon, short capacity, point2f *output)
{
	point2f copy[128];
	long sides[128];
	if (points == output)
	{
		memcpy(copy, points, count * sizeof(point2f));
		points = copy;
	}
	long original_count = count;
	long positive = 0;
	long negative = 0;
	for (long i = 0; i < original_count; i++)
	{
		real distance = points[i].y * plane->n.j + points[i].x * plane->n.i - plane->d;
		if (distance > epsilon)
		{
			sides[i] = 1;
			positive++;
		}
		else if (0.f - epsilon > distance)
		{
			sides[i] = 0;
			negative++;
		}
		else
			sides[i] = NONE;
	}
	long result = 0;
	if (!negative)
	{
		memcpy(output, points, original_count * sizeof(point2f));
		return (short)original_count;
	}
	if (!positive)
		return 0;
	long previous = original_count - 1;
	for (long current = 0; current < original_count; previous = current++)
	{
		if (sides[current] == 0)
		{
			if (sides[previous] == 1 && polygon_clip_intersection_23a430(plane,
				&points[current], &points[previous], result, capacity, &output[result]))
				result++;
		}
		else
		{
			if (sides[current] == 1 && sides[previous] == 0 && polygon_clip_intersection_23a430(plane,
				&points[previous], &points[current], result, capacity, &output[result]))
				result++;
			if (result < capacity)
				output[result++] = points[current];
		}
	}
	return (short)result;
}

static inline real dot_product2d(vector2f const *a, point2f const *b)
{
	return a->i * b->x + a->j * b->y;
}

static inline real normalize2d(vector2f *v)
{
	real m = (real)sqrt(v->i * v->i + v->j * v->j);
	if (fabs(m) < k_real_epsilon)
		return 0.f;
	real inv = 1.f / m;
	v->i = inv * v->i;
	v->j = v->j * inv;
	return m;
}

static inline bool points2d_equal(point2f const *a, point2f const *b)
{
	return fabs(a->x - b->x) < k_real_epsilon && fabs(a->y - b->y) < k_real_epsilon;
}

/* two pi, set up at run time */
real g_55e470;

long function_239d50(long count, point2f const *points, point2f *hull);
short function_239e50(short count, point2f const *points, short *indices);

/* 0 when every point is the same, 1 when they are on one line, 2 otherwise */
// score 42 (was 42): state/index/point registers (retail ECX/EDX/ESI) and the XMM homes
// differ; retail keeps the line normal's j in XMM2 through the scaling, so its constants
// sit one XMM register higher. Local/formal point cursor with short ordinal 94/93; short
// remaining count 94/93; long ordinal 97/97; long remaining count 94/93; byte state 91;
// unsigned word ordinal 85; state increments 76; terminal equality 43; first point before
// scan 85; normalizer reference 42; point-first dot 42; success normalizer 102; normalizer
// input vector 126; compound scales 42; factor-first scales 42; positive normalizer scope
// 42; long point index 101; count-first guard 99; long state 86; plane/point names 42;
// forced normalizer 42; forced dot 42; both forced 42; single-result normalizer 42;
// squared-length expression 42; staged scales 42; reverse scale publication 42; length
// workspace 56; signed-distance expression 42; native first-point components 63;
// accumulated dot result 46; repeated j input 42; repeated i input 42; both scalar inputs
// 126; state renamed to sort before the index 42; zero-length arm first 44; `>= epsilon`
// far test 68; named normalizer length 56; line declared before the first point 42.
// state/index/point and normalization SSE homes still differ at frame 0x18.
// Earlier: coupled state/index/XMM homes and normalized Y load remain;
// local/formal point cursor with short ordinal 94/93; short remaining count
// 94/93; long ordinal 97/97; long remaining count 94/93. Opening body restored.
// zero/one SSE homes, state/index/point registers and normalized Y load remain;
// byte state 91; unsigned word ordinal 85; state increments 76; terminal equality 43;
// first point before scan 85; normalizer reference 42; point-first dot 42; success normalizer 102.
// Frame 0x18 agrees; state/index, point pointer and SSE constant registers differ.
// normalizer input vector 126; compound scales 42; factor-first scales 42; positive normalizer scope 42; long point index 101; count-first guard 99; long state 86; plane/point names 42; forced normalizer 42; forced dot 42; both forced 42.
// Earlier: state/index/point and normalization XMM homes remain.
// Single-result normalizer 42; squared-length expression 42; staged scales 42;
// reverse scale publication 42; length workspace 56; signed-distance expression 42;
// native first-point components 63; accumulated dot result 46.
// Repeated j input 42; repeated i input 42; both scalar inputs 126.
// Shared normalizer/magnitude 42/42; tested initial/distance states 81/76; both tested states 79;
// early distance default 65; shared normalizer with tested states/default 79/65.
// @retail 0x239b80
short function_239b80(short count, point2f const *points)
{
	point2f first;
	plane2f line;
	short state = NONE;

	for (short i = 0; state < 2 && i < count; i++)
	{
		switch (state)
		{
		case NONE:
			first = points[i];
			state = 0;
			break;
		case 0:
			line.n.i = first.y - points[i].y;
			line.n.j = points[i].x - first.x;
			if (normalize2d(&line.n) != 0.f)
			{
				line.d = dot_product2d(&line.n, &points[i]);
				state = 1;
			}
			else
			{
				line.d = 0.f;
			}
			break;
		case 1:
			if (!(fabs(dot_product2d(&line.n, &points[i]) - line.d) < k_real_epsilon))
				state = 2;
			break;
		}
	}

	return state;
}

// @retail 0x239cb0
long function_239cb0(long count, point3f const *points, point2f *hull)
{
	point2f points2d[MAXIMUM_POLYGON_POINTS];

	if (count > MAXIMUM_POLYGON_POINTS)
		count = MAXIMUM_POLYGON_POINTS;
	for (long i = 0; i < count; i++)
	{
		points2d[i].x = points[i].x;
		points2d[i].y = points[i].y;
	}

	return function_239d50(count, points2d, hull);
}

// @retail 0x239d50
long function_239d50(long count, point2f const *points, point2f *hull)
{
	point2f unique_points[MAXIMUM_POLYGON_POINTS];
	short indices[MAXIMUM_POLYGON_POINTS];

	short unique_count = (short)count;
	memcpy(unique_points, points, sizeof(point2f) * (count > MAXIMUM_POLYGON_POINTS ? MAXIMUM_POLYGON_POINTS : count));
	for (long i = 0; i < unique_count - 1; i++)
	{
		for (long j = i + 1; j < unique_count; j++)
		{
			if (fabs(unique_points[i].x - unique_points[j].x) < k_real_epsilon &&
				fabs(unique_points[i].y - unique_points[j].y) < k_real_epsilon)
			{
				unique_points[j] = unique_points[unique_count - 1];
				unique_count--;
			}
		}
	}

	short hull_count = function_239e50(unique_count, unique_points, indices);
	if (hull_count >= 3)
	{
		for (long i = 0; i < hull_count; i++)
			hull[i] = unique_points[indices[i]];
	}
	else
	{
		hull_count = 0;
	}
	return hull_count;
}

/* gift wrapping: the indices of the convex hull of the points, starting from
   the lowest */
// score 250 (was 261): scan/count registers, equality scheduling and compaction inline boundary differ. Tried direct index output 261; plain lowest scan 250; full current index 299; full candidate counter 256; native completion returns 279; plain scan direct output 250; plain scan append then count 250.
// Full count tests 274; current-point snapshot 271; byte start state 250; float workspace names 250; still-at-origin state 264; inline classifier declaration 250; forced equality declaration 250.
// @retail 0x239e50
short function_239e50(short count, point2f const *points, short *indices)
{
	long hull_count = 0;

	if (function_239b80(count, points) == 2)
	{
		real previous_angle = 0.f;
		bool left_start = false;
		real lowest_x = FLT_MAX;
		real lowest_y = FLT_MAX;
		short current = count;

		for (short i = 0; i < count; ++i)
		{
			if (lowest_y - k_real_epsilon > points[i].y ||
				lowest_y > points[i].y && lowest_x + k_real_epsilon > points[i].x ||
				lowest_y + k_real_epsilon > points[i].y && lowest_x - k_real_epsilon > points[i].x)
			{
				lowest_x = points[i].x;
				lowest_y = points[i].y;
				current = i;
			}
		}

		while ((short)hull_count < count)
		{
			real best_distance = -FLT_MAX;
			indices[(short)hull_count++] = current;
			short next = NONE;
			real best_angle = FLT_MAX;
			real best_delta = FLT_MAX;

			for (short j = 0; j < count; j++)
			{
				real dx = points[current].x - points[j].x;
				real dy = points[current].y - points[j].y;
				real distance = (real)sqrt(dx * dx + dy * dy);
				if (distance > 0.000244140625f)
				{
					real angle = (real)atan2(points[j].y - points[current].y, points[j].x - points[current].x);
					real delta = angle - previous_angle;
					while (delta < -k_real_epsilon)
						delta += g_55e470;
					if (delta < best_delta - k_real_epsilon ||
						!(delta > best_delta + k_real_epsilon) &&
						(j == indices[0] || next != indices[0] && distance > best_distance))
					{
						best_distance = distance;
						best_angle = angle;
						best_delta = delta;
						next = j;
					}
				}
			}

			current = next;
			previous_angle = best_angle;
			if (next == NONE)
				goto finished;
			if (!left_start)
				left_start = !points2d_equal(&points[next], &points[indices[0]]);
			if (next == indices[0])
				goto finished;
			if (left_start && points2d_equal(&points[next], &points[indices[0]]))
				goto finished;
		}

		for (short i = 0; i < (short)hull_count; i++)
		{
			short j;
			for (j = 0; j < i; j++)
			{
				if (indices[j] == indices[i])
				{
					hull_count = i - j;
					memcpy(indices, &indices[j], sizeof(short) * (short)hull_count);
					break;
				}
			}
			if (j < i)
				break;
		}
	}

finished:
	return hull_count;
}

PRIVATE __forceinline void polygon_difference_23a220(point2f const *a, point2f const *b, vector2f *result)
{
	result->i = a->x - b->x;
	result->j = a->y - b->y;
}

// score 50 (was 50): retail loads the count once (DX, then EBX sign-extended for the
// wrap) and compares the index with the count's stack home as a word; ours re-reads the
// count each pass. The XMM homes differ too (retail offset XMM0/XMM3, edge XMM1/XMM2). Short
// wrap snapshot 78, long 68, later short 78; ordinary count 73 (moves the point to the stack
// and breaks the matched caller 0x14a370), ordinary count with long/short shared bound
// 67/73; cached-long direct rejection 63/184 bytes, ordinary direct rejection 67;
// byte/short/native result 102/104/102; unsigned-short induction 50; early cross 58;
// distance limit scalar 50; cross square scalar 50; both squared parts 50; edge first 48;
// vertex receiver 97; wrap if 63; positive wrap 50; degenerate continue 50; nested
// predicates 50; entry success 51; predicate result 51; ordinary count with a volatile read
// of it only at the loop test 69 (192 bytes); offset-first cross operands, the length sum
// without casts and a pointer cross-product inline all compile identically (50).
// entry count load and XMM offset/edge lifetimes still differ; short wrap snapshot 78, long 68, later short 78; ordinary count 73, ordinary count with long/short shared bound 67/73; cached-long direct rejection 63/184 bytes, ordinary direct rejection 67.
// score 50 (was 50): entry count load, word tail and XMM edge/offset homes remain.
// Current point value 111; advancing point cursor 58 at 184 bytes; ordinary while 50;
// named edge squares/cross products/both 50/50/50; point value with edge squares/both 111/111.
// The initial count load, widened loop tail and XMM edge/offset homes still
// entry count load, word loop tail and offset/edge SSE homes still differ.
// Earlier: entry count load and XMM offset/edge lifetimes still differ; short wrap snapshot 78, long 68, later short 78; ordinary count 73, ordinary count with long/short shared bound 67/73; cached-long direct rejection 63/184 bytes, ordinary direct rejection 67.
// Earlier: The initial count load, widened loop tail and XMM edge/offset homes still
// differ. Byte/short/native result 102/104/102; unsigned-short induction 50; early cross 58; distance
// limit scalar 50; cross square scalar 50; both squared parts 50.
// initial count load, wrap-bound ownership and XMM allocation remain.
// Edge first 48; vertex receiver 97; wrap if 63; positive wrap 50; degenerate continue 50;
// nested predicates 50; entry success 51; predicate result 51. Two-point gain rejected.
// Next before offset 50; radius square at use 71; const radius square 50;
// outer offset/edge/both storage 50/50/50; early next with outer vectors 50; radius at use with outer vectors 71.
// @retail 0x23a160
bool function_23a160(point2f const *point, real radius, short volatile count, point2f const *points)
{
	real radius_squared = radius * radius;
	bool result = true;
	for (short i = 0; i < count; i++)
	{
		vector2f offset;
		polygon_difference_23a220(point, &points[i], &offset);
		long next = (i + 1 >= count) ? 0 : i + 1;
		vector2f edge;
		polygon_difference_23a220(&points[next], &points[i], &edge);
		real length_squared = (real)(edge.i * edge.i) + (real)(edge.j * edge.j);
		if (length_squared != 0.f)
		{
			real cross = edge.j * offset.i - edge.i * offset.j;
			if (cross > 0.f && cross * cross > length_squared * radius_squared)
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

// score 31 (was 31): short body index/tail width and point/wrap homes remain.
// Difference helper ordinary inline/pointer result/input references 31/31/31;
// input values 161; staged differences 31; output reference 31;
// current point value 82; advancing current-point cursor 42.
// The induction is carried at native width; point and wrap-register homes still
// differ. Direct rejection 45; short/native result 68/66; rejection result 80; short next 43;
// unsigned-short induction 31; negative threshold 38; result from cross test 39.
// Promoted current index 31; plain while 31; explicit wrap assignment 44;
// modulo wrap 42; signed area 31; first/second/both product parts 31/31/31;
// reused short/native bound values 43/47.
// Test-point value 97; function-scope vectors 31; edge before offset 31; role names 31;
// difference helper y-first/output-first/base-first/vector result 31/31/31/144.
// @retail 0x23a220
bool function_23a220(point2f const *point, short volatile count, point2f const *points, real epsilon)
{
	(void)&count;
	bool result = true;
	for (short i = 0; i < count; i++)
	{
		vector2f offset;
		polygon_difference_23a220(point, &points[i], &offset);
		long next = (i + 1 >= count) ? 0 : i + 1;
		vector2f edge;
		polygon_difference_23a220(&points[next], &points[i], &edge);
		if (edge.i * offset.j - edge.j * offset.i < -epsilon)
		{
			result = false;
			break;
		}
	}
	return result;
}

PRIVATE __forceinline bool clip_points_equal_23a6f0(point2f const *a, point2f const *b, real epsilon)
{
	return fabs((double)a->x - b->x) < epsilon && fabs((double)a->y - b->y) < epsilon;
}

// score 243 (was 243): count/stride homes and distance/intersection lifetimes differ. Tried capacity break common result 245; shared mask return 254; existing plane dot 243; plain previous side 265; previous side branches 259; byte side presence 243; named distance products 243; native clipping role homes 243.
// Native current ordinal 249; long side states 264; prior-point ordinal 288; ordered fraction clamp 243; clear-mask arm first 243; shared normalized count 275; existing point difference 243.
// @retail 0x23a6f0
short function_23a6f0(point2f *output, short count, point2f const *points,
	plane2f const *plane, short capacity, dword *point_mask, bool *clipped, real epsilon)
{
	point2f copy[512];
	short result = 0;
	bool positive = false;
	bool negative = false;
	dword mask = 0;
	if (clipped)
		*clipped = false;
	if (points == output)
	{
		memcpy(copy, points, count * sizeof(point2f));
		points = copy;
	}
	point2f const *previous = &points[count - 1];
	volatile bool previous_inside = previous->y * plane->n.j + previous->x * plane->n.i - plane->d >= 0.f;
	for (short i = 0; i < count; i++)
	{
		point2f const *current = &points[i];
		real distance = current->y * plane->n.j + plane->n.i * current->x - plane->d;
		bool inside = distance >= 0.f;
		if (distance > epsilon)
			positive = true;
		else if (0.f - epsilon > distance)
			negative = true;
		if (inside != previous_inside)
		{
			if (result == capacity)
				goto overflow;
			if (clipped)
				*clipped = true;
			real dy = previous->y - current->y;
			real dx = previous->x - current->x;
			real denominator = plane->n.i * dx + dy * plane->n.j;
			real fraction = 0.f;
			if (denominator != 0.f)
				fraction = 0.f - (current->y * plane->n.j + plane->n.i * current->x - plane->d) / denominator;
			fraction = fraction < 0.f ? 0.f : fraction > 1.f ? 1.f : fraction;
			output[result].x = dx * fraction + current->x;
			output[result].y = dy * fraction + current->y;
			mask |= 1 << result;
			result++;
			if (result != 1 && (clip_points_equal_23a6f0(&output[result - 1], output, epsilon) ||
				clip_points_equal_23a6f0(&output[result - 1], &output[result - 2], epsilon)))
				result--;
		}
		if (inside)
		{
			if (result == capacity)
				goto overflow;
			output[result] = *current;
			if (point_mask && (*point_mask & (1 << i)))
				mask |= 1 << result;
			else
				mask &= ~(1 << result);
			result++;
			if (result != 1 && (clip_points_equal_23a6f0(&output[result - 1], output, epsilon) ||
				clip_points_equal_23a6f0(&output[result - 1], &output[result - 2], epsilon)))
				result--;
		}
		previous = current;
		previous_inside = inside;
	}
	if (result < 3)
		result = 0;
	if (!positive)
		result = 0;
	else if (!negative)
	{
		result = count;
		memcpy(output, points, count * sizeof(point2f));
	}
	if (point_mask)
		*point_mask = mask;
	return result;
overflow:
	memcpy(output, points, count * sizeof(point2f));
	if (point_mask)
		*point_mask = mask;
	return NONE;
}

// @retail 0x23a2b0
short function_23a2b0(short count, point2f const *points, short clip_count,
    point2f const *clip, short capacity, point2f *output, real epsilon)
{
    point2f buffers[2][512];
    for (short i = 0; i < clip_count && count > 0; i++)
    {
        short previous = i ? i - 1 : clip_count - 1;
        point2f *destination = i == clip_count - 1 ? output : buffers[i & 1];
        plane2f plane;
        plane.n.i = clip[previous].y - clip[i].y;
        plane.n.j = clip[i].x - clip[previous].x;
        real length = (real)sqrt(plane.n.i * plane.n.i + plane.n.j * plane.n.j);
        if (!(fabs(length) < 0.0001f))
        {
            real inverse = 1.f / length;
            plane.n.i *= inverse;
            plane.n.j *= inverse;
        }
        else
            length = 0.f;
        if (length != 0.f)
        {
            plane.d = plane.n.i * clip[i].x + plane.n.j * clip[i].y;
            count = function_23a430(count, points, &plane, epsilon, capacity, destination);
            if (count == NONE)
                return NONE;
        }
        else
        {
            plane.d = 0.f;
            memcpy(destination, points, count * sizeof(point2f));
        }
        points = destination;
    }
    return count;
}
