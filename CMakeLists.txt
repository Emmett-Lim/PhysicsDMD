cmake_minimum_required(VERSION 3.4...3.18)
project(pybind_setup)

add_subdirectory(external/lib/pybind11)

pybind11_add_module(module_add module.cpp)
install(TARGETS module_add
    LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Linux/macOS
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Windows
)