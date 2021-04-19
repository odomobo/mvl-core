#pragma once
#include "mvl_library.h"

#define MVL mvl_api_ptr.load()
#define STACKFRAME_PUSH(inst) stackframe_push(inst, __func__, __FILE__, __LINE__)

void error_memory(mvl_i* inst);
void verify_0_args(mvl_i* inst, mvl_obj* list);
mvl_obj* extract_1_args(mvl_i* inst, mvl_obj* list);
std::array<mvl_obj*, 2> extract_2_args(mvl_i* inst, mvl_obj* list);
std::array<mvl_obj*, 3> extract_3_args(mvl_i* inst, mvl_obj* list);