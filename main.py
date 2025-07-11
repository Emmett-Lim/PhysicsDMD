import numpy as npy
import matplotlib.pyplot as mplt

import utils.dmd_plotter
#from utils.dmd_plotter import eigenvalue_spectrum, dmd_modes_spatial, dmd_modes_temporal, singular_value_plot
from utils.dmd_plotter import *

import utils.eigen_dmd
from utils.eigen_dmd import MatrixTest, EigenDMD

# Load complex data and x coordinates
y_frames = npy.load("data/y_frames.npy", mmap_mode='r')
x_coords = npy.loadtxt("data/x_coord.txt")
t_coords = npy.arange(len(y_frames[0]))

print("Size of Original Data: ", y_frames.shape)

# Plot raw data of first 4 snapshots (x, y)
mplt.subplot(1, 2, 1)
for i in range(4):
    mplt.plot(x_coords, npy.real(y_frames[:, i]), label=f"Frame {i}")

mplt.xlabel("x")
mplt.ylabel("y")
mplt.title("Original Traveling Waves (Real Part)")
mplt.legend()
mplt.tight_layout()

mplt.subplot(1, 2, 2)
for i in range(4):
    mplt.plot(x_coords, npy.imag(y_frames[:, i]), label=f"Frame {i}")

mplt.xlabel("x")
mplt.ylabel("y")
mplt.title("Original Traveling Waves (Imaginary Part)")
mplt.legend()
mplt.tight_layout()

mplt.show()

print("Size of Original Data (Transposed): ", y_frames.T.shape)

dmd = EigenDMD()

# Calculate SVD on the first snapshot to analyze singular values
dmd.calculateSVD(y_frames)
svd = dmd.getSVDResult()

# Plot results from DMD algorithm as visual graphs
singular_value_plot(svd.s_values)
mplt.show()

num_modes = int(input("Enter the amount of required modes (integers only): "))

# Calculate DMD of the complex data
dmd.standardDMD(y_frames, reduced_rank=num_modes)
#dmd.standardDMD(y_frames) # This is for full rank

eigenvalues  = dmd.getEigenvalues()
eigenvectors = dmd.getEigenvectors()


eigenvalue_spectrum(eigenvalues)
mplt.show()

print("Dynamic Mode Matrix Size: ", dmd.getDynamicModes().shape)
dmd_modes_spatial(x_coords, dmd.getDynamicModes(), num_modes)
mplt.show()

print("Time Dynamics Matrix Size: ", dmd.getTimeDynamics().shape)
dmd_modes_temporal(t_coords, dmd.getTimeDynamics(), num_modes)
mplt.show()

X_Rec = dmd.reconstructData()
print("Size of Reconstructed Data: ", X_Rec.shape)


# Plot Reconstructed Data of first 4 snapshots (x, y)
mplt.subplot(1, 2, 1)
for i in range(4):
    mplt.plot(x_coords, npy.real(X_Rec[:, i]), label=f"Frame {i}")

mplt.xlabel("x")
mplt.ylabel("y")
mplt.title("Reconstructed Traveling Waves (Real Part)")
mplt.legend()
mplt.tight_layout()

mplt.subplot(1, 2, 2)
for i in range(4):
    mplt.plot(x_coords, npy.imag(X_Rec[:, i]), label=f"Frame {i}")

mplt.xlabel("x")
mplt.ylabel("y")
mplt.title("Reconstructed Traveling Waves (Imaginary Part)")
mplt.legend()
mplt.tight_layout()

mplt.show()