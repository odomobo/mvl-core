#include "pch.h"

struct List
{
    std::vector<mvl_obj*> data;

    List(size_t data_length, mvl_obj** data_arg) : data{data_length}
    {
        for (int i = 0; i < data_length; i++)
        {
            data.push_back(data_arg[i]);
        }
    }
};

void list_init()
{
    mvl.type_register(core_List_token, list_registration);
}

// new(size_t* length, mvl_obj** list_data, ...)
// Data is copied, so the caller retains ownership of data.
// Note that if *length is 0, then data is not even accessed.
mvl_obj* list_new(void* a, void* b, void* c, void* d)
{
    auto length = *static_cast<size_t*>(a);
    auto list_data = static_cast<mvl_obj**>(b);

    auto native_data = new List{ length, list_data };
    return mvl.object_create(core_List_token, native_data);
}

void list_free(mvl_obj* obj)
{
    auto data = static_cast<List*>(mvl.object_getDataPointer(obj));
    delete data;
}

// getNativeData(mvl_obj* string, size_t* length_out, mvl_obj*** list_data_out,...);
// Note that this gives a pointer to the list's native data; that means if the mvl_obj* is freed or if the list is modified, then the reference to the list data is no longer valid.
void list_getNativeData(mvl_obj* obj, void* a, void* b, void* c, void* d)
{
    List* dataPointer = static_cast<List*>(mvl.object_getDataPointer(obj));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->data.size();
    *a_length = length_val;

    auto b_list_data = static_cast<mvl_obj***>(b);
    auto list_val = dataPointer->data.data();
    *b_list_data = list_val;
}

size_t list_getReferences(mvl_obj* obj, mvl_obj*** references_out)
{
    List* dataPointer = static_cast<List*>(mvl.object_getDataPointer(obj));
    auto length = dataPointer->data.size();

    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
    {
        mvl.error("Memory allocation failed");
        return 0;
    }
    std::copy(std::begin(dataPointer->data), std::end(dataPointer->data), *references_out);

    return length;
}

mvl_type_register_callbacks list_registration = {
    list_new,
    list_free,
    list_getNativeData,
    list_getReferences
};