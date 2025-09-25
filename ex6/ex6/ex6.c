/********************
* Name: Elad
 * ID: 331526079
 * Assignment: ex6
 ********************/

#include "ex6.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define INT_BUFFER 128

// ================================================
// Basic struct definitions from ex6.h assumed:
//   PokemonData { int id; char *name; PokemonType TYPE; int hp; int attack; EvolutionStatus CAN_EVOLVE; }
//   PokemonNode { PokemonData* data; PokemonNode* left, *right; }
//   OwnerNode   { char* ownerName; PokemonNode* pokedexRoot; OwnerNode *next, *prev; }
//   OwnerNode* ownerHead;
//   const PokemonData pokedex[];
// ================================================

// --------------------------------------------------------------
// 1) Safe integer reading
// --------------------------------------------------------------

// Remove leading/trailing whitespace (including '\r')
void trimWhitespace(char *str) {
    // Remove leading spaces/tabs/\r
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;

    if (start > 0) {
        int idx = 0;
        while (str[start])
            str[idx++] = str[start++];
        str[idx] = '\0';
    }

    // Remove trailing spaces/tabs/\r
    int len = (int) strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}

// Read an integer safely, re-prompt if invalid.
int readIntSafe(const char *prompt) {
    char buffer[INT_BUFFER];
    int value;
    int success = 0;

    while (!success) {
        printf("%s", prompt);

        // If we fail to read, treat it as invalid
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Invalid input.\n");
            clearerr(stdin);
            continue;
        }

        // 1) Strip any trailing \r or \n
        //    so "123\r\n" becomes "123"
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';
        if (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
            buffer[--len] = '\0';

        // 2) Check if empty after stripping
        if (len == 0) {
            printf("Invalid input.\n");
            continue;
        }

        // 3) Attempt to parse integer with strtol
        char *endptr;
        value = (int) strtol(buffer, &endptr, 10);

        // If endptr didn't point to the end => leftover chars => invalid
        // or if buffer was something non-numeric
        if (*endptr != '\0') {
            printf("Invalid input.\n");
        } else {
            // We got a valid integer
            success = 1;
        }
    }
    return value;
}

// --------------------------------------------------------------
// Utility: getDynamicInput (for reading a line into malloc'd memory)
// --------------------------------------------------------------
char *getDynamicInput() {
    char *input = NULL;
    size_t size = 0, capacity = 1; // Start with an initial size and capacity
    input = (char *) malloc(capacity);
    if (!input) {
        printf("malloc falied.\n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (size + 1 >= capacity) {
            capacity *= 2;
            char *temp = (char *) realloc(input, capacity);
            if (!temp) {
                printf("malloc failed.\n");
                free(input);
                return NULL;
            }
            input = temp;
        }
        input[size++] = (char) c;
    }
    input[size] = '\0';

    // Trim any leading/trailing whitespace or carriage returns
    trimWhitespace(input);

    return input;
}

// --------------------------------------------------------------
// 2) Utility: Get type name from enum
// --------------------------------------------------------------
const char *getTypeName(PokemonType type) {
    switch (type) {
        case GRASS:
            return "GRASS";
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case BUG:
            return "BUG";
        case NORMAL:
            return "NORMAL";
        case POISON:
            return "POISON";
        case ELECTRIC:
            return "ELECTRIC";
        case GROUND:
            return "GROUND";
        case FAIRY:
            return "FAIRY";
        case FIGHTING:
            return "FIGHTING";
        case PSYCHIC:
            return "PSYCHIC";
        case ROCK:
            return "ROCK";
        case GHOST:
            return "GHOST";
        case DRAGON:
            return "DRAGON";
        case ICE:
            return "ICE";
        default:
            return "UNKNOWN";
    }
}

// A function that displays BFS
void displayBFS(PokemonNode *root) {
    BFSGeneric(root, printPokemonNode);
}

// a generic BFS function
void BFSGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }

    int treeHeight = findTreeHeight(root);

    for (int level = 1; level <= treeHeight; level++) {
        printTreeLevel(root, level, visit);
    }
}

// Finds a tree 'height' given its root
int findTreeHeight(PokemonNode *root) {
    if (root == NULL) {
        return 0;
    }

    int treeHeightLeft = findTreeHeight(root->left);
    int treeHeightRight = findTreeHeight(root->right);

    if (treeHeightLeft > treeHeightRight) {
        return treeHeightLeft + 1;
    }
    return treeHeightRight + 1;
}

// Recursive func to print a single tree level
void printTreeLevel(PokemonNode *root, int level, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        visit(root); // func on the root
    }
    if (level > 1) {
        printTreeLevel(root->left, level - 1, visit);
        printTreeLevel(root->right, level - 1, visit);
    }
}

// Prints a tree pre-order (Root->Left->Right).
void preOrderTraversal(PokemonNode *root) {
    preOrderGeneric(root, printPokemonNode);
}

// A generic pre-order function
void preOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }

    visit(root); // Root
    preOrderGeneric(root->left, visit); // Left
    preOrderGeneric(root->right, visit); // Right
}

// Prints a tree in-order (Left->Root->Right).
void inOrderTraversal(PokemonNode *root) {
    inOrderGeneric(root, printPokemonNode);
}

// A generic in-order function
void inOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }
    inOrderGeneric(root->left, visit); // Left
    visit(root); // Root
    inOrderGeneric(root->right, visit); // Right
}

// Prints a tree post-order (Left->Right->Root).
void postOrderTraversal(PokemonNode *root) {
    postOrderGeneric(root, printPokemonNode);
}

// A generic post-order function
void postOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        return;
    }
    postOrderGeneric(root->left, visit); // Left
    postOrderGeneric(root->right, visit); // Right
    visit(root); // Root
}

// Display a whole tree in alphabetical order
void displayAlphabetical(PokemonNode *root) {
    // find the bin tree size
    int sizeOfTree = sizeOfBinTree(root);
    if (sizeOfTree == 0) {
        printf("Pokedex is empty.\n");
        return;
    }

    NodeArray nodeArray; // Create a node array
    initNodeArray(&nodeArray, sizeOfTree); // Initialize the array

    // Convert the tree to an array
    collectAll(root, &nodeArray);

    // sort the array alphabetically
    qsort(nodeArray.nodes, sizeOfTree, sizeof(PokemonNode *), compareByNameNode);
    // Print the array
    for (int i = 0; i < sizeOfTree; i++) {
        printPokemonNode(nodeArray.nodes[i]);
    }
    free(nodeArray.nodes);
}

// Return the size of a bin tree given its root
int sizeOfBinTree(PokemonNode *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + sizeOfBinTree(root->left)
           + sizeOfBinTree(root->right);
}

// Initialize an array with a given capacity
void initNodeArray(NodeArray *na, int cap) {
    // Initialize the array
    na->capacity = cap;
    na->size = cap;

    na->nodes = malloc(cap * sizeof(PokemonNode **));
    if (na->nodes == NULL) {
        printf("malloc failed.\n");
        freeAllOwners();
        exit(1);
    }
    // Set the whole array to NULL
    for (int i = 0; i < cap; i++) {
        na->nodes[i] = NULL;
    }
}

// Add a PokemonNode pointer to NodeArray, realloc if needed.
void addNode(NodeArray *na, PokemonNode *node) {
    // Go over the whole array to check if there is an empty place
    for (int i = 0; i < na->size; i++) {
        if (na->nodes[i] == NULL) {
            na->nodes[i] = node;
            return;
        }
    }
}

// Recursively collect all nodes from the BST into a NodeArray.
void collectAll(PokemonNode *root, NodeArray *na) {
    if (root == NULL) {
        return;
    }
    // Go over BTS pre-order and add the elements to the array
    addNode(na, root); // Add the root
    // Call the func with its children
    collectAll(root->left, na); // Left
    collectAll(root->right, na); // Right
}

// Compares 2 nodes by their names
int compareByNameNode(const void *a, const void *b) {
    const PokemonNode *nodeA = *(const PokemonNode **) a;
    const PokemonNode *nodeB = *(const PokemonNode **) b;

    return strcmp(nodeA->data->name, nodeB->data->name); // Compare names
}

// Copies data from one pokemon to the other
void copyDataBetweenPokemons(PokemonNode **dest, PokemonNode **src) {
    if (dest == NULL || src == NULL || *dest == NULL || *src == NULL) {
        return;
    }

    // Copy the data from src to dest
    (*dest)->data->attack = (*src)->data->attack;
    (*dest)->data->hp = (*src)->data->hp;
    (*dest)->data->id = (*src)->data->id;
    (*dest)->data->name = (*src)->data->name;
    (*dest)->data->TYPE = (*src)->data->TYPE;
    (*dest)->data->CAN_EVOLVE = (*src)->data->CAN_EVOLVE;
}

// Removes a pokemon from a tree based on its id
RESAULT freePokemon(PokemonNode **rootPtr, int id) {
    // If the tree or subtree is empty
    if (!rootPtr || !(*rootPtr)) {
        return FAILURE;
    }

    PokemonNode *root = *rootPtr;

    // Search for the root
    if (id < root->data->id) {
        return freePokemon(&(root->left), id); // Go left
    }
    if (id > root->data->id) {
        return freePokemon(&(root->right), id); // Go right
    }
    // found node to remove

    // Case 1: No children - a leaf
    if (!root->left && !root->right) {
        free(root->data); // Free PokemonData
        free(root); // Free PokemonNode
        *rootPtr = NULL; // Set pointer to NULL (Could be the pokedex root!)
        return SUCCESS;
    }

    // Case 2: One child
    if (!root->left || !root->right) {
        PokemonNode *temp = NULL;
        if (root->left) {
            temp = root->left;
        } else {
            temp = root->right;
        }
        free(root->data); // Free PokemonData
        free(root); // Free PokemonNode
        *rootPtr = temp; // Update pointer to child, (Could be the pokedex root!)
        return SUCCESS;
    }

    // Case 3: Two children
    PokemonNode *temp = findMaxBinTree(root->left); // Find in-order successor
    copyDataBetweenPokemons(&root, &temp); // Replace current node's data
    return freePokemon(&(root->left), temp->data->id); // Remove successor
}

// Returns the root of highest value in a bin tree
PokemonNode *findMaxBinTree(PokemonNode *root) {
    while (root && root->right) {
        root = root->right;
    }
    return root;
}

// Lets the user pick two Pokemon by ID in the same Pokedex to fight.
void pokemonFight(OwnerNode *owner) {
    // Get the id of the two pokemons
    const int pokemonOneId = readIntSafe("Enter ID of the first Pokemon: ");
    const int pokemonTwoId = readIntSafe("Enter ID of the second Pokemon: ");
    PokemonNode *pokemonOne = findInBinTreeByIDBFS(owner->pokedexRoot, pokemonOneId);
    PokemonNode *pokemonTwo = findInBinTreeByIDBFS(owner->pokedexRoot, pokemonTwoId);

    // If one or more pokemons weren't not found
    if (!pokemonOne || !pokemonTwo) {
        printf("One or both Pokemon IDs not found.\n");
        return;
    }

    const double pokemoneOneScore = pokedex[pokemonOneId - 1].attack * 1.5 + pokedex[pokemonOneId - 1].hp * 1.2;
    const double pokemoneTwoScore = pokedex[pokemonTwoId - 1].attack * 1.5 + pokedex[pokemonTwoId - 1].hp * 1.2;

    printf("Pokemon 1: %s (Score = %.2f)\n", pokedex[pokemonOneId - 1].name, pokemoneOneScore);
    printf("Pokemon 2: %s (Score = %.2f)\n", pokedex[pokemonTwoId - 1].name, pokemoneTwoScore);

    if (pokemoneOneScore > pokemoneTwoScore) {
        printf("%s wins!\n", pokedex[pokemonOneId - 1].name);
    } else if (pokemoneOneScore < pokemoneTwoScore) {
        printf("%s wins!\n", pokedex[pokemonTwoId - 1].name);
    } else {
        printf("It's a tie!\n");
    }
}

// Evolve a Pokemon (ID -> ID+1) if allowed.
void evolvePokemon(OwnerNode *owner) {
    const int oldID = readIntSafe("Enter ID of Pokemon to evolve: ");

    // Check if the pokemon is in the tree
    PokemonNode *oldPokemon = findInBinTreeByIDBFS(owner->pokedexRoot, oldID);
    if (!oldPokemon) {
        printf("No Pokemon with ID %d found.\n", oldID);
        return;
    }

    // Check if the pokemon can evolve
    if (!pokedex[oldID - 1].CAN_EVOLVE) {
        printf("%s (ID %d) cannot evolve.\n", pokedex[oldID - 1].name, oldID);
        return;
    }

    // Remove old
    RESAULT isVal = freePokemon(&(owner->pokedexRoot), oldID);
    if (isVal == MEM_ERROR) {
        printf("malloc failed\n");
        freeAllOwners();
        exit(1);
    }

    // Add new
    RESAULT isVal2 = addPokemonToBinTree(owner->pokedexRoot, oldID + 1);
    if (isVal2 == MEM_ERROR) {
        printf("malloc failed\n");
        freeAllOwners();
        exit(1);
    }
    // Evolved pokemon already exists
    if (isVal2 == FAILURE) {
        printf("Evolution ID %d (%s) already in the Pokedex. Releasing %s (ID %d).\n"
               "Removing Pokemon %s (ID %d).\n", oldID + 1, pokedex[oldID].name,
               pokedex[oldID - 1].name, oldID, pokedex[oldID - 1].name, oldID);
        return;
    }
    // Evolved pokemon doesn't exist
    printf("Removing Pokemon %s (ID %d).\n"
           "Pokemon evolved from %s (ID %d) to %s (ID %d).\n",
           pokedex[oldID - 1].name, oldID, pokedex[oldID - 1].name, oldID,
           pokedex[oldID].name, oldID + 1);
}

// Deletes a pokedox
void deletePokedex(int pokedexNum) {
    OwnerNode *currentOwner = ownerHead; // Set owner
    for (int i = 1; i < pokedexNum; i++) {
        currentOwner = currentOwner->next;
    }
    // Delete the entire pokedox tree
    postOrderDeletion(currentOwner, currentOwner->pokedexRoot);
    currentOwner->pokedexRoot = NULL; // Set root to NULL

    // Case 1: a single owner
    if (currentOwner->next == currentOwner) {
        ownerHead = NULL;
    } else {
        if (currentOwner == ownerHead) {
            ownerHead = currentOwner->next; // Update head pointer
        }
        currentOwner->prev->next = currentOwner->next;
        currentOwner->next->prev = currentOwner->prev;
    }

    // free the owner name if its not NULL
    if (currentOwner->ownerName) {
        free(currentOwner->ownerName);
    }
    free(currentOwner); // free owner node
}

// Deletes a tree post-order (Left->Right->Root).
void postOrderDeletion(OwnerNode *owner, PokemonNode *root) {
    if (root == NULL) {
        return;
    }

    postOrderDeletion(owner, root->left); // Left
    postOrderDeletion(owner, root->right); // Right
    freePokemon(&(owner->pokedexRoot), root->data->id); // Root
}

// Merges two pokedoxes
void mergePokedexMenu(int *numOfOwners) {
    printf("\n=== Merge Pokedexes ===\n");
    printf("Enter name of first owner: ");
    char *firstOwnerName = getDynamicInput();
    if (firstOwnerName == NULL) {
        freeAllOwners();
        exit(1);
    }

    printf("Enter name of second owner: ");
    char *secondOwnerName = getDynamicInput();
    if (secondOwnerName == NULL) {
        free(firstOwnerName);
        freeAllOwners();
        exit(1);
    }

    OwnerNode *firstOwner = ownerHead;

    // Search the pokedexes
    for (int i = 0; i < *numOfOwners; i++) {
        if (strcmp(firstOwner->ownerName, firstOwnerName) == 0) {
            break;
        }
        firstOwner = firstOwner->next;
    }

    OwnerNode *secondOwner = ownerHead;

    int secondOwnerIndex = 1;
    for (int i = 0; i < *numOfOwners; i++) {
        if (strcmp(secondOwner->ownerName, secondOwnerName) == 0) {
            break;
        }
        secondOwner = secondOwner->next;
        secondOwnerIndex++;
    }

    // Merge the pokedexes
    printf("Merging %s and %s...\n", firstOwnerName, secondOwnerName);
    RESAULT isVal = SUCCESS;
    isVal = mergeBFS(firstOwner->pokedexRoot, secondOwner->pokedexRoot);
    if (isVal == MEM_ERROR) {
        printf("malloc failed.\n");
        free(firstOwnerName);
        free(secondOwnerName);
        freeAllOwners();
        exit(1);
    }
    printf("Merge completed.\n");

    deletePokedex(secondOwnerIndex); // Delete the second owner
    printf("Owner '%s' has been removed after merging.\n", secondOwnerName);

    // free the names
    free(firstOwnerName);
    free(secondOwnerName);
}

// Merge two owners by BFS
RESAULT mergeBFS(PokemonNode *destRoot, PokemonNode *srcRoot) {
    if (srcRoot == NULL) {
        return SUCCESS;
    }
    int treeHeight = findTreeHeight(srcRoot);

    for (int level = 1; level <= treeHeight; level++) {
        RESAULT isVal = mergeTreeLevel(destRoot, srcRoot, srcRoot, level);
        if (isVal == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return SUCCESS;
}

// Recursive func to merge a single tree level
RESAULT mergeTreeLevel(PokemonNode *destRoot, PokemonNode *srcPokedoxRoot,
                       PokemonNode *currentRoot, int level) {
    if (currentRoot == NULL) {
        return FAILURE;
    }
    if (level == 1) {
        // Add pokemon from owner 2 to tree of owner 1
        RESAULT isAddVal = addPokemonToBinTree(destRoot, currentRoot->data->id);
        if (isAddVal == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    if (level > 1) {
        RESAULT isVal1 = mergeTreeLevel(destRoot, srcPokedoxRoot, currentRoot->left, level - 1);
        if (isVal1 == MEM_ERROR) {
            return MEM_ERROR;
        }
        RESAULT isVal2 = mergeTreeLevel(destRoot, srcPokedoxRoot, currentRoot->right, level - 1);
        if (isVal2 == MEM_ERROR) {
            return MEM_ERROR;
        }
    }
    return SUCCESS;
}

// Sort the circular owners list by name.
void sortOwners(int *numOfOwners) {
    for (int i = 0; i < *numOfOwners - 1; i++) {
        OwnerNode *currentOwner = ownerHead; // Set the current owner to the first owner
        for (int j = 0; j < *numOfOwners - 1 - i; j++) {
            if (strcmp(currentOwner->ownerName, currentOwner->next->ownerName) > 0) {
                if (j == 0) {
                    ownerHead = currentOwner->next;
                }
                swapOwnerData(currentOwner, currentOwner->next); // Swap the nodes
            } else {
                currentOwner = currentOwner->next;
            }
        }
    }
}

// Swaps two adjacent elements in the circular list
void swapOwnerData(OwnerNode *A, OwnerNode *B) {
    // Adjust pointers of adjacent nodes
    A->prev->next = B;
    B->next->prev = A;

    // Swap prev and next pointers of A and B
    B->prev = A->prev;
    A->next = B->next;

    A->prev = B;
    B->next = A;
}

// Print the owners forwad or backwards
void printOwnersCircular() {
    printf("Enter direction (F or B): ");
    char *direction = getDynamicInput();
    if (direction == NULL) {
        freeAllOwners();
        exit(1);
    }

    OwnerNode *currentOwner = ownerHead;

    int numOfPrints = readIntSafe("How many prints? ");
    // Print owners forwards
    if (*direction == 'f' || *direction == 'F') {
        for (int i = 1; i <= numOfPrints; i++) {
            printf("[%d] %s\n", i, currentOwner->ownerName);
            currentOwner = currentOwner->next;
        }
    }

    // Print owners backwards
    else if (*direction == 'b' || *direction == 'B') {
        for (int i = 1; i <= numOfPrints; i++) {
            printf("[%d] %s\n", i, currentOwner->ownerName);
            currentOwner = currentOwner->prev;
        }
    }

    free(direction); // free the direction
}

// frees all owners
void freeAllOwners() {
    if (ownerHead == NULL) {
        return;
    }
    int firstOwnerNum = 1;

    do {
        deletePokedex(firstOwnerNum); // Delete the pokedox
    } while (ownerHead != NULL);
    ownerHead = NULL;
}

// Function to print a single Pokemon node
void printPokemonNode(PokemonNode *node) {
    if (!node)
        return;
    printf("ID: %d, Name: %s, Type: %s, HP: %d, Attack: %d, Can Evolve: %s\n",
           node->data->id,
           node->data->name,
           getTypeName(node->data->TYPE),
           node->data->hp,
           node->data->attack,
           (node->data->CAN_EVOLVE == CAN_EVOLVE) ? "Yes" : "No");
}

// --------------------------------------------------------------
// Sub-menu for existing Pokedex
// --------------------------------------------------------------

// Gets an id and a tree and returns the root it it found it, else - NULL
PokemonNode *findInBinTreeByIDBFS(PokemonNode *root, int pokemonID) {
    if (root == NULL) {
        return NULL;
    }

    const int treeHeight = findTreeHeight(root);

    // Traverse levels of the tree
    for (int level = 1; level <= treeHeight; level++) {
        PokemonNode *result = searchTreeLevelBFS(root, level, pokemonID);
        if (result != NULL) {
            return result; // Return the node if found
        }
    }
    return NULL; // ID not found
}

// Recursive func to search root in a single tree level
PokemonNode *searchTreeLevelBFS(PokemonNode *root, int level, int pokemonID) {
    if (root == NULL) {
        return NULL;
    }
    if (level == 1) {
        if (root->data->id == pokemonID) {
            return root; // Match found
        }
        return NULL; // No match at this level
    }
    if (level > 1) {
        // Recursively search in left and right subtrees
        PokemonNode *leftResult = searchTreeLevelBFS(root->left, level - 1, pokemonID);
        if (leftResult != NULL) {
            return leftResult; // Return if found in left subtree
        }
        return searchTreeLevelBFS(root->right, level - 1, pokemonID); // Search in right subtree
    }
    return NULL; // Should never reach here - just in case
}

// Add a pokemon to a bin tree
RESAULT addPokemonToBinTree(PokemonNode *pokedexRoot, int pokemonID) {
    if (pokedexRoot == NULL) {
        return FAILURE;
    }
    if (pokedexRoot->data->id > pokemonID) {
        if (pokedexRoot->left != NULL) {
            return addPokemonToBinTree(pokedexRoot->left, pokemonID);
        }
        pokedexRoot->left = createBinTree(pokemonID);
        if (pokedexRoot->left == NULL) {
            return MEM_ERROR;
        }
        return SUCCESS;
    }

    if (pokedexRoot->data->id < pokemonID) {
        if (pokedexRoot->right != NULL) {
            return addPokemonToBinTree(pokedexRoot->right, pokemonID);
        }
        pokedexRoot->right = createBinTree(pokemonID);
        if (pokedexRoot->right == NULL) {
            return MEM_ERROR;
        }
        return SUCCESS;
    }
    return FAILURE; // The pokemon already exists
}

// Creates a bin tree
PokemonNode *createBinTree(int id) {
    // Allocate memory for the new pokemon node
    PokemonNode *newPokemonRoot = (PokemonNode *) malloc(sizeof(PokemonNode));
    if (newPokemonRoot == NULL) {
        return NULL;
    }

    // Allocate memory for the data inside the node
    newPokemonRoot->data = (PokemonData *) malloc(sizeof(PokemonData));
    if (newPokemonRoot->data == NULL) {
        free(newPokemonRoot); // Free the allocated node before returning
        return NULL;
    }

    // Set the new pokemon data
    newPokemonRoot->data->id = pokedex[id - 1].id;
    newPokemonRoot->data->name = pokedex[id - 1].name;
    newPokemonRoot->data->TYPE = pokedex[id - 1].TYPE;
    newPokemonRoot->data->hp = pokedex[id - 1].hp;
    newPokemonRoot->data->attack = pokedex[id - 1].attack;
    newPokemonRoot->data->CAN_EVOLVE = pokedex[id - 1].CAN_EVOLVE;

    // Set the children to NULL
    newPokemonRoot->left = NULL;
    newPokemonRoot->right = NULL;

    return newPokemonRoot;
}

// --------------------------------------------------------------
// Display Menu
// --------------------------------------------------------------
void displayMenu(OwnerNode *owner) {
    if (!owner->pokedexRoot) {
        printf("Pokedex is empty.\n");
        return;
    }

    printf("Display:\n");
    printf("1. BFS (Level-Order)\n");
    printf("2. Pre-Order\n");
    printf("3. In-Order\n");
    printf("4. Post-Order\n");
    printf("5. Alphabetical (by name)\n");

    int choice = readIntSafe("Your choice: ");

    switch (choice) {
        case 1:
            displayBFS(owner->pokedexRoot);
            break;
        case 2:
            preOrderTraversal(owner->pokedexRoot);
            break;
        case 3:
            inOrderTraversal(owner->pokedexRoot);
            break;
        case 4:
            postOrderTraversal(owner->pokedexRoot);
            break;
        case 5:
            displayAlphabetical(owner->pokedexRoot);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// Adds a pokemon to a bin tree
void createPokemon(OwnerNode *owner) {
    int pokemonID = readIntSafe("Enter ID to add: ");
    if (findInBinTreeByIDBFS(owner->pokedexRoot, pokemonID) != NULL) {
        printf("Pokemon with ID %d is already in the Pokedex. No changes made.\n", pokemonID);
        return;
    }

    if (owner->pokedexRoot == NULL) {
        owner->pokedexRoot = createBinTree(pokemonID);
        if (owner->pokedexRoot == NULL) {
            printf("malloc falied.\n");
            freeAllOwners();
            exit(1);
        }
        printf("Pokemon %s (ID %d) added.\n", pokedex[pokemonID - 1].name, pokemonID);
        return;
    }

    RESAULT isVal = addPokemonToBinTree(owner->pokedexRoot, pokemonID);
    if (isVal == MEM_ERROR) {
        printf("malloc failed.\n");
        free(owner->pokedexRoot);
        freeAllOwners();
        exit(1);
    }
    if (isVal == SUCCESS) {
        printf("Pokemon %s (ID %d) added.\n", pokedex[pokemonID - 1].name, pokemonID);
    }
}

// Let user pick an existing Pokedex (owner) by number, then sub-menu.
void enterExistingPokedexMenu(int *numOfOwners) {
    if (*numOfOwners == 0) {
        printf("No existing Pokedexes.\n");
        return;
    }

    // list owners
    printf("\nExisting Pokedexes:\n");
    OwnerNode *currentOwner = ownerHead;
    for (int i = 0; i < *numOfOwners; i++) {
        printf("%d. %s\n", i + 1, currentOwner->ownerName);
        currentOwner = currentOwner->next;
    }

    // Get the user's pokedex choice
    int pokedexChoice = readIntSafe("Choose a Pokedex by number: ");

    currentOwner = ownerHead; // Reset current owner
    for (int i = 1; i < pokedexChoice; i++) {
        currentOwner = currentOwner->next;
    }

    printf("\nEntering %s's Pokedex...\n", currentOwner->ownerName);

    int subChoice;
    do {
        printf("\n-- %s's Pokedex Menu --\n", currentOwner->ownerName);
        printf("1. Add Pokemon\n");
        printf("2. Display Pokedex\n");
        printf("3. Release Pokemon (by ID)\n");
        printf("4. Pokemon Fight!\n");
        printf("5. Evolve Pokemon\n");
        printf("6. Back to Main\n");

        subChoice = readIntSafe("Your choice: ");

        switch (subChoice) {
            case 1: // CREATE POKEMON
                createPokemon(currentOwner);
                break;
            case 2: // DISPLAY MENU
                displayMenu(currentOwner);
                break;
            case 3: // REMOVE POKEMON
                if (currentOwner->pokedexRoot == NULL) {
                    printf("No Pokemon to release.\n");
                    break;
                }
                int pokemonID = readIntSafe("Enter Pokemon ID to release: ");

                RESAULT isValid = freePokemon(&(currentOwner->pokedexRoot), pokemonID);
                if (isValid == FAILURE) {
                    printf("No Pokemon with ID %d found.\n", pokemonID);
                }
                if (isValid == SUCCESS) {
                    printf("Removing Pokemon %s (ID %d).\n", pokedex[pokemonID - 1].name, pokemonID);
                }
                break;
            case 4: // POKEMON FIGHT
                if (currentOwner->pokedexRoot == NULL) {
                    printf("Pokedex is empty.\n");
                    break;
                }
                pokemonFight(currentOwner);
                break;
            case 5: // EVOLVE
                if (currentOwner->pokedexRoot == NULL) {
                    printf("Cannot evolve. Pokedex empty.\n");
                    break;
                }
                evolvePokemon(currentOwner);
                break;
            case 6: // BACK TO MAIN
                printf("Back to Main Menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (subChoice != 6);
}

// Creates a new Pokedex (prompt for name, check uniqueness, choose starter).
void openPokedexMenu(int *numOfOwners) {
    printf("Your name: ");
    char *newOwnerName = getDynamicInput();
    if (newOwnerName == NULL) {
        freeAllOwners();
        exit(1);
    }

    if (ownerHead != NULL) {
        OwnerNode *current = ownerHead;
        do {
            if (strcmp(current->ownerName, newOwnerName) == 0) {
                printf("Owner '%s' already exists. Not creating a new Pokedex.\n", newOwnerName);
                free(newOwnerName);
                return;
            }
            current = current->next;
        } while (current != ownerHead); // Stop when we've looped back to the head
    }

    // Allocate memory for a new OwnerNode
    OwnerNode *newOwner = (OwnerNode *) malloc(sizeof(OwnerNode));
    if (newOwner == NULL) {
        printf("malloc falied.\n");
        free(newOwnerName);
        freeAllOwners();
        exit(1);
    }

    newOwner->ownerName = newOwnerName;
    newOwnerName = NULL;

    if (*numOfOwners == 0) {
        // first owner in list
        newOwner->next = newOwner;
        newOwner->prev = newOwner;
        ownerHead = newOwner; // Set the head to the new first owner
    } else {
        // Insert new owner into the circular list
        OwnerNode *last = ownerHead->prev;
        newOwner->next = ownerHead; // Set the new owner's next to the head
        newOwner->prev = last; // Set the new owner's prev to the last owner
        last->next = newOwner; // Set the last owner's next to the new owner
        ownerHead->prev = newOwner; // Set the head's prev to the new owner
    }

    // Prompt and get the user's starter
    int starterPokemonChoice =
            readIntSafe("Choose Starter:\n1. Bulbasaur\n2. Charmander\n3. Squirtle\nYour choice: ");
    int bulbasaurId = 1, charmanderId = 4, squirtleId = 7, isValid = 1; // Save the pokemon's Idis

    // Print the pokemon based on the user's choice
    switch (starterPokemonChoice) {
        case 1:
            newOwner->pokedexRoot = createBinTree(bulbasaurId);
            if (newOwner->pokedexRoot == NULL) {
                isValid = 0;
                break;
            }
            printf("New Pokedex created for %s with starter Bulbasaur.\n", newOwner->ownerName);
            break;
        case 2:
            newOwner->pokedexRoot = createBinTree(charmanderId);
            if (newOwner->pokedexRoot == NULL) {
                isValid = 0;
                break;
            }
            printf("New Pokedex created for %s with starter Charmander.\n", newOwner->ownerName);
            break;
        case 3:
            newOwner->pokedexRoot = createBinTree(squirtleId);
            if (newOwner->pokedexRoot == NULL) {
                isValid = 0;
                break;
            }
            printf("New Pokedex created for %s with starter Squirtle.\n", newOwner->ownerName);
            break;
        default:
            printf("Invalid choice.\n");
    }
    if (!isValid) {
        printf("malloc failed.\n");
        free(newOwner->ownerName);
        free(newOwner);
        freeAllOwners();
        exit(1);
    }
    (*numOfOwners)++; // Increase num of owners
}

// --------------------------------------------------------------
// Main Menu
// --------------------------------------------------------------
void mainMenu() {
    int numOfOwners = 0;
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. New Pokedex\n");
        printf("2. Existing Pokedex\n");
        printf("3. Delete a Pokedex\n");
        printf("4. Merge Pokedexes\n");
        printf("5. Sort Owners by Name\n");
        printf("6. Print Owners in a direction X times\n");
        printf("7. Exit\n");
        choice = readIntSafe("Your choice: ");

        switch (choice) {
            case 1: // NEW POKEDOX
                openPokedexMenu(&numOfOwners);
                break;
            case 2: // POKEDOX MENU
                if (numOfOwners == 0) {
                    printf("No existing Pokedexes.\n");
                    break;
                }
                enterExistingPokedexMenu(&numOfOwners);
                break;
            case 3: // DELETE POKEDOX
                if (ownerHead == NULL) {
                    printf("No existing Pokedexes to delete.\n");
                    break;
                }
                printf("\n=== Delete a Pokedex ===\n");
            // Display pokedexes
                OwnerNode *currentOwner = ownerHead;
                for (int i = 0; i < numOfOwners; i++) {
                    printf("%d. %s\n", i + 1, currentOwner->ownerName);
                    currentOwner = currentOwner->next;
                }

            // Get the user's pokedex choice
                int pokedexNum = readIntSafe("Choose a Pokedex to delete by number: ");

                currentOwner = ownerHead; // Reset current owner
                for (int i = 1; i < pokedexNum; i++) {
                    currentOwner = currentOwner->next;
                }

                printf("Deleting %s's entire Pokedex...\n", currentOwner->ownerName);
                deletePokedex(pokedexNum); // Delete the pokedex
                numOfOwners--;
                printf("Pokedex deleted.\n"); // Success
                break;
            case 4: // MERGE POKEDEXES
                if (numOfOwners < 2) {
                    printf("Not enough owners to merge.\n");
                    break;
                }
                mergePokedexMenu(&numOfOwners);
                numOfOwners--;
                break;
            case 5: // SORT OWNERS
                if (numOfOwners < 2) {
                    printf("0 or 1 owners only => no need to sort.\n");
                    break;
                }
                sortOwners(&numOfOwners);
                printf("Owners sorted by name.\n");
                break;
            case 6: // PRINT CIRCULAR LIST
                if (numOfOwners == 0) {
                    printf("No owners.\n");
                    break;
                }
                printOwnersCircular();
                break;
            case 7:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid.\n");
        }
    } while (choice != 7);
}

// main func
int main() {
    mainMenu();
    freeAllOwners();
    return 0;
}
