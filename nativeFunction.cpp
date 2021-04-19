#include "pch.h"

////////////////////
// Type Functions //
////////////////////

struct NativeFunction
{
    token nativeFunction_token;
    mvl_nativeFunction_t nativeFunction_fp;
    mvl_obj* signature;
    mvl_obj* help_text;
};

// self.new(token* nativeFunction_token, mvl_nativeFunction_t* nativeFunction_fp, mvl_obj* signature, mvl_obj* help_text)
void CALL_CONVENTION nativeFunction_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto nativeFunction_token = *static_cast<token*>(a);
    auto nativeFunction_fp = *static_cast<mvl_nativeFunction_t*>(b);
    auto signature = static_cast<mvl_obj*>(c);
    auto help_text = static_cast<mvl_obj*>(d);

    NativeFunction* data = nullptr;
    try {
        data = new NativeFunction{ nativeFunction_token, nativeFunction_fp, signature, help_text };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, data);
    MVL->stackframe_pop(inst);
}

mvl_obj* nativeFunction_new_internal(mvl_i* inst, token nativeFunction_token, mvl_nativeFunction_t nativeFunction_fp, char const* signature, char const* help_text)
{
    MVL->STACKFRAME_PUSH(inst);
    mvl_obj* signature_obj;
    if (signature == nullptr)
        signature_obj = none_new_internal(inst);
    else
        signature_obj = STRING_NEW_INTERNAL_BORROW(inst, signature);

    mvl_obj* help_text_obj;
    if (help_text == nullptr)
        help_text_obj = none_new_internal(inst);
    else
        help_text_obj = STRING_NEW_INTERNAL_BORROW(inst, help_text);

    auto ret = MVL->object_new(inst, tokens::core_NativeFunction, &nativeFunction_token, &nativeFunction_fp, signature_obj, help_text_obj);
    MVL->stackframe_pop(inst);
    return ret;
}

void CALL_CONVENTION nativeFunction_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<NativeFunction*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(mvl_nativeFunction_t* nativeFunction_out, ...);
void CALL_CONVENTION nativeFunction_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    NativeFunction* dataPointer = static_cast<NativeFunction*>(MVL->object_getDataPointer(inst, self));
    auto a_nativeFunction_fp = static_cast<mvl_nativeFunction_t*>(a);
    auto nativeFunction_fp_val = dataPointer->nativeFunction_fp;
    *a_nativeFunction_fp = nativeFunction_fp_val;
    MVL->stackframe_pop(inst);
}

size_t CALL_CONVENTION nativeFunction_getReferences(mvl_i* inst, mvl_obj* self, mvl_obj*** references_out)
{
    MVL->STACKFRAME_PUSH(inst);
    NativeFunction* dataPointer = static_cast<NativeFunction*>(MVL->object_getDataPointer(inst, self));

    size_t const length = 2;
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
        error_memory(inst); // terminates the application
    
    *references_out[0] = dataPointer->signature;
    *references_out[1] = dataPointer->help_text;

    MVL->stackframe_pop(inst);
    return length;
}

mvl_type_register_callbacks const nativeFunction_registration = {
    nativeFunction_new,
    nativeFunction_free,
    nativeFunction_getNativeData,
    nativeFunction_getReferences
};

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void CALL_CONVENTION nativeFunction_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, tokens::core_NativeFunction, nativeFunction_registration);
    MVL->stackframe_pop(inst);
}

void nativeFunction_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // TODO
    MVL->stackframe_pop(inst);
}