#pragma once
#include "mvl_library.h"

mvl_obj* double_new_internal(double val);
double double_get_internal(mvl_obj* double_obj);

void double_register_type();
void double_register_nativeFunctions();