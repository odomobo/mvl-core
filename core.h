#pragma once
// To use: make sure you include the following global in one of your
// source files:
//
// CoreCache core_cache;
//
// Without that line, or will multiple instances of it, you'll get linker errors.
// Additionally, make sure you call core_init() before using any of the provided functions.

#include "mvl_library.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CoreCache
{
    mvl_library_api* mvl;

    mvl_token token_core_None;
    mvl_token token_core_None_new;
    mvl_token token_core_None_str;
    mvl_token token_core_None_hash;
    
    mvl_token token_core_None_mStr;
    mvl_token token_core_None_mEquals;
    mvl_token token_core_None_mHash;

    mvl_token token_core_Bool;
    mvl_token token_core_Bool_new;
    mvl_token token_core_Bool_getVal;
    mvl_token token_core_Bool_str;
    mvl_token token_core_Bool_hash;
    mvl_token token_core_Bool_and;
    mvl_token token_core_Bool_or;
    mvl_token token_core_Bool_not;
    
    mvl_token token_core_Bool_mStr;
    mvl_token token_core_Bool_mEquals;
    mvl_token token_core_Bool_mHash;

    mvl_token token_core_Double;
    mvl_token token_core_Double_new;
    mvl_token token_core_Double_getVal;
    mvl_token token_core_Double_str;
    mvl_token token_core_Double_hash;
    mvl_token token_core_Double_isInt;
    mvl_token token_core_Double_canParse;
    mvl_token token_core_Double_tryParse;
    mvl_token token_core_Double_parse;

    mvl_token token_core_Double_mStr;
    mvl_token token_core_Double_mEquals;
    mvl_token token_core_Double_mHash;
    mvl_token token_core_Double_mGreaterThan;
    mvl_token token_core_Double_mLessThan;
    mvl_token token_core_Double_mAdd;
    mvl_token token_core_Double_mSubtract;
    mvl_token token_core_Double_mMultiply;
    mvl_token token_core_Double_mDivide;
    mvl_token token_core_Double_mNegate;

    mvl_token token_core_String;
    mvl_token token_core_String_new;
    mvl_token token_core_String_getVal;

    mvl_token token_core_List;
    mvl_token token_core_List_new;
    mvl_token token_core_List_getVal;
    mvl_token token_core_List_get;
    mvl_token token_core_List_length;

    mvl_token token_core_List_mGet;
    mvl_token token_core_List_mLength;

    mvl_token token_core_NativeFunction;
    mvl_token token_core_NativeFunction_new;
    mvl_token token_core_NativeFunction_getToken;
    mvl_token token_core_NativeFunction_getNativeFunction;
    mvl_token token_core_NativeFunction_getSignature;
    mvl_token token_core_NativeFunction_getHelpText;

    //////////////////////////////////////////////////
    
    mvl_libraryFunction_fp none_new;
    mvl_libraryFunction_fp none_str;
    mvl_libraryFunction_fp none_hash;

    mvl_libraryFunction_fp bool_new;
    mvl_libraryFunction_fp bool_getVal;
    mvl_libraryFunction_fp bool_str;
    mvl_libraryFunction_fp bool_hash;
    
    mvl_libraryFunction_fp double_new;
    mvl_libraryFunction_fp double_getVal;
    mvl_libraryFunction_fp double_str;
    mvl_libraryFunction_fp double_hash;
    mvl_libraryFunction_fp double_isInt;
    mvl_libraryFunction_fp double_canParse;
    mvl_libraryFunction_fp double_tryParse;

    mvl_libraryFunction_fp string_new;
    mvl_libraryFunction_fp string_getVal;


    mvl_libraryFunction_fp list_new;
    mvl_libraryFunction_fp list_getVal;
    mvl_libraryFunction_fp list_get;
    mvl_libraryFunction_fp list_length;


    mvl_libraryFunction_fp nativeFunction_new;
    mvl_libraryFunction_fp nativeFunction_getToken;
    mvl_libraryFunction_fp nativeFunction_getNativeFunction;
    mvl_libraryFunction_fp nativeFunction_getSignature;
    mvl_libraryFunction_fp nativeFunction_getHelpText;
};
typedef struct CoreCache CoreCache;

extern CoreCache core_cache;

inline void core_init_tokens(mvl_library_api* mvl)
{
    core_cache.mvl = mvl;

    core_cache.token_core_None = mvl->token_get("core.None");
    core_cache.token_core_None_new = mvl->token_get("core.None.new");
    core_cache.token_core_None_str = mvl->token_get("core.None.str");
    core_cache.token_core_None_hash = mvl->token_get("core.None.hash");

    core_cache.token_core_None_mStr = mvl->token_get("core.None$str");
    core_cache.token_core_None_mEquals = mvl->token_get("core.None$equals");
    core_cache.token_core_None_mHash = mvl->token_get("core.None$hash");

    core_cache.token_core_Bool = mvl->token_get("core.Bool");
    core_cache.token_core_Bool_new = mvl->token_get("core.Bool.new");
    core_cache.token_core_Bool_getVal = mvl->token_get("core.Bool.get_val");
    core_cache.token_core_Bool_str = mvl->token_get("core.Bool.str");
    core_cache.token_core_Bool_hash = mvl->token_get("core.Bool.hash");
    core_cache.token_core_Bool_and = mvl->token_get("core.Bool.and");
    core_cache.token_core_Bool_or = mvl->token_get("core.Bool.or");
    core_cache.token_core_Bool_not = mvl->token_get("core.Bool.not");
    
    core_cache.token_core_Bool_mStr = mvl->token_get("core.Bool$str");
    core_cache.token_core_Bool_mEquals = mvl->token_get("core.Bool$equals");
    core_cache.token_core_Bool_mHash = mvl->token_get("core.Bool$hash");

    core_cache.token_core_Double = mvl->token_get("core.Double");
    core_cache.token_core_Double_new = mvl->token_get("core.Double.new");
    core_cache.token_core_Double_getVal = mvl->token_get("core.Double.get_val");
    core_cache.token_core_Double_str = mvl->token_get("core.Double.str");
    core_cache.token_core_Double_hash = mvl->token_get("core.Double.hash");
    core_cache.token_core_Double_isInt = mvl->token_get("core.Double.is_int");
    core_cache.token_core_Double_canParse = mvl->token_get("core.Double.can_parse");
    core_cache.token_core_Double_tryParse = mvl->token_get("core.Double.try_parse");
    core_cache.token_core_Double_parse = mvl->token_get("core.Double.parse");
    
    core_cache.token_core_Double_mStr = mvl->token_get("core.Double$str");
    core_cache.token_core_Double_mEquals = mvl->token_get("core.Double$equals");
    core_cache.token_core_Double_mHash = mvl->token_get("core.Double$hash");
    core_cache.token_core_Double_mGreaterThan = mvl->token_get("core.Double$greater_than");
    core_cache.token_core_Double_mLessThan = mvl->token_get("core.Double$less_than");
    core_cache.token_core_Double_mAdd = mvl->token_get("core.Double$add");
    core_cache.token_core_Double_mSubtract = mvl->token_get("core.Double$subtract");
    core_cache.token_core_Double_mMultiply = mvl->token_get("core.Double$multiply");
    core_cache.token_core_Double_mDivide = mvl->token_get("core.Double$divide");
    core_cache.token_core_Double_mNegate = mvl->token_get("core.Double$negate");

    core_cache.token_core_String = mvl->token_get("core.String");
    core_cache.token_core_String_new = mvl->token_get("core.String.new");
    core_cache.token_core_String_getVal = mvl->token_get("core.String.get_val");

    core_cache.token_core_List = mvl->token_get("core.List");
    core_cache.token_core_List_new = mvl->token_get("core.List.new");
    core_cache.token_core_List_getVal = mvl->token_get("core.List.get_val");
    core_cache.token_core_List_get = mvl->token_get("core.List.get");
    core_cache.token_core_List_length = mvl->token_get("core.List.length");

    core_cache.token_core_List_mGet = mvl->token_get("core.List$get");
    core_cache.token_core_List_mLength = mvl->token_get("core.List$length");

    core_cache.token_core_NativeFunction = mvl->token_get("core.NativeFunction");
    core_cache.token_core_NativeFunction_new = mvl->token_get("core.NativeFunction.new");
    core_cache.token_core_NativeFunction_getToken = mvl->token_get("core.NativeFunction.get_token");
    core_cache.token_core_NativeFunction_getNativeFunction = mvl->token_get("core.NativeFunction.get_native_function");
    core_cache.token_core_NativeFunction_getSignature = mvl->token_get("core.NativeFunction.get_signature");
    core_cache.token_core_NativeFunction_getHelpText = mvl->token_get("core.NativeFunction.get_help_text");
}

inline void core_init_libraryFunctions()
{
    core_cache.none_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_new);
    core_cache.none_str = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_str);
    core_cache.none_hash = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_hash);

    core_cache.bool_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_new);
    core_cache.bool_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_getVal);
    core_cache.bool_str = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_str);
    core_cache.bool_hash = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_hash);
    
    core_cache.double_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_new);
    core_cache.double_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_getVal);
    core_cache.double_str = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_str);
    core_cache.double_hash = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_hash);
    core_cache.double_isInt = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_isInt);
    core_cache.double_canParse = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_canParse);
    core_cache.double_tryParse = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_tryParse);

    core_cache.string_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_String_new);
    core_cache.string_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_String_getVal);


    core_cache.list_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_new);
    core_cache.list_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_getVal);
    core_cache.list_get = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_get);
    core_cache.list_length = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_length);


    core_cache.nativeFunction_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_NativeFunction_new);
    core_cache.nativeFunction_getToken = core_cache.mvl->libraryFunction_get(core_cache.token_core_NativeFunction_getToken);
    core_cache.nativeFunction_getNativeFunction = core_cache.mvl->libraryFunction_get(core_cache.token_core_NativeFunction_getNativeFunction);
    core_cache.nativeFunction_getSignature = core_cache.mvl->libraryFunction_get(core_cache.token_core_NativeFunction_getSignature);
    core_cache.nativeFunction_getHelpText = core_cache.mvl->libraryFunction_get(core_cache.token_core_NativeFunction_getHelpText);
}

inline void core_init(mvl_library_api* mvl)
{
    core_init_tokens(mvl);
    core_init_libraryFunctions();
}

//////////////////////////////
//           None           //
//////////////////////////////

inline mvl_obj* core_none_new()
{
    return core_cache.none_new(unused(), unused(), unused(), unused()).mvl_obj_val;
}

inline char const* core_none_str(mvl_obj* self)
{
    return core_cache.none_str(mvl_obj_val(self), unused(), unused(), unused()).const_string_val;
}

// assumes self is of type core.None
inline uint64_t core_none_hash(mvl_obj* self)
{
    return core_cache.none_hash(mvl_obj_val(self), unused(), unused(), unused()).uint64_val;
}

//////////////////////////////
//           Bool           //
//////////////////////////////

inline mvl_obj* core_bool_new(bool b)
{
    return core_cache.bool_new(bool_val(b), unused(), unused(), unused()).mvl_obj_val;
}

// assumes self is of type core.Bool
inline bool core_bool_getVal(mvl_obj* self)
{
    return core_cache.bool_getVal(mvl_obj_val(self), unused(), unused(), unused()).bool_val;
}

// assumes self is of type core.Bool
// returns a reference to a const string, which doesn't need to be freed
inline char const* core_bool_str(mvl_obj* self)
{
    return core_cache.bool_str(mvl_obj_val(self), unused(), unused(), unused()).const_string_val;
}

// assumes self is of type core.Bool
inline uint64_t core_bool_hash(mvl_obj* self)
{
    return core_cache.bool_hash(mvl_obj_val(self), unused(), unused(), unused()).uint64_val;
}

////////////////////////////////
//           Double           //
////////////////////////////////

inline mvl_obj* core_double_new(double d)
{
    return core_cache.double_new(double_val(d), unused(), unused(), unused()).mvl_obj_val;
}

// assumes self is of type core.Double
inline double core_double_getVal(mvl_obj* self)
{
    return core_cache.double_getVal(mvl_obj_val(self), unused(), unused(), unused()).double_val;
}

// assumes self is of type core.Double
// passes ownership of the string to the caller
inline char* core_double_str(mvl_obj* self, size_t* length_out)
{
    return core_cache.double_str(mvl_obj_val(self), size_out(length_out), unused(), unused()).string_val;
}

// assumes self is of type core.Double
inline uint64_t core_double_hash(mvl_obj* self)
{
    return core_cache.double_hash(mvl_obj_val(self), unused(), unused(), unused()).uint64_val;
}

// assumes self is of type core.Double
inline bool core_double_isInt(mvl_obj* self)
{
    return core_cache.double_isInt(mvl_obj_val(self), unused(), unused(), unused()).bool_val;
}

// If parsing is successful, val_out will be set to the parsed value.
// If length is 0, then it will be calculated with strlen().
// If val_out is NULL, then it won't be set.
// TODO: should this pass out a double or a core.Double?
inline bool core_double_tryParse(char const* str, size_t length, double* val_out)
{
    return core_cache.double_isInt(const_string_val(str), size_val(length), double_out(val_out), unused()).bool_val;
}

////////////////////////////////
//           String           //
////////////////////////////////

// if length is 0, then it's calculated with strlen
inline mvl_obj* core_string_new_copy(char const* str_const, size_t length)
{
    int copy_mode = 0; // copy
    auto c_str = const_cast<char*>(str_const); // I promise we won't touch your precious chars
    return core_cache.string_new(string_val(c_str), size_val(length), int_val(copy_mode), unused()).mvl_obj_val;
}

// If length is 0, then it's calculated with strlen.
// Behavior defaults to copying, which is the safest.
inline mvl_obj* core_string_new(char const* str_const, size_t length)
{
    return core_string_new_copy(str_const, length);
}

// if length is 0, then it's calculated with strlen
inline mvl_obj* core_string_new_borrow(char const* str_const, size_t length)
{
    auto str = const_cast<char*>(str_const); // I promise we won't touch your precious chars
    int copy_mode = 1; // borrow
    return core_cache.string_new(string_val(str), size_val(length), int_val(copy_mode), unused()).mvl_obj_val;
}

// if length is 0, then it's calculated with strlen
inline mvl_obj* core_string_new_take(char* str, size_t length)
{
    int copy_mode = 2; // take
    return core_cache.string_new(string_val(str), size_val(length), int_val(copy_mode), unused()).mvl_obj_val;
}

inline char const* core_string_getVal(mvl_obj* string, size_t* length_out)
{
    return core_cache.string_getVal(mvl_obj_val(string), size_out(length_out), unused(), unused()).const_string_val;
}

//////////////////////////////
//           List           //
//////////////////////////////

inline mvl_obj* core_list_new(mvl_obj** list_data, size_t length)
{
    return core_cache.list_new(mvl_obj_array_val(list_data), size_val(length), unused(), unused()).mvl_obj_val;
}

inline mvl_obj** core_list_getVal(mvl_obj* self, size_t* length_out)
{
    return core_cache.list_getVal(mvl_obj_val(self), size_out(length_out), unused(), unused()).mvl_obj_array_val;
}

inline mvl_obj* core_list_get(mvl_obj* self, size_t index)
{
    return core_cache.list_get(mvl_obj_val(self), size_val(index), unused(), unused()).mvl_obj_val;
}

inline size_t core_list_length(mvl_obj* self)
{
    return core_cache.list_length(mvl_obj_val(self), unused(), unused(), unused()).size_val;
}

//////////////////////////////
//      NativeFunction      //
//////////////////////////////

inline mvl_obj* core_nativeFunction_new(mvl_token nativeFunction_token, mvl_nativeFunction_fp nativeFunction_fp, char const* signature, char const* help_text)
{
    mvl_obj* signature_obj;
    if (signature == nullptr)
        signature_obj = core_none_new();
    else
        signature_obj = core_string_new_borrow(signature, 0);

    mvl_obj* help_text_obj;
    if (help_text == nullptr)
        help_text_obj = core_none_new();
    else
        help_text_obj = core_string_new_borrow(help_text, 0);

    return core_cache.nativeFunction_new(mvl_token_val(nativeFunction_token), mvl_nativeFunction_val(nativeFunction_fp), mvl_obj_val(signature_obj), mvl_obj_val(help_text_obj)).mvl_obj_val;
}

#ifdef __cplusplus
}
#endif

//////////////////////////////
//   C++ helper functions   //
//////////////////////////////
#ifdef __cplusplus

#include <string>
#include <vector>

//////////////////////////////
//           None           //
//////////////////////////////

//////////////////////////////
//           Bool           //
//////////////////////////////

////////////////////////////////
//           Double           //
////////////////////////////////

////////////////////////////////
//           String           //
////////////////////////////////

inline mvl_obj* core_string_new_copy(std::string& str)
{
    auto c_str_const = str.c_str();
    auto c_str = const_cast<char*>(c_str_const); // I promise we won't touch your precious chars
    auto length = str.size();
    int copy_mode = 0; // copy
    return core_cache.string_new(string_val(c_str), size_val(length), int_val(copy_mode), unused()).mvl_obj_val;
}

inline mvl_obj* core_string_new(std::string& str)
{
    return core_string_new_copy(str);
}

inline std::string core_string_getVal(mvl_obj* string)
{
    size_t length;
    auto c_str = core_cache.string_getVal(mvl_obj_val(string), size_out(&length), unused(), unused()).const_string_val;
    return std::string{ c_str, length };
}

//////////////////////////////
//           List           //
//////////////////////////////

// TODO: add another core_list_new that takes a std::span<mvl_obj*>... need to upgrade vs to get c++20 support first.
inline mvl_obj* core_list_new(std::vector<mvl_obj*> elements)
{
    auto list_data = elements.data();
    auto length = elements.size();
    return core_cache.list_new(mvl_obj_array_val(list_data), size_val(length), unused(), unused()).mvl_obj_val;
}

inline std::vector<mvl_obj*> core_list_getVal(mvl_obj* self)
{
    size_t length;
    mvl_obj** list_data = core_cache.list_getVal(mvl_obj_val(self), size_out(&length), unused(), unused()).mvl_obj_array_val;
    std::vector<mvl_obj*> ret;
    for (size_t i = 0; i < length; i++)
        ret.push_back(list_data[i]);

    return ret;
}

//////////////////////////////
//      NativeFunction      //
//////////////////////////////

#endif