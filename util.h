#pragma once
#include "mvl_library.h"

void error_memory();
void verify_0_args(mvl_obj* args);
void verify_1_args(mvl_obj* args);
mvl_obj* extract_1_args(mvl_obj* args);
std::array<mvl_obj*, 2> extract_2_args(mvl_obj* args);
std::array<mvl_obj*, 3> extract_3_args(mvl_obj* args);
