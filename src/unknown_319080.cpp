// @flags /O2 /GL-
// Havok (third-party physics library): an object that keeps the object it
// was made for, with one reference.
#include "owned_reference_318b90.h"
#include "matrix_compare_2da7f0.h"

// @retail 0x319080
class_319080::class_319080(void *owner)
	: owner(owner)
{
}

class type_query_319230
{
public:
	virtual void slot_0() = 0;
	virtual void slot_1() = 0;
	virtual void slot_2() = 0;
	virtual void slot_3() = 0;
	virtual void slot_4() = 0;
	virtual void slot_5() = 0;
	virtual long slot_6() = 0;
};

struct object_319230
{
	char unknown0[0x3c];
	type_query_319230 *field_3c;
	unsigned char field_40;
};

struct input_319230
{
	char unknown0[0x20];
	object_319230 *field_20;
};

class query_319230
{
public:
	bool_result_2da7f0 function_319230(input_319230 const *first, input_319230 const *second) const;
};

// score 22 (was unwritten): first call setup differs; pointer local 22;
// two pointer locals 38; direct field reads 35; combined test 19;
// separate tests 22; single result 36; declarations reversed 27; and test 22.
// @retail 0x319230
bool_result_2da7f0 query_319230::function_319230(input_319230 const *first, input_319230 const *second) const
{
	object_319230 *a = first->field_20;
	object_319230 *b = second->field_20;
	if (a->field_40 || b->field_40 || a->field_3c->slot_6() == 6 || b->field_3c->slot_6() == 6)
	{
		return true;
	}
	return false;
}
