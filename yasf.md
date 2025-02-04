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
- Recreate Grocery Store simulator

## cmake-init notes
### C++ version
Doesn't support > c++20. Crashes if given c++23.

The workflows/ci.yml file is not prepared for > c++20 either.
### Building documentation
I was missing a couple python packages: `jinja2` and `pygments`. Even after installing these, it throws an exception.
### CMakeUserPresets.json
This file contains the "dev" builds and is not tracked by the repo. If I clone the repo on another machine for development, I don't have the dev presets. I had to run cmake-init on an empty project to grab the user presets.
### Special features
cmake-init adds a lot of cool builds like ci, coverage, thread sanitization, but I don't know how to take advantage of these features. See HACKING.md for documentation on how to use these features. After reading this, I still don't know how to use the features.

## object 
I dislike how add_child/add_component invalidates your handle to the child you add. Perhaps add_child/add_component could return a handle on success.

## History tracking
Perhaps there could be a `component` that enables tracking the history of members. Some object could collect these `component`s and records the value of members. This would cleanly separate the "results" from the "configuration". Should I try to make this generic or should I provide an implementation for each "tracker"?

## object/component naming convention
Perhaps I should use a naming convention for these classes. 
### Ideas
- `oentity`, `cposition`
- `o_entity`, `c_position`
- `object_entity`, `component_postion`

## Simulation tree
I guess it's that time: design the layout of the tree.

`simulation`: `object`
    ├── children
    │   ├── `entity_service` (root of `entity`s)
    │   └── `processor_service` (root of `processor`s)
    ├── components
    └── `clock`
        └── `time_updater`

At the moment, I can't think of any other high-level classes I'll need.

## How to stop?
I need to implement knowing when to stop.

## Async
I'm going to have to think about thread safety at some point, if I even want to support that.

## Event-based simulations.
With the current implementation, the `time_updater` `component` of the `clock` is responsible for determining the next simulation time. If it were an event-based simulation, another `time_updater` would be aware of the next event to process and update time accordingly. Who owns the events in this scenario?

For now, I've decided to put that responsibility on the user. I have the changes somewhere.

After thinking about this, I think it would make the most sense for the events to be owned by the simulation. I would like it to be convenient to queue events.

I created an event specific `simulation` in grocery-store-sim, but the framework doesn't really allow for that. For example, getting the `simulation` from `processor::get_simulation()` returns a `yasf::simulation`. If the user wants to define their own `simulation`, they'll have to recreate a chunk of the framework.

## Logger
### Encapsulation
The question I need to answer first is "how do I want to interact with the logger?". Do I want to use macros or do I want to interact with some kind of logger object? Macros would be much simpler, although the linter would probably complain that I'm not using a constexpr function. The object would provide more flexibility, but I don't think I'll really take advantage of that.

```cpp
if (bad_condition) {
    yasf::log::error() << "a bad thing happened!";
    yasf::log::error("a bad thing {}", "happened");
}
```
### Backtraces
I'd like to enable backtraces on certain logger messages. For example: `yasf::ensure` should log a critical message and it should include a back trace.

## User should be able to specify time_type
It might be really convenient if the user was able to specify what the base time unit is.
