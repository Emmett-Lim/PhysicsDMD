import utils.pymodule_test
from utils.pymodule_test import *

# Warnings coming from using wildcard (*) when importing

# print(dir(utils.pymodule_test))

help(add_fn_python)

print(add_fn_python(3.5, 3.5))

m = PySomeClass(5)

print(m.multiplier)

print(m.multiply(10))

m.multiplier = 10

print(m.multiplier)

print(m.multiply(10))