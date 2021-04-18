#include "pch.h"

token core_None_token;
token core_Bool_token;
token core_Double_token;
token core_String_token;
token core_List_token;
token core_NativeFunction_token;

void init_tokens()
{
    core_None_token = mvl.token_get("core.None");
    core_Bool_token = mvl.token_get("core.Bool");
    core_Double_token = mvl.token_get("core.Double");
    core_String_token = mvl.token_get("core.String");
    core_List_token = mvl.token_get("core.List");
    core_NativeFunction_token = mvl.token_get("core.NativeFunction");
}
