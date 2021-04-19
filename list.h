#pragma once
#include "mvl_library.h"

mvl_obj* list_new_internal(mvl_i* inst, std::vector<mvl_obj*> elements);

mvl_obj* list_get_internal(mvl_i* inst, mvl_obj* list, int index);
size_t list_length_internal(mvl_i* inst, mvl_obj* list);

void list_register_type(mvl_i* inst);
void list_register_nativeFunctions(mvl_i* inst);