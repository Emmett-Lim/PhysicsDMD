#include <pybind11/pybind11.h>

namespace py = pybind11;

float add_fn(float arg1, float arg2) {
    return arg1 + arg2;
}

PYBIND11_MODULE(module_add, handle) {
    handle.doc() = "This is a module doc thingy.";
    handle.def("add_fn_python", &add_fn);
}