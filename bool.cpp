#include "pch.h"

////////////////////
// Type Functions //
////////////////////

// self.new(int* data_bool, ...)
void CALL_CONVENTION bool_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
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

void CALL_CONVENTION bool_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<int*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(int* bool_out,...);
void CALL_CONVENTION bool_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
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

////////////////////////
// Internal Functions //
////////////////////////

mvl_obj* bool_new_internal(mvl_i* inst, bool val)
{
    MVL->STACKFRAME_PUSH(inst);
    auto ret = MVL->object_new(inst, TOKENS[inst].core_Bool, &val, nullptr, nullptr, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

// assumes bool_obj is actually of type core.Bool
bool bool_get_internal(mvl_i* inst, mvl_obj* bool_obj)
{
    MVL->STACKFRAME_PUSH(inst);
    auto val = *static_cast<int*>(MVL->object_getDataPointer(inst, bool_obj));
    MVL->stackframe_pop(inst);
    return static_cast<bool>(val);
}

static bool check_bool_self(mvl_i* inst, mvl_obj* obj)
{
    bool is_bool = MVL->typeof(inst, obj) == TOKENS[inst].core_Bool;
    if (!is_bool)
        MVL->error(inst, "Expected self to be type core.Bool");

    return is_bool;
}

static bool check_bool_other(mvl_i* inst, mvl_obj* obj)
{
    bool is_bool = MVL->typeof(inst, obj) == TOKENS[inst].core_Bool;
    if (!is_bool)
        MVL->error(inst, "Expected other to be type core.Bool");

    return is_bool;
}

//////////////////////
// Method Functions //
//////////////////////

mvl_obj* CALL_CONVENTION bool_str(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto self = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self))
        return nullptr;

    bool val = bool_get_internal(inst, self);
    mvl_obj* ret = val ? STRING_NEW_INTERNAL_BORROW(inst, "true") : STRING_NEW_INTERNAL_BORROW(inst, "false");

    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION bool_equals(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto [self, other] = extract_2_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self))
        return nullptr;

    bool other_is_bool = MVL->typeof(inst, other) == TOKENS[inst].core_Bool;

    bool match = false;
    if (other_is_bool)
    {
        match = bool_get_internal(inst, self) == bool_get_internal(inst, other);
    }

    auto ret = bool_new_internal(inst, other_is_bool && match);

    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION bool_hash(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto self = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self))
        return nullptr;

    bool val = bool_get_internal(inst, self);
    auto ret = double_new_internal(inst, static_cast<double>(val));
    
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION bool_and(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto [self, other] = extract_2_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self) || !check_bool_other(inst, self))
        return nullptr;

    bool val = bool_get_internal(inst, self) && bool_get_internal(inst, other);
    auto ret = bool_new_internal(inst, val);

    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION bool_or(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto [self, other] = extract_2_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self) || !check_bool_other(inst, self))
        return nullptr;

    bool val = bool_get_internal(inst, self) || bool_get_internal(inst, other);
    auto ret = bool_new_internal(inst, val);

    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION bool_not(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto self = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_bool_self(inst, self))
        return nullptr;

    bool val = !bool_get_internal(inst, self);
    auto ret = bool_new_internal(inst, val);
    
    MVL->stackframe_pop(inst);
    return ret;
}

////////////////////////////
//      Registration      //
////////////////////////////

void bool_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, TOKENS[inst].core_Bool, bool_registration);
    MVL->stackframe_pop(inst);
}

void bool_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_str, bool_str);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_equals, bool_equals);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_hash, bool_hash);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_and, bool_and);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_or, bool_or);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_Bool_not, bool_not);
    MVL->stackframe_pop(inst);
}