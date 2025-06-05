#include "eigen_dmd.hpp"

/*
// ----------------
// regular C++ code
// ----------------
*/

/*
// [ TODO ]:
// 1.) Extract data into matrix X (current) and Y (future)
// 2.) Apply SVD
// 3.) Compute eigenvalues + eigenvectors --> extract eigenvalues
// 4.) Get DMD Modes
// 5.) Plotting
//
// [ Thoughts ]:
// - Where to keep data of matrices in (Python or C++)
// - Python for UI, C++ for Computational purposes
// - y_frames.npy   --> array size: (200, 50); y data
// - x_coord.txt    --> x data corresponding to each column from y data (potentially spatial position correlated to y frames?)
*/




/*
//  === TEST CLASS ===
*/
class MyTestClass {
    Eigen::MatrixXd matrix_A = Eigen::MatrixXd::Zero(3, 3);
public:
    Eigen::MatrixXd &getMatrix() { return matrix_A; }
    const Eigen::MatrixXd &viewMatrix() { return matrix_A; }

    void testMatrix() {
        matrix_A.row(0) << 1, 2, 3;
        matrix_A.row(1) << 4, 5, 6;
        matrix_A.row(2) << 7, 8, 9;
    }
};
/*
//  === TEST CLASS ===
*/


/*
// ----------------
// Python interface
// ----------------
*/

namespace py = pybind11;

PYBIND11_MODULE(eigen_dmd, handle) {
    handle.doc() = "Module used to calculate DMD via Eigen library.";

    /*
        === TEST CLASS ===
    */
    py::class_<MyTestClass>(handle, "MatrixTest")
        .def(py::init<>())
        .def("copy_matrix", &MyTestClass::getMatrix) // Makes a copy!
        .def("get_matrix", &MyTestClass::getMatrix, py::return_value_policy::reference_internal)
        .def("view_matrix", &MyTestClass::viewMatrix, py::return_value_policy::reference_internal)
        .def("test_matrix", &MyTestClass::testMatrix)
        ;
    /*
        === TEST CLASS ===
    */


}