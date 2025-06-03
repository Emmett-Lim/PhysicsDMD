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

Debug Mode:

```bash
chmod u+x build-debug.sh
./build-debug.sh
```

Release Mode:

```bash
chmod u+x build-release.sh
./build-release.sh
```

Or if using pip install `scikit-build-core`; that is, ```pip install scikit-build-core build```,
then execute:

```bash
mkdir build
pip install .
```

> [!NOTE]
> If required to rebuild, simply rerun the bash file in specific mode. If using pip,
> run the following in root directory:

```bash
pip install . --force-reinstall
```

## License

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.