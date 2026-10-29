// @flags /O2 /GL-
// Havok service replacement: release the previous singleton before installing
// its replacement. The allocator uses a long reference count; the other
// services use the sized-reference header and the game's release callback.
#include "unknown_146a20.h"
#include "sized_reference_a9ef0.h"

class error_handler_2d97d0;
class reporter_2ff210;
extern error_handler_2d97d0 *g_480178;
extern reporter_2ff210 *g_48017c;
extern c_sized_reference_a9ef0 *g_480180;
bool __cdecl function_279740(long value);
