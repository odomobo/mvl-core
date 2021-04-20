#include "pch.h"

////////////////////
// Type Functions //
////////////////////

struct List
{
    std::vector<mvl_obj*> data;

    List(mvl_obj** data_arg, size_t data_length) : data{data_length}
    {
        for (size_t i = 0; i < data_length; i++)
        {
            data.push_back(data_arg[i]);
        }
    }
};

void CALL_CONVENTION list_free(mvl_obj* self)
{
    auto data = static_cast<List*>(mvl->object_getData(self).voidp_val);
    delete data;
}

mvl_references_list CALL_CONVENTION list_getReferences(mvl_obj* self)
{
    List* dataPointer = static_cast<List*>(mvl->object_getData(self).voidp_val);

    size_t length = dataPointer->data.size();
    mvl_obj** references = nullptr;

    if (length != 0)
    {
        references = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
        if (references == nullptr)
            error_memory();
    
        std::copy(std::begin(dataPointer->data), std::end(dataPointer->data), references);
    }

    return {references, length};
}

mvl_type_register_callbacks const list_registration = {
    list_free,
    list_getReferences
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(mvl_obj_array_val list_data, size_val length,...)
// Data is copied, so the caller retains ownership of data.
// Note that if length is 0, then data is not even accessed.
mvl_data CALL_CONVENTION list_new_libraryFunction(mvl_data list_data, mvl_data length, mvl_data c, mvl_data d)
{
    List* native_data = nullptr;
    try {
        native_data = new List{ list_data.mvl_obj_array_val, length.size_val };
    }
    catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    return mvl_obj_val(mvl->object_create(core_cache.token_core_List, voidp_val(native_data)));
}

// mvl_obj_array_val getVal(mvl_obj_val self, size_out length,...)
// Assumes self is core.List
// Borrows a reference to object array. Only valid until list is modified or freed.
mvl_data CALL_CONVENTION list_getVal_libraryFunction(mvl_data self, mvl_data length_out, mvl_data c, mvl_data d)
{
    List* native_data = static_cast<List*>(mvl->object_getData(self.mvl_obj_val).voidp_val);
    if (length_out.size_out != nullptr)
        *length_out.size_out = native_data->data.size();

    return mvl_obj_array_val(native_data->data.data());
}

// mvl_obj_val getVal(mvl_obj_val self, size_val index,...)
// Assumes self is core.List
// Assumes that self is long enough that "index" is a valid index.
mvl_data CALL_CONVENTION list_get_libraryFunction(mvl_data self, mvl_data index, mvl_data c, mvl_data d)
{
    List* native_data = static_cast<List*>(mvl->object_getData(self.mvl_obj_val).voidp_val);
    return mvl_obj_val(native_data->data[index.size_val]);
}

// size_val length(mvl_obj_val self,...)
// Assumes self is core.List
mvl_data CALL_CONVENTION list_length_libraryFunction(mvl_data self, mvl_data index, mvl_data c, mvl_data d)
{
    List* native_data = static_cast<List*>(mvl->object_getData(self.mvl_obj_val).voidp_val);
    return size_val(native_data->data.size());
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_list_self(mvl_obj* obj)
{
    bool is_list = mvl->typeof(obj) == core_cache.token_core_List;
    if (!is_list)
        mvl->error("self is not type core.List");

    return is_list;
}

mvl_obj* CALL_CONVENTION list_length(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    if (!check_list_self(self))
        return nullptr;

    size_t length = core_list_length(self);
    return core_double_new(length);
}

////////////////////////////
//      Registration      //
////////////////////////////

void list_register_type()
{
    mvl->type_register(core_cache.token_core_List, list_registration);
}

void list_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_List_new, list_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_List_getVal, list_getVal_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_List_get, list_get_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_List_length, list_length_libraryFunction);
    // TODO
}

void list_register_nativeFunctions()
{
    mvl->nativeFunction_register(core_cache.token_core_List_mLength, list_length);
    // TODO
}