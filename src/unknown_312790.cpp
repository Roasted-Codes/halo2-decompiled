// @flags /O2 /GL-
// Havok (third-party physics library): an object placed by a transform set
// from a description: the settings of its base, then the transform when it
// moved by more than a small tolerance.
#include "placed_shape_312800.h"
#include "unknown_1cec30.h"
#include "listened_object_315950.h"

// @retail 0x312790
void placed_shape_312800::function_312790(description_315ba0 const *description)
{
	((class_312430 *)this)->function_3124c0(description);
	if (!description->transform.equal_within(transform, 1e-4f).value)
	{
		((hkRigidBody *)this)->pose_write((hkTransform const &)description->transform);
	}
}

class class_30b700 : public class_315950
{
};

// score 1 (was unwritten): base destructor call; explicit destructors 1;
// destructor declaration 1; allocator forms 1.
// @retail 0x3127d0 deleting class_30b700
