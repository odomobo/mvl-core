#pragma once
#include "mvl_library.h"
#include <atomic>
#include <map>
#include <mutex>

struct TokensStruct
{
    token core_None;
    token core_None_str;
    token core_None_equals;
    token core_None_hash;

    token core_Bool;
    token core_Double;
    token core_String;
    token core_List;
    token core_NativeFunction;
};

extern std::atomic<std::map<mvl_i*, TokensStruct>*> tokens;
#define TOKENS (*tokens.load())

void tokens_init(mvl_i* inst);