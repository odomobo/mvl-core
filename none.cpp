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

// bool_val equals(mvl_obj_val self, mvl_obj_val other, ...)
// assumes self is core.None
mvl_data CALL_CONVENTION none_equals_libraryFunction(mvl_data self, mvl_data other, mvl_data c, mvl_data d)
{
    bool other_is_none = mvl->typeof(other.mvl_obj_val) == core_cache.token_core_None;
    return bool_val(other_is_none);
}

// uint32_val hash(mvl_obj_val self, ...)
// assumes self is core.None
mvl_data CALL_CONVENTION none_hash_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return uint32_val(0); // TODO: what value to use for hash?
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_none_self(mvl_obj* obj)
{
    bool is_none = mvl->typeof(obj) == core_cache.token_core_None;
    if (!is_none)
        mvl->error("Expected self to be type core.None");

    return is_none;
}

mvl_obj* CALL_CONVENTION none_str(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

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

    if (!check_none_self(self))
        return nullptr;

    bool val = core_none_equals(self, other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION none_hash(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_none_self(self))
        return nullptr;

    uint32_t hash = core_none_hash(self);
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
    mvl->libraryFunction_register(core_cache.token_core_None_equals, none_equals_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_None_hash, none_hash_libraryFunction);
}

void none_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_None_mStr, none_str);
    mvl->nativeFunction_register(core_cache.token_core_None_mEquals, none_equals);
    mvl->nativeFunction_register(core_cache.token_core_None_mHash, none_hash);
}