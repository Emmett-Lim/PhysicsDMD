#include <pybind11/pybind11.h>

namespace py = pybind11;

float add_fn(float arg1, float arg2) {
    return arg1 + arg2;
}

class SomeClass {
    float multiplier;

public:
    SomeClass(float multiplier_) : multiplier(multiplier_) {};
    float multiply(float input) {
        return multiplier * input;
    }

    void set_mult(float val) {
        multiplier = val;
    }

    float get_mult() {
      return multiplier;
    }
};

PYBIND11_MODULE(pymodule_test, handle) {
    handle.doc() = "This is a module doc thingy.";
    handle.def(
        "add_fn_python",
        &add_fn,
        "A function that adds two numbers",
        py::arg("arg1"),
        py::arg("arg2")
    );

    py::class_<SomeClass>(
        handle, "PySomeClass"
    )
    .def_property("multiplier", &SomeClass::get_mult, &SomeClass::set_mult)
    .def(py::init<float>())
    .def("multiply", &SomeClass::multiply);
}