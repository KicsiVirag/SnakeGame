# Snake Game – C++ / SDL2

A graphical implementation of the classic Snake game written in C++ using an SDL2-based graphics library. Collect food to grow the snake while avoiding obstacles, screen boundaries and the snake's own body.

## Features

- Classic grid-based gameplay
- Randomly generated food and walls
- Snake growth and collision detection
- Three difficulty levels
- Game Over screen and restart functionality
- 600 × 400 pixel playing field with 20 × 20 pixel cells

## Controls

| Key | Action |
| --- | --- |
| Arrow keys | Change movement direction |
| 1 | Hard (50 ms per step) |
| 2 | Normal (100 ms per step) |
| 3 | Easy (150 ms per step) |
| Space | Restart after Game Over and select difficulty again |
| Esc | Exit from menu or Game Over screen; end current run during gameplay |

Difficulty is selected in the start menu. Direct reversal of the snake's direction is prevented.

## Technologies

- C++ and the Standard Library
- SDL2 and SDL2_ttf
- graphicslib (rendering and event handling)
- Code::Blocks and GCC/MinGW

## Getting started

### Run on Windows

The original project archive includes a precompiled `GraphicsProject.exe`. Extract the archive and launch the executable from the project root. Keep the supplied DLL files and `LiberationSans-Regular.ttf` alongside it.

### Build from source

1. Install Code::Blocks with a compatible GCC/MinGW toolchain.
2. Open `GraphicsProject.cbp`.
3. Select the `Release` build target.
4. Choose **Build and Run** (F9).

The configuration uses the bundled `include/` and `lib/` directories. If linking fails, check that the compiler architecture matches the SDL2 libraries. Use the project root as the working directory.

## Project structure

```text
.
├── main.cpp                    # Game logic, rendering and input
├── GraphicsProject.cbp         # Code::Blocks configuration
├── graphicslib/                # Graphics library source
├── include/                    # Graphics and SDL2 headers
├── lib/                        # SDL2 linking libraries
├── LiberationSans-Regular.ttf  # Game font
└── *.dll                       # Windows runtime dependencies
```

## Implementation

The `Snakegame` class manages the snake, food, obstacles, movement direction and game state. Snake segments and walls are stored in vectors of `Point` structures.

At each timer event, the game calculates the next head position and checks for collisions. If the move is valid, a new head is inserted and the tail is removed unless food has been collected. The `genv` graphics interface handles rendering and keyboard events.

## Known limitations

- No score counter or high-score system is implemented.
- Wall generation does not fully validate overlapping walls, food placement or whether all wall segments remain within the playing field.
- The supplied build configuration targets Windows; other platforms may require adjustments.

## License

No project-level license was included in the original archive. Third-party libraries and fonts are subject to their respective licenses.
