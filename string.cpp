#include "pch.h"

////////////////////
// Type Functions //
////////////////////

struct String
{
    enum class CopyMode
    {
        Copy = 0,
        Borrow = 1,
        Take = 2,
    };

    char* string;
    size_t length;
    CopyMode copy_mode;

    String(char* string_arg, size_t length_arg, int copy_mode_arg)
      : length{length_arg},
        copy_mode{static_cast<CopyMode>(copy_mode_arg)}
    {
        
        if (copy_mode == CopyMode::Copy)
        {
            string = static_cast<char*>(malloc(length + 1));
            if (string == nullptr)
                error_memory(); // terminates the application

            string[length] = 0;
            memcpy(string, string_arg, length);
        }
        else
        {
            string = string_arg;
        }
        
    }

    ~String()
    {
        if (copy_mode != CopyMode::Borrow)
        {
            free(string);
        }
    }
};

void CALL_CONVENTION string_free(mvl_obj* self)
{
    auto data = static_cast<String*>(mvl->object_getData(self).voidp_val);
    delete data;
}

mvl_type_register_callbacks const string_registration = {
    string_free,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(string_val string, size_val length, int_val copy_mode,...)
// 
// Copy modes are:
//   0: *Copy*
//   1: Borrow
//   2: Take
//
// If copy_mode is Copy, the a copy of the string is made and the caller retains ownership of string.
//
// If copy_bool is Borrow, then the mvl_obj* borrows a reference to the string, and will not free it.
// It's expected that this is a reference to a string literal.
//
// If copy_bool is Take, then the mvl_obj* takes ownership of string and will be responsible for it being freed.
// Such a string must have been allocated with malloc() or calloc(), because it will be freed with free().
mvl_data CALL_CONVENTION string_new_libraryFunction(mvl_data string, mvl_data length, mvl_data copy_mode, mvl_data d)
{
    String* data = nullptr;
    try {
        data = new String{ string.string_val, length.size_val, copy_mode.int_val };
    }
    catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    return mvl_obj_val(mvl->object_create(core_cache.token_core_String, voidp_val(data)));
}

// const_string_val getVal(mvl_obj_val self [, size_out length_out], ...)
// Assumes self is a core.String object.
// If length_out is null_out(), and it simply won't be assigned
mvl_data CALL_CONVENTION string_getVal_libraryFunction(mvl_data self, mvl_data length_out, mvl_data c, mvl_data d)
{
    auto data = static_cast<String*> (mvl->object_getData(self.mvl_obj_val).voidp_val);
    if (length_out.size_out != nullptr)
        *length_out.size_out = data->length;

    return const_string_val(data->string);
}

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void string_register_type()
{
    mvl->type_register(core_cache.token_core_String, string_registration);
}

void string_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_String_new, string_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_String_getVal, string_getVal_libraryFunction);
    // TODO
}

void string_register_nativeFunctions()
{
    // TODO
}