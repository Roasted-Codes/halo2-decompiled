// @flags /O2 /GL-
// Havok (third-party physics library): copying an object's settings into a
// description and back.
#include "description_312430.h"
#include "unknown_1cec30.h"

ELEMENTS_2D91D0(array_312530, s_havok_entity_property);
typedef char assert_array_312530_size[(sizeof(array_312530) == sizeof(s_havok_array)) ? 1 : -1];

// score 6 (was 38): six loop loads/stores use different registers;
// direct append 38, input value 27/27, pair snapshot 28; value access or
// long index 38/38, array aliases 38/38; slot and pair 30/27, scalars 30,
// const pair 30; output base/index 6 in four orders, input value 28/28,
// force inline 6, element pointer 30; shared pair assignment 21/30,
// assignment by value 30, const element value 27.
// @retail 0x312430
void class_312430::function_312430(description_312430 *description) const
{
	description->field_4 = field_c;
	description->field_8 = field_24;
	description->pairs.ensure_capacity(pairs.size);
	for (int i = 0; i < pairs.size; i++)
	{
		description->pairs.append_unchecked(pairs[i]);
	}
	description->field_0 = field_28;
}

// score 17 (was 26): source/output registers and the second output reload;
// long index 26; pair assignment direct 51/51, all reads first 51/51,
// by value 37/37, const element value 26; pair local/expression 17/17,
// scalar snapshots 27, element references 26; two-use pair 17, with
// element references 51/37/43; force inline pair copy 51/51; long/const 17/17.
// @retail 0x3124c0
void class_312430::function_3124c0(description_312430 const *description)
{
	if (field_28 != description->field_0)
	{
		field_28 = description->field_0;
	}
	pairs.resize(description->pairs.size);
	for (int i = 0; i < description->pairs.size; i++)
	{
		pair_312430 value = description->pairs[i];
		pairs[i].field_0 = value.field_0;
		pairs[i].field_4 = value.field_4;
	}
}

// @retail 0x312530
void hkEntity::entity_property_put(dword key, s_havok_property_word value)
{
	for (long i = 0; i < m_property_count; i++)
	{
		if (m_properties[i].m_key == key)
		{
			return;
		}
	}
	s_havok_entity_property property;
	property.m_key = key;
	property.m_value = value;
	((array_312530 *)&m_properties)->append_copy(property);
}
