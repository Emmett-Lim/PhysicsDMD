#ifndef EIGEN_DMD_HPP
#define EIGEN_DMD_HPP

#include <cmath>
#include <complex>
#include <iostream>

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

        void standardDMD(const Eigen::MatrixXcd& complex_matrix);   // complex double values
        void standardDMD(const Eigen::MatrixXcd& complex_matrix,
                                        const int reduced_rank);    // complex double values (reduced matrix)
        //void standardDMD(const Eigen::MatrixXcf& complex_matrix);   // complex float values

    private:
        Eigen::MatrixXcd _x_current, _x_next;
        Eigen::MatrixXcd _eigenvalues, _dmd_modes;

        void separateSnapshots(const Eigen::MatrixXcd& complex_matrix);
};

#endif // EIGEN_DMD_HPP