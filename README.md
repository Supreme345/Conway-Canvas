# Conway-Canvas

A C++ SDL2-based interactive simulation of Conway's Game of Life, implementing the famous cellular automaton.  
This project brings the grid to life with drawing capabilities, pause/resume features, and updates like generation count and alive cells.

---

## About the Game

Conway's Game of Life is a zero-player game devised by mathematician John Conway.  
It consists of a grid of cells, each of which can be either alive (1) or dead (0).  
Each cell has eight neighbors, and the state of each cell in the next generation is determined by the following rules:

### Rules

1. **Birth**: A dead cell with exactly three live neighbors becomes alive.  
2. **Survival**: A live cell with two or three live neighbors stays alive.  
3. **Death**:  
   - A live cell with fewer than two live neighbors dies (underpopulation).  
   - A live cell with more than three live neighbors dies (overpopulation).

This implementation uses a finite grid (100 x 150 cells) with wrap-around edges, meaning the top connects to the bottom and the left connects to the right.

---

## Features

- Random Initialization or Draw your own pattern  
- Interactive Draw Mode:  
  - Left-click to add live cells  
  - Right-click to kill them  
- Pause / Resume simulation at any time  
- Step Forward: Advance one generation at a time when paused  
- Clear Grid: Reset the grid and enter draw mode  
- Exit Summary: Shows total generations and count of alive cells

---

## User Experience

### Startup Prompt

Choose initialization mode:                                                                                                                                  1 - Random Initialization                                                                                                                                    2 - Draw Custom Pattern

### Controls (shown in console)

- `p` : Pause and enter draw mode  
- `r` : Resume automatic simulation  
- `n` : Advance one generation (only in pause mode)  
- `c` : Clear the grid and enter draw mode  
- Close the window to quit

### Visuals

- Grid-based display  
- White squares represent alive cells  
- Simulation updates every 100ms unless paused

### On Exit

The console will display:

- Total generations simulated  
- Number of alive cells in the final state

---
## Build & Run
Make sure SDL2 is installed.


      make       # Builds the project
      ./LifeGrid # Runs the simulation (on windows - ./LifeGrid.exe)
      make clean # Clean build files
