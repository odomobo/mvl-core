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
    
    auto data = static_cast<String*>(mvl->object_getDataPointer(self));
    delete data;
    
}

// self.getNativeData(char const** string_out, size_t* length_out, ...);
// Note that this gives a pointer to the string's native data; that means if the mvl_obj* is freed, then the reference to the string is no longer valid.
void CALL_CONVENTION string_getNativeData(mvl_obj* self, void* a, void* b, void* c, void* d)
{
    
    String* dataPointer = static_cast<String*>(mvl->object_getDataPointer(self));

    auto a_string = static_cast<char const**>(a);
    auto string_val = dataPointer->string;
    *a_string = string_val;

    auto b_length = static_cast<size_t*>(b);
    auto length_val = dataPointer->length;
    *b_length = length_val;
    
}

mvl_type_register_callbacks const string_registration = {
    string_free,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(string_in string, size_in length, int_in copy_mode,...)
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
        data = new String{ string.string_in, length.size_in, copy_mode.int_in };
    }
    catch (std::bad_alloc&) {
        error_memory(); // terminates the application
    }

    return mvl_obj_val(mvl->object_create(core_cache.token_core_String, voidp_val(data)));
}

// TODO: move the below to core.h

// assumes mvl_obj is a string
char const* string_get_internal_borrow(mvl_obj* string, size_t* length_out)
{

    auto data = static_cast<String*> (mvl->object_getDataPointer(string));
    if (length_out != nullptr)
        *length_out = data->length;

    return data->string;
}



// assumes mvl_obj is a string
std::string string_get_internal_copy(mvl_obj* string)
{
    
    auto data = static_cast<String*> (mvl->object_getDataPointer(string));
    auto ret = std::string{ data->string, data->length };
    
    return ret;
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

void string_register_nativeFunctions()
{
    
    // TODO
    
}