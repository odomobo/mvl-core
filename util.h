#pragma once
#include <functional>
#include "mvl_library.h"

void verify_0_args(mvl_obj* args);
void verify_1_args(mvl_obj* args);
mvl_obj* extract_1_args(mvl_obj* args);
std::array<mvl_obj*, 2> extract_2_args(mvl_obj* args);
std::array<mvl_obj*, 3> extract_3_args(mvl_obj* args);

// The first attempt after a failed malloc should be to run GC and retry.
// After that, terminate the application with mvl_error_memory().
template <typename T>
T retry_malloc(size_t size)
{
    void* temp = malloc(size);

    if (temp != nullptr)
    {
        return static_cast<T>(temp);
    }
    
    mvl->gc_run();
    temp = malloc(size);
    
    if (temp != nullptr)
    {
        return static_cast<T>(temp);
    }
    
    mvl->error_memory(); // terminates the application
    throw std::bad_alloc{}; // can't reach here
}

// The first attempt after a failed new should be to run GC and retry.
// After that, terminate the application with mvl_error_memory().
template <typename T, typename ... TArgs>
T* retry_new(TArgs& ... args)
{
    try
    {
        return new T{ args... };
    }
    catch (std::bad_alloc&)
    {
        mvl->gc_run();
    }

    try
    {
        return new T{ args... };
    }
    catch (std::bad_alloc&)
    {
        mvl->error_memory(); // terminates the application
        throw std::bad_alloc{}; // can't reach here
    }
}

// The first attempt after a failed container update should be to run GC and retry.
// After that, terminate the application with mvl_error_memory().
inline void retry_update(std::function<void()> fn)
{
    try
    {
        fn();
    }
    catch (std::bad_alloc&)
    {
        mvl->gc_run();
    }

    try
    {
        fn();
    }
    catch (std::bad_alloc&)
    {
        mvl->error_memory(); // terminates the application
        throw std::bad_alloc{}; // can't reach here
    }
}