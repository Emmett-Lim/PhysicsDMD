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

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.