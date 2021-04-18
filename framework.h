#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
    // Windows Header Files
    #include <windows.h>
#else

#endif

#include <vector>
#include <atomic>

extern std::atomic<mvl_library_api*> mvl_api_ptr;
#define MVL mvl_api_ptr.load()

#define STACKFRAME_PUSH(inst) stackframe_push(inst, __func__, __FILE__, __LINE__)

void load(mvl_i* inst, mvl_library_api* mvl_api);
void error_memory(mvl_i* inst);
