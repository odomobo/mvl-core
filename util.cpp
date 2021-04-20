#include "pch.h"

void error_memory()
{
    mvl->error_memory();
    throw std::exception{}; // should not be reached
}

// assumes args is a core.List
void verify_0_args(mvl_obj* args)
{
    

#ifdef _DEBUG
    if (mvl->object_getTypename_token(args) != core_cache.token_core_List)
    {
        mvl->error("Function parameter list was not a list!");
        return;
    }
#endif

    if (list_length_internal(args) != 0)
    {
        mvl->error("Expected 0 parameters");
        return;
    }

    
}

// assumes args is a core.List
void verify_1_args(mvl_obj* args)
{
    

#ifdef _DEBUG
    if (mvl->object_getTypename_token(args) != core_cache.token_core_List)
    {
        mvl->error("Function parameter list was not a list!");
        return;
    }
#endif

    if (list_length_internal(args) != 1)
    {
        mvl->error("Expected 1 parameter");
        return;
    }

    
}

// assumes args is a core.List
mvl_obj* extract_1_args(mvl_obj* args)
{
    

#ifdef _DEBUG
    if (mvl->object_getTypename_token(args) != core_cache.token_core_List)
    {
        mvl->error("Function parameter list was not a list!");
        return nullptr;
    }
#endif

    if (list_length_internal(args) != 1)
    {
        mvl->error("Expected 1 parameter");
        return nullptr;
    }

    auto ret = list_get_internal(args, 0);

    
    return ret;
}

// assumes args is a core.List
std::array<mvl_obj*, 2> extract_2_args(mvl_obj* args)
{
    

#ifdef _DEBUG
    if (mvl->object_getTypename_token(args) != core_cache.token_core_List)
    {
        mvl->error("Function parameter list was not a list!");
        return { nullptr, };
    }
#endif

    if (list_length_internal(args) != 2)
    {
        mvl->error("Expected 2 parameters");
        return { nullptr, };
    }

    auto arg0 = list_get_internal(args, 0);
    auto arg1 = list_get_internal(args, 1);

    
    return {arg0, arg1};
}

// assumes args is a core.List
std::array<mvl_obj*, 3> extract_3_args(mvl_obj* args)
{
    

#ifdef _DEBUG
    if (mvl->object_getTypename_token(args) != core_cache.token_core_List)
    {
        mvl->error("Function parameter list was not a list!");
        return { nullptr, };
    }
#endif

    if (list_length_internal(args) != 3)
    {
        mvl->error("Expected 3 parameters");
        return { nullptr, };
    }

    auto arg0 = list_get_internal(args, 0);
    auto arg1 = list_get_internal(args, 1);
    auto arg2 = list_get_internal(args, 2);

    
    return { arg0, arg1, arg2 };
}