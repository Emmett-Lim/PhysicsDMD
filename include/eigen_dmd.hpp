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

struct EigenSVD {
            Eigen::MatrixXcd _u_matrix;
            Eigen::VectorXd _s_values;
            Eigen::MatrixXcd _v_matrix;
};

class EigenDMD {

    private:
        Eigen::MatrixXcd _x_current, _x_next;           // Snapshots

        EigenSVD _svd;

        Eigen::MatrixXcd _dynamic_matrix;

        Eigen::MatrixXcd _dmd_modes, _time_dynamics;

        Eigen::MatrixXcd _eigenvectors;
        Eigen::VectorXcd _eigenvalues;

        Eigen::VectorXcd _amplitudes;

        void separateSnapshots(const Eigen::MatrixXcd& complex_matrix);
    
    public:
        EigenDMD() {}
        ~EigenDMD() {}

        void standardDMD(const Eigen::MatrixXcd& complex_matrix, int reduced_rank = -1);    // complex double values
        //void standardDMD(const Eigen::MatrixXcf& complex_matrix);   // complex float values

        const Eigen::MatrixXcd reconstructData();

        const EigenSVD& getSVDResult() const { return _svd; }

        const Eigen::VectorXcd& getEigenvalues() const { return _eigenvalues; } // Returns 1D data containing complex eigenvalues
        const Eigen::MatrixXcd& getEigenvectors() const { return _eigenvectors; }

        const Eigen::MatrixXcd& getDynamicModes() const { return _dmd_modes; }  // Returns a 2D matrix containing complex dynamic mode data
        const Eigen::MatrixXcd& getTimeDynamics() const { return _time_dynamics; }

        const Eigen::VectorXcd& getAmplitudes() const { return _amplitudes; }

};

#endif // EIGEN_DMD_HPP