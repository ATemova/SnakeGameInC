#include <stdio.h>      // Standard input/output library
#include <stdlib.h>     // Standard library
#include <conio.h>      // Console input/output library
#include <windows.h>    // Windows API library

#define WIDTH 40        // Width of game area
#define HEIGHT 20       // Height of game area
#define SNAKE_LENGTH 3  // Initial length of snake

int score = 0;          // Current score
int gameover = 0;       // Game over flag

// Point structure to represent a point on the game area
typedef struct {
    int x;
    int y;
} point;

point head;             // Head of the snake
point tail;             // Tail of the snake
point food;             // Position of the food

int snake_length = SNAKE_LENGTH;    // Length of the snake
point snake[SNAKE_LENGTH];          // Array to store the positions of each segment of the snake

// Enumeration to represent the possible directions of the snake
enum direction { UP, DOWN, LEFT, RIGHT };
enum direction current_dir;

// Function to draw the game area on the console
void draw() {
    system("cls");      // Clear console screen

    // Draw top border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // Draw game area
    for (int i = 0; i < HEIGHT; i++) {
        printf("#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head.y && j == head.x) {
                printf("O");
            } else if (i == food.y && j == food.x) {
                printf("X");
            } else {
                int flag = 0;
                for (int k = 0; k < snake_length; k++) {
                    if (i == snake[k].y && j == snake[k].x) {
                        printf("o");
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    printf(" ");
                }
            }
        }
        printf("#\n");
    }

    // Draw bottom border
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    printf("Score: %d\n", score);   // Display current score
}

// Function to initialize the game state
void init() {
    // Initialize head and tail position
    head.x = WIDTH / 2;
    head.y = HEIGHT / 2;
    tail.x = head.x;
    tail.y = head.y;

    // Initialize snake body
    for (int i = 0; i < snake_length; i++) {
        snake[i].x = head.x;
        snake[i].y = head.y + i;
    }

    // Initialize food position
    srand(time(NULL));  // Seed random number generator
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

// Function to update the game state
void update() {
    // Update snake body position
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    snake[0].x = head.x;
    snake[0].y = head.y;

    // Update head position
    switch (current_dir)
{
    case UP:
        head.y--;
        break;
    case DOWN:
        head.y++;
        break;
    case LEFT:
        head.x--;
        break;
    case RIGHT:
        head.x++;
        break;
}

// Check collision with walls or snake body
if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
    gameover = 1;
}
for (int i = 1; i < snake_length; i++) {
    if (head.x == snake[i].x && head.y == snake[i].y) {
        gameover = 1;
        break;
    }
}

// Check collision with food
if (head.x == food.x && head.y == food.y) {
    score++;
    snake_length++;

    // Add new tail position to snake body
    snake[snake_length - 1].x = tail.x;
    snake[snake_length - 1].y = tail.y;

    // Move tail position to new position
    tail.x = snake[1].x;
    tail.y = snake[1].y;

    // Generate new food position
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}
}

// Function to handle user input
void input() {
if (_kbhit()) { // Check if a key has been pressed
switch (_getch()) {
case 'w':
if (current_dir != DOWN) {
current_dir = UP;
}
break;
case 's':
if (current_dir != UP) {
current_dir = DOWN;
}
break;
case 'a':
if (current_dir != RIGHT) {
current_dir = LEFT;
}
break;
case 'd':
if (current_dir != LEFT) {
current_dir = RIGHT;
}
break;
}
}
}

// Main function
int main() {
init(); // Initialize game state
// Game loop
while (!gameover) {
    draw();     // Draw game area
    input();    // Handle user input
    update();   // Update game state
    Sleep(100); // Wait for a short time to control game speed
}

// Display game over message and score
printf("Game Over!\n");
printf("Score: %d\n", score);

return 0;
}
