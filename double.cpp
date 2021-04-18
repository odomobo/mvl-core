#include "pch.h"

void double_init()
{
    mvl.type_register(core_Double_token, double_registration);
}

// new(double* data, ...)
mvl_obj* double_new(void* a, void* b, void* c, void* d)
{
    auto val = *static_cast<double*>(a);
    auto data = new double{ val };
    return mvl.object_create(core_Double_token, data);
}

void double_free(mvl_obj* obj)
{
    auto data = static_cast<double*>(mvl.object_getDataPointer(obj));
    delete data;
}

// getNativeData(mvl_obj* double, double* val_out,...);
void double_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    auto a_double = static_cast<double*>(a);
    auto val = *static_cast<double*>(mvl.object_getDataPointer(obj));
    *a_double = val;
}

mvl_type_register_callbacks double_registration = {
    double_new,
    double_free,
    double_getNativeData,
    nullptr
};