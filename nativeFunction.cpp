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

static NativeFunction* get_data(mvl_obj* self)
{
    return static_cast<NativeFunction*>(mvl->object_getData(self).voidp_val);
}

static NativeFunction* get_data(mvl_data self)
{
    return get_data(self.mvl_obj_val);
}

void CALL_CONVENTION nativeFunction_free(mvl_obj* self)
{
    auto data = get_data(self);
    delete data;
}

mvl_references_list CALL_CONVENTION nativeFunction_getReferences(mvl_obj* self)
{
    NativeFunction* dataPointer = get_data(self);

    size_t const length = 2;
    mvl_obj** references = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (references == nullptr)
        error_memory(); // terminates the application
    
    references[0] = dataPointer->signature;
    references[1] = dataPointer->help_text;

    return {references, length};
}

mvl_type_register_callbacks const nativeFunction_registration = {
    nativeFunction_free,
    nativeFunction_getReferences
};

///////////////////////
// Library Functions //
///////////////////////



// mvl_obj_val new(mvl_token_val nativeFunction_token, mvl_nativeFunction_val nativeFunction_fp, mvl_obj* signature, mvl_obj* help_text)
// Both signature and help_text can be either core.String or core.None
mvl_data CALL_CONVENTION nativeFunction_new_libraryFunction(mvl_data nativeFunction_token, mvl_data nativeFunction_fp, mvl_data signature, mvl_data help_text)
{
    NativeFunction* data = nullptr;
    try {
        data = new NativeFunction{ nativeFunction_token.mvl_token_val, nativeFunction_fp.mvl_nativeFunction_val, signature.mvl_obj_val, help_text.mvl_obj_val };
    }
    catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    return mvl_obj_val(mvl->object_create(core_cache.token_core_NativeFunction, voidp_val(data)));
}

// mvl_token_val getToken(mvl_obj_val self, ...)
// Self must be core.NativeFunction
mvl_data CALL_CONVENTION nativeFunction_getToken_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    auto data = get_data(self);
    return mvl_token_val(data->nativeFunction_token);
}

// mvl_nativeFunction_val getNativeFunction(mvl_obj_val self, ...)
// Self must be core.NativeFunction
mvl_data CALL_CONVENTION nativeFunction_getNativeFunction_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    auto data = get_data(self);
    return mvl_nativeFunction_val(data->nativeFunction_fp);
}

// mvl_obj_val getSignature(mvl_obj_val self, ...)
// Self must be core.NativeFunction
mvl_data CALL_CONVENTION nativeFunction_getSignature_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    auto data = get_data(self);
    return mvl_obj_val(data->signature);
}

// mvl_obj_val getHelpText(mvl_obj_val self, ...)
// Self must be core.NativeFunction
mvl_data CALL_CONVENTION nativeFunction_getHelpText_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    auto data = get_data(self);
    return mvl_obj_val(data->help_text);
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
    mvl->libraryFunction_register(core_cache.token_core_NativeFunction_new, nativeFunction_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_NativeFunction_getToken, nativeFunction_getToken_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_NativeFunction_getNativeFunction, nativeFunction_getNativeFunction_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_NativeFunction_getSignature, nativeFunction_getSignature_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_NativeFunction_getHelpText, nativeFunction_getHelpText_libraryFunction);
    // TODO
}

void nativeFunction_register_nativeFunctions()
{
    // TODO
}