#include "pch.h"

std::mutex tokens_mutex;
std::atomic<std::map<mvl_i*, TokensStruct>*> tokens = nullptr;

// What the heck is going on here? The first thing to note is that different MVL
// instances can have different token values for a given token string. So, tokens
// need to be indexed by instance. Next, tokens_init can be called via two different
// threads, with two different instances, at the same time. Or it can be called by one
// thread while another thread is accessing the "tokens" object to get tokens.
// We don't want to cause race conditions. So, in a mutex locked section, we
// first make a copy of the existing "tokens" map, then we make all the changes
// to that copy (adding another key for the new set of tokens), and finally we
// atomically copy the new pointer over the old one.
//
// You might be wondering, does this leak the old "tokens" map? Yes it does, but
// with this approach, there's no way around it. Some other thread (for some other
// mvl instance) could have a reference to the old "tokens" map object, for an
// indefinite amount of time. We have know way of knowing, so we can't delete it.
// It's not really a concern, because the normal expectation is that this will only
// be called a handful of times at most, over the application's lifetime.
//
// Still, it could be worth trying a different approach. One simple way is instead
// of using raw pointers, we could use shared_pointers. However, this seems like
// a lot of overhead to prevent a tiny memory leak.
void tokens_init(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // We don't need to do any of this if the instance has already been registered.
    if (TOKENS.count(inst) == 0)
    {
        std::lock_guard<std::mutex> lock_guard{ tokens_mutex };
        std::map<mvl_i*, TokensStruct>* tokens_copy = nullptr;
        try {
            tokens_copy = new std::map<mvl_i*, TokensStruct>{ *tokens.load() };
        } catch (std::bad_alloc&) {
            error_memory(inst); // terminates the application
        }

        TokensStruct tokens_struct{};

        tokens_struct.core_None = MVL->token_get(inst, "core.None");
        tokens_struct.core_None_str = MVL->token_get(inst, "core.None$str");
        tokens_struct.core_None_equals = MVL->token_get(inst, "core.None$equals");
        tokens_struct.core_None_hash = MVL->token_get(inst, "core.None$hash");

        tokens_struct.core_Bool = MVL->token_get(inst, "core.Bool");
        tokens_struct.core_Bool_str = MVL->token_get(inst, "core.Bool$str");
        tokens_struct.core_Bool_equals = MVL->token_get(inst, "core.Bool$equals");
        tokens_struct.core_Bool_hash = MVL->token_get(inst, "core.Bool$hash");
        tokens_struct.core_Bool_and = MVL->token_get(inst, "core.Bool.and");
        tokens_struct.core_Bool_or = MVL->token_get(inst, "core.Bool.or");
        tokens_struct.core_Bool_not = MVL->token_get(inst, "core.Bool.not");

        tokens_struct.core_Double = MVL->token_get(inst, "core.Double");
        tokens_struct.core_String = MVL->token_get(inst, "core.String");
        tokens_struct.core_List = MVL->token_get(inst, "core.List");
        tokens_struct.core_NativeFunction = MVL->token_get(inst, "core.NativeFunction");

        (*tokens_copy)[inst] = tokens_struct;
        tokens.store(tokens_copy);
    }
    MVL->stackframe_pop(inst);
}