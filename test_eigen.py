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

X = npy.random.randn(100, 80) + 1j * npy.random.randn(100, 80)
X = X.astype(npy.complex128)

dmd = EigenDMD()
dmd.standardDMD(X)

### === EigenDMD Test === ###



#data = npy.load("data/y_frames.npy", mmap_mode='r')
#print(data.dtype)
#print(data)
#print("Data size: ", data.shape)