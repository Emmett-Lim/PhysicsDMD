# PhysicsDMD

A Physics program using Dynamic Mode Decomposition (DMD), incorporating the use of [pybind11](https://github.com/pybind/pybind11)
to create a Python module from C++.

## Prerequisites

- A compiler with **C++17** support
- **CMake ≥ 3.14** (3.14+ is required on Windows; 3.4 is no longer valid with modern CMake)
- **Python ≥ 3.6**
- (Recommended) [pip](https://pip.pypa.io/) for `pyproject.toml` (Use Ninja or Make if using Linux/MacOS)

## Installation

Clone this repository and note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive <the-repo-url>
cd ./pybind11-setup
```

For use of pip, please install scikit-build-core: ```pip install scikit-build-core build```

## Build

Pip build:

```bash
./build-pip
```

Cmake and Make/Ninja build:

Debug Mode:

```bash
n/a
```

Release Mode:

```bash
n/a
```

> [!NOTE]
> If required to rebuild, just execute ```./build-pip``` again

## License

This project uses and incorporates third-party libraries under their respective licenses:

### Pybind11
[Pybind11](https://github.com/pybind/pybind11) is provided under a BSD-style license that can be found in the [LICENSE](https://github.com/pybind/pybind11/blob/master/LICENSE)
file.

### Eigen
[Eigen](http://eigen.tuxfamily.org) is [Free Software](https://www.gnu.org/philosophy/free-sw.html), licensed under the [MPL2](https://www.mozilla.org/en-US/MPL/2.0/), which is a simple weak copyleft license. A copy of the license is provided in ```external/lib/eigen/LICENSE```