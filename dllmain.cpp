// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

mvl_library_api* mvl;
CoreCache core_cache;

static void register_types()
{
    none_register_type();
    bool_register_type();
    double_register_type();
    string_register_type();
    list_register_type();
    nativeFunction_register_type();
}

static void register_libraryFunctions()
{
    none_register_libraryFunctions();
    bool_register_libraryFunctions();
    double_register_libraryFunctions();
    string_register_libraryFunctions();
    list_register_libraryFunctions();
    libraryFunction_register_libraryFunctions();
}

static void register_nativeFunctions()
{
    none_register_nativeFunctions();
    bool_register_nativeFunctions();
    double_register_nativeFunctions();
    string_register_nativeFunctions();
    list_register_nativeFunctions();
    nativeFunction_register_nativeFunctions();
}

static void set_globals()
{
    throw std::exception("not implemented");
}

void load(mvl_library_api* mvl_api)
{
    mvl = mvl_api;
    core_init_tokens(mvl_api);

    register_types();

    register_libraryFunctions();
    // must be called after registering library functions, but should be called as soon as possible
    core_init_libraryFunctions(mvl_api);

    register_nativeFunctions();
    set_globals();
}