#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
    // Windows Header Files
    #include <windows.h>
#else

#endif

#include <vector>
#include <atomic>
#include <array>
#include <exception>
#include <string>
#include <cstring>

extern std::atomic<mvl_library_api*> mvl_api_ptr;

void load(mvl_i* inst, mvl_library_api* mvl_api);
