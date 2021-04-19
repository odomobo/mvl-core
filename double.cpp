#include "pch.h"

////////////////////
// Type Functions //
////////////////////

// self.new(double* data, ...)
void CALL_CONVENTION double_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto val = *static_cast<double*>(a);
    
    double* data = nullptr;
    try {
        data = new double{ val };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, data);
    MVL->stackframe_pop(inst);
}

void CALL_CONVENTION double_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<double*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(double* val_out,...);
void CALL_CONVENTION double_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto a_double = static_cast<double*>(a);
    auto val = *static_cast<double*>(MVL->object_getDataPointer(inst, self));
    *a_double = val;
    MVL->stackframe_pop(inst);
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

mvl_obj* double_new_internal(mvl_i* inst, double val)
{
    MVL->STACKFRAME_PUSH(inst);
    auto ret = MVL->object_new(inst, TOKENS[inst].core_Double, &val, nullptr, nullptr, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

// assumes double_obj is actually of type core.Double
double double_get_internal(mvl_i* inst, mvl_obj* double_obj)
{
    MVL->STACKFRAME_PUSH(inst);
    auto val = *static_cast<double*> (MVL->object_getDataPointer(inst, double_obj));
    MVL->stackframe_pop(inst);
    return val;
}

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void double_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, TOKENS[inst].core_Double, double_registration);
    MVL->stackframe_pop(inst);
}

void double_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // TODO
    MVL->stackframe_pop(inst);
}