#include "pch.h"

////////////////////
// Type Functions //
////////////////////

void CALL_CONVENTION none_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    // no native data to set
}

void CALL_CONVENTION none_free(mvl_i* inst, mvl_obj* self)
{
    // no native data to free
}

void CALL_CONVENTION none_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    // no native data to get
}

mvl_type_register_callbacks const none_registration = {
    none_new,
    none_free,
    none_getNativeData,
    nullptr
};

////////////////////////
// Internal Functions //
////////////////////////

mvl_obj* none_new_internal(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    auto ret = MVL->object_new(inst, TOKENS[inst].core_None, nullptr, nullptr, nullptr, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

static bool check_none_self(mvl_i* inst, mvl_obj* obj)
{
    bool is_none = MVL->typeof(inst, obj) == TOKENS[inst].core_None;
    if (!is_none)
        MVL->error(inst, "Expected self to be type core.None");

    return is_none;
}

//////////////////////
// Method Functions //
//////////////////////

mvl_obj* CALL_CONVENTION none_str(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto self = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_none_self(inst, self))
        return nullptr;

    auto ret = STRING_NEW_INTERNAL_BORROW(inst, "none");
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION none_equals(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto [self, other] = extract_2_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_none_self(inst, self))
        return nullptr;

    // if other is core.None, then they are equal; otherwise they aren't
    auto other_is_none = MVL->typeof(inst, other) == TOKENS[inst].core_None;

    auto ret = bool_new_internal(inst, other_is_none);
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* CALL_CONVENTION none_hash(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto self = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (!check_none_self(inst, self))
        return nullptr;

    auto ret = double_new_internal(inst, 0);
    MVL->stackframe_pop(inst);
    return ret;
}

////////////////////////////
//      Registration      //
////////////////////////////

void none_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, TOKENS[inst].core_None, none_registration);
    MVL->stackframe_pop(inst);
}

void none_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_None_str, none_str);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_None_equals, none_equals);
    MVL->nativeFunction_register(inst, TOKENS[inst].core_None_hash, none_hash);
    MVL->stackframe_pop(inst);
}