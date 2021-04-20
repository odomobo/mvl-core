#include "pch.h"

////////////////////
// Type Functions //
////////////////////

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

// self.new(mvl_obj** list_data, size_t* length, ...)
// Data is copied, so the caller retains ownership of data.
// Note that if *length is 0, then data is not even accessed.
void CALL_CONVENTION list_new(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    auto list_data = static_cast<mvl_obj**>(a);
    auto length = *static_cast<size_t*>(b);
    
    List* native_data = nullptr;
    try {
        native_data = new List{ length, list_data };
    } catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    mvl->object_setDataPointer(self, native_data);
}

// TODO: not yet registered, etc
// mvl_obj_val list_new(mvl_obj_array_in list_data, size_in length,...)
mvl_data CALL_CONVENTION list_new_libraryFunction(mvl_data list_data, mvl_data length, mvl_data c, mvl_data d)
{
    List* native_data = nullptr;
    try {
        native_data = new List{ length.size_in, list_data.mvl_obj_array_in };
    }
    catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    mvl_obj* ret = mvl->object_create(core_cache.token_core_List, voidp_val(static_cast<void*>(native_data)));
    return mvl_obj_val(ret);
}

// TODO: add another list_new_internal that takes a std::span<mvl_obj*>... need to upgrade vs to get c++20 support first.
mvl_obj* list_new_internal(std::vector<mvl_obj*> elements)
{
    auto list_data = elements.data();
    auto length = elements.size();
    return mvl->object_new(core_cache.token_core_List, list_data, &length, nullptr, nullptr);
}

// TODO: add another core_list_new that takes a std::span<mvl_obj*>... need to upgrade vs to get c++20 support first.
mvl_obj* core_list_new(std::vector<mvl_obj*> elements)
{
    auto list_data = elements.data();
    auto length = elements.size();
    mvl_libraryFunction_t core_libraryFunction_list_new = list_new_libraryFunction; // TODO: get from library function cache
    return core_libraryFunction_list_new(mvl_obj_array_in(list_data), size_in(length), unused(), unused()).mvl_obj_val;
}

void CALL_CONVENTION list_free(mvl_obj* self)
{
    auto data = static_cast<List*>(mvl->object_getDataPointer(self));
    delete data;
}

// self.getNativeData(size_t* length_out, mvl_obj*** list_data_out,...);
// Note that this gives a pointer to the list's native data; that means if the mvl_obj* is freed or if the list is modified, then the reference to the list data is no longer valid.
void CALL_CONVENTION list_getNativeData(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    List* dataPointer = static_cast<List*>(mvl->object_getDataPointer(self));
    auto a_length = static_cast<size_t*>(a);
    auto length_val = dataPointer->data.size();
    *a_length = length_val;

    auto b_list_data = static_cast<mvl_obj***>(b);
    auto list_val = dataPointer->data.data();
    *b_list_data = list_val;
}

size_t CALL_CONVENTION list_getReferences(mvl_obj* self, mvl_obj*** references_out)
{
    List* dataPointer = static_cast<List*>(mvl->object_getDataPointer(self));

    auto length = dataPointer->data.size();
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
        error_memory();
    
    std::copy(std::begin(dataPointer->data), std::end(dataPointer->data), *references_out);
   
    return length;
}

mvl_type_register_callbacks const list_registration = {
    list_new,
    list_free,
    list_getNativeData,
    list_getReferences
};

////////////////////////
// Internal Functions //
////////////////////////

// Assumes that list is actually a list object, and is long enough that "index" is a valid index
mvl_obj* list_get_internal(mvl_obj* list, int index)
{
    List* dataPointer = static_cast<List*>(mvl->object_getDataPointer(list));
    return dataPointer->data[index];
}

// Assumes that list is actually a list object
size_t list_length_internal(mvl_obj* list)
{
    List* dataPointer = static_cast<List*>(mvl->object_getDataPointer(list));
    return dataPointer->data.size();
}

//////////////////////
// Method Functions //
//////////////////////

mvl_obj* CALL_CONVENTION list_length(mvl_obj* args)
{
    auto list = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (mvl->object_getTypename_token(list) != core_cache.token_core_List)
    {
        mvl->error("args[0] is not a core.List");
        return nullptr;
    }
    
    double length = static_cast<double>(list_length_internal(list));
    return double_new_internal(length);
}

////////////////////////////
//      Registration      //
////////////////////////////

void list_register_type()
{
    mvl->type_register(core_cache.token_core_List, list_registration);
}

void list_register_nativeFunctions()
{
    
    // TODO
    
}