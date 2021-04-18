#include "pch.h"

mvl_obj* false_obj;
mvl_obj* true_obj;

void bool_init()
{
    mvl.type_register(core_Bool_token, bool_registration);

    auto val_false = new int{ 0 };
    auto val_true = new int{ 1 };
    false_obj = mvl.object_create(core_Bool_token, val_false);
    true_obj = mvl.object_create(core_Bool_token, val_true);
}

// new(int* data_bool, ...)
mvl_obj* bool_new(void* a, void* b, void* c, void* d)
{
    auto val = *static_cast<int*>(a);
    if (val == 0)
        return false_obj;
    else
        return true_obj;
}

void bool_free(mvl_obj* obj)
{
    auto data = static_cast<int*>(mvl.object_getDataPointer(obj));
    delete data;
}

// getNativeData(mvl_obj* bool, int* val_out,...);
void bool_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    auto a_int = static_cast<int*>(a);
    auto val = *static_cast<int*>(mvl.object_getDataPointer(obj));
    *a_int = val;
}

mvl_type_register_callbacks bool_registration = {
    bool_new,
    bool_free,
    bool_getNativeData,
    nullptr
};
