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
#define QUEEN_BOARD_SIZE 20
#define CROSSWORD_BOARD_SIZE 30
#define NUM_OF_SLOTS 100
#define NUM_OF_WORDS 100
#define MAX_WORD_LENGTH 16
#define NUM_OF_VARIABLES 4

// Declaring functions
void task1RobotPaths();

void task2HumanPyramid();

// Set all the weights to '-1.0'
void setWeights(float weights[][NUM_OF_CHEERLEADER_COLS],
    int numOfCheerleaderRows, int numOfCheerleaderCols, int row, int col);

void task3ParenthesisValidator();

void task4QueensBattle();

void task5CrosswordGenerator();

// Fills the whole grid with '#'
void fillGridWithHashtag(char grid[][CROSSWORD_BOARD_SIZE], int gridSize, int i, int j);

// Set the grid with the structure '_' where slots need to be
void setGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],char orientationArray[],
    int slotLengths[], int numOfSlots, int currentSlot, int currentLengthIndex);

// Set the word lengths to the array
void setWordsLengths(char words[][MAX_WORD_LENGTH], int wordsLengths[], int numOfWords, int index);

// Task 1: Calculates the number of possible paths from a given point to (0,0)
int findPath(int column, int row);

// Task 2: Calculates the total weight supported by a cheerleader at a specific position
float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column);

// Task 3: Validates if a string of parentheses is balanced correctly
int isParValid(char lastPar, int counter);

// Returns the opposite parenthesis for a given character
char oppositePar(char parenthesis);

// Clears the buffer until '\n'
void clearBufferEnter();

// Clears the buffer until '\n' or ' '
void clearBufferSpaceAndEnter();

// Task 4: Checks if a Queens puzzle board is solvable
int isQueensSolvable(char queensArr[][QUEEN_BOARD_SIZE],
    int dimension, int queensCounter, char zonesTaken[], int row, int col);

// Checks if the last queen keeps the board valid
int isBoardValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, char zonesTaken[]);

// Checks if there are queens in the same row as the new queen
int checkRow(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentCol);

// Checks if there are queens in the same col as the new queen
int checkCol(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentRow);

// Checks if there are queens in the same zone as the new queen
int checkZone(char zonesTaken[], int dimension, char zone, int currentIndex);

// Check if diagonal is within bound and not a queen
int isDiagonalValid(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col);

// Task 5: Determines if a crossword puzzle is solvable
int IsCrosswordSolvable(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],
    int slotLengths[], char orientationArray[], char words[][MAX_WORD_LENGTH],
    int wordsUsed[], int wordsLengths[], int slotsCounter, int gridSize, int numOfSlots,
    int numOfWords, int wordsCounter);

// Checks if a word fits in a specific slot in the crossword grid
int isWordValid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter);

// Copies a 2D char array to another array
void copy2DArrayChar(char grid[][CROSSWORD_BOARD_SIZE], char tempGrid[][CROSSWORD_BOARD_SIZE],
    int row, int col, int gridSize);

// Copies a 1D int array to another array
void copyArrInt(int wordsUsed[], int tempWordsUsed[], int index, int gridSize);

// Inserts a word into the crossword grid at the specific slot
void insertWordToGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter);

// Prints a 2D crossword grid
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

// Implementing tasks

// Task 1: Robot Paths
// Asks the user for coordinates and calculates the number of paths
void task1RobotPaths() {
    int row, col;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &col, &row);

    printf("The total number of paths the robot can take to reach home is: ");
    int numOfPaths = findPath(col, row);
    printf("%d\n", numOfPaths);
}

// Task 2: Human Pyramid
// Asks the user for weights of cheerleaders and calculates total weight on each cheerleader
void task2HumanPyramid() {
    int startingIndex = 0;
    // Set all weights to -1
    float weights[NUM_OF_CHEERLEADER_ROWS][NUM_OF_CHEERLEADER_COLS];

    // Set all weights to '-1'
    setWeights(weights, NUM_OF_CHEERLEADER_ROWS,
        NUM_OF_CHEERLEADER_COLS, startingIndex, startingIndex);

    // Gets and check cheerleader weights
    int isValid = 0;
    while (!isValid) {
        printf("Please enter the weights of the cheerleaders:\n");
        for (int i = 0; i < NUM_OF_CHEERLEADER_ROWS; i++) {
            for (int j = 0; j < NUM_OF_CHEERLEADER_COLS; j++) {
                if (j > i) {
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

    // Calculates and prints weight on each cheerleader
    for (int i = 0; i < NUM_OF_CHEERLEADER_ROWS; i++) {
        for (int j = 0; j <= i; j++) {
            float totalWeight = calcWeightsAbove(weights, i, j);
            printf("%.2f ", totalWeight);
        }
        printf("\n");
    }
}

// Set all the weights to '-1.0'
void setWeights(float weights[][NUM_OF_CHEERLEADER_COLS],
    int numOfCheerleaderRows, int numOfCheerleaderCols, int row, int col) {
    int startingIndex = 0;
    if (row >= numOfCheerleaderRows) {
        return; // Return when finished all rows
    }

    if (col >= numOfCheerleaderCols) {
        // Move to the next row and reset column index
        setWeights(weights, numOfCheerleaderRows, numOfCheerleaderCols, row + 1, startingIndex);
        return;
    }

    // Set the current cell to -1.0
    weights[row][col] = (float)-1.0;

    // Move to the next col in the same row
    setWeights(weights, numOfCheerleaderRows, numOfCheerleaderCols, row, col + 1);
}

// Task 3: Parenthesis Validator
// Asks the user for a string and checks if parentheses are balanced
void task3ParenthesisValidator() {
    // Clear the buffer
    clearBufferSpaceAndEnter();
    printf("Please enter a term for validation:\n");

    char newChar = '\0';
    int counter = 0;
    // Calls the recursion func
    int isStringValid = isParValid(newChar, counter);

    if (isStringValid) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

// Task 4: Queens Battle
// Prompts the user for a Queens puzzle board and checks if it's solvable
void task4QueensBattle() {
    int startingIndex = 0, queensCounter = 0;
    char zonesTaken[QUEEN_BOARD_SIZE] = {'\0'};
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

    int isPossible = isQueensSolvable(queensArr, dimension, queensCounter,
        zonesTaken, startingIndex, startingIndex);

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
    printf("\n");
}

// Task 5: Crossword Generator
// Prompts the user for crossword details and attempts to generate a solution
void task5CrosswordGenerator() {
    // Define all necessary arrays and values
    int gridSize, numOfSlots, numOfWords, slotsCounter = 0, wordsCounter = 0, startingIndex = 0;
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
    fillGridWithHashtag(grid, CROSSWORD_BOARD_SIZE, startingIndex, startingIndex);

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

    // Set the grid with the structure '_' where slots need to be
    setGrid(grid, xCoords, yCoords, orientationArray, slotLengths, numOfSlots, startingIndex, startingIndex);

    printf("Please enter the number of words in the dictionary:\n");
    scanf(" %d", &numOfWords);

    // Validating numOfWords is valid
    while (numOfWords < numOfSlots) {
        printf("The dictionary must contain at least %d words. ", numOfSlots);
        printf("Please enter a valid dictionary size:\n");
        scanf(" %d", &numOfWords);
    }

    printf("Please enter the words for the dictionary:\n");
    // Insert the words to the words array
    for (int i = 0; i < numOfWords; i++) {
        if (scanf("%15s", words[i]) != 1) {
        }
    }

    // Set the words length to the array
    setWordsLengths(words, wordsLengths, numOfWords, startingIndex);

    // Call the recursion
    int isBoardValid = IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths, orientationArray, words,
        wordsUsed, wordsLengths, slotsCounter, gridSize, numOfSlots, numOfWords, wordsCounter);
    if (!isBoardValid) {
        printf("This crossword cannot be solved.\n");
    }
}


// Fills the whole grid with '#'
void fillGridWithHashtag(char grid[][CROSSWORD_BOARD_SIZE], int gridSize, int i, int j) {
    int startingIndex = 0;
    if (i >= gridSize) {
        return; // Return when finished all rows
    }
    if (j >= gridSize) {
        fillGridWithHashtag(grid, gridSize, i + 1, startingIndex); // Move to the next row
        return;
    }

    grid[i][j] = '#'; // Set the current cell
    fillGridWithHashtag(grid, gridSize, i, j + 1); // Move to the next column in the same row
}

// Set the grid with the structure '_' where slots need to be
void setGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],char orientationArray[],
    int slotLengths[], int numOfSlots, int currentSlot, int currentLengthIndex) {
    int startingIndex = 0;
    if (currentSlot >= numOfSlots) {
        return; // Return when finished all slots
    }

    if (currentLengthIndex >= slotLengths[currentSlot]) {
        // Move to the next slot if the current one is completely finished
        setGrid(grid, xCoords, yCoords, orientationArray, slotLengths,
            numOfSlots, currentSlot + 1, startingIndex);
        return;
    }

    // Fill the grid for the current slot and index
    if (orientationArray[currentSlot] == 'H') {
        grid[xCoords[currentSlot]][yCoords[currentSlot] + currentLengthIndex] = '_';
    } else if (orientationArray[currentSlot] == 'V') {
        grid[xCoords[currentSlot] + currentLengthIndex][yCoords[currentSlot]] = '_';
    }

    // Continue with the next index of the current slot
    setGrid(grid, xCoords, yCoords, orientationArray, slotLengths,
        numOfSlots, currentSlot, currentLengthIndex + 1);
}

// Sets the lengths of the words to the array
void setWordsLengths(char words[][MAX_WORD_LENGTH], int wordsLengths[], int numOfWords, int index) {
    // Return when finished all words
    if (index >= numOfWords) {
        return;
    }

    wordsLengths[index] = (int)strlen(words[index]); // Set the length of the current word
    setWordsLengths(words, wordsLengths, numOfWords, index + 1); // Recursive call for the next word
}

// Task 1: Calculates the number of possible paths from a given point to (0,0)
int findPath(int column, int row) {
    // Return 0 if place is out of bound
    if (column < 0 || row < 0) {
        return 0;
    }

    // return 1 if the row/column are 0(one way left)
    if (row == 0 || column == 0) {
        return 1;
    }
    // Call the recursion with the next 2 possible places
    return findPath(column - 1, row) + findPath(column, row - 1);
}

// Task 2: Calculates the total weight supported by a cheerleader at a specific position
float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column) {
    // Return 0 if out of bound
    if (weights[row][column] == -1 || row < 0 || column < 0) {
        return (float)0.0f;
    }
    return weights[row][column]
           + (calcWeightsAbove(weights, row - 1, column) / (float)2.0)
           + (calcWeightsAbove(weights, row - 1, column - 1) / (float)2.0);
}

// Task 3: Validates if a string of parentheses is balanced correctly
int isParValid(char lastPar, int counter) {
    char newPar;
    // Get the next char
    scanf("%c", &newPar);
    if (newPar == '\n') {
        if (counter == 0) {
            return 1;
        }
        return 0;
    }

    // If open par, call the recursion with it
    if (newPar == '{' || newPar == '('
        || newPar == '[' || newPar == '<') {
        if (!isParValid(newPar, counter + 1)) {
            return 0;
        }
    }

    // If it's a closing par, check for matching opening one
    if (newPar == '}' || newPar == ')' || newPar == ']' || newPar == '>') {
        if (counter == 0 || oppositePar(lastPar) != newPar) {
            // Clear the buffer
            clearBufferEnter();
            return 0; // unmatched closing parenthesis
        }
        return 1; // Valid match
    }

    // Call the recursion to get the next char
    return isParValid(lastPar, counter);
}

// Returns the opposite parenthesis for a given character
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

// Clears the buffer until '\n'
void clearBufferEnter() {
    char c;
    if (scanf("%c", &c) == 1 && c != '\n') {
        clearBufferEnter(); // Clear the buffer until '\n'
    }
}

// Clears the buffer until '\n' or ' '
void clearBufferSpaceAndEnter() {
    char c;
    if (scanf("%c", &c) == 1 && c != '\n' && c != ' ') {
        clearBufferSpaceAndEnter(); // Clear the buffer until '\n' ot ' '
    }
}

// Task 4: Checks if a Queens puzzle board is solvable
int isQueensSolvable(char queensArr[][QUEEN_BOARD_SIZE], int dimension,
    int queensCounter, char zonesTaken[], int row, int col) {
    int startingIndex = 0;
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
        return isQueensSolvable(queensArr, dimension, queensCounter,
            zonesTaken, row + 1, startingIndex);
    }

    // Check if the queen placement is valid
    if (isBoardValid(queensArr, dimension, row, col, zonesTaken)) {

        // Set the queen and the zone
        char zone = queensArr[row][col];
        zonesTaken[queensCounter] = zone; // Set zone
        queensArr[row][col] = '-'; // Set queen

        // Try placing the next queen, starting from (0, 0)
        if (isQueensSolvable(queensArr, dimension, queensCounter + 1,
            zonesTaken, startingIndex, startingIndex)) {
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
int isBoardValid(char queensArr[][QUEEN_BOARD_SIZE],
    int dimension, int row, int col, char zonesTaken[]) {
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
    // Return 1 no point in row had a queen
    if (currentCol >= dimension) return 1;

    // Return 0 if there is a queen in the row
    if (currentCol != col && queensArr[row][currentCol] == '-') return 0;

    // Call the recursion with the next point
    return checkRow(queensArr, dimension, row, col, currentCol + 1);
}

// Checks if there are queens in the same col as the new queen
int checkCol(char queensArr[][QUEEN_BOARD_SIZE], int dimension, int row, int col, int currentRow) {
    // Return 1 no point in col had a queen
    if (currentRow >= dimension) return 1;

    // Return 0 if there is a queen in the col
    if (currentRow != row && queensArr[currentRow][col] == '-') return 0;

    // Call the recursion with the next point
    return checkCol(queensArr, dimension, row, col, currentRow + 1);
}

// Checks if there are queens in the same zone as the new queen
int checkZone(char zonesTaken[], int dimension, char zone, int currentIndex) {
    // Return 1 no point in zone had a queen
    if (currentIndex >= dimension) return 1;

    // Return 0 if there is a queen in the zone
    if (zonesTaken[currentIndex] == zone) return 0;

    // Call the recursion with the next point
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

// Task 5: Determines if a crossword puzzle is solvable
int IsCrosswordSolvable(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[], int yCoords[],
    int slotLengths[], char orientationArray[], char words[][MAX_WORD_LENGTH],
    int wordsUsed[], int wordsLengths[], int slotsCounter, int gridSize,
    int numOfSlots, int numOfWords, int wordsCounter) {

    int startingIndex = 0;

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
        orientationArray[slotsCounter], words, wordsCounter, slotsCounter, startingIndex);

    // If the word is not valid, call the recursion with the next word
    if (isWordAlreadyUsed || isWordLength || !isWordFitting) {
        return IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths,
        orientationArray, words, wordsUsed, wordsLengths, slotsCounter,
        gridSize, numOfSlots, numOfWords, wordsCounter + 1);
        }

    // Create new array to copy the grid into
    char tempGrid[CROSSWORD_BOARD_SIZE][CROSSWORD_BOARD_SIZE];
    // Create new array to copy the used words into
    int tempWordsUsed[NUM_OF_WORDS];

    // Copy current state into the new arrays
    copy2DArrayChar(grid, tempGrid, startingIndex, startingIndex, gridSize);
    copyArrInt(wordsUsed, tempWordsUsed, startingIndex,numOfWords);

    // Mark the current word as used
    tempWordsUsed[wordsCounter] = 1;

    // Insert the word into the grid
    insertWordToGrid(tempGrid, xCoords, yCoords, slotLengths[slotsCounter],
        orientationArray[slotsCounter], words, wordsCounter, slotsCounter, startingIndex);

    // If word fits, attempt recursion with updated state
    if (IsCrosswordSolvable(tempGrid, xCoords, yCoords, slotLengths,
            orientationArray, words, tempWordsUsed, wordsLengths,
            slotsCounter + 1, gridSize, numOfSlots, numOfWords, startingIndex)) {
        return 1;
            }

    // Reset state after recursion
    copy2DArrayChar(grid, tempGrid, startingIndex, startingIndex, gridSize);
    copyArrInt(wordsUsed, tempWordsUsed, startingIndex,numOfWords);

    // Try next word
    return IsCrosswordSolvable(grid, xCoords, yCoords, slotLengths,
            orientationArray, words, tempWordsUsed, wordsLengths,
            slotsCounter, gridSize, numOfSlots, numOfWords, wordsCounter + 1);
}

// Checks if a word fits in a specific slot in the crossword grid
int isWordValid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter) {
    // if none of the letters were wrong, return 1
    if (lettersCounter == slotLength) {
        return 1;
    }

    // Checks if in the next letter in the two words are the same, not including '_'
    if (orientation == 'H') {
        char newLetter = grid[xCoords[slotsCounter]][yCoords[slotsCounter] + lettersCounter];
        if (newLetter != '_') {
            if (newLetter != words[wordsCounter][lettersCounter]) {
                return 0;
            }
        }
    }

    // Checks if in the next letter in the two words are the same, not including '_'
    if (orientation == 'V') {
        char newLetter = grid[xCoords[slotsCounter] + lettersCounter][yCoords[slotsCounter]];
        if (newLetter != '_') {
            if (newLetter != words[wordsCounter][lettersCounter]) {
                return 0;
            }
        }
    }

    // Call the recursion with the next letter
    return isWordValid(grid, xCoords, yCoords, slotLength,
        orientation, words, wordsCounter, slotsCounter, lettersCounter + 1);
}

// Copies a 2D char array to another array
void copy2DArrayChar(char grid[][CROSSWORD_BOARD_SIZE],
    char tempGrid[][CROSSWORD_BOARD_SIZE], int row, int col, int gridSize) {
    if (row == gridSize) {
        return; // Base case: All rows copied
    }

    if (col == gridSize) {
        // End of the current row, move to the next row
        copy2DArrayChar(grid, tempGrid, row + 1, 0, gridSize);
        return;
    }

    // Copy the current element
    tempGrid[row][col] = grid[row][col];

    // Move to the next column
    copy2DArrayChar(grid, tempGrid, row, col + 1, gridSize);
}

// Copies a 1D int array to another array
void copyArrInt(int wordsUsed[], int tempWordsUsed[], int index, int gridSize) {
    if (index == gridSize) {
        return; // Base case: All rows copied
    }

    // Copy the current element
    tempWordsUsed[index] = wordsUsed[index];

    // Move to the next column
    copyArrInt(wordsUsed, tempWordsUsed, index + 1, gridSize);
}

// Inserts a word into the crossword grid at the specified slot
void insertWordToGrid(char grid[][CROSSWORD_BOARD_SIZE], int xCoords[],
    int yCoords[], int slotLength, char orientation, char words[][MAX_WORD_LENGTH],
    int wordsCounter, int slotsCounter, int lettersCounter) {

    // Returns when finished all letters
    if (lettersCounter == slotLength) {
        return;
    }

    // Inserts the next letter
    if (orientation == 'H') {
        grid[xCoords[slotsCounter]][yCoords[slotsCounter] + lettersCounter] =
            words[wordsCounter][lettersCounter];
    }

    // Inserts the next letter
    if (orientation == 'V') {
        grid[xCoords[slotsCounter] + lettersCounter][yCoords[slotsCounter]] =
            words[wordsCounter][lettersCounter];
    }

    // Call the recursion with the next letter
    insertWordToGrid(grid, xCoords, yCoords, slotLength, orientation,
        words, wordsCounter, slotsCounter, lettersCounter + 1);
}

// Prints a 2D crossword grid
void printCrossword(char newGrid[][CROSSWORD_BOARD_SIZE], int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // Print each cell with '|'
            printf("| %c ", newGrid[i][j]);
        }
        // Close the row and move to the next line
        printf("|\n");
    }
}