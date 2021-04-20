#include "pch.h"

////////////////////
// Type Functions //
////////////////////

mvl_type_register_callbacks const double_registration = {
    nullptr,
    nullptr
};

///////////////////////
// Library Functions //
///////////////////////

// mvl_obj_val new(double_val data_double, ...)
mvl_data CALL_CONVENTION double_new_libraryFunction(mvl_data data_double, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl_obj_val(mvl->object_create(core_cache.token_core_Double, bool_val(data_double.double_val)));
}

// double_val new(mvl_obj_val self, ...)
// assumes self is actually of type core.Double
mvl_data CALL_CONVENTION double_getVal_libraryFunction(mvl_data self, mvl_data b, mvl_data c, mvl_data d)
{
    return mvl->object_getData(self.mvl_obj_val);
}

//////////////////////
// Method Functions //
//////////////////////



////////////////////////////
//      Registration      //
////////////////////////////

void double_register_type()
{
    mvl->type_register(core_cache.token_core_Double, double_registration);
}

void double_register_libraryFunctions()
{
    mvl->libraryFunction_register(core_cache.token_core_Double_new, double_new_libraryFunction);
    mvl->libraryFunction_register(core_cache.token_core_Double_getVal , double_getVal_libraryFunction);
    // TODO
}

void double_register_nativeFunctions()
{
    // TODO
}