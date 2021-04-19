#pragma once
#include "mvl_library.h"

namespace tokens
{
    extern token core_None;
    extern token core_None_str;
    extern token core_None_equals;
    extern token core_None_hash;

    extern token core_Bool;
    extern token core_Double;
    extern token core_String;
    extern token core_List;
    extern token core_NativeFunction;

    void init(mvl_i* inst);
}