#include "pch.h"

void none_register(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, tokens::core_None, none_registration);
    MVL->stackframe_pop(inst);
}

void none_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    // no native data to set
}

void none_free(mvl_i* inst, mvl_obj* self)
{
    // no native data to free
}

void none_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    // no native data to get
}


mvl_type_register_callbacks const none_registration = {
    none_new,
    none_free,
    none_getNativeData,
    nullptr
};