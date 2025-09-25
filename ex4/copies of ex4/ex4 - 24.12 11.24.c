/******************
Name: Elad Cohen
ID: 331526079
Assignment: ex4
*******************/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
//
#include <time.h>


#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_CHEERLEADER_ROWS 5
#define NUM_OF_CHEERLEADER_COLS 5
#define QUEEN_BOARD_SIZE 20
#define CROSSWORD_BOARD_SIZE 30
#define NUM_OF_SLOTS 100
#define NUM_OF_WORDS 100
#define MAX_WORD_LENGTH 16
#define NUM_OF_VARIABLES 4

// Declaring functions
void task1RobotPaths();

void task2HumanPyramid();

void task3ParenthesisValidator();

void task4QueensBattle();

void task5CrosswordGenerator();

int findPath(int column, int row);

float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column);

int isParValid(char lastPar, int counter);

char oppositePar(char parenthesis);

int isQueensSolvable(char queensArr[QUEEN_BOARD_SIZE][QUEEN_BOARD_SIZE], int dimension, int queensCounter, char zonesTaken[], int row, int col);

int checkRow(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentCol);

int checkCol(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentRow);

int checkZone(char zonesTaken[], int dimension, char zone, int currentIndex);

int isBoardValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, char zonesTaken[]);

int isDiagonalValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col);

int IsCrosswordSolvable(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],
    int slotLengths[], char orientationArray[], char words[][MAX_WORD_LENGTH],
    int wordsUsed[], int wordsLengths[], int slotsCounter, int gridSize, int numOfSlots,
    int numOfWords, int wordsCounter);

int isWordValid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter);


void copy2DArrayChar(char grid[][CROSSWORD_BOARD_SIZE], char newGrid[][CROSSWORD_BOARD_SIZE],
    int row, int col, int gridSize);

void copyArrInt(int wordsUsed[], int newWordsUsed[], int index, int gridSize);

void insertWordToGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter);

void printArr(char newGrid[][CROSSWORD_BOARD_SIZE], int gridSize, int row, int col);

void printCrossword(char newGrid[][CROSSWORD_BOARD_SIZE], int gridSize);

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

    int isStringValid = isParValid(newChar, counter);

    if (isStringValid) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

void task4QueensBattle() {
    char queensArr[QUEEN_BOARD_SIZE][QUEEN_BOARD_SIZE] = {0};

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

    char zonesTaken[QUEEN_BOARD_SIZE] = {'\0'};
    int startRow = 0, startCol = 0, isPossible = 0, queensCounter = 0;

    // Record the starting time
    clock_t start = clock();

    isPossible = isQueensSolvable(queensArr, dimension, queensCounter, zonesTaken, startRow, startCol);

    if (isPossible) {
        printf("Solution:\n");

        // Print the solution
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (queensArr[i][j] == '-') {
                    printf("X ");
                    continue;
                }
                if (queensArr[i][j] != '\0') {
                    printf("* ");
                }
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }

    // Record the ending time
    clock_t end = clock();

    // Calculate and display the elapsed time in seconds
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f seconds\n", elapsed_time);



    printf("\n");
}

void task5CrosswordGenerator() {

    int gridSize, numOfSlots, numOfWords, slotsCounter = 0, wordsCounter = 0;

    char grid[CROSSWORD_BOARD_SIZE][CROSSWORD_BOARD_SIZE] = {0}; // Defining the board
    int xCoords[NUM_OF_SLOTS] = {0};
    int yCoords[NUM_OF_SLOTS] = {0};
    int slotLengths[NUM_OF_SLOTS] = {0};
    char orientationArray[NUM_OF_SLOTS] = {0};

    // MAX_WORD_LENGTH = 16 so that each length is max 15 + '\0'
    char words[NUM_OF_WORDS][MAX_WORD_LENGTH] = {0};
    int wordsUsed[NUM_OF_WORDS] = {0};
    int wordsLengths[NUM_OF_WORDS] = {0};

    // Set to whole grid to '#'
    for (int i = 0; i < CROSSWORD_BOARD_SIZE; i++) {
        for (int j = 0; j < CROSSWORD_BOARD_SIZE; j++) {
            grid[i][j] = '#';
        }
    }

    printf("Please enter the dimensions of the crossword grid:\n");
    scanf(" %d", &gridSize); // 30 max

    printf("Please enter the number of slots in the crossword:\n");
    scanf(" %d", &numOfSlots); // 100 max

    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");

    // Inserting values to arrays
    for (int i = 0; i < numOfSlots; i++) {
        scanf(" %d", &xCoords[i]);
        scanf(" %d", &yCoords[i]);
        scanf(" %d", &slotLengths[i]);
        scanf(" %c", &orientationArray[i]);
    }

    // Set the grid with the structure '_' where words need to be
    for (int i = 0; i < numOfSlots; i++) {
        if (orientationArray[i] == 'H') {
            for (int j = 0; j < slotLengths[i]; j++) {
                grid[xCoords[i]][yCoords[i] + j] = '_';
            }
        }
        if (orientationArray[i] == 'V') {
            for (int j = 0; j < slotLengths[i]; j++) {
                grid[xCoords[i] + j][yCoords[i]] = '_';
            }
        }
    }

    printf("Please enter the number of words in the dictionary:\n");
    scanf(" %d", &numOfWords);

    // Validating numOfWordsDictionary is valid
    while (numOfWords < numOfSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numOfSlots);
        scanf(" %d", &numOfWords);
    }

    printf("Please enter the words for the dictionary:\n");

    for (int i = 0; i < numOfWords; i++) {
        if (scanf("%15s", words[i]) != 1) {
        }
    }

    for (int i = 0; i < numOfWords; i++) {
        wordsLengths[i] = strlen(words[i]); // Set the words length to the array
    }

    for (int i = 0; i < numOfWords; i++) {
        printf("%d\n", wordsLengths[i]);
    }

    int isBoardValid = IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths, orientationArray, words,
        wordsUsed, wordsLengths, slotsCounter, gridSize, numOfSlots, numOfWords, wordsCounter);
    if (!isBoardValid) {
        printf("This crossword cannot be solved.\n");
    }
}

int IsCrosswordSolvable(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],
    int slotLengths[], char orientationArray[], char words[][MAX_WORD_LENGTH],
    int wordsUsed[], int wordsLengths[], int slotsCounter, int gridSize,
    int numOfSlots, int numOfWords, int wordsCounter) {

    /*printf("WordCounter: %d\n", wordsCounter);
    printf("slotsCounter in the crossword is: %d\n", slotsCounter);
    printf("Next word: \n%s\n", words[wordsCounter]);
    printArr(grid, gridSize, 0, 0);

    for (int i = 0; i < numOfWords; i++) {
        printf("%d ", wordsUsed[i]);
    } */

    int startingIndex = 0, lettersCounter = 0;

    // If we've successfully placed words in all slots, return 1
    if (slotsCounter >= numOfSlots) {
        printCrossword(grid, gridSize);
        return 1;
    }

    // If we tried all the words, and none worked, Return 0
    if (wordsCounter >= numOfWords) {
        return 0;
    }

    // Check if the new word is valid in the slot
    int isWordAlreadyUsed = wordsUsed[wordsCounter] == 1;
    int isWordLength = wordsLengths[wordsCounter] != slotLengths[slotsCounter];
    int isWordFitting = isWordValid(grid, xCoords, yCoords, slotLengths[slotsCounter],
        orientationArray[slotsCounter], words, wordsCounter, slotsCounter, lettersCounter);

    // If the word is not valid, call the recursion with the next word
    if (isWordAlreadyUsed || isWordLength || !isWordFitting) {
        // printf("isWordAlreadyUsed = %d, isWordLength = %d, isWordMatch = %d\n", isWordAlreadyUsed, isWordLength, !isWordFitting);
        return IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths,
        orientationArray, words, wordsUsed, wordsLengths, slotsCounter,
        gridSize, numOfSlots, numOfWords, wordsCounter + 1);
        }


    char tempGrid[CROSSWORD_BOARD_SIZE][CROSSWORD_BOARD_SIZE];
    int tempWordUsed[NUM_OF_WORDS];
    // Copy current state into the new array
    copy2DArrayChar(grid, tempGrid, startingIndex, startingIndex, gridSize);
    copyArrInt(wordsUsed, tempWordUsed, startingIndex,numOfWords);

    // Mark the current word as used
    tempWordUsed[wordsCounter] = 1;

    // Insert the word into the grid
    insertWordToGrid(tempGrid, xCoords, yCoords, slotLengths[slotsCounter],
        orientationArray[slotsCounter], words, wordsCounter, slotsCounter, lettersCounter);

    /* printf("Original Grid:\n");
    printArr(grid, gridSize, startingIndex, startingIndex);
    printf("Copied Grid:\n");
    printArr(tempGrid, gridSize, 0, 0); */

    // If word fits, attempt recursion with updated state
    if (IsCrosswordSolvable(tempGrid, xCoords, yCoords, slotLengths,
            orientationArray, words, tempWordUsed, wordsLengths,
            slotsCounter + 1, gridSize, numOfSlots, numOfWords, 0)) {
        return 1;
            }

    /* printf("(Recurion failed - before setting)Original Grid:\n");
    printArr(grid, gridSize, 0, 0);
    printf("(Recurion failed - before setting)Copied Grid:\n");
    printArr(tempGrid, gridSize, 0, 0); */

    // Reset state after recursion
    copy2DArrayChar(grid, tempGrid, 0, 0, gridSize);
    copyArrInt(wordsUsed, tempWordUsed, startingIndex,numOfWords);

    /* printf("(Reucrion failed - after setting)Original Grid:\n");
    printArr(grid, gridSize, 0, 0);
    printf("(Reucrion failed - after setting)Copied Grid:\n");
    printArr(tempGrid, gridSize, 0, 0); */

    // Try next word
    return IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths,
            orientationArray, words, tempWordUsed, wordsLengths,
            slotsCounter, gridSize, numOfSlots, numOfWords, wordsCounter + 1);
}

// Checks if the new word doesnt overlap any existing word
int isWordValid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter) {

    // Checks if in the place where a letter should be, there is the same letter or _, and it returns 1 if true
    if (lettersCounter == slotLength) {
        // Make a func that prints the latest arr
        return 1;
    }

    if (orientation == 'H') {
        char newLetter = grid[xCoords[slotsCounter]][yCoords[slotsCounter] + lettersCounter];
        if (newLetter != '_') {
            if (newLetter != words[wordsCounter][lettersCounter]) {
                return 0;
            }
        }
    }

    if (orientation == 'V') {
        char newLetter = grid[xCoords[slotsCounter] + lettersCounter][yCoords[slotsCounter]];
        if (newLetter != '_') {
            if (newLetter != words[wordsCounter][lettersCounter]) {
                return 0;
            }
        }
    }

    return isWordValid(grid, xCoords, yCoords, slotLength,
        orientation, words, wordsCounter, slotsCounter, lettersCounter + 1);
}

// Coping grid into newGrid
void copy2DArrayChar(char grid[][CROSSWORD_BOARD_SIZE], char newGrid[][CROSSWORD_BOARD_SIZE], int row, int col, int gridSize) {
    if (row == gridSize) {
        return; // Base case: All rows copied
    }

    if (col == gridSize) {
        // End of the current row, move to the next row
        copy2DArrayChar(grid, newGrid, row + 1, 0, gridSize);
        return;
    }

    // Copy the current element
    newGrid[row][col] = grid[row][col];

    // Move to the next column
    copy2DArrayChar(grid, newGrid, row, col + 1, gridSize);
}

void copyArrInt(int wordsUsed[], int newWordsUsed[], int index, int gridSize) {
    if (index == gridSize) {
        return; // Base case: All rows copied
    }

    // Copy the current element
    newWordsUsed[index] = wordsUsed[index];

    // Move to the next column
    copyArrInt(wordsUsed, newWordsUsed, index + 1, gridSize);
}

void insertWordToGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter) {

    // Checks if in the place where a letter should be, there is the same letter or _, and it returns 1 if true
    if (lettersCounter == slotLength) {
        return;
    }
    if (orientation == 'H') {
        grid[xCoords[slotsCounter]][yCoords[slotsCounter] + lettersCounter] = words[wordsCounter][lettersCounter];
    }

    if (orientation == 'V') {
        grid[xCoords[slotsCounter] + lettersCounter][yCoords[slotsCounter]] = words[wordsCounter][lettersCounter];
    }

    insertWordToGrid(grid, xCoords, yCoords, slotLength, orientation, words, wordsCounter, slotsCounter, lettersCounter + 1);
}

void printCrossword(char newGrid[][CROSSWORD_BOARD_SIZE], int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // Print each cell enclosed with '|'
            printf("| %c ", newGrid[i][j]);
        }
        // Close the row and move to the next line
        printf("|\n");
    }
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

int isQueensSolvable(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int queensCounter, char zonesTaken[], int row, int col) {
    int firstCol = 0;
    int firstRow = 0;
    // Check If we've skipped the row without putting a queen
    if (queensCounter < row) {
        return 0;
    }

    // base: check if all queens are placed
    if (queensCounter == dimension) {
        return 1; // Puzzle solved
    }

    // if we've finished all rows, this state is not solvable
    if (row >= dimension) {
        return 0;
    }

    // If we've reached to the end of the row, move to the next col
    if (col >= dimension) {
        return isQueensSolvable(queensArr, dimension, queensCounter, zonesTaken, row + 1, firstCol);
    }

    // Check if the queen placement is valid
    if (isBoardValid(queensArr, dimension, row, col, zonesTaken)) {

        // Set the queen and the zone
        char zone = queensArr[row][col];
        zonesTaken[queensCounter] = zone; // Set zone
        queensArr[row][col] = '-'; // Set queen

        // Try placing the next queen, starting from (0, 0)
        if (isQueensSolvable(queensArr, dimension, queensCounter + 1, zonesTaken, firstRow, firstCol)) {
            return 1;
        }

        // unset zone the queen if the current placement is not valid
        zonesTaken[queensCounter] = '\0'; // Unset zone
        queensArr[row][col] = zone; // Unset queen
    }

    // call the recursion, with the next index in the row
    return isQueensSolvable(queensArr, dimension, queensCounter, zonesTaken, row, col + 1);
}

// Checks if the last queen keeps the board valid
int isBoardValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, char zonesTaken[]) {
    // Return false if zone is out of bound or a queen
    char zone = queensArr[row][col];
    if (col < 0 || col >= dimension
        || row < 0 || row >= dimension
        || zone == '\0'
        || zone == '-') {
        return 0;
        }
    int currentPosition = 0;
     /*
     * For the new queen, return 0 if:
     * there are queens in the same row
     * there are queens in the same column
     * there for queens in the same zone
     * there are queens in the same diagonal(touching)
     */
    return checkRow(queensArr, dimension, row, col, currentPosition) &&
           checkCol(queensArr, dimension, row, col, currentPosition) &&
           checkZone(zonesTaken, dimension, zone, currentPosition) &&
           isDiagonalValid(queensArr, dimension, row, col);
}

// Checks if there are queens in the same row as the new queen
int checkRow(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentCol) {
    if (currentCol >= dimension) return 1;
    if (currentCol != col && queensArr[row][currentCol] == '-') return 0;
    return checkRow(queensArr, dimension, row, col, currentCol + 1);
}

// Checks if there are queens in the same col as the new queen
int checkCol(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentRow) {
    if (currentRow >= dimension) return 1;
    if (currentRow != row && queensArr[currentRow][col] == '-') return 0;
    return checkCol(queensArr, dimension, row, col, currentRow + 1);
}

// Checks if there are queens in the same zone as the new queen
int checkZone(char zonesTaken[], int dimension, char zone, int currentIndex) {
    if (currentIndex >= dimension) return 1;
    if (zonesTaken[currentIndex] == zone) return 0;
    return checkZone(zonesTaken, dimension, zone, currentIndex + 1);
}

// Check if diagonal is within bound and not a queen
int isDiagonalValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col) {
    if (col + 1 < dimension && row + 1 < dimension
        && queensArr[row + 1][col + 1] == '-') {
        return 0;
    }

    if (col + 1 < dimension && row - 1 >= 0
        && queensArr[row - 1][col + 1] == '-') {
        return 0;
    }

    if (col - 1 >= 0 && row + 1 < dimension
        && queensArr[row + 1][col - 1] == '-') {
        return 0;
    }

    if (col - 1 >= 0 && row - 1 >= 0
        && queensArr[row - 1][col - 1] == '-') {
        return 0;
    }

    return 1;
}