#pragma once
#include "mvl_library.h"

mvl_obj* nativeFunction_new_internal(mvl_token nativeFunction_token, mvl_nativeFunction_t* nativeFunction_fp, char const* signature, char const* help_text);

void nativeFunction_register_type();
void nativeFunction_register_nativeFunctions();