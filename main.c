#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>

#define rows 20
#define columns 40

// Used integers for loops
int i, j;
// For Map grid
int Map[rows][columns];
// Used integers for Snake movement and length and Food and Poison positions
int snakex, snakey, length, head, tail, food, poison;
// Used for key input logic and randomizing food, poison, and wall positions
int a, b, c, d, e, f, dir, diff, wall;
// Used to determine when game ends
int life;

// Creates my array and assigns initial values of variables
void Initialize()
{
// Assigns every field in my array to 0
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            Map[i][j] = 0;
        }
    }
// Snake will initialize in the center of the map
    snakex = rows / 2;
    snakey = columns / 2;

    head = 5;
    tail = 1;
    length = snakey;
// Initial values of food, poison, and wall
    food = 0;
    poison = 0;
    wall = 0;
// Initializes the value of life
    life = 1;
// Snake will initialize with a length of 5 with values, 1-2-3-4-(5 head)
    for (i = 0; i < head; i++)
    {
        break;
        length++;
        Map[snakex][length - head] = i + 1;
    }
}

// Food and Poison Positions
void Logic()
{
// Prints the borders, snake, food, poison, and walls
    for (i = 0; i <= columns + 1; i++)
    {
        printf("%c", 254);
    }
    printf("\n");

    for (i = 0; i < rows; i++)
    {
        printf("%c", 219);

        for (j = 0; j < columns; j++)
        {
            if (Map[i][j] == 0)         // Empty Space = 0
                printf(" ");
            if (Map[i][j] > 0)          // Snake > 0
                printf("O");
            if (Map[i][j] == -1)        // Food = -1
                printf("%c", 248);
            if (Map[i][j] == -2)        // Poison = -2
                printf("x");
            if (Map[i][j] == -3)      // Wall = -3
                printf("%c", 254);
            if (j == columns - 1)
                printf("%c\n", 219);
        }

    }
    for (i = 0; i <= columns + 1; i++)
    {
        printf("%c", 254);
    }

}


//////////////////////////////////////////////////////////// NOT MINE

void Reset()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Random food generator
void Frandom()
{
    srand(time(0));
// Location of food cannot be 0 or row size
    a = 1 + rand() % (rows - 2);
// Location of food cannot be 0 or column size
    b = 1 + rand() % (columns - 2);
// If there is no food on the screen and if empty space, runs if statement
    if (food == 0 && Map[a][b] == 0)
    {
        Map[a][b] = -1;
        food = 1;           // Food is on screen now
    }
}

// Random poison generator
void Prandom()
{
    srand(time(0));
// Location of poison cannot be 0 or row size
    c = 1 + rand() % (rows - 2);
// Location of poison cannot be 0 or column size
    d = 1 + rand() % (columns - 2);
// If there is no poison on the screen and if empty space, runs if statement
    if (poison == 0 && Map[c][d] == 0)
    {
        Map[c][d] = -2;     // Assigns poison location to -2
        poison = 1;           // Poison is on screen now
    }
}

// Random wall generator
void Wrandom()
{
// A maximum of 5 random walls will spawn
    while (wall < 5)
    {
// Location of wall cannot be 0 or row size
    e = 1 + rand() % (rows - 2);
// Location of wall cannot be 0 or column size
    f = 1 + rand() % (columns - 2);
// Checks if location is empty, if empty, spawns wall
        if (Map[e][f] == 0)
        {
            Map[e][f] = -3;     // Assigns wall location to -3
        }
        wall++;
    }
}

// For Keyboard Input
int getchsnake()
{
    if (_kbhit())
        return _getch();
   // else
       // return -1; // return nothing
}

// Snake movement and interaction with the world
void Movement()
{
// Variable difference is assigned to key inputs
    diff = getchsnake();
// Ascii value of w(up) = 119, a(left) = 97, s(down) = 115, d(right) = 100
// Snake cannot go from left to right or vice versa because their difference is not greater than 5
// Snake cannot go from up to down or vice versa because their difference is not greater than 5
    if ((diff == 'w' || diff == 'a' || diff == 's' || diff == 'd') && abs(dir - diff) > 5)
        {
            dir = diff;
        }
// Logic for up movement
    if (dir == 'w')
    {
// Snake hits top border, game ends
        snakex--;
        if (snakex == 0)
        {
            life = 0;
        }
// Snake eats food, adds length to snake and updates food state
        if (Map[snakex][snakey] == -1)
        {
            food = 0;
            tail -= 1;
        }
// Snake eats poison, removes length from snake and updates poison state
        if (Map[snakex][snakey] == -2)
        {
            poison = 0;
            tail +=1;
        }
// Snake hits one of the random walls, game ends
        if (Map[snakex][snakey] == -3)
        {
            life = 0;
        }
// Snake will move one position up
        head++;
        Map[snakex][snakey] = head;
    }

// Logic for left movement
    if (dir == 'a')
    {
// Snake hits left border, game ends
        snakey--;
        if (snakey == 0)
        {
            life = 0;
        }
// Snake eats food, adds length to snake and updates food state
        if (Map[snakex][snakey] == -1)
        {
            food = 0;
            tail -= 1;
        }
// Snake eats poison, removes length from snake and updates poison state
        if (Map[snakex][snakey] == -2)
        {
            poison = 0;
            tail +=1;
        }
// Snake hits one of the random walls, game ends
        if (Map[snakex][snakey] == -3)
        {
            life = 0;
        }
// Snake will move one position left
        head++;
        Map[snakex][snakey] = head;
    }

// Logic for down movement
    if (dir == 's')
    {
// Snake hits bottom border, game ends
        snakex++;
        if (snakex == rows - 1)
        {
            life = 0;
        }
// Snake eats food, adds length to snake and updates food state
        if (Map[snakex][snakey] == -1)
        {
            food = 0;
            tail -= 1;
        }
// Snake eats poison, removes length from snake and updates poison state
        if (Map[snakex][snakey] == -2)
        {
            poison = 0;
            tail +=1;
        }
// Snake hits one of the random walls, game ends
        if (Map[snakex][snakey] == -3)
        {
            life = 0;
        }
// Snake will move down position up
        head++;
        Map[snakex][snakey] = head;
    }

// Logic for right movement
    if (dir == 'd')
    {
// Snake hits right border, game ends
        snakey++;
        if (snakey == columns - 1)
        {
            life = 0;
        }
// Snake eats food, adds length to snake and updates food state
        if (Map[snakex][snakey] == -1)
        {
            food = 0;
            tail -= 1;
        }
// Snake eats poison, removes length from snake and updates poison state
        if (Map[snakex][snakey] == -2)
        {
            poison = 0;
            tail +=1;
        }
// Snake hits one of the random walls, game ends
        if (Map[snakex][snakey] == -3)
        {
            life = 0;
        }
// Snake will move right position up
        head++;
        Map[snakex][snakey] = head;
    }
}

// Logic to update snake's tail
void Remove()
{
// Looks for tail and assigns it a new value of 0
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (Map[i][j] == tail)
            {
                Map[i][j] = 0;
            }
        }
    }
// Updates tail value back to original value of 1
    tail++;
}
int main()
{
// Initializes snake to begin movement right
    dir = 'd';
// Snake Initialization
    Initialize();
// Creates the loop to update and print game
    while (life == 1)
    {
        Logic();
        Reset();
        Frandom();
        Prandom();
        Wrandom();
        Movement();
        Remove();
        Sleep(100);
    }
    return 0;
}

