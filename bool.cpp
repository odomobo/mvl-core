#include "pch.h"

////////////////////
// Type Functions //
////////////////////

mvl_type_register_callbacks const bool_registration = {
    nullptr,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(bool_val data_bool, ...)
mvl_data CALL_CONVENTION bool_new_libraryFunction(mvl_data data_bool, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl_obj_val(mvl->object_create(core_cache.token_core_Bool, bool_val(data_bool.bool_val)));
}

// const_string_val str(mvl_obj_val self, ...)
// assumes self is actually of type core.Bool
mvl_data CALL_CONVENTION bool_str_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    bool val = mvl->object_getData(self.mvl_obj_val).bool_val;
    if (val)
        return const_string_val("true");
    else
        return const_string_val("false");
}

// bool_val equals(mvl_obj_val self, mvl_obj_val other, ...)
// assumes self is actually of type core.Bool
mvl_data CALL_CONVENTION bool_equals_libraryFunction(mvl_data self, mvl_data other, mvl_data c, mvl_data d)
{
    bool other_is_bool = mvl->typeof(other.mvl_obj_val) == core_cache.token_core_Bool;
    if (!other_is_bool)
        return bool_val(false);

    bool self_val = mvl->object_getData(self.mvl_obj_val).bool_val;
    bool other_val = mvl->object_getData(other.mvl_obj_val).bool_val;

    return bool_val(self_val == other_val);
}

// uint64_val hash(mvl_obj_val self, ...)
// assumes self is actually of type core.Bool
mvl_data CALL_CONVENTION bool_hash_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    // TODO: what value to use for hash values?
    bool val = mvl->object_getData(self.mvl_obj_val).bool_val;
    if (val)
        return uint64_val(0);
    else
        return uint64_val(1);
}

// bool_val getVal(mvl_obj_val self, ...)
// assumes self is actually of type core.Bool
mvl_data CALL_CONVENTION bool_getVal_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl->object_getData(self.mvl_obj_val);
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_bool(mvl_obj* obj, char const* name)
{
    bool is_bool = mvl->typeof(obj) == core_cache.token_core_Bool;
    if (!is_bool)
    {
        std::string message = std::string{ name } + " is not type core.Bool; instead it was " + std::string{ mvl->token_toString(mvl->typeof(obj)) };
        mvl->error(message.c_str());
    }

    return is_bool;
}

mvl_obj* CALL_CONVENTION bool_str_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_bool(self, "self"))
        return nullptr;

    char const* string = core_bool_str(self);
    return core_string_new_borrow(string, 0); // TODO: set length
}

mvl_obj* CALL_CONVENTION bool_equals_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_bool(self, "self"))
        return nullptr;

    bool other_is_bool = mvl->typeof(other) == core_cache.token_core_Bool;
    if (!other_is_bool)
        return core_bool_new(false);

    bool val = core_bool_getVal(self) == core_bool_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_hash_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_bool(self, "self"))
        return nullptr;

    uint64_t hash = core_bool_hash(self);
    return core_double_new(static_cast<double>(hash));
}

mvl_obj* CALL_CONVENTION bool_and_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_bool(self, "self") || !check_bool(other, "other"))
        return nullptr;

    bool val = core_bool_getVal(self) && core_bool_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_or_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_bool(self, "self") || !check_bool(other, "other"))
        return nullptr;

    bool val = core_bool_getVal(self) || core_bool_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_not_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_bool(self, "self"))
        return nullptr;

    bool val = !core_bool_getVal(self);
    return core_bool_new(val);
}

////////////////////////////
//      Registration      //
////////////////////////////

void bool_register_type()
{
    mvl->type_register(core_cache.token_core_Bool, bool_registration);
}

void bool_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_Bool_new, bool_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Bool_str, bool_str_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Bool_hash, bool_hash_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Bool_getVal, bool_getVal_libraryFunction);
}

void bool_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_Bool_mStr, bool_str_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Bool_mEquals, bool_equals_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Bool_mHash, bool_hash_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Bool_and, bool_and_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Bool_or, bool_or_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Bool_not, bool_not_nativeFunction);
}