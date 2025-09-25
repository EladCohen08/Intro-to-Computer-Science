/********************
 * Name: Elad
 * ID: 331526079
 * Assignment: ex5
 ********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WATCH_PLAYLISTS 1
#define ADD_PLAYLIST 2
#define REMOVE_PLAYLIST 3
#define EXIT 4

typedef struct Song {
    char *title;
    char *artist;
    int year;
    char *lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char *name;
    Song **songs;
    int songsNum;
} Playlist;


/************************************************
 * DECLARING FUNCTIONS
 * **********************************************/
void printMainMenu();

void printAllPlaylistsMenu(Playlist *allPlaylistsPtr, int numOfPlaylists);

void printInPlaylistMenu();

void freeSong(Song *song);

void freePlaylist(Playlist *playlist);

void freeAll(Playlist *allPlaylistsPtr, int numOfPlaylists);

void deleteSong(Playlist *playlist, int indexDeletedSong, Playlist *allPlaylistsPtr, int numOfPlaylists);

void removePlaylist(Playlist **allPlaylistsPtr, int *numOfPlaylists, int indexDeletedPlaylist);

char *getString(Playlist *allPlaylistsPtr, int numOfPlaylists);

void addSong(Song ***allSongs, int *numOfSongsPtr, Playlist *allPlaylistsPtr, int numOfPlaylists);

void printSongs(Song **allSongs, int *numOfSongs);

void playSong(Song **allSongs, int songIndex);

void playAllSongs(Song **allSongs, int *numOfSongs);

void showPlaylist(Song **allSongs, int *numOfSongs);

void sortPlaylist(Song **allSongs, int *numOfSongs);

/************************************************
 * MAIN FUNCTION
 * **********************************************/
int main() {
    Playlist *allPlaylistsPtr = NULL; // pointer to all playlists
    // Declare the menu choice and num of playlists
    int mainMenuChoice = 0, numOfPlaylists = 0;
    do {
        printMainMenu(); // Print the main menu
        if (scanf(" %d", &mainMenuChoice)) {
            switch (mainMenuChoice) {
                case WATCH_PLAYLISTS:
                    // Declare all int type variables
                    int userPlaylistChoice = -1, actionInPlaylistChoice = -1, indexDeletedSong = -1;
                    do {
                        // Print the playlist menu
                        printAllPlaylistsMenu(allPlaylistsPtr, numOfPlaylists);
                        // Get the user's choice
                        if (scanf(" %d", &userPlaylistChoice)) {
                            // Validate the user's choice
                            if (userPlaylistChoice <= 0 || userPlaylistChoice > numOfPlaylists + 1) {
                                printf("Invalid option\n");
                                continue; // Print the menu again
                            }

                            // Break if the user entered back to main
                            if (userPlaylistChoice == numOfPlaylists + 1) {
                                break;
                            }
                            // Print: "playlist 'playlist name':"
                            printf("playlist %s:\n", allPlaylistsPtr[userPlaylistChoice - 1].name);
                            do {
                                printInPlaylistMenu();
                                // Get the user's choice
                                scanf(" %d", &actionInPlaylistChoice);
                                switch (actionInPlaylistChoice) {
                                    case 1:
                                        // Show Playlist
                                        showPlaylist(allPlaylistsPtr[userPlaylistChoice - 1].songs,
                                                     &allPlaylistsPtr[userPlaylistChoice - 1].songsNum);
                                        break;
                                    case 2:
                                        // Add Song
                                        addSong(&allPlaylistsPtr[userPlaylistChoice - 1].songs,
                                                &allPlaylistsPtr[userPlaylistChoice - 1].songsNum,
                                                allPlaylistsPtr,
                                                numOfPlaylists);
                                        break;
                                    case 3:
                                        // Delete Song
                                        // Print the songs in the playlist
                                        printSongs(allPlaylistsPtr[userPlaylistChoice - 1].songs,
                                                   &allPlaylistsPtr[userPlaylistChoice - 1].songsNum);
                                        // Get the user's choice of which song to delete
                                        printf("choose a song to delete, or 0 to quit:\n");
                                        scanf("%d", &indexDeletedSong);
                                        // Validate the choice
                                        if (indexDeletedSong > 0 &&
                                            indexDeletedSong <= allPlaylistsPtr[userPlaylistChoice - 1].songsNum) {
                                            // Delete the song
                                            deleteSong(&allPlaylistsPtr[userPlaylistChoice - 1],
                                                       indexDeletedSong - 1,
                                                       allPlaylistsPtr, numOfPlaylists);
                                            printf("Song deleted successfully.\n");
                                        }
                                        break;
                                    case 4:
                                        // Sort
                                        sortPlaylist(allPlaylistsPtr[userPlaylistChoice - 1].songs,
                                                     &allPlaylistsPtr[userPlaylistChoice - 1].songsNum);
                                        break;
                                    case 5:
                                        // Play
                                        playAllSongs(allPlaylistsPtr[userPlaylistChoice - 1].songs,
                                                     &allPlaylistsPtr[userPlaylistChoice - 1].songsNum);
                                        break;
                                    case 6:
                                        // exit, nothing to do here
                                        break;
                                    default:
                                        printf("Invalid option\n");
                                        break;
                                }
                            } while (actionInPlaylistChoice != 6); // 6 is Exit
                        } else {
                            scanf("%*s");
                        }
                    } while (userPlaylistChoice != numOfPlaylists + 1);
                    break;
                case ADD_PLAYLIST:
                    // Create the new playlist
                    Playlist newPlaylist;

                // Get and assign the playlist's name
                    printf("Enter playlist's name:\n");
                    char *playlistName = getString(allPlaylistsPtr, numOfPlaylists);

                    newPlaylist.name = playlistName;
                    newPlaylist.songsNum = 0; // Initialize numOfSongs
                    newPlaylist.songs = NULL; // Initialize songs to NULL

                // Create space in allPlaylists for the new playlist
                    Playlist *newAllPlaylists = realloc(allPlaylistsPtr,
                                                        (numOfPlaylists + 1) * sizeof(Playlist));
                    if (newAllPlaylists == NULL) {
                        printf("malloc failed\n");
                        freeAll(allPlaylistsPtr, numOfPlaylists);
                        return 1;
                    }
                // Add the new playlist
                    newAllPlaylists[numOfPlaylists] = newPlaylist;
                    numOfPlaylists++;

                // Set all playlists with the new playlist
                    allPlaylistsPtr = newAllPlaylists;
                    break;
                case REMOVE_PLAYLIST:
                    // Print playlist menu
                    printAllPlaylistsMenu(allPlaylistsPtr, numOfPlaylists);

                    int indexDeletedPlaylist = -1;
                    scanf(" %d", &indexDeletedPlaylist);

                    if (indexDeletedPlaylist > 0 && indexDeletedPlaylist <= numOfPlaylists) {
                        // Remove playlist
                        removePlaylist(&allPlaylistsPtr, &numOfPlaylists, indexDeletedPlaylist - 1);
                        printf("Playlist deleted.\n");
                    }
                    break;
                case EXIT:
                    freeAll(allPlaylistsPtr, numOfPlaylists);
                    printf("Goodbye!\n");
                    return 0;
                default:
                    // Default, invalid number
                    printf("Invalid option\n");
                    break;
            }
        } else {
            scanf("%*s");
        }
    } while (mainMenuChoice != 4);
    return 0;
}

/************************************************
 * ALL FUNCTION
 * **********************************************/
void printMainMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}

// Print all playlists menu
void printAllPlaylistsMenu(Playlist *allPlaylistsPtr, int numOfPlaylists) {
    printf("Choose a playlist:\n");
    for (int i = 0; i < numOfPlaylists; i++) {
        printf("\t%d. %s\n", i + 1, allPlaylistsPtr[i].name);
    }
    // Print playlist's names in between
    printf("\t%d. Back to main menu\n", numOfPlaylists + 1);
}

// Print in playlist menu
void printInPlaylistMenu() {
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}

// free a song, and all its elements
void freeSong(Song *song) {
    if (song == NULL) {
        return;
    }
    // Free individual song fields
    free(song->title);
    free(song->artist);
    free(song->lyrics);
    free(song); // Free the song structure itself
}

// free a playlist and all its elements
void freePlaylist(Playlist *playlist) {
    if (playlist == NULL) {
        return;
    }
    // Free the playlist name
    free(playlist->name);
    for (int j = 0; j < playlist->songsNum; j++) {
        // Free a specific song in the playlist
        freeSong(playlist->songs[j]);
    }
    // Free the array of song pointers
    free(playlist->songs);
}

// free everything
void freeAll(Playlist *allPlaylistsPtr, int numOfPlaylists) {
    if (allPlaylistsPtr == NULL) {
        return;
    }
    // free all the playlists
    for (int i = 0; i < numOfPlaylists; i++) {
        freePlaylist(&allPlaylistsPtr[i]);
    }
    // free the arrays of playlists
    free(allPlaylistsPtr);
}

// Delete a song
void deleteSong(Playlist *playlist, int indexDeletedSong, Playlist *allPlaylistsPtr, int numOfPlaylists) {
    if (playlist == NULL || playlist->songs == NULL) {
        return;
    }
    // free the song
    freeSong(playlist->songs[indexDeletedSong]);

    // Shift all other songs to fill the gap
    for (int i = indexDeletedSong; i < playlist->songsNum - 1; i++) {
        playlist->songs[i] = playlist->songs[i + 1];
    }

    // Reallocate to a new smaller memory for all songs
    Song **allSongsNewPtr = realloc(playlist->songs, sizeof(Song *) * (playlist->songsNum - 1));
    if (allSongsNewPtr == NULL && (playlist->songsNum - 1) > 0) {
        printf("malloc failed\n");
        freeAll(allPlaylistsPtr, numOfPlaylists);
        exit(1);
    }
    playlist->songs = allSongsNewPtr; // Update the caller's pointer
    // Decrease the song counter
    playlist->songsNum--;
}

// Remove a playlist
void removePlaylist(Playlist **allPlaylistsPtr, int *numOfPlaylists, int indexDeletedPlaylist) {
    // Check if the playlist is not NULL
    if (allPlaylistsPtr == NULL || *allPlaylistsPtr == NULL || *numOfPlaylists <= 0) {
        return;
    }

    // free the playlist
    freePlaylist(&(*allPlaylistsPtr)[indexDeletedPlaylist]);

    // Shift all other playlists to fill the gap
    for (int i = indexDeletedPlaylist; i < *numOfPlaylists - 1; i++) {
        (*allPlaylistsPtr)[i] = (*allPlaylistsPtr)[i + 1];
    }

    // Set the removed playlist to NULL
    (*allPlaylistsPtr)[*numOfPlaylists - 1] = (Playlist){0};

    // Added this just after the test
    if (*numOfPlaylists <= 1) {
        (*numOfPlaylists)--; // Decrease the playlist count
        return;
    }

    // Reallocate to a new smaller memory
    Playlist *newPtr = realloc(*allPlaylistsPtr, sizeof(Playlist) * (*numOfPlaylists - 1));
    if (newPtr == NULL) {
        printf("malloc failed\n");
        freeAll(*allPlaylistsPtr, *numOfPlaylists);
        exit(1);
    }
    *allPlaylistsPtr = newPtr; // Update the caller's pointer
    (*numOfPlaylists)--; // Decrease the playlist count
}

// Get and return an unlimited length string
char *getString(Playlist *allPlaylistsPtr, int numOfPlaylists) {
    char letter;
    size_t size = 0; // size of current str

    char *name = NULL; // Set the name to NULL

    scanf(" %c", &letter); // Read the first char
    // Read a single character at a time
    while (letter != '\n') {
        // Increase the capacity
        char *newName = realloc(name, (size + 1) * sizeof(char));
        if (newName == NULL) {
            printf("malloc failed\n");
            freeAll(allPlaylistsPtr, numOfPlaylists);
            exit(1);
        }
        name = newName;
        name[size++] = letter; // Add the character to the string
        name[size] = '\0'; // Add a null in the end of the string

        scanf("%c", &letter); // Read the next character
    }
    // Remove the '\r' from the string's end
    if (size > 0 && name[size - 1] == '\r') {
        name[--size] = '\0'; // Replace '\r' with null terminator
    }
    return name;
}

// Add a song to a playlist
void addSong(Song ***allSongs, int *numOfSongsPtr, Playlist *allPlaylistsPtr, int numOfPlaylists) {
    if (allSongs == NULL || numOfSongsPtr == NULL) {
        return; // return if allSongs or numOfSongsPtr are NULL
    }
    // Resize the array of songs
    Song **newAllSongs = realloc(*allSongs, (*numOfSongsPtr + 1) * sizeof(Song *));
    if (newAllSongs == NULL) {
        printf("malloc failed.\n");
        freeAll(allPlaylistsPtr, numOfPlaylists);
        exit(1);
    }
    *allSongs = newAllSongs; // Update the caller's pointer

    // Allocate and initialize the new song
    Song *newSong = malloc(sizeof(Song));
    if (newSong == NULL) {
        printf("Memory allocation failed.\n");
        freeAll(allPlaylistsPtr, numOfPlaylists);
        exit(1);
    }

    // Add the Song pointer to the array
    (*allSongs)[*numOfSongsPtr] = newSong;

    newSong->title = NULL;
    newSong->artist = NULL;
    newSong->lyrics = NULL;
    newSong->year = 0;
    newSong->streams = 0;

    // Get the title
    printf("Enter song's details\nTitle:\n");
    char *songTitle = getString(allPlaylistsPtr, numOfPlaylists);
    newSong->title = songTitle;

    // Get the song's artist
    printf("Artist:\n");
    char *songArtist = getString(allPlaylistsPtr, numOfPlaylists);
    newSong->artist = songArtist;

    // Get the release year
    printf("Year of release:\n");
    if (scanf("%d", &newSong->year) == 1) {
    }

    // Get the song's lyrics
    printf("Lyrics:\n");
    char *lyrics = getString(allPlaylistsPtr, numOfPlaylists);
    newSong->lyrics = lyrics;
    newSong->streams = 0;

    (*numOfSongsPtr)++; // Update the songs counter
}

// Print all songs in a playlist
void printSongs(Song **allSongs, int *numOfSongs) {
    for (int i = 0; i < *numOfSongs; i++) {
        // Print all elements each song
        if (allSongs[i] != NULL && allSongs[i]->title != NULL) {
            printf("%d. Title: %s\n", i + 1, allSongs[i]->title);
            printf("   Artist: %s\n", allSongs[i]->artist);
            printf("   Released: %d\n", allSongs[i]->year);
            printf("   Streams: %d\n", allSongs[i]->streams);
        }
    }
}

// Play a specific song
void playSong(Song **allSongs, int songIndex) {
    if (allSongs == NULL) {
        return;
    }
    // Print the song and its lyrics
    printf("Now playing %s:\n", allSongs[songIndex]->title);
    printf("$ ");
    printf("%s", allSongs[songIndex]->lyrics);
    printf(" $\n");
    allSongs[songIndex]->streams++;
}

// Play all the songs in a playlist
void playAllSongs(Song **allSongs, int *numOfSongs) {
    if (allSongs == NULL || numOfSongs == NULL) {
        return;
    }
    for (int i = 0; i < *numOfSongs; i++) {
        // Play a specific song in a playlist
        playSong(allSongs, i);
        printf("\n");
    }
}

// Show a playlist
void showPlaylist(Song **allSongs, int *numOfSongs) {
    int songChoice = -1;
    printSongs(allSongs, numOfSongs);
    // Ask the user if he wants to play a song
    printf("choose a song to play, or 0 to quit:\n");
    scanf(" %d", &songChoice);
    while (songChoice > 0 && songChoice <= *numOfSongs) {
        // Play the song the user chose
        playSong(allSongs, songChoice - 1);
        // Ask the user if he wants to play another song
        printf("choose a song to play, or 0 to quit:\n");
        scanf(" %d", &songChoice);
    }
}

// Sort a playlist by the user's choice
void sortPlaylist(Song **allSongs, int *numOfSongs) {
    int sortChoice = -1;
    printf("choose:\n"
        "1. sort by year\n"
        "2. sort by streams - ascending order\n"
        "3. sort by streams - descending order\n"
        "4. sort alphabetically\n");
    scanf(" %d", &sortChoice);
    switch (sortChoice) {
        case 1:
            // Sort by year - ascending
            // Use bubble sorting
            for (int i = 0; i < *numOfSongs - 1; i++) {
                for (int j = 0; j < *numOfSongs - i - 1; j++) {
                    if (allSongs[j]->year > allSongs[j + 1]->year) {
                        // Swap arr[j] and arr[j+1]
                        Song *temp = allSongs[j];
                        allSongs[j] = allSongs[j + 1];
                        allSongs[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            // sort by streams - ascending
            // Bubble sorting
            for (int i = 0; i < *numOfSongs - 1; i++) {
                for (int j = 0; j < *numOfSongs - i - 1; j++) {
                    if (allSongs[j]->streams > allSongs[j + 1]->streams) {
                        // Swap arr[j] and arr[j+1]
                        Song *temp = allSongs[j];
                        allSongs[j] = allSongs[j + 1];
                        allSongs[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            // sort by streams - descending order
            // Bubble sorting
            for (int i = 0; i < *numOfSongs - 1; i++) {
                for (int j = 0; j < *numOfSongs - i - 1; j++) {
                    if (allSongs[j]->streams < allSongs[j + 1]->streams) {
                        // Swap arr[j] and arr[j+1]
                        Song *temp = allSongs[j];
                        allSongs[j] = allSongs[j + 1];
                        allSongs[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            // sort alphabetically - ascending
            // Bubble sorting
            for (int i = 0; i < *numOfSongs - 1; i++) {
                for (int j = 0; j < *numOfSongs - i - 1; j++) {
                    if (strcmp(allSongs[j]->title, allSongs[j + 1]->title) > 0) {
                        // Swap arr[j] and arr[j+1]
                        Song *temp = allSongs[j];
                        allSongs[j] = allSongs[j + 1];
                        allSongs[j + 1] = temp;
                    }
                }
            }
            break;
    }
    printf("sorted\n");
}