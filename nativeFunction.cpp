#include "pch.h"

struct NativeFunction
{
    // TODO

    char* string;
    size_t length;

    NativeFunction(size_t length_arg, char* nativeFunction_arg, bool copy) : length{ length_arg }
    {
        if (copy)
        {
            string = static_cast<char*>(malloc(length + 1));
            string[length] = 0;
            memcpy(string, nativeFunction_arg, length);
        }
        else
        {
            string = nativeFunction_arg;
        }
    }
};

void nativeFunction_init()
{
    mvl.type_register(core_NativeFunction_token, nativeFunction_registration);
}

// new(token* nativeFunction_token, mvl_nativeFunction_t* nativeFunction_fp, mvl_obj* signature, mvl_obj* help_text)
mvl_obj* nativeFunction_new(void* a, void* b, void* c, void* d)
{
    auto nativeFunction_token = *static_cast<token*>(a);
    auto nativeFunction_fp = *static_cast<mvl_nativeFunction_t*>(b);
    auto signature = static_cast<mvl_obj*>(c);
    auto help_text = static_cast<mvl_obj*>(d);

    // TODO
    auto data = new NativeFunction{ length, string, copy_bool };
    return mvl.object_create(core_NativeFunction_token, data);
}

void nativeFunction_free(mvl_obj* obj)
{
    auto data = static_cast<NativeFunction*>(mvl.object_getDataPointer(obj));
    delete data;
}

// getNativeData(mvl_obj* string, mvl_nativeFunction_t* nativeFunction_out, ...);
void nativeFunction_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    // TODO
    NativeFunction* dataPointer = static_cast<NativeFunction*>(mvl.object_getDataPointer(obj));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->length;
    *a_length = length_val;

    auto b_string = static_cast<char**>(b);
    auto nativeFunction_val = dataPointer->string;
    *b_string = nativeFunction_val;
}

size_t nativeFunction_getReferences(mvl_obj* obj, mvl_obj*** references_out)
{
    NativeFunction* dataPointer = static_cast<NativeFunction*>(mvl.object_getDataPointer(obj));

    size_t const length = 2;
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
    {
        mvl.error_memory(); // terminates the application
    }
    *references_out[0] = dataPointer->signature;
    *references_out[1] = dataPointer->help_text;

    return length;
}

mvl_type_register_callbacks nativeFunction_registration = {
    nativeFunction_new,
    nativeFunction_free,
    nativeFunction_getNativeData,
    nativeFunction_getReferences
};