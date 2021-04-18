#include "pch.h"

struct String
{
    char* string;
    size_t length;

    String(mvl_i* inst, size_t length_arg, char* string_arg, bool copy) : length{length_arg}
    {
        MVL->STACKFRAME_PUSH(inst);
        if (copy)
        {
            string = static_cast<char*>(malloc(length + 1));
            if (string == nullptr)
                error_memory(inst); // terminates the application

            string[length] = 0;
            memcpy(string, string_arg, length);
        }
        else
        {
            string = string_arg;
        }
        MVL->stackframe_pop(inst);
    }
};

void string_register(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, tokens::core_String, string_registration);
    MVL->stackframe_pop(inst);
}

// self.new(size_t* length, char* string, int* copy_bool,...)
// If *copy_bool is true, the a copy of the string is made and the caller retains ownership of string.
// If *copy_bool is false, then the mvl_obj* takes ownership of string and will be responsible for it being freed.
// Such a string must have been allocated with malloc() or calloc(), because it will be freed with free().
void string_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto length = *static_cast<size_t*>(a);
    auto string = static_cast<char*>(b);
    int copy_bool = *static_cast<int*>(c);

    String* data = nullptr;
    try {
        data = new String{ inst, length, string, static_cast<bool>(copy_bool) };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, data);
    MVL->stackframe_pop(inst);
}

void string_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<String*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(size_t* length_out, char** string_out,...);
// Note that this gives a pointer to the string's native data; that means if the mvl_obj* is freed, then the reference to the string is no longer valid.
void string_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    String* dataPointer = static_cast<String*>(MVL->object_getDataPointer(inst, self));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->length;
    *a_length = length_val;

    auto b_string = static_cast<char**>(b);
    auto string_val = dataPointer->string;
    *b_string = string_val;
    MVL->stackframe_pop(inst);
}

mvl_type_register_callbacks const string_registration = {
    string_new,
    string_free,
    string_getNativeData,
    nullptr
};