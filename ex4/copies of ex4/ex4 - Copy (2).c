/******************
Name: Elad Cohen
ID: 331526079
Assignment: ex4
*******************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_CHEERLEADER_ROWS 5
#define NUM_OF_CHEERLEADER_COLS 5
#define SIZE 20

// Declaring functions
void task1RobotPaths();

void task2HumanPyramid();

void task3ParenthesisValidator();

void task4QueensBattle();

void task5CrosswordGenerator();

float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column);

int findPath(int column, int row);

int isParValid(char lastPar, int counter);

char oppositePar(char parenthesis);

int isQueensSolvable(char queensArr[SIZE][SIZE], int dimension, int queensCounter, int x, int y, char zonesTaken[]);

char getAndCheckPoint(char queensArr[][SIZE], int dimension, int x, int y);

void setZone(char zonesTaken[], int dimension, char zone);

void unsetZone(char zonesTaken[], int dimension, char zone);

int isPlaceValid(char queensArr[SIZE][SIZE], int dimension, int x, int y);

void setQueen(char queensArr[][SIZE], int x, int y);

void unsetQueen(char queensArr[][SIZE], int x, int y, char zone);

int isBoardValid(char queensArr[][SIZE], int dimension, int x, int y, char zonesTaken[], char zone);

int isDiagonalValid(char queensArr[][SIZE], int dimension, int x, int y);

// main func
int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
            "1. Robot Paths\n"
            "2. The Human Pyramid\n"
            "3. Parenthesis Validation\n"
            "4. Queens Battle\n"
            "5. Crossword Generator\n"
            "6. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
                case 6:
                    printf("Goodbye!\n");
                    break;
                case 1:
                    task1RobotPaths();
                    break;
                case 2:
                    task2HumanPyramid();
                    break;
                case 3:
                    task3ParenthesisValidator();
                    break;
                case 4:
                    task4QueensBattle();
                    break;
                case 5:
                    task5CrosswordGenerator();
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s");
        }
    } while (task != 6);
}

void task1RobotPaths() {
    int row, coloumn;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &coloumn, &row);

    printf("The total number of paths the robot can take to reach home is: ");
    int numOfPaths = findPath(coloumn, row);
    printf("%d\n", numOfPaths);
}

void task2HumanPyramid() {
    //check if i can do loop to make all -1 or its against the rules
    float weights[NUM_OF_CHEERLEADER_ROWS][NUM_OF_CHEERLEADER_COLS];
    for (int i = 0; i < NUM_OF_CHEERLEADER_ROWS; i++) {
        for (int j = 0; j < NUM_OF_CHEERLEADER_COLS; j++) {
            weights[i][j] = -1.0;
        }
    }
    int isValid = 0;
    while (!isValid) {
        printf("Please enter the weights of the cheerleaders:\n");
        for (int i = 0; i < NUM_OF_CHEERLEADER_ROWS; i++) {
            for (int j = 0; j < NUM_OF_CHEERLEADER_COLS; j++) {
                if (j > i) {
                    weights[i][j] = -1.0;
                    continue;
                }
                if (scanf("%f", &weights[i][j]) == 1) {
                    if (weights[i][j] < 0.0) {
                        printf("Negative weights are not supported.\n");
                        return;
                    }
                }
                isValid = 1;
            }
        }
    }
    printf("The total weight on each cheerleader is:\n");

    for (int i = 0; i < NUM_OF_CHEERLEADER_ROWS; i++) {
        for (int j = 0; j <= i; j++) {
            float totalWeight = calcWeightsAbove(weights, i, j);
            printf("%.2f ", totalWeight);
        }
        printf("\n");
    }
}

void task3ParenthesisValidator() {
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
    }

    printf("Please enter a term for validation:\n");

    char newChar = '\0';
    int counter = 0;

    int isQueensValid = isParValid(newChar, counter);

    if (isQueensValid) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

void task4QueensBattle() {
    char queensArr[SIZE][SIZE] = {0};

    int dimension;

    printf("Please enter the board dimensions:\n");
    scanf(" %d", &dimension);

    // Clear the buffer
    char c, value;
    while (scanf("%c", &c) == 1 && c != '\n') {
    }
    printf("Please enter a %d*%d puzzle board:\n", dimension, dimension);

    // Set all values to the array, in its size
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            scanf(" %c", &value);
            queensArr[i][j] = value;
        }
    }

    char zonesTaken[SIZE] = {'\0'};
    int startRow = 0, startCol = 0, isPossible = 0, queensCounter = 0;

    isPossible = isQueensSolvable(queensArr, dimension, queensCounter, startRow, startCol, zonesTaken);

    if (isPossible) {
        printf("Solution:\n");

        // Print the solution
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (queensArr[i][j] == '-') {
                    queensArr[i][j] = 'X';
                }
                if (queensArr[i][j] != '\0') {
                    printf("%c ", queensArr[i][j]);
                }
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }


    printf("\n");
}

void task5CrosswordGenerator() {
    // Todo
}

int findPath(int column, int row) {
    if (column < 0 || row < 0) {
        return 0;
    }

    /* return 1 if the row/column are 0
    because is means there is only way to get to (0,0) from there */
    if (row == 0 || column == 0) {
        return 1;
    }
    return findPath(column - 1, row) + findPath(column, row - 1);
}

float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column) {
    if (weights[row][column] == -1 || row < 0 || column < 0) {
        return 0.0;
    }
    return weights[row][column]
           + (calcWeightsAbove(weights, row - 1, column) / 2.0)
           + (calcWeightsAbove(weights, row - 1, column - 1) / 2.0);
}

int isParValid(char lastPar, int counter) {
    int isValid;
    char newPar;
    scanf("%c", &newPar);
    if (newPar == '\n') {
        if (counter == 0) {
            return 1;
        }
        return 0;
    }
    if (newPar == '{'
        || newPar == '('
        || newPar == '['
        || newPar == '<') {
        isValid = isParValid(newPar, counter + 1);
        if (!isValid) {
            return isValid;
        }
    }

    // If it's a closing parenthesis, check for matching opening one
    if (newPar == '}' || newPar == ')' || newPar == ']' || newPar == '>') {
        if (counter == 0 || oppositePar(lastPar) != newPar) {
            char c;
            while (scanf("%c", &c) == 1 && c != '\n') {
            }
            return 0; // unmatched closing parenthesis
        }
        return 1; // Valid match
    }
    return isParValid(lastPar, counter);
}

char oppositePar(char parenthesis) {
    if (parenthesis == '(') {
        return ')';
    }
    if (parenthesis == '{') {
        return '}';
    }
    if (parenthesis == '[') {
        return ']';
    }
    if (parenthesis == '<') {
        return '>';
    }
    return parenthesis;
}

int isQueensSolvable(char queensArr[][SIZE], int dimension, int queensCounter, int x, int y, char zonesTaken[]) {

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%c ", queensArr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int firstCol = 0;
    char zone = getAndCheckPoint(queensArr, dimension, x, y);
    if (!((zone >= 'A' && zone <= 'Z') || (zone >= 'a' && zone <= 'z'))) {
        return 0; // Return 0 if zone is not in A-Z or a-z
    }


    setZone(zonesTaken, dimension, zone);
    setQueen(queensArr, x, y);

    // Check if the current position is valid
    if (!isBoardValid(queensArr, dimension, x, y, zonesTaken, zone)) {
        return 0;
    }

    if (queensCounter == dimension) {
        return 1; // We've solved the puzzle!
    }

    // Should do solve for all 40! not just first 1
    // if I can mention all cases it would work worked

    // if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 1, y, zonesTaken)) return 1;
    // if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 1, zonesTaken)) return 1;

    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 0, 0, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 0, 1, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 0, 2, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 0, 3, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 1, 0, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 1, 1, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 1, 2, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 0, 3, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 2, 0, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 2, 1, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 2, 2, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 2, 3, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 3, 0, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 3, 1, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 3, 2, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, 3, 3, zonesTaken)) return 1;


    /* if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 1, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 2, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 3, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 4, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 5, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 6, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 7, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 8, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, x + 9, y, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 1, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 2, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 3, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 4, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 5, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 6, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 7, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 8, zonesTaken)) return 1;
    if (isQueensSolvable(queensArr, dimension, queensCounter + 1, firstCol, y + 9, zonesTaken)) return 1; */

    unsetZone(zonesTaken, dimension, zone);
    unsetQueen(queensArr, x, y, zone);


    return 0; // problem here
}

char getAndCheckPoint(char queensArr[][SIZE], int dimension, int x, int y) {
    // Check if the point is out of bound, or if a queen is there
    char point = queensArr[y][x];
    if (x < 0 || x >= dimension
        || y < 0 || y >= dimension
        || point == '\0'
        || point == '-'
        || point == '*') {
        return '*';
    }
    return point;
}

void setZone(char zonesTaken[], int dimension, char zone) {
    if (zone >= 'a' && zone <= 'z') {
        /*
        'a' to 'z' have ASCII values from 97 to 122.
        'A' to 'Z' have ASCII values from 65 to 90.
        so, to convert from lower to upper case, we add the distance from 'A' to 'a'
        */
        zone += 'A' - 'a';
    }
    for (int i = 0; i < dimension; i++) {
        if (zonesTaken[i] == '\0') {
            zonesTaken[i] = zone;
            return;
        }
    }
}

// unsets the last zone
void unsetZone(char zonesTaken[], int dimension, char zone) {
    for (int i = 0; i < dimension; i++) {
        if (zonesTaken[i] == '\0') {
            zonesTaken[i - 1] = '\0';
            return;
        }
    }
    zonesTaken[dimension - 1] = '\0';
}

void setQueen(char queensArr[][SIZE], int x, int y) {
    queensArr[y][x] = '-';
}

void unsetQueen(char queensArr[][SIZE], int x, int y, char zone) {
    queensArr[y][x] = zone;
}

// Checks if the last queen keeps the board valid
int isBoardValid(char queensArr[][SIZE], int dimension, int x, int y, char zonesTaken[], char zone) {

    // Return 0 if there are any queens in the same row as the last
    for (int i = 0; i < dimension; i++) {
        if ((queensArr[y][i] == '-') && (i != x)) {
            return 0;
        }
    }

    // Return 0 if there are any queens in the same col as the last
    for (int i = 0; i < dimension; i++) {
        if ((queensArr[i][x] == '-') && (i != y)) {
            return 0;
        }
    }

    /*
    Checks if the diagonal is in bound and not a queen
    can check only diagonal because the row and col are clear
    */
    if (!isDiagonalValid(queensArr, dimension, x, y)) {
        return 0;
    }

    // Return 0 if there are two queens in the same zone
    int countSameZones = 0;
    for (int i = 0; i < dimension; i++) {
        if (zonesTaken[i] == zone) {
            countSameZones ++;
        }
        if (countSameZones >= 2) {
            return 0;
        }
    }
    return 1; // Returns true if nothing is wrong
}

// Check if diagonal is within bound and not a queen
int isDiagonalValid(char queensArr[][SIZE], int dimension, int x, int y) {
    if (x + 1 < dimension && y + 1 < dimension
        && queensArr[x + 1][y + 1] == 'X') {
        return 0;
    }

    if (x - 1 > 0 && y + 1 < dimension
        && queensArr[x - 1][y + 1] == 'X') {
        return 0;
    }

    if (x + 1 < dimension && y - 1 > 0
        && queensArr[x + 1][y - 1] == 'X') {
        return 0;
    }

    if (x - 1 > 0 && y - 1 > 0
        && queensArr[x - 1][y - 1] == 'X') {
        return 0;
    }

    return 1;
}
