#pragma once
#include "mvl_library.h"

extern mvl_obj* false_obj;
extern mvl_obj* true_obj;

void bool_init();

extern mvl_type_register_callbacks bool_registration;