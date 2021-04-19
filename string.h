#pragma once
#include "mvl_library.h"

mvl_obj* string_new_internal_copy(mvl_i* inst, std::string& str);
mvl_obj* string_new_internal_copy(mvl_i* inst, char const* str_const);
mvl_obj* string_new_internal_borrow(mvl_i* inst, char const* str_const, size_t length);
mvl_obj* string_new_internal_take(mvl_i* inst, char* str, size_t length);
std::string string_get_internal_copy(mvl_i* inst, mvl_obj* string);
char const* string_get_internal_borrow(mvl_i* inst, mvl_obj* string, size_t* length_out = nullptr);

#define STRING_NEW_INTERNAL_BORROW(inst, str) string_new_internal_borrow(inst, str, sizeof(str)-1)
#define STRING_NEW_INTERNAL_TAKE(inst, str) string_new_internal_take(inst, str, sizeof(str)-1)

void string_register_type(mvl_i* inst);
void string_register_nativeFunctions(mvl_i* inst);