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

        const Eigen::VectorXcd& getEigenvalues() const { return _eigenvalues; } // Returns 1D data containing complex eigenvalues
        const Eigen::MatrixXcd& getDynamicModes() const { return _dmd_modes; }  // Returns a 2D matrix containing complex dynamic mode data
        const Eigen::VectorXcd& getAmplitudes() const { return _amplitudes; }

    private:
        Eigen::MatrixXcd _x_current, _x_next;           // Snapshots
        Eigen::MatrixXcd _dynamic_matrix, _dmd_modes;

        Eigen::MatrixXcd _eigenvectors;
        Eigen::VectorXcd _eigenvalues;

        Eigen::VectorXcd _amplitudes;

        void separateSnapshots(const Eigen::MatrixXcd& complex_matrix);

};

#endif // EIGEN_DMD_HPP