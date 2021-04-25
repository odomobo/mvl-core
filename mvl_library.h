#pragma once

///////////////////////////
//      Macro Magic      //
///////////////////////////

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#include <stdbool.h>
#endif

#ifdef _WIN32
#define CALL_CONVENTION __cdecl
#ifdef __cplusplus
#define EXPORT(type) extern "C" type __declspec(dllexport) __cdecl
#else
#define EXPORT(type) extern type __declspec(dllexport) __cdecl
#endif
#else
#define CALL_CONVENTION
#define EXPORT(type) extern type
#endif

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////
//          Types          //
/////////////////////////////

// A struct pointing to an MVL object.
// These are automatically memory managed, and will be GCd automatically.
// If you have access to one while in a library call (for example, if you
// have the only reference to the object), the GC is not allowed to
// free it until returning from the library call.
struct mvl_obj;
typedef struct mvl_obj mvl_obj;

typedef uint64_t mvl_token;

/////////////////////////
// MVL Data Type Union //
/////////////////////////

// this is needed before mvl_data, because it is part of the mvl_data union
typedef mvl_obj* (CALL_CONVENTION* mvl_nativeFunction_fp)(mvl_obj* list);

union mvl_data
{
    int int_val;
    uint8_t uint8_val;
    char char_val;
    int32_t int32_val;
    uint32_t uint32_val;
    int64_t int64_val;
    uint64_t uint64_val;
    size_t size_val;
    float float_val;
    double double_val;
    bool bool_val;
    char* string_val;
    char const* const_string_val;
    mvl_token mvl_token_val;
    mvl_obj* mvl_obj_val;
    mvl_obj** mvl_obj_array_val;
    mvl_nativeFunction_fp mvl_nativeFunction_val;
    void* voidp_val;

    int* int_out;
    uint8_t* uint8_out;
    char* char_out;
    int32_t* int32_out;
    uint32_t* uint32_out;
    int64_t* int64_out;
    uint64_t* uint64_out;
    size_t* size_out;
    float* float_out;
    double* double_out;
    bool* bool_out;
    char** string_out;
    char const** const_string_out;
    mvl_token* mvl_token_out;
    mvl_obj** mvl_obj_out;
    mvl_obj*** mvl_obj_array_out;
    mvl_nativeFunction_fp* mvl_nativeFunction_out;
    void** voidp_out;
};
typedef union mvl_data mvl_data;

#define MVL_DATA_HELPER(type, identifier) \
    inline mvl_data identifier##_val(type v) { \
        mvl_data ret; \
        ret.identifier##_val = v; \
        return ret; \
    } \
    inline mvl_data identifier##_out(type* p) { \
        mvl_data ret; \
        ret.identifier##_out = p; \
        return ret; \
    }

MVL_DATA_HELPER(int, int)
MVL_DATA_HELPER(uint8_t, uint8)
MVL_DATA_HELPER(char, char)
MVL_DATA_HELPER(int32_t, int32)
MVL_DATA_HELPER(uint32_t, uint32)
MVL_DATA_HELPER(int64_t, int64)
MVL_DATA_HELPER(uint64_t, uint64)
MVL_DATA_HELPER(size_t, size)
MVL_DATA_HELPER(float, float)
MVL_DATA_HELPER(double, double)
MVL_DATA_HELPER(bool, bool)
MVL_DATA_HELPER(char*, string)
MVL_DATA_HELPER(char const*, const_string)
MVL_DATA_HELPER(mvl_token, mvl_token)
MVL_DATA_HELPER(mvl_obj*, mvl_obj)
MVL_DATA_HELPER(mvl_obj**, mvl_obj_array)
MVL_DATA_HELPER(mvl_nativeFunction_fp, mvl_nativeFunction)
MVL_DATA_HELPER(void*, voidp)

inline mvl_data unused()
{
    return int_val(0);
}

inline mvl_data null_out()
{
    return voidp_val(NULL);
}

#undef MVL_DATA_HELPER

struct mvl_reference_iterator
{
    mvl_data data;
    mvl_obj* self;
};
typedef struct mvl_reference_iterator mvl_reference_iterator;

/////////////////////////////////
// Type Registration Callbacks //
/////////////////////////////////

// only responsible for freeing the native data; the interpreter will free the mvl_obj*
typedef void (CALL_CONVENTION* mvl_object_free_callback_fp)(mvl_obj* self);

typedef mvl_reference_iterator(CALL_CONVENTION* mvl_object_getReferenceIterator_callback_fp)(mvl_obj* self);
typedef mvl_obj*(CALL_CONVENTION* mvl_object_getNextReference_callback_fp)(mvl_reference_iterator* iter);
typedef void    (CALL_CONVENTION* mvl_object_freeReferenceIterator_callback_fp)(mvl_reference_iterator* iter);

struct mvl_type_register_callbacks {
    // if this is NULL, then that's asserting there is no data pointer
    // that needs to be freed
    mvl_object_free_callback_fp                  free_callback;

    // If any of the following is NULL, they must all be null.
    // That's an indication that this type never has any references.
    mvl_object_getReferenceIterator_callback_fp  getReferenceIterator_callback;
    mvl_object_getNextReference_callback_fp      getNextReference_callback;
    mvl_object_freeReferenceIterator_callback_fp freeReferenceIterator_callback;
};
typedef struct mvl_type_register_callbacks mvl_type_register_callbacks;

///////////////////////////////
// General Library Functions //
///////////////////////////////

// Causes a stack trace to be printed.
typedef void    (CALL_CONVENTION* mvl_error_fp)(char const* error_message);
typedef void    (CALL_CONVENTION* mvl_error_memory_fp)();
typedef int     (CALL_CONVENTION* mvl_is_error_fp)();
// Token is an identifier which is created from a string. Tokens should only be used internally for various lightweight identifiers, because they are never freed.
typedef mvl_token   (CALL_CONVENTION* mvl_token_get_fp)(char const* string);
// Caller is responsible for freeing string
typedef char*   (CALL_CONVENTION* mvl_token_toString_fp)(mvl_token t);
typedef mvl_token   (CALL_CONVENTION* mvl_typeof_fp)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_import_fp)(char const* library);
typedef void    (CALL_CONVENTION* mvl_script_run_fp)(char const* script_name, char const* source);

/////////////////////////////////
// Memory Management Functions //
/////////////////////////////////

typedef void    (CALL_CONVENTION* mvl_gc_run_fp)();
typedef void    (CALL_CONVENTION* mvl_internalReference_increment_fp)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_internalReference_decrement_fp)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_objectReference_increment_fp)(mvl_obj* owner, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_objectReference_decrement_fp)(mvl_obj* owner, mvl_obj* obj);

///////////////////////////////////////
// Function- & Method-Call Functions //
///////////////////////////////////////

typedef mvl_obj*(CALL_CONVENTION* mvl_function_callOnObject_fp)(mvl_obj* func, mvl_obj* args);
typedef mvl_obj*(CALL_CONVENTION* mvl_function_callByGlobalIdentifier_fp)(mvl_token identifier, mvl_obj* args);
typedef mvl_obj*(CALL_CONVENTION* mvl_method_call_fp)(mvl_obj* object, mvl_token method, mvl_obj* args);

///////////////////////////////////
// Global Manipulation Functions //
///////////////////////////////////

typedef mvl_obj*(CALL_CONVENTION* mvl_global_get_fp)(mvl_token identifier);
typedef void    (CALL_CONVENTION* mvl_global_set_fp)(mvl_token identifier, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_global_unset_fp)(mvl_token identifier);
typedef int     (CALL_CONVENTION* mvl_global_exists_fp)(mvl_token identifier);
// Returns length of "identifiers_out", which is also the number of globals. Caller is responsible for freeing "identifiers_out" with free(). "identifiers_out" is a pointer to an array of tokens.
typedef size_t  (CALL_CONVENTION* mvl_global_getAllIdentifiers_fp)(mvl_token** identifiers_out);

////////////////////////////////////////////
// Native Object Access; Native Functions //
////////////////////////////////////////////

typedef mvl_data(CALL_CONVENTION* mvl_libraryFunction_fp)(mvl_data a, mvl_data b, mvl_data c, mvl_data d);

// Each type should have its own new function that calls this.
typedef mvl_obj*(CALL_CONVENTION* mvl_object_create_fp)(mvl_token type_name, mvl_data data);
typedef void    (CALL_CONVENTION* mvl_nativeFunction_register_fp)(mvl_token nativeFunction_identifier, mvl_nativeFunction_fp function_callback);
typedef void    (CALL_CONVENTION* mvl_libraryFunction_register_fp)(mvl_token libraryFunction_identifier, mvl_libraryFunction_fp function_callback);
typedef mvl_libraryFunction_fp(CALL_CONVENTION* mvl_libraryFunction_get_fp)(mvl_token libraryFunction_identifier);

///////////////////////
// Type Registration //
///////////////////////

typedef void    (CALL_CONVENTION* mvl_type_register_fp)(mvl_token type_name, mvl_type_register_callbacks callbacks);
// Returns the data pointer, so the data can be accessed
typedef mvl_data(CALL_CONVENTION* mvl_object_getData_fp)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_object_setData_fp)(mvl_obj* obj, mvl_data data);
typedef mvl_token(CALL_CONVENTION* mvl_object_getTypename_token_fp)(mvl_obj* obj);

//////////////////////////////
// MVL API Callbacks Struct //
//////////////////////////////

struct mvl_library_api
{
    mvl_error_fp                           error;
    mvl_error_memory_fp                    error_memory;
    mvl_is_error_fp                        is_error;
    mvl_token_get_fp                       token_get;
    mvl_token_toString_fp                  token_toString;
    mvl_typeof_fp                          typeof;
    mvl_import_fp                          import;
    mvl_script_run_fp                      script_run;

    mvl_gc_run_fp                          gc_run;
    mvl_internalReference_increment_fp     internalReference_increment;
    mvl_internalReference_decrement_fp     internalReference_decrement;
    mvl_objectReference_increment_fp       objectReference_increment;
    mvl_objectReference_decrement_fp       objectReference_decrement;

    mvl_function_callOnObject_fp           function_callOnObject;
    mvl_function_callByGlobalIdentifier_fp function_callByGlobalIdentifier;
    mvl_method_call_fp                     method_call;

    mvl_global_get_fp                      global_get;
    mvl_global_set_fp                      global_set;
    mvl_global_unset_fp                    global_unset;
    mvl_global_exists_fp                   global_exists;
    mvl_global_getAllIdentifiers_fp        global_getAllIdentifiers;

    mvl_object_create_fp                   object_create;
    mvl_nativeFunction_register_fp         nativeFunction_register;
    mvl_libraryFunction_register_fp        libraryFunction_register;
    mvl_libraryFunction_get_fp             libraryFunction_get;

    mvl_type_register_fp                   type_register;
    mvl_object_getData_fp                  object_getData;
    mvl_object_setData_fp                  object_setData;
    mvl_object_getTypename_token_fp        object_getTypename_token;
};
typedef struct mvl_library_api mvl_library_api;

#ifdef __cplusplus
}
#endif