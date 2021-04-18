#include "pch.h"

struct String
{
    char* string;
    size_t length;

    String(size_t length_arg, char* string_arg, bool copy) : length{length_arg}
    {
        if (copy)
        {
            string = static_cast<char*>(malloc(length + 1));
            string[length] = 0;
            memcpy(string, string_arg, length);
        }
        else
        {
            string = string_arg;
        }
    }
};

void string_init()
{
    mvl.type_register(core_String_token, string_registration);
}

// new(size_t* length, char* string, int* copy_bool,...)
// If *copy_bool is true, the a copy of the string is made and the caller retains ownership of string.
// If *copy_bool is false, then the mvl_obj* takes ownership of string and will be responsible for it being freed.
// Such a string must have been allocated with malloc() or calloc(), because it will be freed with free().
mvl_obj* string_new(void* a, void* b, void* c, void* d)
{
    auto length = *static_cast<size_t*>(a);
    auto string = static_cast<char*>(b);
    int copy_bool = *static_cast<int*>(c);

    auto data = new String{ length, string, copy_bool };
    return mvl.object_create(core_String_token, data);
}

void string_free(mvl_obj* obj)
{
    auto data = static_cast<String*>(mvl.object_getDataPointer(obj));
    delete data;
}

// getNativeData(mvl_obj* string, size_t* length_out, char** string_out,...);
// Note that this gives a pointer to the string's native data; that means if the mvl_obj* is freed, then the reference to the string is no longer valid.
void string_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    String* dataPointer = static_cast<String*>(mvl.object_getDataPointer(obj));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->length;
    *a_length = length_val;

    auto b_string = static_cast<char**>(b);
    auto string_val = dataPointer->string;
    *b_string = string_val;
}

mvl_type_register_callbacks string_registration = {
    string_new,
    string_free,
    string_getNativeData,
    nullptr
};