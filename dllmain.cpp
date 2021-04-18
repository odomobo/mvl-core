// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

std::atomic<mvl_library_api*> mvl_api_ptr;

static void register_types(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    none_register(inst);
    bool_register(inst);
    double_register(inst);
    string_register(inst);
    list_register(inst);
    nativeFunction_register(inst);
    MVL->stackframe_pop(inst);
}

static void register_methods(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    throw std::exception("not yet implemented");
    MVL->stackframe_pop(inst);
}

static void set_globals(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    // nativeFunction_set_global_new_method();

    throw std::exception("not implemented");
    MVL->stackframe_pop(inst);
}

void load(mvl_i* inst, mvl_library_api* mvl_api)
{
    MVL->STACKFRAME_PUSH(inst);
    mvl_api_ptr = mvl_api;

    tokens::init(inst);
    register_types(inst);
    register_methods(inst);
    set_globals(inst);
    MVL->stackframe_pop(inst);
}

void error_memory(mvl_i* inst)
{
    MVL->error_memory(inst);
    throw std::exception{}; // should not be reached
}