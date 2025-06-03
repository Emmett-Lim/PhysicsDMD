cmake_minimum_required(VERSION 3.14)
project(PhysicsDMD)

add_subdirectory(external/lib/pybind11)

pybind11_add_module(eigen_module src/eigen_module.cpp)

target_link_libraries(eigen_module PRIVATE pybind11::module)

target_include_directories(eigen_module
  PRIVATE ${CMAKE_SOURCE_DIR}/external/lib/eigen
  PUBLIC  ${CMAKE_SOURCE_DIR}/include
)

pybind11_add_module(pymodule_test module.cpp)

install(TARGETS eigen_module pymodule_test
    LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Linux/macOS
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/mylib        # Windows
)