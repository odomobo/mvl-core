#include "pch.h"

void error_memory(mvl_i* inst)
{
    MVL->error_memory(inst);
    throw std::exception{}; // should not be reached
}

// assumes args is a core.List
void verify_0_args(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);

#ifdef _DEBUG
    if (MVL->object_getTypename_token(inst, args) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "Function parameter list was not a list!");
        return;
    }
#endif

    if (list_length_internal(inst, args) != 0)
    {
        MVL->error(inst, "Expected 0 parameters");
        return;
    }

    MVL->stackframe_pop(inst);
}

// assumes args is a core.List
void verify_1_args(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);

#ifdef _DEBUG
    if (MVL->object_getTypename_token(inst, args) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "Function parameter list was not a list!");
        return;
    }
#endif

    if (list_length_internal(inst, args) != 1)
    {
        MVL->error(inst, "Expected 1 parameter");
        return;
    }

    MVL->stackframe_pop(inst);
}

// assumes args is a core.List
mvl_obj* extract_1_args(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);

#ifdef _DEBUG
    if (MVL->object_getTypename_token(inst, args) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "Function parameter list was not a list!");
        return nullptr;
    }
#endif

    if (list_length_internal(inst, args) != 1)
    {
        MVL->error(inst, "Expected 1 parameter");
        return nullptr;
    }

    auto ret = list_get_internal(inst, args, 0);

    MVL->stackframe_pop(inst);
    return ret;
}

// assumes args is a core.List
std::array<mvl_obj*, 2> extract_2_args(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);

#ifdef _DEBUG
    if (MVL->object_getTypename_token(inst, args) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "Function parameter list was not a list!");
        return { nullptr, };
    }
#endif

    if (list_length_internal(inst, args) != 2)
    {
        MVL->error(inst, "Expected 2 parameters");
        return { nullptr, };
    }

    auto arg0 = list_get_internal(inst, args, 0);
    auto arg1 = list_get_internal(inst, args, 1);

    MVL->stackframe_pop(inst);
    return {arg0, arg1};
}

// assumes args is a core.List
std::array<mvl_obj*, 3> extract_3_args(mvl_i* inst, mvl_obj* args)
{
    MVL->STACKFRAME_PUSH(inst);

#ifdef _DEBUG
    if (MVL->object_getTypename_token(inst, args) != TOKENS[inst].core_List)
    {
        MVL->error(inst, "Function parameter list was not a list!");
        return { nullptr, };
    }
#endif

    if (list_length_internal(inst, args) != 3)
    {
        MVL->error(inst, "Expected 3 parameters");
        return { nullptr, };
    }

    auto arg0 = list_get_internal(inst, args, 0);
    auto arg1 = list_get_internal(inst, args, 1);
    auto arg2 = list_get_internal(inst, args, 2);

    MVL->stackframe_pop(inst);
    return { arg0, arg1, arg2 };
}