#pragma once

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


struct mvl_obj;
typedef struct mvl_obj mvl_obj;

typedef uint64_t token;

// should call mvl_object_create to get the object to return
typedef mvl_obj* (CALL_CONVENTION* mvl_object_new_callback_t)(void* a, void* b, void* c, void* d);
// only responsible for freeing the native data; the interpreter will free the mvl_obj*
typedef void (CALL_CONVENTION* mvl_object_free_callback_t)(mvl_obj* obj);
typedef void (CALL_CONVENTION* mvl_object_getNativeData_callback_t)(mvl_obj* obj, void* a, void* b, void* c, void* d);
// Returns reference count.
// Caller is responsible for freeing references_out array.
// “references_out” is a pointer to an array of mvl_obj*.
typedef size_t (CALL_CONVENTION* mvl_object_getReferences_callback_t)(mvl_obj* obj, mvl_obj*** references_out);

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

typedef mvl_obj* (CALL_CONVENTION* mvl_nativeFunction_callback)(mvl_obj* obj);

// ## library util ##
// Uses a reference to function_sig, so it should not be modified or freed until the matching mvl_stackframe_pop.
typedef void    (CALL_CONVENTION* mvl_stackframe_push_t)(char const* function_sig, char const* file, int line);
typedef void    (CALL_CONVENTION* mvl_stackframe_pop_t)();
// Causes a stack trace to be printed.
typedef void    (CALL_CONVENTION* mvl_error_t)(char const* error_message);
typedef void    (CALL_CONVENTION* mvl_error_memory_t)();
typedef int     (CALL_CONVENTION* mvl_is_error_t)();
// Token is an identifier which is created from a string. Tokens should only be used internally for various lightweight identifiers, because they are never freed.
typedef token   (CALL_CONVENTION* mvl_token_get_t)(char const* string);
// Caller is responsible for freeing string
typedef char*   (CALL_CONVENTION* mvl_token_toString_t)(token t);
typedef token   (CALL_CONVENTION* mvl_typeof_t)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_import_t)(char const* library);
typedef void    (CALL_CONVENTION* mvl_script_run_t)(char const* script_name, char const* source);
typedef void    (CALL_CONVENTION* mvl_gc_run_t)();


// ## global manipulation ##
typedef mvl_obj*(CALL_CONVENTION* mvl_global_get_t)(token identifier);
typedef void    (CALL_CONVENTION* mvl_global_set_t)(token identifier, mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_global_unset_t)(token identifier);
typedef int     (CALL_CONVENTION* mvl_global_exists_t)(token identifier);
// Returns length of “identifiers_out”, which is also the number of globals. Caller is responsible for freeing “identifiers_out”. “identifiers_out” is a pointer to an array of tokens.
typedef size_t  (CALL_CONVENTION* mvl_global_getAllIdentifiers_t)(token** identifiers_out);


// ## native object access, native functions ##
// called by the type's "new" callback to create an object
typedef mvl_obj*(CALL_CONVENTION* mvl_object_create_t)(token type_name, void* data);
// Used to get a new object of the specified type, from native data. This can be called across libraries.
// Each type will have its own interface.
typedef mvl_obj*(CALL_CONVENTION* mvl_object_new_t)(token type_name, void* a, void* b, void* c, void* d);
// Used to get native data from an object. You should check that the object has the right type before trying to get its data.
// Can be called across libraries.
typedef void    (CALL_CONVENTION* mvl_object_getNativeData_t)(token type_name, mvl_obj* obj, void* a, void* b, void* c, void* d);
typedef void    (CALL_CONVENTION* mvl_nativeFunction_register_t)(token library_function, mvl_nativeFunction_callback function_callback);
typedef mvl_obj*(CALL_CONVENTION* mvl_nativeFunction_call_t)(token library_function, mvl_obj* list);

typedef mvl_obj*(CALL_CONVENTION* mvl_nativeFunction_t)(mvl_obj* list);


// ## type registration ##
typedef void    (CALL_CONVENTION* mvl_type_register_t)(token type_name, mvl_type_register_callbacks callbacks);
// Returns the data pointer, so the data can be accessed
typedef void*   (CALL_CONVENTION* mvl_object_getDataPointer_t)(mvl_obj* obj);
typedef void    (CALL_CONVENTION* mvl_object_setDataPointer_t)(mvl_obj* obj, void* data);
typedef token   (CALL_CONVENTION* mvl_object_getTypename_token_t)(mvl_obj* obj);


// ## api struct ##
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
    mvl_object_create_t                   object_create;
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