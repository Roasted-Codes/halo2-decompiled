// @flags /O2 /GL-
// Format a string and compare ASCII text without regard to letter case.
#include <stdarg.h>
#include <stdio.h>

// @retail 0x2d8cc0
int __cdecl format_2d8cc0(char *buffer, char const *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	return vsprintf(buffer, format, arguments);
}

static inline char to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + ('a' - 'A');
	}
	return c;
}

// @retail 0x2d8ce0
int __cdecl compare_ignoring_case_2d8ce0(char const *left, char const *right)
{
	for (int i = 0; left[i] != 0 || right[i] != 0; i++)
	{
		if (to_lower(left[i]) < to_lower(right[i]))
		{
			return -1;
		}
		if (to_lower(left[i]) > to_lower(right[i]))
		{
			return 1;
		}
	}
	return 0;
}
