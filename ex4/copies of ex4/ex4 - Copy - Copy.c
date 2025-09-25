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


void task1RobotPaths();

void task2HumanPyramid();

void task3ParenthesisValidator();

void task4QueensBattle();

void task5CrosswordGenerator();

float calcWeightsAbove(float weights[][NUM_OF_CHEERLEADER_COLS], int row, int column);

int findPath(int column, int row);

int isParValid(char newTerm, int counter);

char oppositePar(char parenthesis);

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

    int isValid = isParValid(newChar, counter);

    if (isValid) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

void task4QueensBattle() {
    // Todo
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


// {............{..........}..............}....{

// {[...............]<............>}.............{}

int isParValid(char lastPar, int counter) {
    int isValid;
    char newPar;
    scanf("%c", &newPar);
    while (newPar != '\n') {
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

        scanf("%c", &newPar);
    }
    // if user pressed enter, check if the string is valid
    if (newPar == '\n') {
        if (counter == 0) {
            return 1;
        }
        return 0;
    }
    return 0; // Shouldn't reach here, just in case
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
}

/*
*int isParValid(char lastPar, int counter) {
    int isValid;
    char newPar;
    scanf("%c", &newPar);

    // if user pressed enter, check if the string is valid
    if (newPar == '\n') {
        return counter == 0;
    }

    // Ignore invalid characters
    if (newPar != '{' && newPar != '}' && newPar != '(' && newPar != ')'
        && newPar != '[' && newPar != ']' && newPar != '<' && newPar != '>') {
        return isParValid(lastPar, counter);
        }

    if (newPar == '{'
        || newPar == '('
        || newPar == '['
        || newPar == '<') {
        isValid = isParValid(newPar, counter + 1);
        if (!isValid) {
            char c;
            while (scanf("%c", &c) == 1 && c != '\n') {
            }
            return isValid;
        }
        if (isValid) {
            return isParValid(lastPar, counter);
        }
        /* if (counter != 0)  {
            return isParValid(lastPar, counter);
        }
        else {
            return isParValid(lastPar, counter);
        }
    }

// If it's a closing parenthesis, check for matching opening one
if (newPar == '}' || newPar == ')' || newPar == ']' || newPar == '>') {
    if (counter == 0 || oppositePar(lastPar) != newPar) {
        return 0; // unmatched closing parenthesis
    }
    return 1; // Valid match
}

return 0; // Shouldn't reach here, just in case
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
} */
