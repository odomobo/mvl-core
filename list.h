#pragma once
#include "mvl_library.h"

mvl_obj* list_new_internal(std::vector<mvl_obj*> elements);

mvl_obj* list_get_internal(mvl_obj* list, int index);
size_t list_length_internal(mvl_obj* list);

void list_register_type();
void list_register_nativeFunctions();