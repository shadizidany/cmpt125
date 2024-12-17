/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a2_question2.h"
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
        return superhero = NULL;
    }
    // Copy the provided values into the Superhero struct fields
    strcpy(superhero->name, name);
    superhero->feetInHeight = feetInHeight;
    superhero->inchesInHeight = inchesInHeight;
    strcpy(superhero->superpower, superpower);
    strcpy(superhero->traits, traits);
    return superhero;
}