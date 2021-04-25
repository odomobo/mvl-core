#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
    // Windows Header Files
    #include <windows.h>
#else

#endif

#include <vector>
#include <array>
#include <exception>
#include <string>
#include <cstring>
#include <map>
#include <functional>
#include <cmath>

extern mvl_library_api* mvl;

void load(mvl_library_api* mvl_api);
