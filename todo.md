# TODO

## gameplay
- create basic world
    - single screen, entrances and exits, player can move between screens
- look into raylib camera functionality

## tech
- look into rendering stuffs
    - opengl? metal? vulkan? moltenvk? look into what can be used
    - will i want custom shaders?
- look into [faudio](https://github.com/FNA-XNA/FAudio)
- look into sqlite for save games (if needed)
- maybe look into [concurrentqueue](https://github.com/cameron314/concurrentqueue)
    - setting up your own multi threading may be okay too, but first identify what needs it
- refactor components to be structs containing a union (see https://stackoverflow.com/questions/252552/why-do-we-need-c-unions)
    - we can move these components to the stack, use generational ids to index them

