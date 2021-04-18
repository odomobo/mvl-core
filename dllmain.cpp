// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

mvl_library_api mvl;

static void register_and_init()
{
    none_init();
    bool_init();
    double_init();
    string_init();
    list_init();
    nativeFunction_init();
}

static void set_globals()
{
    throw std::exception("not implemented");
}

void load(mvl_library_api* mvl_api)
{
    mvl = *mvl_api;

    register_and_init();
    set_globals();
}

int get_references(mvl_obj*** references_out)
{
    size_t const length = 3;
    *references_out = static_cast<mvl_obj**>(calloc(length, sizeof(mvl_obj*)));
    if (*references_out == nullptr)
    {
        mvl.error_memory(); // terminates the application
        return 0;
    }

    *references_out[0] = none_obj;
    *references_out[1] = true_obj;
    *references_out[2] = false_obj;

    return length;
}