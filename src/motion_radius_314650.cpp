// @flags /O2 /GL-
#include "constraint_helpers_314090.h"

struct bounds_314650
{
	__m128 minimum, maximum;
};
class shape_bounds_314650
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void bounds(void const *transform, float tolerance, bounds_314650 *output) const = 0;
};
// Identity transform used by the retail bounds query at 0x461ea0, including
// the homogeneous position lane. The result uses only the three spatial axes.
static __declspec(align(16)) float const identity_314650[16] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

// Store the squared half-diagonal of the shape's bounds, or -1 without a shape.
// @retail 0x314650
float c_314710::update_radius_squared(shape_bounds_314650 const *shape)
{
	motion_limits_view_314450 *object = (motion_limits_view_314450 *)this;
	if (shape)
	{
		bounds_314650 box;
		shape->bounds(identity_314650, 0.0f, &box);
		__m128 extent = _mm_sub_ps(box.maximum, box.minimum);
		__m128 scale = _mm_set_ss(0.5f);
		scale = _mm_shuffle_ps(scale, scale, 0);
		__m128 radius = _mm_mul_ps(scale, extent);
		__m128 squared = _mm_mul_ps(radius, radius);
		__m128 y = _mm_shuffle_ps(squared, squared, 0x55);
		__m128 z = _mm_shuffle_ps(squared, squared, 0xaa);
		y = _mm_add_ss(y, squared);
		z = _mm_add_ss(z, y);
		float result;
		_mm_store_ss(&result, z);
		object->radius_squared = result;
	}
	else
		object->radius_squared = -1.0f;
	return object->radius_squared;
}
