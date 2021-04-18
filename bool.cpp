#include "pch.h"

void bool_register(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, tokens::core_Bool, bool_registration);
    MVL->stackframe_pop(inst);
}

// self.new(int* data_bool, ...)
void bool_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto val = *static_cast<int*>(a);
    if (val != 0)
        val = 1;

    int* data = nullptr;
    try {
        data = new int{ val };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, data);
    MVL->stackframe_pop(inst);
}

void bool_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<int*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(int* bool_out,...);
void bool_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto a_int = static_cast<int*>(a);
    auto val = *static_cast<int*>(MVL->object_getDataPointer(inst, self));
    *a_int = val;
    MVL->stackframe_pop(inst);
}

mvl_type_register_callbacks const bool_registration = {
    bool_new,
    bool_free,
    bool_getNativeData,
    nullptr
};
