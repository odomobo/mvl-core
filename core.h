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

    mvl_libraryFunction_t none_new;
    mvl_libraryFunction_t none_str;
    mvl_libraryFunction_t none_hash;

    mvl_libraryFunction_t bool_new;
    mvl_libraryFunction_t bool_getVal;
    mvl_libraryFunction_t bool_str;
    mvl_libraryFunction_t bool_hash;
    
    mvl_libraryFunction_t double_new;
    mvl_libraryFunction_t double_getVal;


    mvl_libraryFunction_t string_new;
    mvl_libraryFunction_t string_getVal;


    mvl_libraryFunction_t list_new;
    mvl_libraryFunction_t list_getVal;
    mvl_libraryFunction_t list_get;
    mvl_libraryFunction_t list_length;
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
    core_cache.token_core_Bool_getVal = mvl->token_get("core.Bool.getVal");
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
    core_cache.token_core_Double_getVal = mvl->token_get("core.Double.getVal");

    core_cache.token_core_String = mvl->token_get("core.String");
    core_cache.token_core_String_new = mvl->token_get("core.String.new");
    core_cache.token_core_String_getVal = mvl->token_get("core.String.getVal");

    core_cache.token_core_List = mvl->token_get("core.List");
    core_cache.token_core_List_new = mvl->token_get("core.List.new");
    core_cache.token_core_List_getVal = mvl->token_get("core.List.getVal");
    core_cache.token_core_List_get = mvl->token_get("core.List.get");
    core_cache.token_core_List_length = mvl->token_get("core.List.length");

    core_cache.token_core_List_mGet = mvl->token_get("core.List$get");
    core_cache.token_core_List_mLength = mvl->token_get("core.List$length");

    core_cache.token_core_NativeFunction = mvl->token_get("core.NativeFunction");
}

inline void core_init_libraryFunctions()
{
    core_cache.none_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_new);
    core_cache.none_str = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_str);
    core_cache.none_hash = core_cache.mvl->libraryFunction_get(core_cache.token_core_None_hash);

    core_cache.bool_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_new);
    core_cache.bool_str = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_str);
    core_cache.bool_hash = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_hash);
    core_cache.bool_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_Bool_getVal);

    core_cache.double_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_new);
    core_cache.double_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_Double_getVal);


    core_cache.string_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_String_new);
    core_cache.string_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_String_getVal);


    core_cache.list_new = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_new);
    core_cache.list_getVal = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_getVal);
    core_cache.list_get = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_get);
    core_cache.list_length = core_cache.mvl->libraryFunction_get(core_cache.token_core_List_length);
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
inline uint32_t core_none_hash(mvl_obj* self)
{
    return core_cache.none_hash(mvl_obj_val(self), unused(), unused(), unused()).uint32_val;
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
inline char const* core_bool_str(mvl_obj* self)
{
    return core_cache.bool_str(mvl_obj_val(self), unused(), unused(), unused()).const_string_val;
}

// assumes self is of type core.Bool
inline uint32_t core_bool_hash(mvl_obj* self)
{
    return core_cache.bool_hash(mvl_obj_val(self), unused(), unused(), unused()).uint32_val;
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