#include "eigen_dmd.hpp"

/*
// ----------------
// regular C++ code
// ----------------
*/


/*
// [ TODO ]:
// 1.) Extract data into matrix X (current) and Y (future) [ DONE ]
// 2.) Apply SVD [ DONE ]
// 3.) Compute eigenvalues + eigenvectors --> extract eigenvalues [ DONE ]
// 4.) Get DMD Modes [ DONE ]
// 5.) Plotting
//
// [ Thoughts ]:
// - Where to keep data of matrices in (Python or C++)
// - Python for UI, C++ for Computational purposes
// - Change standardDMD algo to return int type to catch errors?
*/



void EigenDMD::separateSnapshots(const Eigen::MatrixXcd& complex_matrix) {
    /* [ === NOT UNIT TESTED == ]
    // Copy values from complex_matrix [n, p] and split into two snapshots
    // _x_current   containing data from [n, (p-1)]
    // _x_next      containing data from [(n+1), p]
    */

    int column_size = static_cast<int>(complex_matrix.cols() - 1);
    int row_size    = static_cast<int>(complex_matrix.rows());

    _x_current  = complex_matrix.block(0, 0, row_size, column_size);
    _x_next     = complex_matrix.block(0, 1, row_size, column_size);

}

void EigenDMD::standardDMD(const Eigen::MatrixXcd& complex_matrix, int reduced_rank) {

    if (static_cast<int>(complex_matrix.cols()) <= 1) {
        std::cout << "Cannot compute DMD on small or empty complex data!\n";
        return;
    }

    // Separate the complex matrix into current and next/future snapshots
    std::cout << "Creating separate snapshots.\n";
    separateSnapshots(complex_matrix);

    // Calculate Reduced/Full SVD of _x_current
    // NOTE: For SVD, might need to use Eigen::BDCSVD since dealing w/ large dataset, else use Jacobian
    // WARNING: Check the complier CMake is using - see Eigen documentation regarding BDCSVD
    // === [ Note: might need to set a reduced rank first, then use ComputeFull ] ===

    std::cout << "Calculating SVD for current snapshot.\n";
    Eigen::BDCSVD<Eigen::MatrixXcd> svd(_x_current, Eigen::ComputeThinU | Eigen::ComputeThinV); // Unknown as to whether if need Full or Thin
    
    // SVD Original Components (svd = USV*): 
    _svd._u_matrix = svd.matrixU();
    _svd._s_values = svd.singularValues();   // Note: Returned as a vector, not a matrix. Use .asDiagonal() to convert into matrix form
    _svd._v_matrix = svd.matrixV();          // Note: This is not given in its adjoint version (V*)

    // Apply rank-reduction if reduced_rank > -1
    if (reduced_rank >= 0) {
        std::cout << "Applying rank-reduction to results of SVD.\n";
        int max_rank = std::min(
            {
                reduced_rank,
                static_cast<int>(_svd._u_matrix.cols()),
                static_cast<int>(_svd._s_values.size()),
                static_cast<int>(_svd._v_matrix.cols())
            }
        );

        _svd._u_matrix = _svd._u_matrix.leftCols(max_rank);
        _svd._s_values = _svd._s_values.head(max_rank);
        _svd._v_matrix = _svd._v_matrix.leftCols(max_rank);
    }

    // Calculate inverse of the singular values
    std::cout << "Inverting singular values.\n";
    Eigen::VectorXd s_values_inv(_svd._s_values.size());

    // Add tolerance to avoid instability when inverting singular values (needs more research)
    double epsilon   = std::numeric_limits<double>::epsilon();
    double tolerance = epsilon * std::max(_x_current.rows(), _x_current.cols()) * _svd._s_values(0);

    for (int i = 0; i < static_cast<int>(_svd._s_values.size()); ++i) {
        if (_svd._s_values(i) > tolerance) {
            s_values_inv(i) = 1.0 / _svd._s_values(i);
        } else {
            s_values_inv(i) = 0.0;
        }
    }

    Eigen::MatrixXd s_matrix_inv = s_values_inv.asDiagonal();

    // Get reduced-rank dynamic matrix
    std::cout << "Creating reduced-rank dynamics matrix.\n";
    _dynamic_matrix = _svd._u_matrix.adjoint() * _x_next * _svd._v_matrix * s_matrix_inv;

    // Get corresponding eigenvalues and eigenvectors from _dynamic_matrix
    std::cout << "Computing eigenvalues and eigenvectors.\n";
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> complex_eigen;
    complex_eigen.compute(_dynamic_matrix);

    _eigenvalues  = complex_eigen.eigenvalues();
    _eigenvectors = complex_eigen.eigenvectors();

    // Get Exact Dynamic Modes & calculate Mode Amplitudes
    std::cout << "Extracting exact dynamic modes of the system and calculating mode amplitudes.\n";
    _dmd_modes  = _x_next * _svd._v_matrix * s_matrix_inv * _eigenvectors;
    _amplitudes = _dmd_modes.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(_x_current.col(0));

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

    py::class_<EigenSVD>(handle, "EigenSVD")
        .def_readonly("u_matrix", &EigenSVD::_u_matrix)
        .def_readonly("s_values", &EigenSVD::_s_values)
        .def_readonly("v_matrix", &EigenSVD::_v_matrix);

    py::class_<EigenDMD>(handle, "EigenDMD")
        .def(py::init<>())
        .def("standardDMD",
             &EigenDMD::standardDMD,
             "Compute Dynamic Mode Decomposition",
             py::arg("complex_matrix"),
             py::arg("reduced_rank") = -1
            )
        .def("getSVDResult",
             &EigenDMD::getSVDResult,
             py::return_value_policy::reference_internal,
             "Returns the SVD result that contains a left-matrix u_matrix, right-matrix v_matrix, and singular values s_values"
            )
        .def("getEigenvalues", 
             &EigenDMD::getEigenvalues,
             py::return_value_policy::reference_internal,
             "Returns 1D data containing complex eigenvalues"
            )
        .def("getEigenvectors", 
             &EigenDMD::getEigenvectors,
             py::return_value_policy::reference_internal,
             "Returns 2D data containing complex eigenvectors on each column"
            )
        .def("getDynamicModes",
             &EigenDMD::getDynamicModes,
             py::return_value_policy::reference_internal,
             "Returns a 2D matrix containing complex dynamic mode data"
            )
        ;



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