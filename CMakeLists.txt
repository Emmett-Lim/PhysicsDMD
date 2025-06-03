cmake_minimum_required(VERSION 3.4...3.18)
project(PhysicsDMD)

add_subdirectory(external/lib/pybind11)

pybind11_add_module(pymodule_test module.cpp)
install(TARGETS pymodule_test
    LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Linux/macOS
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Windows
)