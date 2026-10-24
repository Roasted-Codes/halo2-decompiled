// @flags /O2 /GL-
// Havok (third-party physics library): reporting an error message through
// the error handler the game installs.
#include "stream_holder_2d8e70.h"

// the game's error handler; its third slot reports a message
class error_handler_2d97d0
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void report(char const *title, unsigned long id, char const *message, char const *file, long line) {}
};

error_handler_2d97d0 *g_480178;

// score 29 (was 29): retail reserves four more frame bytes and records the
// outgoing flag object's address. Earlier /GX, /EHa, /EHsc and /EHs forms
// add exception registration or leave the store absent. Implicit argument
// 29; explicit object 29; trivial copy implicit/explicit 29/26; char storage
// 29/26; default constructor and conversion 29; member initializer 29;
// forced constructor 29; placement after the stream constructor with /GX
// 93; out-of-class inline/force-inline constructor 29/29. Original body kept.
// @retail 0x2d97d0
void __cdecl function_2d97d0(char const *message)
{
	char buffer[0x200];
	flag_2d8e70 zero(true);
	stream_holder_2d8e70 stream(buffer, sizeof(buffer), zero);
	stream.function_2d8f10(message);
	g_480178->report("Error", 0x2636fe25, buffer, ".\\error\\hkError.cpp", 27);
}
