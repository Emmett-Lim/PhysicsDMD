import numpy as npy
import matplotlib.pyplot as mplt
#import matplotlib.animation as animation

import utils.dmd_plotter
from utils.dmd_plotter import eigenvalue_spectrum, dmd_modes_spatial, dmd_modes_temporal

import utils.eigen_dmd
from utils.eigen_dmd import MatrixTest, EigenDMD


#//# ==== PYTHON VERSION ==== #
#//matrix_py = npy.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
#//
#//mplt.matshow(matrix_py)
#//mplt.title("Python Heatmap")
#//# ======================== #
#//
#//
#//# ==== C++ VERSION ==== #
#//matrix_cpp = MatrixTest()
#//matrix_cpp.test_matrix()
#//
#//mplt.matshow(matrix_cpp.get_matrix())
#//mplt.title("C++ Heatmap")
#//# ===================== #
#//
#//
#//mplt.show()



### === EigenDMD Test === ###

def f1(x, t):
    return 1.0 / npy.cosh(x + 3) * npy.exp(2.3j * t)

def f2(x, t):
    return 2.0 / npy.cosh(x) * npy.tanh(x) * npy.exp(2.8j * t)

nx = 65
nt = 129

x = npy.linspace(-5, 5, nx)
t = npy.linspace(0, 4 * npy.pi, nt)
xgrid, tgrid = npy.meshgrid(x, t)

X1 = f1(xgrid, tgrid)
X2 = f2(xgrid, tgrid)
X = X1 + X2

print(X.shape)

titles = ["$f_1(x,t)$", "$f_2(x,t)$", "$f$"]
data   = [X1, X2, X]

fig = mplt.figure(figsize=(17, 6))
for n, title, d in zip(range(131, 134), titles, data):
    mplt.subplot(n)
    mplt.pcolor(xgrid, tgrid, d.real)
    mplt.title(title)
    mplt.xlabel("Space")
    mplt.ylabel("Time")
    mplt.colorbar()
mplt.show()

dmd = EigenDMD()
print(X.T.shape)
dmd.standardDMD(X.T, reduced_rank=2)

svd = dmd.getSVDResult()

eigenvalues  = dmd.getEigenvalues()
eigenvectors = dmd.getEigenvectors()

eigenvalue_spectrum(eigenvalues)
mplt.show()

print(dmd.getDynamicModes().shape)
dmd_modes_spatial(x, dmd.getDynamicModes(), 2)
mplt.show()

print(dmd.getTimeDynamics().shape)
dmd_modes_temporal(t, dmd.getTimeDynamics(), 2)
mplt.show()

X_Rec = dmd.reconstructData()
print(X_Rec.shape)

mplt.pcolor(xgrid, tgrid, X_Rec.T.real)
mplt.title("$f_{reconstructed}$")
mplt.xlabel("Space")
mplt.ylabel("Time")
mplt.colorbar()
mplt.show()

### === EigenDMD Test === ###