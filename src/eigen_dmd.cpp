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



void EigenDMD::separateSnapshots(const Eigen::MatrixXcd& complex_matrix) {
    /* [ === NOT UNIT TESTED == ]
    // Copy values from complex_matrix and split into two snapshots
    // _x_current   containing data from [1, (n-1)]
    // _x_next      containing data from [2, n]
    */

    int column_size = static_cast<int>(complex_matrix.cols() - 1);
    int row_size    = static_cast<int>(complex_matrix.rows());

    _x_current  = complex_matrix.block(0, 0, row_size, column_size);
    _x_next     = complex_matrix.block(0, 1, row_size, column_size);
}

void EigenDMD::standardDMD(const Eigen::MatrixXcd& complex_matrix) {
    if (static_cast<int>(complex_matrix.size()) <= 1) {
        std::cout << "Cannot compute DMD on empty matrix!\n";
        return;
    }

    // Separate the complex matrix into current and next/future snapshots
    separateSnapshots(complex_matrix);

    // Calculate Reduced SVD of _x_current (not sure about rank...)
    // NOTE: For SVD, might need to use Eigen::BDCSVD since dealing w/ large dataset.
    

}



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
    //  === TEST CLASS ===
    */
    py::class_<MyTestClass>(handle, "MatrixTest")
        .def(py::init<>())
        .def("copy_matrix", &MyTestClass::getMatrix) // Makes a copy!
        .def("get_matrix", &MyTestClass::getMatrix, py::return_value_policy::reference_internal)
        .def("view_matrix", &MyTestClass::viewMatrix, py::return_value_policy::reference_internal)
        .def("test_matrix", &MyTestClass::testMatrix)
        ;
    /*
    //  === TEST CLASS ===
    */


}