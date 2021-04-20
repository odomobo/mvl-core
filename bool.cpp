#include "pch.h"

////////////////////
// Type Functions //
////////////////////

void CALL_CONVENTION bool_free(mvl_obj* self)
{
    
    auto data = static_cast<int*>(mvl->object_getDataPointer(self));
    delete data;
    
}

// self.getNativeData(int* bool_out,...);
void CALL_CONVENTION bool_getNativeData(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    auto a_int = static_cast<int*>(a);
    auto val = *static_cast<int*>(mvl->object_getDataPointer(self));
    *a_int = val;
    
}

mvl_type_register_callbacks const bool_registration = {
    bool_free,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(bool_in data_bool, ...)
mvl_data CALL_CONVENTION bool_new_libraryFunction(mvl_data data_bool, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl_obj_val(mvl->object_create(core_cache.token_core_Bool, bool_val(data_bool.bool_in)));
}

mvl_obj* core_bool_new(bool val)
{
    
    auto ret = mvl->object_new(core_cache.token_core_Bool, &val, nullptr, nullptr, nullptr);
    
    return ret;
}

// assumes bool_obj is actually of type core.Bool
bool core_bool_getVal(mvl_obj* bool_obj)
{
    
    auto val = *static_cast<int*>(mvl->object_getDataPointer(bool_obj));
    
    return static_cast<bool>(val);
}

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

//////////////////////
// Method Functions //
//////////////////////

mvl_obj* CALL_CONVENTION bool_str(mvl_obj* args)
{
    
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    bool val = bool_get_internal(self);
    mvl_obj* ret = val ? STRING_NEW_INTERNAL_BORROW("true") : STRING_NEW_INTERNAL_BORROW("false");

    
    return ret;
}

mvl_obj* CALL_CONVENTION bool_equals(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    bool other_is_bool = mvl->typeof(other) == core_cache.token_core_Bool;

    bool match = false;
    if (other_is_bool)
    {
        match = bool_get_internal(self) == bool_get_internal(other);
    }

    auto ret = bool_new_internal(other_is_bool && match);

    
    return ret;
}

mvl_obj* CALL_CONVENTION bool_hash(mvl_obj* args)
{
    
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    bool val = bool_get_internal(self);
    auto ret = double_new_internal(static_cast<double>(val));
    
    
    return ret;
}

mvl_obj* CALL_CONVENTION bool_and(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self) || !check_bool_other(self))
        return nullptr;

    bool val = bool_get_internal(self) && bool_get_internal(other);
    auto ret = bool_new_internal(val);

    
    return ret;
}

mvl_obj* CALL_CONVENTION bool_or(mvl_obj* args)
{
    
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self) || !check_bool_other(self))
        return nullptr;

    bool val = bool_get_internal(self) || bool_get_internal(other);
    auto ret = bool_new_internal(val);

    
    return ret;
}

mvl_obj* CALL_CONVENTION bool_not(mvl_obj* args)
{
    
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_bool_self(self))
        return nullptr;

    bool val = !bool_get_internal(self);
    auto ret = bool_new_internal(val);
    
    
    return ret;
}

////////////////////////////
//      Registration      //
////////////////////////////

void bool_register_type()
{
    
    mvl->type_register(core_cache.token_core_Bool, bool_registration);
    
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