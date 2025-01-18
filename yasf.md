# Yet Another Simulation Framework (yasf)
## Goals
- Modern architecture
	- All third party dependencies will be built with a package manager (vcpkg, conan). Nothing will manually be built from source.
	- Newest available C++ compilers. Try to use newest C++ features.
- Minimize work done during CMake time.
- Attempt to innovate on maintaining data history.
- Try composition instead of inheritance.
- Standardize use of Factory/Builder.
- Tests first.

## Objects
- Built via Factory/Builder.
- On the fence about `Impl`.

## End goal
- Recreate WSU parking lot simulator

## cmake-init notes
### C++ version
Doesn't support C++ > 20. Crashes if given c++23.
### Building documentation
I was missing a couple python packages: `jinja2` and `pygments`. Even after installing these, it throws an exception.
### CMakeUserPresets.json
This file contains the "dev" builds and is not tracked by the repo. If I clone the repo on another machine for development, I don't have the dev presets. I had to run cmake-init on an empty project to grab the user presets.
### Special features
cmake-init adds a lot of cool builds like ci, coverage, thread sanitization, but I don't know how to take advantage of these features. See HACKING.md for documentation on how to use these features.
