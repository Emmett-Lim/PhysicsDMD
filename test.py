import mylib.pymodule_test
from mylib.pymodule_test import *

# print(dir(mylib.pymodule_test))

help(add_fn_python)

print(add_fn_python(3.5, 3.5))

m = PySomeClass(5)

print(m.multiplier)

print(m.multiply(10))

m.multiplier = 10

print(m.multiplier)

print(m.multiply(10))