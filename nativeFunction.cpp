#include "pch.h"

////////////////////
// Type Functions //
////////////////////

struct NativeFunction
{
    mvl_token nativeFunction_token;
    mvl_nativeFunction_fp nativeFunction_fp;
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

mvl_reference_iterator nativeFunction_getReferenceIterator(mvl_obj* self)
{
    return { int_val(0), self };
}

mvl_obj* nativeFunction_getNextReference(mvl_reference_iterator* iter)
{
    auto data = get_data(iter->self);
    int index = iter->data.int_val;
    mvl_obj* ret = nullptr;
    if (index == 0)
        ret = data->signature;
    else if (index == 1)
        ret = data->help_text;

    if (ret != nullptr)
    {
        mvl->internalReference_increment(ret);
        iter->data = int_val(index + 1);
    }

    return ret;
}

void nativeFunction_freeReferenceIterator(mvl_reference_iterator* iter)
{
    // nothing to free
}

mvl_type_register_callbacks const nativeFunction_registration = {
    nativeFunction_free,
    nativeFunction_getReferenceIterator,
    nativeFunction_getNextReference,
    nativeFunction_freeReferenceIterator,
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(mvl_token_val nativeFunction_token, mvl_nativeFunction_val nativeFunction_fp, mvl_obj* signature, mvl_obj* help_text)
// Both signature and help_text can be either core.String or core.None
mvl_data CALL_CONVENTION nativeFunction_new_libraryFunction(mvl_data nativeFunction_token, mvl_data nativeFunction_fp, mvl_data signature, mvl_data help_text)
{
    NativeFunction* data = retry_new<NativeFunction>( nativeFunction_token.mvl_token_val, nativeFunction_fp.mvl_nativeFunction_val, signature.mvl_obj_val, help_text.mvl_obj_val );

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
    mvl->internalReference_increment(data->signature);
    return mvl_obj_val(data->signature);
}

// mvl_obj_val getHelpText(mvl_obj_val self, ...)
// Self must be core.NativeFunction
mvl_data CALL_CONVENTION nativeFunction_getHelpText_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    auto data = get_data(self);
    mvl->internalReference_increment(data->help_text);
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