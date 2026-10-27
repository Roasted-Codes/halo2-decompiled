// @flags /O2 /GL- /GX
// Havok (third-party physics library): its default error handler, which
// counts silenced source locations and switches report ids off.
#include "error_handler_2d8030.h"

// @retail 0x2d8030
void error_handler_2d8030::report_2d8030(char const *title, long id, char const *message, char const *file, long line)
{
	if (!is_silenced(file, line, id).value)
	{
		show(2, title, id, message, file, line, flag_2d8e70(true));
	}
}

// @retail 0x2d81f0
flag_2d8e70 error_handler_2d8030::is_silenced(char const *file, long line, long id)
{
	location_2d8280 location;
	location.file = file_name(file);
	location.line = line;
	if (counts.find(location) != 0 || silenced.find(id) != 0)
	{
		return flag_2d8e70(true);
	}
	return flag_2d8e70(false);
}

// @retail 0x2d82e0
void error_handler_2d8030::report_2d82e0(char const *title, long id, char const *message, char const *file, long line)
{
	if (!is_silenced(file, line, id).value)
	{
		show(0, title, id, message, file, line, flag_2d8e70(true));
	}
}

// @retail 0x2d8330
void error_handler_2d8030::report_2d8330(char const *title, long id, char const *message, char const *file, long line)
{
	if (!is_silenced(file, line, id).value)
	{
		show(3, title, id, message, file, line, flag_2d8e70(false));
	}
}

// @retail 0x2d8380
void error_handler_2d8030::set_enabled(long id, bool enabled)
{
	if (enabled)
	{
		if (silenced.find(id) != 0)
		{
			silenced.remove(id);
		}
	}
	else
	{
		if (silenced.find(id) == 0)
		{
			*silenced.get(id) = 1;
		}
	}
}

// @retail 0x2d84e0 deleting error_handler_2d8030

// score 39 (was 39): Extra class-table store and first release argument staging remain.
// Earlier suppressed table store 30; owned storage/both storage/element byte size/
// named byte size 0, but deleting destructor missing; capacity/signed ownership/
// unowned return 30; storage before guard 3. All rejected. Separate noinline/inline/
// forceinline declarations 39 each; pure virtual, with those three boundaries,
// 39 each and deleting destructor missing; suppressed table with noinline 30, also missing.
// @retail 0x2d8510
error_handler_2d8030::~error_handler_2d8030()
{
}

// @retail 0x2d8640
void error_handler_2d8030::count_location(char const *file, long line)
{
	location_2d8280 location;
	location.file = file_name(file);
	location.line = line;
	if (counts.find(location) == 0)
	{
		*counts.get(location) = 1;
	}
	else
	{
		++*counts.get(location);
	}
}

// @retail 0x2d86a0
void error_handler_2d8030::uncount_location(char const *file, long line)
{
	location_2d8280 location;
	location.file = file_name(file);
	location.line = line;
	if (counts.find(location) != 0)
	{
		long *count = counts.get(location);
		if ((*count)-- == 0)
		{
			counts.remove(location);
		}
	}
}
