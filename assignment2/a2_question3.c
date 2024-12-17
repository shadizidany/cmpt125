/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include <stdio.h>
#include "a2_question2.h"
#define INITIAL_CAPACITY 16
#define BUFFER_SIZE 301 // each line having at most 300 characters
/*
The `printSuperheroes` function displays a formatted list of superhero details.
It takes an array of pointers to `Superhero` structures and an integer
representing the number of superheroes. The function prints a header for
the "Superheroes Lookup System" and iterates through the array,outputting each
superhero's name, height, superpower, and traits in a structured format.
*/
void printSuperheroes(Superhero** superheroes, int size) {
    // Print the header for the Superheroes Lookup System
    printf("==========================================================\n");
    printf("================Superheroes Lookup System=================\n");
    printf("=======================Shadi Zidany=======================\n");
    printf("========================000000000=========================\n");
    printf("=======================cmptid@sfu.ca======================\n");
    printf("==========================================================\n");
    // Iterate through the array of Superhero pointers and print their details
    for (int i = 0; i < size; i++) {
        printf("Superhero #%d\n", i+1);
        printf("%s\n", superheroes[i]->name);
        printf("%d'%d\"\n", superheroes[i]->feetInHeight,
                            superheroes[i]->inchesInHeight);
        printf("%s: %s\n", superheroes[i]->superpower, superheroes[i]->traits);
        printf("==========================================================\n");
    }
}
/*
The `freeSuperheroes` function releases memory allocated for an array of
`Superhero` pointers. It iterates through the array, calling `clearSuperhero`
to free any associated resources for each superhero,then deallocates the memory
for the superhero objects themselves and sets their pointers to `NULL`.
Finally, it frees the array of pointers and sets it to `NULL`
to prevent dangling references.
*/
void freeSuperheroes(Superhero** superheroes, int size) {
    /*  Iterate through the array of Superhero pointers to free
        all allocated memory and avoid dangling references */
    for (int i = 0; i < size; i++) {
        clearSuperhero(superheroes[i]);
        free(superheroes[i]);
        superheroes[i] = NULL;
    }
    // Free the array of Superhero pointers and set it to NULL
    free(superheroes);
    superheroes = NULL;
}
/*
The `main` function serves as the entry point of the program,
responsible for reading superhero data from a file named "superheros.txt".
It opens the file and checks for errors, then allocates memory for an array of
`Superhero` pointers. The function reads superhero attributes (name, height,
superpower and traits) from the file, dynamically resizing the array as needed.
After populating the array, it calls `printSuperheroes` to display the details
of the superheroes and finally frees the allocated memory using
`freeSuperheroes`, closing the file before returning.
*/
int main() {
    // Open the file containing superhero data for reading
    FILE* file = fopen("superheros.txt", "r");
    // Check if the file was opened successfully (handle error if not)
    if (!file) {
        perror("Error opening file superheros.txt");
        return 0;
    }
    // Allocate initial memory for an array of Superhero pointers
    Superhero** superheroes = malloc(INITIAL_CAPACITY * sizeof(Superhero*));
    // Verify that memory allocation was successful
    if (!superheroes) {
        fclose(file);
        perror("Memory allocation failed");
        return 0;
    }
    // Initialize capacity and count of used superhero entries
    int capacity = INITIAL_CAPACITY, used = 0;
    // Declare buffers for reading superhero attributes
    char name[BUFFER_SIZE] = { '\0' }, superpower[BUFFER_SIZE] = { '\0' },
                                           traits[BUFFER_SIZE] = { '\0' };
    int feet = 0, inches = 0;
    // Read superheroes from the file until end-of-file is reached
    for (; !feof(file); used++) {
        // Read superhero details from the file
        fscanf(file, " **Name:** %[^\n] ", name);
        fscanf(file, " **Height:** %d'%d\" ", &feet, &inches);
        fscanf(file, " **Superpower:** %[^\n] ", superpower);
        fscanf(file, " %[^\n] ", traits);
        // Check if the array needs to be resized
        if (used == capacity) {
            // Double the capacity of the superheroes array
            capacity *= 2;
            Superhero** temp = realloc(superheroes,
                                       capacity * sizeof(Superhero*));
            // Handle potential memory reallocation failure
            if (!temp) {
                perror(
                   "Incomplete superhero entries: Memory reallocation failed");
                break;
            }
            // Update the pointer to the resized array
            superheroes = temp;
        }
        // Create a new Superhero. If allocation fails, exit the loop
        if (!(superheroes[used] = createSuperhero(name, feet, inches,
                                                        superpower, traits))) {
            perror("File reading incomplete: Memory allocation failed");
            break;
        }
    }
    // Print the details of all superheroes read from the file
    printSuperheroes(superheroes, used);
    // Free allocated memory for superheroes
    freeSuperheroes(superheroes, used);
    fclose(file); // Close the file
    return 0;
}