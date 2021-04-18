#pragma once

///////////////////////////
//      Macro Magic      //
///////////////////////////

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
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

// A struct pointing to the MVL instance.
// This can be null in the case that the MVL interpreter implementation has a single global instance,
// but this allows for the functionality of having multiple independent interpreters running in the
// same application.
struct mvl_i;
typedef struct mvl_i mvl_i;

// A struct pointing to an MVL object.
// These are automatically memory managed, and will be GCd automatically.
// If you have access to one while in a library call (for example, if you
// have the only reference to the object), the GC is not allowed to
// free it until returning from the library call.
struct mvl_obj;
typedef struct mvl_obj mvl_obj;

typedef uint64_t token;

/////////////////////////////////
// Type Registration Callbacks //
/////////////////////////////////

// Needs to update the data in the object provided. The object provided is the correct type, but with a null data pointer.
typedef void (CALL_CONVENTION* mvl_object_new_callback_t)(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d);
// only responsible for freeing the native data; the interpreter will free the mvl_obj*
typedef void (CALL_CONVENTION* mvl_object_free_callback_t)(mvl_i* inst, mvl_obj* self);
typedef void (CALL_CONVENTION* mvl_object_getNativeData_callback_t)(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d);
// Returns reference count.
// Caller is responsible for freeing references_out array.
// "references_out" is a pointer to an array of mvl_obj*.
// *references_out must have been allocated using malloc() or calloc(), because it will be freed with free().
typedef size_t (CALL_CONVENTION* mvl_object_getReferences_callback_t)(mvl_i* inst, mvl_obj* self, mvl_obj*** references_out);

struct mvl_type_register_callbacks {
    // must not be null
    mvl_object_new_callback_t new_callback;
    // must not be NULL
    mvl_object_free_callback_t free_callback;
    // must not be null
    mvl_object_getNativeData_callback_t getNativeData_callback;
    // if this is NULL, then that’s asserting this type 
    // never has any references
    mvl_object_getReferences_callback_t getReferences_callback;
};
typedef struct mvl_type_register_callbacks mvl_type_register_callbacks;

typedef mvl_obj* (CALL_CONVENTION* mvl_nativeFunction_callback)(mvl_i* inst, mvl_obj* obj);

///////////////////////////////
// General Library Functions //
///////////////////////////////

// Uses a reference to function_sig, so it should not be modified or freed until the matching mvl_stackframe_pop.
typedef void    (CALL_CONVENTION* mvl_stackframe_push_t)(mvl_i* inst, char const* function_sig, char const* file, int line);
typedef void    (CALL_CONVENTION* mvl_stackframe_pop_t)(mvl_i* inst);
// Causes a stack trace to be printed.
typedef void    (CALL_CONVENTION* mvl_error_t)(mvl_i* inst, char const* error_message);
typedef void    (CALL_CONVENTION* mvl_error_memory_t)(mvl_i* inst);
typedef int     (CALL_CONVENTION* mvl_is_error_t)(mvl_i* inst);
// Token is an identifier which is created from a string. Tokens should only be used internally for various lightweight identifiers, because they are never freed.
typedef token   (CALL_CONVENTION* mvl_token_get_t)(mvl_i* inst, char const* string);
// Caller is responsible for freeing string
typedef char*   (CALL_CONVENTION* mvl_token_toString_t)(mvl_i* inst, token t);
typedef token   (CALL_CONVENTION* mvl_typeof_t)(mvl_i* inst, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_import_t)(mvl_i* inst, char const* library);
typedef void    (CALL_CONVENTION* mvl_script_run_t)(mvl_i* inst, char const* script_name, char const* source);
typedef void    (CALL_CONVENTION* mvl_gc_run_t)(mvl_i* inst);

///////////////////////////////////
// Global Manipulation Functions //
///////////////////////////////////

typedef mvl_obj*(CALL_CONVENTION* mvl_global_get_t)(mvl_i* inst, token identifier);
typedef void    (CALL_CONVENTION* mvl_global_set_t)(mvl_i* inst, token identifier, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_global_unset_t)(mvl_i* inst, token identifier);
typedef int     (CALL_CONVENTION* mvl_global_exists_t)(mvl_i* inst, token identifier);
// Returns length of "identifiers_out", which is also the number of globals. Caller is responsible for freeing "identifiers_out". "identifiers_out" is a pointer to an array of tokens.
typedef size_t  (CALL_CONVENTION* mvl_global_getAllIdentifiers_t)(mvl_i* inst, token** identifiers_out);

////////////////////////////////////////////
// Native Object Access; Native Functions //
////////////////////////////////////////////

// Used to get a new object of the specified type, from native data. This can be called across libraries.
// Each type will have its own interface.
typedef mvl_obj*(CALL_CONVENTION* mvl_object_new_t)(mvl_i* inst, token type_name, void* a, void* b, void* c, void* d);
// Used to get native data from an object. You should check that the object has the right type before trying to get its data.
// Can be called across libraries.
typedef void    (CALL_CONVENTION* mvl_object_getNativeData_t)(mvl_i* inst, token type_name, mvl_obj* obj, void* a, void* b, void* c, void* d);
typedef void    (CALL_CONVENTION* mvl_nativeFunction_register_t)(mvl_i* inst, token library_function, mvl_nativeFunction_callback function_callback);
typedef mvl_obj*(CALL_CONVENTION* mvl_nativeFunction_call_t)(mvl_i* inst, token library_function, mvl_obj* list);

typedef mvl_obj*(CALL_CONVENTION* mvl_nativeFunction_t)(mvl_i* inst, mvl_obj* list);

///////////////////////
// Type Registration //
///////////////////////

typedef void    (CALL_CONVENTION* mvl_type_register_t)(mvl_i* inst, token type_name, mvl_type_register_callbacks callbacks);
// Returns the data pointer, so the data can be accessed
typedef void*   (CALL_CONVENTION* mvl_object_getDataPointer_t)(mvl_i* inst, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_object_setDataPointer_t)(mvl_i* inst, mvl_obj* obj, void* data);
typedef token   (CALL_CONVENTION* mvl_object_getTypename_token_t)(mvl_i* inst, mvl_obj* obj);

//////////////////////////////
// MVL API Callbacks Struct //
//////////////////////////////

struct mvl_library_api
{
    mvl_stackframe_push_t                 stackframe_push;
    mvl_stackframe_pop_t                  stackframe_pop;
    mvl_error_t                           error;
    mvl_error_memory_t                    error_memory;
    mvl_is_error_t                        is_error;
    mvl_token_get_t                       token_get;
    mvl_token_toString_t                  token_toString;
    mvl_typeof_t                          typeof;
    mvl_import_t                          import;
    mvl_script_run_t                      script_run;
    mvl_gc_run_t                          gc_run;
    mvl_global_get_t                      global_get;
    mvl_global_set_t                      global_set;
    mvl_global_unset_t                    global_unset;
    mvl_global_exists_t                   global_exists;
    mvl_global_getAllIdentifiers_t        global_getAllIdentifiers;
    mvl_object_new_t                      object_new;
    mvl_object_getNativeData_t            object_getNativeData;
    mvl_nativeFunction_register_t         nativeFunction_register;
    mvl_nativeFunction_call_t             nativeFunction_call;
    mvl_type_register_t                   type_register;
    mvl_object_getDataPointer_t           object_getDataPointer;
    mvl_object_setDataPointer_t           object_setDataPointer;
    mvl_object_getTypename_token_t       object_getTypename_token;
};
typedef struct mvl_library_api mvl_library_api;

#ifdef __cplusplus
}
#endif