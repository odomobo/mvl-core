#include "pch.h"

////////////////////
// Type Functions //
////////////////////

struct NativeFunction
{
    mvl_token nativeFunction_token;
    mvl_nativeFunction_t nativeFunction_fp;
    mvl_obj* signature;
    mvl_obj* help_text;
};

// self.new(token* nativeFunction_token, mvl_nativeFunction_t* nativeFunction_fp, mvl_obj* signature, mvl_obj* help_text)
void CALL_CONVENTION nativeFunction_new(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    auto nativeFunction_token = *static_cast<mvl_token*>(a);
    auto nativeFunction_fp = *static_cast<mvl_nativeFunction_t*>(b);
    auto signature = static_cast<mvl_obj*>(c);
    auto help_text = static_cast<mvl_obj*>(d);

    NativeFunction* data = nullptr;
    try {
        data = new NativeFunction{ nativeFunction_token, nativeFunction_fp, signature, help_text };
    } catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    mvl->object_setData(self, data);
    
}

void CALL_CONVENTION nativeFunction_free(mvl_obj* self)
{
    
    auto data = static_cast<NativeFunction*>(mvl->object_getData(self));
    delete data;
    
}

// self.getNativeData(mvl_nativeFunction_t* nativeFunction_out, ...);
void CALL_CONVENTION nativeFunction_getNativeData(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    NativeFunction* dataPointer = static_cast<NativeFunction*>(mvl->object_getData(self));
    auto a_nativeFunction_fp = static_cast<mvl_nativeFunction_t*>(a);
    auto nativeFunction_fp_val = dataPointer->nativeFunction_fp;
    *a_nativeFunction_fp = nativeFunction_fp_val;
    
}

size_t CALL_CONVENTION nativeFunction_getReferences(mvl_obj* self, mvl_obj*** references_out)
{
    
    NativeFunction* dataPointer = static_cast<NativeFunction*>(mvl->object_getData(self));

    size_t const length = 2;
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
        error_memory(); // terminates the application
    
    *references_out[0] = dataPointer->signature;
    *references_out[1] = dataPointer->help_text;

    
    return length;
}

mvl_type_register_callbacks const nativeFunction_registration = {
    nativeFunction_free,
    nativeFunction_getReferences
};

////////////////////////
// Internal Functions //
////////////////////////

mvl_obj* nativeFunction_new_internal(mvl_token nativeFunction_token, mvl_nativeFunction_t nativeFunction_fp, char const* signature, char const* help_text)
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

    auto ret = mvl->object_new(core_cache.token_core_NativeFunction, &nativeFunction_token, &nativeFunction_fp, signature_obj, help_text_obj);
    
    return ret;
}

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void CALL_CONVENTION nativeFunction_register_type()
{
    mvl->type_register(core_cache.token_core_NativeFunction, nativeFunction_registration);
}

void nativeFunction_register_libraryFunctions()
{
    // TODO
}

void nativeFunction_register_nativeFunctions()
{
    // TODO
}