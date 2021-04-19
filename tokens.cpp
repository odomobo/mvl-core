#include "pch.h"

namespace tokens
{
    token core_None;
    token core_None_str;
    token core_None_equals;
    token core_None_hash;

    token core_Bool;
    token core_Double;
    token core_String;
    token core_List;
    token core_NativeFunction;

    void init(mvl_i* inst)
    {
        MVL->STACKFRAME_PUSH(inst);

        core_None = MVL->token_get(inst, "core.None");
        core_None_str = MVL->token_get(inst, "core.None$str");
        core_None_equals = MVL->token_get(inst, "core.None$equals");
        core_None_hash = MVL->token_get(inst, "core.None$hash");

        core_Bool = MVL->token_get(inst, "core.Bool");
        core_Double = MVL->token_get(inst, "core.Double");
        core_String = MVL->token_get(inst, "core.String");
        core_List = MVL->token_get(inst, "core.List");
        core_NativeFunction = MVL->token_get(inst, "core.NativeFunction");
        MVL->stackframe_pop(inst);
    }
}