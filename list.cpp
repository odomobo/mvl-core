#include "pch.h"

struct List
{
    std::vector<mvl_obj*> data;

    List(mvl_i* inst, size_t data_length, mvl_obj** data_arg) : data{data_length}
    {
        MVL->STACKFRAME_PUSH(inst);
        for (int i = 0; i < data_length; i++)
        {
            data.push_back(data_arg[i]);
        }
        MVL->stackframe_pop(inst);
    }
};

void list_register(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, tokens::core_List, list_registration);
    MVL->stackframe_pop(inst);
}

// self.new(size_t* length, mvl_obj** list_data, ...)
// Data is copied, so the caller retains ownership of data.
// Note that if *length is 0, then data is not even accessed.
void list_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto length = *static_cast<size_t*>(a);
    auto list_data = static_cast<mvl_obj**>(b);

    List* native_data = nullptr;
    try {
        native_data = new List{ inst, length, list_data };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, native_data);
    MVL->stackframe_pop(inst);
}

void list_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<List*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(size_t* length_out, mvl_obj*** list_data_out,...);
// Note that this gives a pointer to the list's native data; that means if the mvl_obj* is freed or if the list is modified, then the reference to the list data is no longer valid.
void list_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    List* dataPointer = static_cast<List*>(MVL->object_getDataPointer(inst, self));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->data.size();
    *a_length = length_val;

    auto b_list_data = static_cast<mvl_obj***>(b);
    auto list_val = dataPointer->data.data();
    *b_list_data = list_val;
    MVL->stackframe_pop(inst);
}

size_t list_getReferences(mvl_i* inst, mvl_obj* self, mvl_obj*** references_out)
{
    MVL->STACKFRAME_PUSH(inst);
    List* dataPointer = static_cast<List*>(MVL->object_getDataPointer(inst, self));

    auto length = dataPointer->data.size();
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
        error_memory(inst);
    
    std::copy(std::begin(dataPointer->data), std::end(dataPointer->data), *references_out);

    MVL->stackframe_pop(inst);
    return length;
}

mvl_type_register_callbacks const list_registration = {
    list_new,
    list_free,
    list_getNativeData,
    list_getReferences
};