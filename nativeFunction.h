#pragma once
#include "mvl_library.h"

mvl_obj* nativeFunction_new_internal(mvl_i* inst, token nativeFunction_token, mvl_nativeFunction_t* nativeFunction_fp, char const* signature, char const* help_text);

void nativeFunction_register_type(mvl_i* inst);
void nativeFunction_register_nativeFunctions(mvl_i* inst);