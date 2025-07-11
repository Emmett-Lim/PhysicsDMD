import numpy as npy
import matplotlib.pyplot as mplt


def singular_value_plot(singular_values):
    
    index = npy.arange(singular_values.size)
    mplt.scatter(index, singular_values)
    mplt.xlabel("Mode Index")
    mplt.ylabel("Singular Values")
    mplt.title("Singular Values Plot")



def eigenvalue_spectrum(eigenvalues):
    
    theta = npy.linspace(0, 2*npy.pi, 100)
    mplt.scatter(eigenvalues.real, eigenvalues.imag)
    mplt.plot(npy.cos(theta), npy.sin(theta), 'k--')
    
    mplt.axis('equal')
    mplt.xlabel("Real")
    mplt.ylabel("Imag")
    mplt.title("Eigenvalue Spectrum")


    
def dmd_modes_spatial(x_coords, dmd_modes, num_modes):
    
    subplots_per_figure = 9
        
    for i in range(num_modes):
        if i % subplots_per_figure == 0:
            fig = mplt.figure(figsize=(10, 8))
            fig.suptitle("DMD Spatial Modes")

        subplot_index = i % subplots_per_figure + 1
        ax = fig.add_subplot(3, 3, subplot_index)

        mplt.plot(x_coords, npy.real(dmd_modes[:, i]), label='Real')
        mplt.plot(x_coords, npy.imag(dmd_modes[:, i]), label='Imag')

        ax.set_title(f"Mode {i + 1}")
        ax.set_xlabel("position (x)")
        ax.set_ylabel("Amplitude")
        ax.legend()



def dmd_modes_temporal(t_coords, dmd_modes, num_modes):
    
    subplots_per_figure = 9
    
    for i in range(num_modes):
        if i % subplots_per_figure == 0:
            fig = mplt.figure(figsize=(10, 8))
            fig.suptitle("DMD Temporal Modes")

        subplot_index = i % subplots_per_figure + 1
        ax = fig.add_subplot(3, 3, subplot_index)

        ax.plot(t_coords, npy.real(dmd_modes[i, :]), label='Real')
        ax.plot(t_coords, npy.imag(dmd_modes[i, :]), label='Imag')

        ax.set_title(f"Mode {i + 1}")
        ax.set_xlabel("time (t)")
        ax.set_ylabel("Amplitude")
        ax.legend()