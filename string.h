#pragma once
#include "mvl_library.h"

mvl_obj* string_new_internal_copy(std::string& str);
mvl_obj* string_new_internal_copy(char const* str_const);
mvl_obj* string_new_internal_borrow(char const* str_const, size_t length);
mvl_obj* string_new_internal_take(char* str, size_t length);
std::string string_get_internal_copy(mvl_obj* string);
char const* string_get_internal_borrow(mvl_obj* string, size_t* length_out = nullptr);

#define STRING_NEW_INTERNAL_BORROW(str) string_new_internal_borrow(str, sizeof(str)-1)
#define STRING_NEW_INTERNAL_TAKE(str) string_new_internal_take(str, sizeof(str)-1)

void string_register_type();
void string_register_nativeFunctions();