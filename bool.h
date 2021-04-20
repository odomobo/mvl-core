#pragma once
#include "mvl_library.h"

mvl_obj* bool_new_internal(bool val);
bool bool_get_internal(mvl_obj* bool_obj);

void bool_register_type();
void bool_register_nativeFunctions();