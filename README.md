# ActionSudokuGame
This Sudoku game, implemented in C++, features a classic 9x9 grid where the objective is to fill it with numbers without repetition in rows, columns, or boxes. The player controls Sparty, navigating the grid to consume digits by pressing the space bar when adjacent to them. The consumed digits are then displayed in an X-ray image. Sparty can regurgitate digits by pressing number keys if they are in his stomach. The game comprises three levels, including an optional test level (Level 0) designed for development purposes. Upon successfully completing a level, the game proceeds to the next, except for Level 3, which repeats.

As part of the project requirements, there is a "File > Solve" menu option allowing the relocation of digits in the playing area to correct positions, potentially concluding the level. The menu also enables users to jump directly to any level, with Level 0 recommended for testing. Level 2 introduces a unique feature: containers that hold digits. Sparty cannot eat digits in the container until he headbutts it by pressing the B key, releasing the digits to random locations above the container for consumption. The entire game is programmed in C++.
