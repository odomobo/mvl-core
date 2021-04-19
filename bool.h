#pragma once
#include "mvl_library.h"

mvl_obj* bool_new_internal(mvl_i* inst, bool val);
bool bool_get_internal(mvl_i* inst, mvl_obj* bool_obj);

void bool_register_type(mvl_i* inst);
void bool_register_nativeFunctions(mvl_i* inst);