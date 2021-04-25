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

static List* get_data(mvl_obj* self)
{
    return static_cast<List*>(mvl->object_getData(self).voidp_val);
}

static List* get_data(mvl_data self)
{
    return get_data(self.mvl_obj_val);
}

void CALL_CONVENTION list_free(mvl_obj* self)
{
    auto data = get_data(self);
    delete data;
}

mvl_reference_iterator list_getReferenceIterator(mvl_obj* self)
{
    return { size_val(0), self };
}

mvl_obj* list_getNextReference(mvl_reference_iterator* iter)
{
    auto data = get_data(iter->self);
    size_t index = iter->data.size_val;

    mvl_obj* ret = nullptr;
    if (index < data->data.size())
    {
        ret = data->data[index];
        mvl->internalReference_increment(ret);
        iter->data = size_val(index + 1);
    }
    return ret;
}

void list_freeReferenceIterator(mvl_reference_iterator* iter)
{
    // nothing to free
}

mvl_type_register_callbacks const list_registration = {
    list_free,
    list_getReferenceIterator,
    list_getNextReference,
    list_freeReferenceIterator,
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(mvl_obj_array_val list_data, size_val length,...)
// Data is copied, so the caller retains ownership of data.
// Note that if length is 0, then data is not even accessed.
mvl_data CALL_CONVENTION list_new_libraryFunction(mvl_data list_data, mvl_data length, mvl_data c, mvl_data d)
{
    List* native_data = retry_new<List>( list_data.mvl_obj_array_val, length.size_val );

    return mvl_obj_val(mvl->object_create(core_cache.token_core_List, voidp_val(native_data)));
}

// mvl_obj_array_val getVal(mvl_obj_val self, size_out length,...)
// Assumes self is core.List
// Borrows a reference to object array. Only valid until list is modified or freed.
mvl_data CALL_CONVENTION list_getVal_libraryFunction(mvl_data self, mvl_data length_out, mvl_data c, mvl_data d)
{
    List* native_data = get_data(self);
    size_t length = native_data->data.size();
    if (length_out.size_out != nullptr)
        *length_out.size_out = length;

    // don't increment internal reference for items; they haven't been accessed yet, and the
    // self object must have an internal reference set.

    return mvl_obj_array_val(native_data->data.data());
}

// mvl_obj_val get(mvl_obj_val self, size_val index,...)
// Assumes self is core.List
// Assumes that self is long enough that "index" is a valid index.
mvl_data CALL_CONVENTION list_get_libraryFunction(mvl_data self, mvl_data index, mvl_data c, mvl_data d)
{
    List* native_data = get_data(self);
    auto element = native_data->data[index.size_val];
    mvl->internalReference_increment(element);
    return mvl_obj_val(element);
}

// size_val length(mvl_obj_val self,...)
// Assumes self is core.List
mvl_data CALL_CONVENTION list_length_libraryFunction(mvl_data self, mvl_data index, mvl_data c, mvl_data d)
{
    List* native_data = get_data(self);
    return size_val(native_data->data.size());
}

//////////////////////
// Method Functions //
//////////////////////

static bool check_list(mvl_obj* obj, char const* name)
{
    bool is_list = mvl->typeof(obj) == core_cache.token_core_List;
    if (!is_list)
    {
        std::string message = std::string{ name } + " is not type core.List; instead it was " + std::string{ mvl->token_toString(mvl->typeof(obj)) };
        mvl->error(message.c_str());
    }

    return is_list;
}

mvl_obj* CALL_CONVENTION list_length(mvl_obj* args)
{
    auto self = extract_1_args(args);
    if (mvl->is_error())
        return nullptr;

    defer (mvl->internalReference_decrement(self));

    if (!check_list(self, "self"))
        return nullptr;

    size_t length = core_list_length(self);
    return core_double_new(static_cast<double>(length));
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