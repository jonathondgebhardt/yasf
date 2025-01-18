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
cmake-init adds a lot of cool builds like ci, coverage, thread sanitization, but I don't know how to take advantage of these features. See HACKING.md for documentation on how to use these features. After reading this, I still don't know how to use the features.

## object 
I dislike how add_child/add_component invalidates your handle to the child you add. Perhaps add_child/add_component could return a handle on success.

## uuid
Should uuid be an inherent part of object?

## History tracking
Perhaps there could be a `component` that enables tracking the history of members. Some object could collect these `component`s and records the value of members. This would cleanly separate the "results" from the "configuration". Should I try to make this generic or should I provide an implementation for each "tracker"?

## object/component naming convention
Perhaps I should use a naming convention for these classes. 
### Ideas
- `oentity`, `cposition`
- `o_entity`, `c_position`
- `object_entity`, `component_postion`

## Classes that work on `component`
I think my first major step towards a simulation is adding a class that moves an `entity`. Until I nail down how the tree looks, I'll just add a class that takes a root `object` and updates it's `position` `component`.

Pseudo-code:
- position += velocity * delta_time

## Classes that require time
I've implemented a basic `mover` that moves an `entity` given it's `position`, `velocity` and delta time. The time is currently hard-coded. I need to design a clock. Maybe for now, I'll just bake a clock into `mover` and extract it when the time comes.
