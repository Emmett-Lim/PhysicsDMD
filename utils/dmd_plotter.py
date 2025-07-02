import numpy as npy
import matplotlib.pyplot as mplt

def eigenvalue_spectrum(eigenvalues):
    theta = npy.linspace(0, 2*npy.pi, 100)
    mplt.scatter(eigenvalues.real, eigenvalues.imag)
    mplt.plot(npy.cos(theta), npy.sin(theta), 'k--')
    
    mplt.axis('equal')
    mplt.xlabel("Real")
    mplt.ylabel("Imag")
    mplt.title("Eigenvalue Spectrum")

    
def dmd_modes_spatial(x_coords, dmd_modes, num_modes):
    mplt.subplot(1, 2, 1)
    for i in range(num_modes):
        mplt.plot(x_coords, npy.real(dmd_modes[:, i]), label=f'Mode {i}')
    mplt.legend()
    mplt.title("DMD Spatial Modes (Real Part)")
    mplt.xlabel("x")
    mplt.ylabel("Amplitude")
    
    mplt.subplot(1, 2, 2)
    for i in range(num_modes):
        mplt.plot(x_coords, npy.imag(dmd_modes[:, i]), label=f'Mode {i}')
    mplt.legend()
    mplt.title("DMD Spatial Modes (Imaginary Part)")
    mplt.xlabel("x")
    mplt.ylabel("Amplitude")


def dmd_modes_temporal(t_coords, dmd_modes, num_modes):
    mplt.subplot(1, 2, 1)
    for i in range(num_modes):
        mplt.plot(t_coords, npy.real(dmd_modes[i, :]), label=f'Mode {i}')
    mplt.legend()
    mplt.title("DMD Temporal Modes (Real Part)")
    mplt.xlabel("time (t)")
    mplt.ylabel("Amplitude")
    
    mplt.subplot(1, 2, 2)
    for i in range(num_modes):
        mplt.plot(t_coords, npy.imag(dmd_modes[i, :]), label=f'Mode {i}')
    mplt.legend()
    mplt.title("DMD Temporal Modes (Imaginary Part)")
    mplt.xlabel("time (t)")
    mplt.ylabel("Amplitude")