#include "pch.h"

mvl_obj* none_obj;

void none_init()
{
    mvl.type_register(core_None_token, none_registration);
    none_obj = mvl.object_create(core_None_token, nullptr);
}

mvl_obj* none_new(void* a, void* b, void* c, void* d)
{
    return none_obj;
}

void none_free(mvl_obj* obj)
{
    // no native data to free
}

void none_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    // no native data to get
}


mvl_type_register_callbacks none_registration = {
    none_new,
    none_free,
    none_getNativeData,
    nullptr
};