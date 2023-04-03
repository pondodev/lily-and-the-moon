# TODO
- create GameContext
    - holds game state and game global vars
    - should be entirely decoupled from app state
    - app state will be used to process how the game receives inputs/is rendered
- set up rendering
    - opengl? metal? vulkan? moltenvk? look into what can be used
- set up input polling
- look into [faudio](https://github.com/FNA-XNA/FAudio)
- look into sqlite for save games (if needed)
- maybe look into [concurrentqueue](https://github.com/cameron314/concurrentqueue)
    - setting up your own multi threading may be okay too, but first identify what needs it

