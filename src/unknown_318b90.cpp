// @flags /O2 /GL-
// Havok (third-party physics library): an object that keeps the object it
// was made for, with one reference.
#include "owned_reference_318b90.h"
#include "lane_a_contact_manager.h"

// @retail 0x318b90
class_318b90::class_318b90(void *owner)
	: owner(owner)
{
}
// score 32 (was 32): extra word store and input loads after allocation;
// first local 33, second 34, both 18; owner local 31, owner and first 30,
// owner and second 31, all three 28. The direct expression is retained.
// @retail 0x318bb0
lane_a_simple_contact_manager *class_318b90::function_318bb0(
    lane_a_contact_body const *first, lane_a_contact_body const *second, void const *input)
{
	return new lane_a_simple_contact_manager((listener_world_318320 *)owner, first->entity, second->entity);
}
