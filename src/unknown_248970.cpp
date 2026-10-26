#include "unknown_11c920.h"
#include "effects.h"

// @flags /O2 /Ob1 /arch:SSE /Gr

struct s_247fd0;
struct s_object_2470e0;
struct s_unknown_13bf00;
extern s_unknown_13bf00 *g_510c50;

struct s_248970
{
	short field_0;
	byte field_2;
	byte field_3;
	long field_4;
	long field_8;
	long field_c;
	point3f field_10;
	real field_1c;
	byte field_20[0x34 - 0x20];
};

struct s_248971
{
	byte field_0[0x18];
	real field_18;
	real field_1c;
	real field_20;
	real field_24;
	real field_28;
	real field_2c;
	long field_30;
	byte *field_34;
};

class c_247470
{
public:
	word field_0;
	word field_2;
	long field_4;
	long field_8;
	real field_c;
	matrix3x3 field_10;
	point3f field_34;
	point3f field_40;
	void function_247470(real arg_0, s_particle_system_datum *arg_1, s_object_2470e0 *arg_2,
		s_247fd0 *arg_3, transform4x3f const *arg_4, dword arg_5);
};

// score 221 (was 221): Frame 0x10/0x14, stacked activation versus AL and metadata/viewer/child homes remain.
// Earlier 221 (was 221): Frame 0x10/0x14 and activation, metadata/viewer/child homes remain.
// Frame 0x10 versus 0x14 and stacked activation versus AL remain; metadata, viewer and child homes differ.
// Prior shared position base 256; child byte stride 258; direct input 265; radius expression 256;
// selected influence 259; active first 253; stored gate 256; activation default 284.
// Early activation 246 with inherited address read rejected; scalar homes 256; short viewer 299;
// allocation failure first 256; maximum branches 257; direct input/early activation 253;
// delayed child handle 252 kept; one initialized/link record pointer 300.
// frame, boolean convention and child-loop homes differ. Tried shared position field base 256; child record byte stride 258; direct location input 265; distance through radius 256; reuse selected influence 259; active branch first 253; stored activation gate 256; activation influence default 284.
// Earlier 221 (was 252): round 108: frame 0x10/0x14, activation and viewer/child homes remain.
// Scan influence accumulator 285; closed double scope 252; shared salted index 228;
// explicit zero falloff 245; allocation-failure return 252; combined 221;
// shared child pointer 228; direct allocated handle 336; complete falloff arms 221.
// Later child count 282; viewer while 252; conditional viewer 282; allocation/link pool scope 252;
// entry child ordinal 252; native position member 252; later child handle 285;
// later child count/handle 280; published gate across getter 254; direct bitfield conditional 271.
// Shared point setter 287; complete position value 282; persistent override influence 289;
// viewer-row cursor 281; library position copy 252.
// Round 111: Per-viewer Boolean override 210 (its 1/0 value written out at each use, not kept); unsigned-word viewer 249; readonly metadata 221; activation-byte contract 221; Boolean/word combination 232; Boolean/late activation 243; Boolean/closed doubles 210.
// Direct sqrt/single-use maximum 221/221; selected falloff expression 241;
// immutable coordinates 221; entry metadata lifetime 221; immutable pool/location receivers
// 221/221; child age initialization first 221. Original arithmetic, receivers and stores restored.
// Round 201: Activation positions 1/3/4/5/6 221 each; reused influence 240; complete viewer arms 238; chained initialization 221; count/handle lexical pair 221; conditional accumulator update 276.
// Round 113: Native viewer state member 221; early child head with shared-index/falloff context 222; child metadata byte cursor 221; default-first reused override float 221; separate allocation handle 228.
// Round 117: Activation in viewer loop 247; child while 221; range-success first 221; native child table 221; reused range limits 243.
// Activation after copy 224; early head with late activation 223; count after position 221;
// combined entry publications 223; named scaled distance 221; coordinate names 221; NONE links first 221; predecessor before head 221.
// @retail 0x248970
void function_248970(s_particle_location_datum *arg_0, bool arg_5, real arg_1, s_particle_system_datum *arg_2,
	real *arg_3, transform4x3f const *arg_4)
{
	s_248970 *local_20 = (s_248970 *)arg_0;
	local_20->field_2 = arg_5;
	s_248971 *local_1 = (s_248971 *)arg_2->function_1751d0();
	long local_0 = local_20->field_4;
	long local_2 = local_1->field_30;
	local_20->field_10 = arg_4->position;
	if (!arg_5)
	{
		local_20->field_1c = 0.f;
		for (long local_3 = 0; local_3 < *(short *)((byte *)g_4e8c20 + 8); ++local_3)
		{
			s_player_state const *local_6 = 0;
			if (local_3 != NONE && g_4686c4 != NONE)
				local_6 = (s_player_state const *)((byte const *)(g_4e9bd4 + local_3) + 0xb8);
			double local_7 = (double)local_20->field_10.x - local_6->position.x;
			double local_8 = (double)local_20->field_10.y - local_6->position.y;
			double local_9 = (double)local_20->field_10.z - local_6->position.z;
			double local_4 = sqrt(local_9 * local_9 + local_8 * local_8 + local_7 * local_7);
			real local_10 = (real)(local_4 * local_6->radius);
			real local_11;
			if (g_510c50 && ((byte *)g_510c50)[5])
				local_11 = 1.f;
			else if (!(local_10 > local_1->field_18 && local_1->field_24 > local_10))
				local_11 = 0.f;
			else
			{
				if (local_1->field_1c + local_1->field_18 > local_10)
					local_11 = (local_10 - local_1->field_18) * local_1->field_20;
				else if (local_10 > local_1->field_24 - local_1->field_28)
					local_11 = (local_1->field_24 - local_10) * local_1->field_2c;
				else
					local_11 = 1.f;
			}
			real local_12 = TEST_FIELD_BIT(arg_2->flag10) ? 1.f : 0.f;
			real local_13 = local_11 > local_12 ? local_11 : local_12;
			local_20->field_1c = local_20->field_1c > local_13 ? local_20->field_1c : local_11 > local_12 ? local_11 : local_12;
		}
	}
	else
		local_20->field_1c = 1.f;
	*(real *)((byte *)arg_3 + 0x1c) = local_20->field_1c;
	for (long local_14 = 0; local_14 < local_2; ++local_14)
	{
		s_record_pool *local_15 = g_51ec88;
		if (local_0 == NONE)
		{
			local_0 = record_pool_allocate(local_15);
			if (local_0 != NONE)
			{
				c_247470 *local_16 = DATUM(local_15, c_247470, local_0);
				local_16->field_8 = NONE;
				local_16->field_2 = 0;
				local_16->field_4 = NONE;
				local_16->field_c = 0.f;
			}
			if (local_0 == NONE)
				break;
			c_247470 *local_17 = DATUM(local_15, c_247470, local_0);
			long local_18 = data_datum_index(local_15, local_17 - (c_247470 *)local_15->data);
			local_17->field_8 = NONE;
			if (local_20->field_4 == NONE)
				local_20->field_4 = local_18;
			if (local_20->field_8 != NONE)
				DATUM(local_15, c_247470, local_20->field_8)->field_8 = local_18;
			local_20->field_8 = local_18;
		}
		c_247470 *local_19 = DATUM(local_15, c_247470, local_0);
		local_19->function_247470(arg_1, arg_2, (s_object_2470e0 *)(local_1->field_34 + local_14 * 0xb8), (s_247fd0 *)arg_3, arg_4, arg_2->color);
		local_0 = local_19->field_8;
	}
}
