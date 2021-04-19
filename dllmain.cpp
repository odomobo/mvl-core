// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

std::atomic<mvl_library_api*> mvl_api_ptr;

static void register_types(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    none_register_type(inst);
    bool_register_type(inst);
    double_register_type(inst);
    string_register_type(inst);
    list_register_type(inst);
    nativeFunction_register_type(inst);
    MVL->stackframe_pop(inst);
}

static void register_nativeFunctions(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    none_register_nativeFunctions(inst);
    bool_register_nativeFunctions(inst);
    double_register_nativeFunctions(inst);
    string_register_nativeFunctions(inst);
    list_register_nativeFunctions(inst);
    nativeFunction_register_nativeFunctions(inst);
    MVL->stackframe_pop(inst);
}

static void set_globals(mvl_i* inst)
{
    MVL->STACKFRAME_PUSH(inst);
    throw std::exception("not implemented");
    MVL->stackframe_pop(inst);
}

void load(mvl_i* inst, mvl_library_api* mvl_api)
{
    MVL->STACKFRAME_PUSH(inst);
    mvl_api_ptr = mvl_api;

    tokens::init(inst);
    register_types(inst);
    register_nativeFunctions(inst);
    set_globals(inst);
    MVL->stackframe_pop(inst);
}