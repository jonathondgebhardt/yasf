# Yet Another Simulation Framework (yasf)
## Goals
- Modern architecture
	- All third party dependencies will be built with a package manager (vcpkg, conan). Nothing will manually be built from source.
	- Newest available C++ compilers.
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
