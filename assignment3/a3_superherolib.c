/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a3_superherolib.h"
/*
Creates a Superhero struct variable storing a pointer to a char array
representing a name, two shorts representing feet in height and inches
in height respectively, a pointer to a char array representing a superpower,
and a pointer to a array representing an the traits.
Returns the address of the dynamically created variable
*/
Superhero* createSuperhero(const char* name, short feetInHeight,
                           short inchesInHeight, const char* superpower,
                                                        const char* traits) {
    // Allocates memory and initializes all bytes in the allocated storage to 0
    Superhero* superhero = calloc(1, sizeof(Superhero));
    // Check if memory allocation was successful
    if (!superhero) {
        return NULL;
    }
    /* Allocate memory for strings and ensure null-termination
       Verify that all string allocations were successful
       Note: sizeof(char) always returns 1 */
    if (!((superhero->name = malloc(strlen(name) + 1)) &&
          (superhero->superpower = malloc(strlen(superpower) + 1)) &&
          (superhero->traits = malloc(strlen(traits) + 1)))) {
        clearSuperhero(superhero);
        free(superhero);
        return NULL;
    }
    // Copy the provided values into the Superhero struct fields
    strcpy(superhero->name, name);
    superhero->feetInHeight = feetInHeight;
    superhero->inchesInHeight = inchesInHeight;
    strcpy(superhero->superpower, superpower);
    strcpy(superhero->traits, traits);
    return superhero;
}
/*
Releases the memory created to store the 3 fields name, superpower,
and traits using the address of a Superhero struct variable. Note
that the parameter can be NULL, and if this is the case the function 
should do nothing.
Also, this function does not release the memory used for the struct variable,
but only those used by the variable's fields. To release all the memory
dynamically allocated for the struct variable, you should call the free()
function with the address of this struct variable right after the function
returns.
*/
void clearSuperhero(Superhero* superhero) {
    // Return if the superhero pointer is NULL
    if (!superhero) {
        return;
    }
    // Free allocated memory for each string in the Superhero struct
    free(superhero->name); // If a NULL pointer, the function does nothing
    free(superhero->superpower);
    free(superhero->traits);
    // Set pointers to NULL to avoid dangling references
    superhero->name = superhero->superpower = superhero->traits = NULL;
}
/*
helper function to look up a superhero entry by superpower (Cstring)
returns a dynamic array storing all the pointers to the superhero entries with
superpower containing the input as a substring, NULL if not found.
To make the size known to the caller, put a NULL as the last item. For example,
if the first 3 entries have superpower containing "Fly",
the array would have 4 items: {address_of_the_first_superhero,
address_of_the_second_superhero, address_of_the_third_superhero, NULL}
*/
Superhero** lookupSuperheroBySuperpower(Superhero **array,
                                        int size, const char* superpower) {
    Superhero** superheroes = NULL;
    // Initialize capacity and count of used superhero entries
    int capacity = 1, used = 0;
    for (int i = 0; i < size; i++) {
        if (strstr(array[i]->superpower, superpower)) {
            // Check if the array needs to be resized
            if (used+1 == capacity) {
                // Double the capacity of the superheroes array
                capacity *= 2;
                /* If superheroes is NULL,
                the behavior is the same as calling malloc(new_size). */
                Superhero** temp = realloc(superheroes,
                                           capacity * sizeof(Superhero*));
                // Handle potential memory reallocation failure
                if (!temp) {
                    free(superheroes);
                    return NULL;
                }
                // Update the pointer to the resized array
                superheroes = temp;
            }
            superheroes[used++] = array[i];
        }
    }
    if (used) {
        superheroes[used] = NULL;
    }
    return superheroes;
}
/*
helper function for the sorting function (e.g., qsort) to compare superheroes
by height (int)
*/
int compareSuperheroesByHeight(const void *p1, const void *p2) {
    // Dereference p1 and p2 to get pointers to Superhero objects
    const Superhero* heroA = *(const Superhero**)p1;
    const Superhero* heroB = *(const Superhero**)p2;
    // Compare the height of the two superheroes using the HEIGHT macro
    int heightComparison = HEIGHT(heroA) - HEIGHT(heroB);
    if (!heightComparison) {
        return strcmp(heroA->name, heroB->name);
    }
    return heightComparison;
}
/*
helper function for the sorting function (e.g., qsort) to compare superheroes
by name (Cstring)
*/
int compareSuperheroesByName(const void *p1, const void *p2) {
    // Dereference p1 and p2 to get pointers to Superhero objects
    const Superhero* heroA = *(const Superhero**)p1;
    const Superhero* heroB = *(const Superhero**)p2;
    // Compare the superheroes' names using strcmp
    int nameComparison = strcmp(heroA->name, heroB->name);
    if (!nameComparison) {
        return HEIGHT(heroA) - HEIGHT(heroB);
    }
    return nameComparison;
}
/*
The `freeSuperheroes` function releases memory allocated for an array of
`Superhero` pointers. It iterates through the array, calling `clearSuperhero`
to free any associated resources for each superhero,then deallocates the memory
for the superhero objects themselves and sets their pointers to `NULL`.
Finally, it frees the array of pointers and sets it to `NULL`
to prevent dangling references.
*/
void freeSuperheroes(Superhero** superheroes) {
    // Return if the superheroes pointer is NULL
    if (!superheroes) {
        return;
    }
    /*  Iterate through the array of Superhero pointers to free
        all allocated memory and avoid dangling references */
    for (int i = 0; superheroes[i]; i++) {
        clearSuperhero(superheroes[i]);
        free(superheroes[i]);
        // superheroes[i] = NULL;
    }
    // Free the array of Superhero pointers and set it to NULL
    free(superheroes);
}
/*
loadSuperheroes() reads superhero data from a specified file and 
returns a dynamically allocated array of pointers to Superhero structures.
It also updates the size variable to reflect the number of superheroes read.
The function handles memory allocation, resizing the array as needed, and 
ensures proper error handling in case of memory allocation failures.
It returns NULL if an error occurs during file reading or memory allocation,
and the size parameter is set to 0 in that case.
*/
Superhero** loadSuperheroes(FILE *file, int *size) {
    // Allocate initial memory for an array of Superhero pointers
    Superhero** superheroes = NULL;
    // Initialize capacity and count of used superhero entries
    int capacity = 1, used = 0, error = 0;
    // Declare buffers for reading superhero attributes
    char name[BUFFER_SIZE] = {0}, superpower[BUFFER_SIZE] = {0},
                                      traits[BUFFER_SIZE] = {0};
    int feet = 0, inches = 0;
    // Read superheroes from the file until end-of-file is reached
    while (!feof(file)) {
        // Read superhero details from the file
        fscanf(file, " **Name:** %[^\n] ", name);
        fscanf(file, " **Height:** %d'%d\" ", &feet, &inches);
        fscanf(file, " **Superpower:** %[^\n] ", superpower);
        fscanf(file, " %[^\n] ", traits);
        // Check if the array needs to be resized
        if (used+1 == capacity) {
            // Double the capacity of the superheroes array
            capacity *= 2;
            Superhero** temp = realloc(superheroes,
                                       capacity * sizeof(Superhero*));
            // Handle potential memory reallocation failure
            if (!temp) {
                error = 1;
                break;
            }
            // Update the pointer to the resized array
            superheroes = temp;
        }
        // Create a new Superhero. If allocation fails, exit the loop
        if (!(superheroes[used++] = createSuperhero(name, feet, inches,
                                                        superpower, traits))) {
            error = 1;
            break;
        }
    }
    // Set the last element to NULL (end of array marker)
    if (used) {
        superheroes[used] = NULL;
    }
    // Free memory if there was an error
    if (error) {
        freeSuperheroes(superheroes);
    }
    // Return the loaded superheroes array or NULL in case of an error
    *size = (!error) ? used : 0;
    return (*size) ? superheroes : NULL;
}