# TDD-Snake

Custom snake implementation. Written with MVC pattern.

### Model
Model is written (mainly) using TDD. Gtest is used. It's independent from Qt,
theoreticaly any gui library could be used to represent game.

Game parameters like grid size or delay between setps are modified by changing constants.hpp file.

### Controller
Simple connector between Model and Controller, uses Qt signals and slots. Also includes
something similar to game main loop (Qtimer triggers next game step).

### View
Single Qt MainWindow class. Takes data directly from model, but don't modify it.

## TODO
 - Initial screen with parameters modification (will replace constants.hpp)
