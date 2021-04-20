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

// uint32_val hash(mvl_obj_val self, ...)
// assumes self is actually of type core.Bool
mvl_data CALL_CONVENTION bool_hash_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    // TODO: what value to use for hash values?
    bool val = mvl->object_getData(self.mvl_obj_val).bool_val;
    if (val)
        return uint32_val(0);
    else
        return uint32_val(1);
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

static bool check_bool_self(mvl_obj* obj)
{
    bool is_bool = mvl->typeof(obj) == core_cache.token_core_Bool;
    if (!is_bool)
        mvl->error("Expected self to be type core.Bool");

    return is_bool;
}

static bool check_bool_other(mvl_obj* obj)
{
    bool is_bool = mvl->typeof(obj) == core_cache.token_core_Bool;
    if (!is_bool)
        mvl->error("Expected other to be type core.Bool");

    return is_bool;
}

mvl_obj* CALL_CONVENTION bool_str(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    char const* string = core_bool_str(self);
    return core_string_new_borrow(string, 0); // TODO: set length
}

mvl_obj* CALL_CONVENTION bool_equals(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    bool val = core_bool_equals(self, other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_hash(mvl_obj* args)
{
    
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    uint32_t hash = core_bool_hash(self);
    return core_double_new(static_cast<double>(hash));
}

mvl_obj* CALL_CONVENTION bool_and(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self) || !check_bool_other(self))
        return nullptr;

    bool val = core_bool_getVal(self) && core_bool_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_or(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self) || !check_bool_other(self))
        return nullptr;

    bool val = core_bool_getVal(self) || core_bool_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION bool_not(mvl_obj* args)
{
    
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
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
    mvl->libraryFunction_register(core_cache.token_core_Bool_equals, bool_equals_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Bool_hash, bool_hash_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Bool_getVal, bool_getVal_libraryFunction);
}

void bool_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_Bool_mStr, bool_str);
    mvl->nativeFunction_register(core_cache.token_core_Bool_mEquals, bool_equals);
    mvl->nativeFunction_register(core_cache.token_core_Bool_mHash, bool_hash);
    mvl->nativeFunction_register(core_cache.token_core_Bool_and, bool_and);
    mvl->nativeFunction_register(core_cache.token_core_Bool_or, bool_or);
    mvl->nativeFunction_register(core_cache.token_core_Bool_not, bool_not);
}