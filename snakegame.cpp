#include <iostream>
#include <conio.h>   // Include the conio.h library for input handling
#include <windows.h> //// Include windows.h for _sleep

using namespace std; // Use the standard namespace

// Define the SnakeGame class
class SnakeGame
{
private:
    int snakeX, snakeY;               // Position of the snake's head
    int currentFruitX, currentFruitY; // Position of the current fruit
    int gameScore;                    // Current game score
    int snakeLength;                  // Length of the snake's tail
    int tailPosX[100], tailPosY[100]; // Arrays to hold the positions of the snake's tail
    int direction;                    // Direction of the snake's movement (0: up, 1: right, 2: down, 3: left)
    const int boardWidth = 20;        // Width of the game board
    const int boardHeight = 20;       // Height of the game board

    // Predefined fruit positions
    int fruitPositions[5][2] = {
        {5, 5},
        {10, 10},
        {15, 15},
        {3, 17},
        {17, 3}};
    int currentFruitIndex; // Index of the current fruit position

public:
    // Constructor to initialize the game with a starting position for the snake
    SnakeGame(int startX, int startY)
    {
        // Check if the starting position is valid
        if (startX < 0 || startX >= boardWidth || startY < 0 || startY >= boardHeight)
        {
            cout << "Invalid starting position!" << endl; // Print error message if invalid
            exit(1);                                      // Exit the program
        }
        snakeX = startX;                                      // Set the initial x position of the snake
        snakeY = startY;                                      // Set the initial y position of the snake
        currentFruitIndex = 0;                                // Initialize the fruit index
        currentFruitX = fruitPositions[currentFruitIndex][0]; // Set the initial fruit x position
        currentFruitY = fruitPositions[currentFruitIndex][1]; // Set the initial fruit y position
        gameScore = 0;                                        // Initialize the score
        snakeLength = 0;                                      // Initialize the snake's length
        direction = 0;                                        // Set the initial direction to up
    }

    // Function to render the game board
    void renderBoard()
    {
        system("cls"); // Clear the console screen
        // Print the top border of the game board
        cout << string(boardWidth + 2, '#') << endl;
        // Loop through each cell of the game board
        for (int i = 0; i < boardHeight; i++)
        {
            for (int j = 0; j < boardWidth; j++)
            {
                if (j == 0)
                    cout << "#"; // Print the left border
                if (i == snakeY && j == snakeX)
                    cout << "O"; // Print the snake's head
                else if (i == currentFruitY && j == currentFruitX)
                    cout << "F"; // Print the fruit
                else
                {
                    bool isTail = false; // Flag to check if the cell is part of the snake's tail
                    for (int k = 0; k < snakeLength; k++)
                    {
                        if (tailPosX[k] == j && tailPosY[k] == i)
                        {
                            cout << "o";   // Print the snake's tail
                            isTail = true; // Set the flag to true
                        }
                    }
                    if (!isTail)
                        cout << " "; // Print an empty space if not part of the tail
                }
                if (j == boardWidth - 1)
                    cout << "#"; // Print the right border
            }
            cout << endl;
        }
        // Print the bottom border of the game board
        cout << string(boardWidth + 2, '#') << endl;
        // Print the current score
        cout << "Score: " << gameScore << endl;
    }

    // Function to process user input
    void processInput()
    {
        if (_kbhit())
        {                              // Check if a key is pressed
            char inputChar = _getch(); // Get the input character without waiting for Enter
            switch (inputChar)
            {
            case 'a':
                direction = 3;
                break; // Change direction to left
            case 'd':
                direction = 1;
                break; // Change direction to right
            case 'w':
                direction = 0;
                break; // Change direction to up
            case 's':
                direction = 2;
                break; // Change direction to down
            case 'x':
                exit(0); // Exit the game
            }
        }
    }

    // Function to update the game logic
    // Function to update the game logic
    void updateGameLogic()
    {
        int prevPosX = tailPosX[0]; // Store the previous x position of the tail
        int prevPosY = tailPosY[0]; // Store the previous y position of the tail
        int prev2PosX, prev2PosY;   // Variables to store the previous positions in the loop
        tailPosX[0] = snakeX;       // Set the new x position of the tail's head
        tailPosY[0] = snakeY;       // Set the new y position of the tail's head
        for (int i = 1; i < snakeLength; i++)
        {
            prev2PosX = tailPosX[i]; // Store the current x position of the tail
            prev2PosY = tailPosY[i]; // Store the current y position of the tail
            tailPosX[i] = prevPosX;  // Update the x position of the tail
            tailPosY[i] = prevPosY;  // Update the y position of the tail
            prevPosX = prev2PosX;    // Update the previous x position for the next iteration
            prevPosY = prev2PosY;    // Update the previous y position for the next iteration
        }
        // Update the snake's position based on the direction
        switch (direction)
        {
        case 0:
            snakeY--;
            break; // Move up
        case 1:
            snakeX++;
            break; // Move right
        case 2:
            snakeY++;
            break; // Move down
        case 3:
            snakeX--;
            break; // Move left
        }
        // Check if the snake goes out of bounds
        if (snakeX >= boardWidth || snakeX < 0 || snakeY >= boardHeight || snakeY < 0)
        {
            cout << "Game Over!" << endl; // Print game over message
            exit(0);                      // Exit the game
        }
        // Check if the snake collides with its tail
        for (int i = 0; i < snakeLength; i++)
            if (tailPosX[i] == snakeX && tailPosY[i] == snakeY)
            {
                cout << "Game Over!" << endl; // Print game over message
                exit(0);                      // Exit the game
            }
        // Check if the snake eats the fruit
        if (snakeX == currentFruitX && snakeY == currentFruitY)
        {
            gameScore += 10;                                      // Increase the score
            currentFruitIndex = (currentFruitIndex + 1) % 5;      // Update the fruit index
            currentFruitX = fruitPositions[currentFruitIndex][0]; // Set the new fruit x position
            currentFruitY = fruitPositions[currentFruitIndex][1]; // Set the new fruit y position
            snakeLength++;                                        // Increase the snake's length
        }
    }

    // Function to initialize or reset the game
    void initializeGame()
    {
        snakeX = boardWidth / 2;                              // Reset the snake's x position
        snakeY = boardHeight / 2;                             // Reset the snake's y position
        currentFruitIndex = 0;                                // Reset the fruit index
        currentFruitX = fruitPositions[currentFruitIndex][0]; // Reset the fruit x position
        currentFruitY = fruitPositions[currentFruitIndex][1]; // Reset the fruit y position
        gameScore = 0;                                        // Reset the score
        snakeLength = 0;                                      // Reset the snake's length
        direction = 0;                                        // Reset the direction to up
    }
};

// Main function
int main()
{

    cout << "Welcome to Snake Game!" << endl; // Display welcome message
    cout << "Press any key to start..." << endl;
    _getch(); // Wait for user to press a key

    SnakeGame game(10, 10); // Create a SnakeGame object starting at position (10, 10)
    while (true)
    {                           // Infinite loop to keep the game running
        game.renderBoard();     // Render the game board
        game.processInput();    // Process user input
        game.updateGameLogic(); // Update the game logic
        _sleep(100);            // Add a small delay to control the game speed
    }

    return 0;
}