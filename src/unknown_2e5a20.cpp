// @flags /O2 /GL-
// Havok (third-party physics library): puts one object in a whole row and a
// whole column of an 8x8 table of reference-counted objects.
#include "reference_counted_2d88a0.h"
#include "agent_table_2e5d50.h"

static inline void assign_2e5a20(referenced_2d88a0 *&slot, referenced_2d88a0 *object)
{
	object->reference_count++;
	referenced_2d88a0 *old = slot;
	if (--old->reference_count == 0)
	{
		delete old;
	}
	slot = object;
}

// The same object as s_1c3a40 (include/agent_table_2e5d50.h), seen from these two functions.
class table_2e5a20
{
public:
	char unknown0[0xc];
	referenced_2d88a0 *entry[8][8];
	unsigned long masks[32];
	char unknown18c[0x4d90 - 0x18c];
	alternate_types_2e5d50 alternate_types;

	void set_all(referenced_2d88a0 *object, long index);
	void function_2e5ce0(long target, long source, long depth);
};

// @retail 0x2e5a20
void table_2e5a20::set_all(referenced_2d88a0 *object, long index)
{
	for (int i = 0; i < 8; i++)
	{
		assign_2e5a20(entry[i][index], object);
		assign_2e5a20(entry[index][i], object);
	}
}
// @retail 0x2e5ce0
void table_2e5a20::function_2e5ce0(long target, long source, long depth)
{
	masks[target] |= masks[source];
	for (long i = 0; i < alternate_types.size; i++)
	{
		alternate_type_2e5d50 const &edge = alternate_types[i];
		if (edge.alternate == target)
		{
			function_2e5ce0(edge.type, edge.alternate, depth + 1);
		}
	}
}
