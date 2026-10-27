// @flags /O2 /GL-
// Havok (third-party physics library): the shared object of kind 1, built
// with one reference and destroyed as its base is.
#include "kind_object_3192b0.h"

kind_object_3192b0 g_480bb8;

// @retail 0x3192b0 destructor kind_object_3192b0

// @retail 0x3192c0
kind_object_3192b0::kind_object_3192b0()
{
}

// score 1 (was unwritten): the call skips the intermediate destructor.
// A derived destructor, explicit member, early exit, object pointer,
// named late/early bit, byte flags and separate returns all score 1;
// a separate destructor declaration does not compile.
// @retail 0x3192d0 deleting kind_object_3192b0
