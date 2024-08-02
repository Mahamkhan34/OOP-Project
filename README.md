# OOP-Project
Snake Game in C++
This is a console-based Snake game implemented in C++. The game is built using the standard library and uses the conio.h library for input handling.
Features:
- Console-based game with a 20x20 game board
- Snake movement in four directions (up, down, left, right)
- Fruit generation at random positions
- Collision detection with walls and snake's tail
- Score tracking
- Game over message when snake collides with wall or tail
Controls:
- 'a' to move left
- 'd' to move right
- 'w' to move up
- 's' to move down
- 'x' to exit the game
Game Logic:
- The game updates the snake's position based on the direction
- Checks for collision with walls and tail
- Updates the fruit position and score when snake eats the fruit
- Increases the snake's length when fruit is eaten
Technical Details:
- Uses C++ standard library and conio.h for input handling
- Implements a SnakeGame class with methods for rendering the board, processing input, updating game logic, and initializing/resetting the game
- Uses a 2D array to store the game board and snake's tail positions
