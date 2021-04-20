#include "pch.h"

////////////////////
// Type Functions //
////////////////////

// self.new(double* data, ...)
void CALL_CONVENTION double_new(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    auto val = *static_cast<double*>(a);
    
    double* data = nullptr;
    try {
        data = new double{ val };
    } catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    mvl->object_setDataPointer(self, data);
    
}

void CALL_CONVENTION double_free(mvl_obj* self)
{
    
    auto data = static_cast<double*>(mvl->object_getDataPointer(self));
    delete data;
    
}

// self.getNativeData(double* val_out,...);
void CALL_CONVENTION double_getNativeData(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    auto a_double = static_cast<double*>(a);
    auto val = *static_cast<double*>(mvl->object_getDataPointer(self));
    *a_double = val;
    
}

mvl_type_register_callbacks const double_registration = {
    double_new,
    double_free,
    double_getNativeData,
    nullptr
};

////////////////////////
// Internal Functions //
////////////////////////

mvl_obj* double_new_internal(double val)
{
    
    auto ret = mvl->object_new(core_cache.token_core_Double, &val, nullptr, nullptr, nullptr);
    
    return ret;
}

// assumes double_obj is actually of type core.Double
double double_get_internal(mvl_obj* double_obj)
{
    
    auto val = *static_cast<double*> (mvl->object_getDataPointer(double_obj));
    
    return val;
}

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void double_register_type()
{
    
    mvl->type_register(core_cache.token_core_Double, double_registration);
    
}

void double_register_nativeFunctions()
{
    
    // TODO
    
}