#include "pch.h"

////////////////////
// Type Functions //
////////////////////

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

// self.new(mvl_obj** list_data, size_t* length, ...)
// Data is copied, so the caller retains ownership of data.
// Note that if *length is 0, then data is not even accessed.
void CALL_CONVENTION list_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto list_data = static_cast<mvl_obj**>(a);
    auto length = *static_cast<size_t*>(b);
    
    List* native_data = nullptr;
    try {
        native_data = new List{ inst, length, list_data };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, native_data);
    MVL->stackframe_pop(inst);
}

// TODO: add another list_new_internal that takes a std::span<mvl_obj*>... need to upgrade vs to get c++20 support first.
mvl_obj* list_new_internal(mvl_i* inst, std::vector<mvl_obj*> elements)
{
    MVL->STACKFRAME_PUSH(inst);
    auto list_data = elements.data();
    auto length = elements.size();
    auto ret = MVL->object_new(inst, TOKENS[inst].core_List, list_data, &length, nullptr, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

void CALL_CONVENTION list_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<List*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(size_t* length_out, mvl_obj*** list_data_out,...);
// Note that this gives a pointer to the list's native data; that means if the mvl_obj* is freed or if the list is modified, then the reference to the list data is no longer valid.
void CALL_CONVENTION list_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
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

size_t CALL_CONVENTION list_getReferences(mvl_i* inst, mvl_obj* self, mvl_obj*** references_out)
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

//////////////////////
// Method Functions //
//////////////////////

// Assumes that list is actually a list object, and is long enough that "index" is a valid index
mvl_obj* list_get_internal(mvl_i* inst, mvl_obj* list, int index)
{
    MVL->STACKFRAME_PUSH(inst);
    List* dataPointer = static_cast<List*>(MVL->object_getDataPointer(inst, list));
    auto ret = dataPointer->data[index];
    MVL->stackframe_pop(inst);
    return ret;
}

// Assumes that list is actually a list object
size_t list_length_internal(mvl_i* inst, mvl_obj* list)
{
    MVL->STACKFRAME_PUSH(inst);
    List* dataPointer = static_cast<List*>(MVL->object_getDataPointer(inst, list));
    auto length = dataPointer->data.size();
    MVL->stackframe_pop(inst);
    return length;
}

mvl_obj* CALL_CONVENTION list_length(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);
    auto list = extract_1_args(inst, args);
    if (MVL->is_error(inst))
        return nullptr;

    if (MVL->object_getTypename_token(inst, list) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "args[0] is not a core.List");
        return nullptr;
    }
    
    double length = list_length_internal(inst, list);
    auto ret = double_new_internal(inst, length);

    MVL->stackframe_pop(inst);
    return ret;
}

////////////////////////////
//      Registration      //
////////////////////////////

void list_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, TOKENS[inst].core_List, list_registration);
    MVL->stackframe_pop(inst);
}

void list_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // TODO
    MVL->stackframe_pop(inst);
}