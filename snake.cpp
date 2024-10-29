/*
SNAKE_GAME__FINAL_CS50-x__PROJECT || Github: danielSeSa

            W
      A            D
            S
*/
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
using namespace std;
////////////////////////////

void move(int dx, int dy); 
void produce();   // Generate food
char getvalue(int value);
void resetGame(); // Reset game state
///////////////////////////

int food;    // When you increase this number, your snake's length increases
int headX;   // Head x position
int headY;   // Head y position
int direction; // Direction of movement

// You can change the size of this map by changing the numbers "height" and "width"
const int width = 30;  // Width of the map
const int height = 30; // Height of the map
const int size = width * height;
int map[size];         // Map representation

bool isRunning; // Game running status
//////////////////////////

int main()
{
    char playAgain;
    do {
        resetGame(); // Initialize game state

        isRunning = true;
        while (isRunning)
        {
            if (kbhit()) // If a key is pressed
            {
                switch (getch())
                {
                    case 'w': if (direction != 2) direction = 0; break;
                    case 'd': if (direction != 3) direction = 1; break;
                    case 's': if (direction != 0) direction = 2; break;
                    case 'a': if (direction != 1) direction = 3; break;
                }
            }

            switch (direction)
            {
                case 0: move(-1, 0); break;
                case 1: move(0, 1); break;
                case 2: move(1, 0); break;
                case 3: move(0, -1); break;
            }

            // Reduce snake values on the map by 1
            for (int i = 0; i < size; i++) 
            {
                if (map[i] > 0)
                    map[i]--;
            }

            system("cls"); // Clear the screen

            // Print the map
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                    cout << getvalue(map[x + y * width]);

                cout << endl;
            }

            _sleep(200); // Wait 0.5 seconds
        }

        cout << "\t\t!Game over! :) " << endl << "\t\tscore: " << food << endl;
        cout << "\tDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}

///////////////////////////////////
void produce()   // This function generates food. After eating an apple, another apple is placed at a random location.
{
    int x, y;
    do {
        x = rand() % (width - 2) + 1;
        y = rand() % (height - 2) + 1;
    } while (map[x + y * width] != 0);

    // Place new food
    map[x + y * width] = -2;
}

//////////////////////////////////////////////
char getvalue(int v)
{
    if (v > 0)
        return 'o';
    
    switch (v)
    {
        case -1: return '#'; // Wall
        case -2: return 'o'; // Food
    }
    return ' '; // Empty space
}

///////////////////////////////////
void move(int dx, int dy)
{
    int newX = headX + dx;
    int newY = headY + dy;

    // Check if the new location has food
    if (map[newX + newY * width] == -2)
    {
        food++;
        produce();
    }

    // Check if the new location is not occupied by the snake
    else if (map[newX + newY * width] != 0)
    {
        isRunning = false; // Game over
        return;
    }

    // Move head to the new location
    headX = newX;
    headY = newY;
    map[headX + headY * width] = food + 1;
}

///////////////////////////////////
void resetGame() // Reset game state
{
    // Initialize snake's head position in the middle of the map
    headX = width / 2;
    headY = height / 2;
    map[headX + headY * width] = 1;

    // Place left and right walls
    for (int x = 0; x < width; ++x)
    {
        map[x] = -1;
        map[x + (height - 1) * width] = -1;
    }

    // Place top and bottom walls
    for (int y = 0; y < height; ++y)
    {
        map[0 + y * width] = -1;
        map[(width - 1) + y * width] = -1;
    }

    // Generate the first piece of food
    produce();

    // Initialize game variables
    food = 5;
    direction = 1; // Default direction to 'right'
    isRunning = true;
}
