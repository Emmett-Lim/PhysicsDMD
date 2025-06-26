#ifndef EIGEN_DMD_HPP
#define EIGEN_DMD_HPP

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <Eigen/Dense>


/*
// [ TODO ]:
// -
*/


class EigenDMD {
    
    public:
        EigenDMD() {}
        ~EigenDMD() {}

        void standardDMD(const Eigen::MatrixXcd& complex_matrix, int reduced_rank = -1);    // complex double values
        //void standardDMD(const Eigen::MatrixXcf& complex_matrix);   // complex float values

    private:
        Eigen::MatrixXcd _x_current, _x_next;           // Snapshots
        Eigen::MatrixXcd _dynamic_matrix, _dmd_modes;

        Eigen::MatrixXcd _eigenvectors;
        Eigen::VectorXcd _eigenvalues;

        void separateSnapshots(const Eigen::MatrixXcd& complex_matrix);

};

#endif // EIGEN_DMD_HPP