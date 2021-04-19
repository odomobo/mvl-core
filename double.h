#pragma once
#include "mvl_library.h"

mvl_obj* double_new_internal(mvl_i* inst, double val);

void double_register_type(mvl_i* inst);
void double_register_nativeFunctions(mvl_i* inst);