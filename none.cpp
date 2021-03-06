#include "pch.h"

////////////////////
// Type Functions //
////////////////////

mvl_type_register_callbacks const none_registration = {
    nullptr,
    nullptr
};

////////////////////////
// Library Functions //
////////////////////////

// mvl_obj_val new(unused, ...)
mvl_data CALL_CONVENTION none_new_libraryFunction(mvl_data a, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl_obj_val(mvl->object_create(core_cache.token_core_None_new, unused()));
}

// const_string_val str(mvl_obj_val self, ...)
// assumes self is core.None
mvl_data CALL_CONVENTION none_str_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return const_string_val("none");
}

// uint64_val hash(mvl_obj_val self, ...)
// assumes self is core.None
mvl_data CALL_CONVENTION none_hash_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return uint64_val(0); // TODO: what value to use for hash?
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_none_self(mvl_obj* obj)
{
    return check_type(obj, "self", core_cache.token_core_None);
}

mvl_obj* CALL_CONVENTION none_str(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_none_self(self))
        return nullptr;

    // TODO: get length, I guess
    auto string = core_none_str(self);
    return core_string_new_borrow(string, 0);
}

mvl_obj* CALL_CONVENTION none_equals(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_none_self(self))
        return nullptr;

    bool other_is_none = mvl->typeof(other) == core_cache.token_core_None;
    return core_bool_new(other_is_none);
}

mvl_obj* CALL_CONVENTION none_hash(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_none_self(self))
        return nullptr;

    uint64_t hash = core_none_hash(self);
    return core_double_new(static_cast<double>(hash));
}

////////////////////////////
//      Registration      //
////////////////////////////

void none_register_type()
{
    mvl->type_register(core_cache.token_core_None, none_registration);
}

void none_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_None_new, none_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_None_str, none_str_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_None_hash, none_hash_libraryFunction);
}

void none_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_None_mStr, none_str);
    mvl->nativeFunction_register(core_cache.token_core_None_mEquals, none_equals);
    mvl->nativeFunction_register(core_cache.token_core_None_mHash, none_hash);
}