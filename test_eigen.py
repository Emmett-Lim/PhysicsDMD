import numpy as npy
import matplotlib.pyplot as mplt
import mylib.eigen_dmd
from mylib.eigen_dmd import MatrixTest, EigenDMD


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

titles = ["$f_1(x,t)$", "$f_2(x,t)$", "$f$"]
data = [X1, X2, X]

fig = mplt.figure(figsize=(17, 6))
for n, title, d in zip(range(131, 134), titles, data):
    mplt.subplot(n)
    mplt.pcolor(xgrid, tgrid, d.real)
    mplt.title(title)
mplt.colorbar()
mplt.show()

dmd = EigenDMD()
dmd.standardDMD(X.T, reduced_rank=2)

#A = npy.random.randn(100, 80) + 1j * npy.random.randn(100, 80)
#A = A.astype(npy.complex128)
#
#dmd = EigenDMD()
#dmd.standardDMD(A)

### === EigenDMD Test === ###



#data = npy.load("data/y_frames.npy", mmap_mode='r')
#print(data.dtype)
#print(data)
#print("Data size: ", data.shape)