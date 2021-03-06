#include "pch.h"

////////////////////
// Type Functions //
////////////////////

mvl_type_register_callbacks const double_registration = {
    nullptr,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(double_val data_double, ...)
mvl_data CALL_CONVENTION double_new_libraryFunction(mvl_data data_double, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl_obj_val(mvl->object_create(core_cache.token_core_Double, double_val(data_double.double_val)));
}

// double_val getVal(mvl_obj_val self, ...)
// assumes self is actually of type core.Double
mvl_data CALL_CONVENTION double_getVal_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl->object_getData(self.mvl_obj_val);
}

// string_val str(mvl_obj_val self [, size_out length_out ], ...)
// Assumes self is actually of type core.Double .
// The returned string must be freed.
mvl_data CALL_CONVENTION double_str_libraryFunction(mvl_data self, mvl_data length_out, mvl_data c, mvl_data d)
{
    auto val = mvl->object_getData(self.mvl_obj_val).double_val;
    auto str = std::to_string(val);
    auto length = str.size();
    if (length_out.size_out != nullptr)
        *length_out.size_out = length;

    auto ret = retry_malloc<char*>(length+1);

    memcpy(ret, str.data(), length);
    ret[length] = 0;

    return string_val(ret);
}

// uint64_val hash(mvl_obj_val self, ...)
// assumes self is actually of type core.Double
mvl_data CALL_CONVENTION double_hash_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    double val = mvl->object_getData(self.mvl_obj_val).double_val;
    std::hash<double> double_hash;
    auto ret = double_hash(val);
    ret = ret % (1ULL << 53); // 2^53 is biggest consecutive whole number representable by IEEE double.
    return uint64_val(ret);
}

// bool_val isInt(mvl_obj_val self, ...)
// assumes self is actually of type core.Double
mvl_data CALL_CONVENTION double_isInt_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    double val = mvl->object_getData(self.mvl_obj_val).double_val;
    double integral_part;
    double floating_part = std::modf(val, &integral_part);

    return bool_val(floating_part == 0);
}

// bool_val tryParse(const_string_val str [, size_val length ] [, double_out val_out] , ...)
// If length is 0, it's calculated with strlen()
// If val_out is NULL, then it won't be set.
// TODO: should this pass out a double or a core.Double?
mvl_data CALL_CONVENTION double_tryParse_libraryFunction(mvl_data str, mvl_data length, mvl_data val_out, mvl_data d)
{
    auto str_val = str.const_string_val;

    size_t length_val = length.size_val;
    if (length_val == 0)
        length_val = strlen(str_val);

    // empty string, or string that starts with whitespace is not allowed!
    if (length_val == 0 || isspace(str_val[0]))
        return bool_val(false);

    char* endptr;
    auto double_val = strtod(str_val, &endptr);

    // if we didn't consume the whole string, then it's not allowed!
    if (endptr != str_val + length_val)
        return bool_val(false);

    // if we consumed an entire non-trivial string, then I guess we succeeded
    if (val_out.double_out != nullptr)
        *val_out.double_out = double_val;

    return bool_val(true);
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_double(mvl_obj* obj, char const* name)
{
    return check_type(obj, name, core_cache.token_core_Double);
}

mvl_obj* CALL_CONVENTION double_str_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_double(self, "self"))
        return nullptr;

    auto str = std::to_string(core_double_getVal(self));
    return core_string_new(str);
}

mvl_obj* CALL_CONVENTION double_equals_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self"))
        return nullptr;

    bool other_is_double = mvl->typeof(other) == core_cache.token_core_Double;
    if (!other_is_double)
        return core_bool_new(false);

    bool val = core_double_getVal(self) == core_double_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION double_hash_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_double(self, "self"))
        return nullptr;

    auto hash = core_double_hash(self);
    return core_double_new(static_cast<double>(hash));
}

mvl_obj* CALL_CONVENTION double_greaterThan_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) > core_double_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION double_lessThan_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) < core_double_getVal(other);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION double_add_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) + core_double_getVal(other);
    return core_double_new(val);
}

mvl_obj* CALL_CONVENTION double_subtract_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) - core_double_getVal(other);
    return core_double_new(val);
}

mvl_obj* CALL_CONVENTION double_multiply_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) * core_double_getVal(other);
    return core_double_new(val);
}

mvl_obj* CALL_CONVENTION double_divide_nativeFunction(mvl_obj* args)
{
    auto [self, other] = extract_2_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));
    defer (mvl->internalReference_decrement(other));

    if (!check_double(self, "self") || !check_double(other, "other"))
        return nullptr;

    auto val = core_double_getVal(self) / core_double_getVal(other);
    return core_double_new(val);
}

mvl_obj* CALL_CONVENTION double_negate_nativeFunction(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_double(self, "self"))
        return nullptr;

    auto val = -core_double_getVal(self);
    return core_double_new(val);
}

mvl_obj* CALL_CONVENTION double_isInt_nativeFunction(mvl_obj* args)
{
    auto d = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(d));

    if (!check_double(d, "d"))
        return nullptr;

    auto val = core_double_isInt(d);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION double_canParse_nativeFunction(mvl_obj* args)
{
    auto s = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(s));

    if (!check_type(s, "s", core_cache.token_core_String))
        return nullptr;

    size_t length;
    auto str = core_string_getVal(s, &length);

    auto val = core_double_tryParse(str, length, nullptr);
    return core_bool_new(val);
}

mvl_obj* CALL_CONVENTION double_parse_nativeFunction(mvl_obj* args)
{
    auto s = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(s));

    if (!check_type(s, "s", core_cache.token_core_String))
        return nullptr;

    size_t length;
    auto str = core_string_getVal(s, &length);

    double ret;
    auto success = core_double_tryParse(str, length, &ret);
    if (!success)
    {
        std::string error_message = std::string{ "Could not parse \"" } + std::string{ str, length } + "\" as a double.";
        mvl->error(error_message.c_str());
        return nullptr;
    }

    return core_double_new(ret);
}

////////////////////////////
//      Registration      //
////////////////////////////

void double_register_type()
{
    mvl->type_register(core_cache.token_core_Double, double_registration);
}

void double_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_Double_new, double_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_getVal, double_getVal_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_str, double_str_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_hash, double_hash_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_isInt, double_isInt_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_tryParse, double_tryParse_libraryFunction);
}

void double_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_Double_mStr, double_str_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mEquals, double_equals_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mHash, double_hash_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mGreaterThan, double_greaterThan_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mLessThan, double_lessThan_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mAdd, double_add_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mSubtract, double_subtract_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mMultiply, double_multiply_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mDivide, double_divide_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_mNegate, double_negate_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_isInt, double_isInt_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_canParse, double_canParse_nativeFunction);
    mvl->nativeFunction_register(core_cache.token_core_Double_parse, double_parse_nativeFunction);
}