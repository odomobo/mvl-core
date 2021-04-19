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

    String(mvl_i* inst, size_t length_arg, char* string_arg, int copy_mode_arg)
      : length{length_arg},
        copy_mode{static_cast<CopyMode>(copy_mode_arg)}
    {
        MVL->STACKFRAME_PUSH(inst);
        if (copy_mode == CopyMode::Copy)
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

    ~String()
    {
        if (copy_mode != CopyMode::Borrow)
        {
            free(string);
        }
    }
};

// self.new(char* string, [size_t* length], [int* copy_mode],...)
// 
// If *length is null, calls strlen(string) to determine length.
//
// Copy modes are:
//   0: *Copy*
//   1: Borrow
//   2: Take
//
//
// If *copy_mode is Copy, the a copy of the string is made and the caller retains ownership of string.
//
// If *copy_bool is Borrow, then the mvl_obj* borrows a reference to the string, and will not free it.
// It's expected that this is a reference to a string literal.
//
// If *copy_bool is Take, then the mvl_obj* takes ownership of string and will be responsible for it being freed.
// Such a string must have been allocated with malloc() or calloc(), because it will be freed with free().
//
// If *copy_mode is null, then it defaults to Copy.
void CALL_CONVENTION string_new(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    auto string = static_cast<char*>(a);
    auto length_ptr = static_cast<size_t*>(b);
    size_t length = length_ptr != nullptr ? *length_ptr : strlen(string);
    auto copy_mode_ptr = static_cast<int*>(c);
    // default to 0, which means Copy
    int copy_mode = copy_mode_ptr != nullptr ? *copy_mode_ptr : 0;

    String* data = nullptr;
    try {
        data = new String{ inst, length, string, static_cast<bool>(copy_mode) };
    } catch (std::bad_alloc&) {
        error_memory(inst); // terminates the application
    }

    MVL->object_setDataPointer(inst, self, data);
    MVL->stackframe_pop(inst);
}

mvl_obj* string_new_internal_copy(mvl_i* inst, std::string& str)
{
    MVL->STACKFRAME_PUSH(inst);
    auto length = str.size();
    auto c_str_const = str.c_str();
    auto c_str = const_cast<char*>(c_str_const); // I promise we won't touch your precious chars
    int copy_mode = 0; // copy
    auto ret = MVL->object_new(inst, TOKENS[inst].core_String, c_str, &length, &copy_mode, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* string_new_internal_copy(mvl_i* inst, char const* str_const)
{
    MVL->STACKFRAME_PUSH(inst);
    auto c_str = const_cast<char*>(str_const); // I promise we won't touch your precious chars
    auto ret = MVL->object_new(inst, TOKENS[inst].core_String, c_str, nullptr, nullptr, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* string_new_internal_borrow(mvl_i* inst, char const* str_const, size_t length)
{
    MVL->STACKFRAME_PUSH(inst);
    auto str = const_cast<char*>(str_const); // I promise we won't touch your precious chars
    int copy_mode = 1; // borrow
    auto ret = MVL->object_new(inst, TOKENS[inst].core_String, str, &length, &copy_mode, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

mvl_obj* string_new_internal_take(mvl_i* inst, char* str, size_t length)
{
    MVL->STACKFRAME_PUSH(inst);
    int copy_mode = 2; // take
    auto ret = MVL->object_new(inst, TOKENS[inst].core_String, str, &length, &copy_mode, nullptr);
    MVL->stackframe_pop(inst);
    return ret;
}

void CALL_CONVENTION string_free(mvl_i* inst, mvl_obj* self)
{
    MVL->STACKFRAME_PUSH(inst);
    auto data = static_cast<String*>(MVL->object_getDataPointer(inst, self));
    delete data;
    MVL->stackframe_pop(inst);
}

// self.getNativeData(char const** string_out, size_t* length_out, ...);
// Note that this gives a pointer to the string's native data; that means if the mvl_obj* is freed, then the reference to the string is no longer valid.
void CALL_CONVENTION string_getNativeData(mvl_i* inst, mvl_obj* self, void* a, void* b, void* c, void* d)
{
    MVL->STACKFRAME_PUSH(inst);
    String* dataPointer = static_cast<String*>(MVL->object_getDataPointer(inst, self));

    auto a_string = static_cast<char const**>(a);
    auto string_val = dataPointer->string;
    *a_string = string_val;

    auto b_length = static_cast<size_t*>(b);
    auto length_val = dataPointer->length;
    *b_length = length_val;
    MVL->stackframe_pop(inst);
}

mvl_type_register_callbacks const string_registration = {
    string_new,
    string_free,
    string_getNativeData,
    nullptr
};

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void string_register_type(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    MVL->type_register(inst, TOKENS[inst].core_String, string_registration);
    MVL->stackframe_pop(inst);
}

void string_register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // TODO
    MVL->stackframe_pop(inst);
}