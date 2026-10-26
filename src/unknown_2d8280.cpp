// @flags /O2 /GL-
// Report-id values and report counts keyed by file name and line number.
#include "growable_array_2d91d0.h"
int __cdecl compare_ignoring_case_2d8ce0(char const *left, char const *right);
struct location_2d8280 { char const *file; long line; };
struct location_count_2d8280 { char const *file; long line; long count; };
struct location_counts_2d8280
{
	ELEMENTS_2D91D0_MEMBERS(location_count_2d8280)
	long *find(location_2d8280 const &location);
	long *get(location_2d8280 const &location);
	int remove(location_2d8280 const &location);
};
struct id_value_2d8410 { long id; long value; };
struct id_values_2d8410
{
	ELEMENTS_2D91D0_MEMBERS(id_value_2d8410)
	int remove(long const &id);
	long *get(long const &id);
};

// @retail 0x2d8410
int id_values_2d8410::remove(long const &id)
{
	for (long i = size - 1; i >= 0; i--)
	{
		if (data[i].id == id)
		{
			remove_at(i);
			return 0;
		}
	}
	return 1;
}
// @retail 0x2d8460
long *id_values_2d8410::get(long const &id)
{
	for (long i = 0; i < size; i++)
	{
		if (data[i].id == id)
		{
			return &data[i].value;
		}
	}
	long index = size;
	resize(index + 1);
	id_value_2d8410 &entry = data[index];
	entry.id = id;
	return &entry.value;
}
// @retail 0x2d8280
long *location_counts_2d8280::find(location_2d8280 const &location)
{
	for (long i = 0; i < size; i++)
	{
		if (data[i].line == location.line && compare_ignoring_case_2d8ce0(data[i].file, location.file) == 0)
		{
			return &data[i].count;
		}
	}
	return 0;
}
// @retail 0x2d85a0
long *location_counts_2d8280::get(location_2d8280 const &location)
{
	for (long i = 0; i < size; i++)
	{
		if (data[i].line == location.line && compare_ignoring_case_2d8ce0(data[i].file, location.file) == 0)
		{
			return &data[i].count;
		}
	}
	long index = size;
	resize(index + 1);
	location_count_2d8280 &entry = data[index];
	entry.file = location.file;
	entry.line = location.line;
	return &entry.count;
}
// @retail 0x2d8700
int location_counts_2d8280::remove(location_2d8280 const &location)
{
	for (long i = size - 1; i >= 0; i--)
	{
		if (data[i].line == location.line && compare_ignoring_case_2d8ce0(data[i].file, location.file) == 0)
		{
			remove_at(i);
			return 0;
		}
	}
	return 1;
}
