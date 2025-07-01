import numpy as npy
import matplotlib.pyplot as mplt

def eigenvalue_spectrum(eigenvalues):
    theta = npy.linspace(0, 2*npy.pi, 100)
    mplt.scatter(eigenvalues.real, eigenvalues.imag)
    mplt.plot(npy.cos(theta), npy.sin(theta), 'k--')
    mplt.xlabel("Real")
    mplt.ylabel("Imag")
    mplt.title("Eigenvalue Spectrum")