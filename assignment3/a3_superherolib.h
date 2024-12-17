/*
name: Shadi Zidany
student ID:
computing-id:
*/
#ifndef _A3_SUPERHEROLIB_H_
#define _A3_SUPERHEROLIB_H_

#include <stdlib.h> //needed for handling dynamic memory
#include <string.h> //needed for some string functions
#include <stdio.h> // needed for reading superheroes data from file
#define BUFFER_SIZE 301 // each line having at most 300 characters
// Macro to calculate total height in inches
#define HEIGHT(hero) ((hero)->feetInHeight * 12 + (hero)->inchesInHeight)
// Macro to select the comparison function based on option
#define COMPARE(option) \
		((option) == 2 ? compareSuperheroesByHeight : compareSuperheroesByName)
//the structure used for holding one superhero entry
typedef struct {
	char* name;
	short feetInHeight;
	short inchesInHeight;
	char* superpower;
	char* traits;
} Superhero;

//Creates a Superhero struct variable storing a pointer to a char array
// representing a name, two shorts representing feet in height and inches
// in height respectively, a pointer to a char array representing a superpower,
// and a pointer to a array representing an the traits.
//Returns the address of the dynamically (i.e., uses malloc) created variable
//For example:
//Given the code 
// (name, superpower, and traits are Cstrings sotring the proper information):
//Superhero*  superhero = createSuperhero(name, 6, 0, superpower, traits);
//printf("%s\n%d\'%d\"\n%s: %s\n", superhero->name, superhero->feetInHeight, 
//      superhero->inchesInHeight, superhero->superpower, superhero->traits);
//will result in an output like this (superpower and traits are in one line):
//Thunderstrike
//6'0"
//Weather Control: Harnessing storms, Thunderstrike commands thunder and 
//lightning, using nature's fury to protect the innocent and fight against evil
Superhero* createSuperhero(const char* name, 
                            short feetInHeight, short inchesInHeight,
                            const char* superpower, const char* traits);

//Releases the memory created to store the 3 fields name, superpower,
// and traits using the address of a Superhero struct variable. Note
// that the parameter can be NULL, and if this is the case the function 
// should do nothing.
//Also, this function does not release the memory used for the struct variable,
// but only those used by the variable's fields. To release all the memory
// dynamically allocated for the struct variable, you should call the free()
// function with the address of this struct variable right after the function
// returns.
void clearSuperhero(Superhero* superhero);

//helper function to look up a superhero entry by superpower (Cstring)
//returns a dynamic array storing all the pointers to the superhero entries with
// superpower containing the input as a substring, NULL if not found.
//To make the size known to the caller, put a NULL as the last item.
// For example, if the first 3 entries have superpower containing "Fly",
// the array would have 4 items: {address_of_the_first_superhero,
// address_of_the_second_superhero, address_of_the_third_superhero, NULL}
Superhero** lookupSuperheroBySuperpower(Superhero **array,
										int size, const char* superpower);

//helper function for the sorting function (e.g., qsort) to compare superheroes
// by height (int)
int compareSuperheroesByHeight(const void *p1, const void *p2);

//helper function for the sorting function (e.g., qsort) to compare superheroes
// by name (Cstring)
int compareSuperheroesByName(const void *p1, const void *p2);

//sort function (uncomment & implement if you are not using the built-in qsort)
//void sortSuperheros(Superhero **array, int size,
//					int(*compar)(const void *, const void *));

/*
The `freeSuperheroes` function releases memory allocated for an array of
`Superhero` pointers. It iterates through the array, calling `clearSuperhero`
to free any associated resources for each superhero,then deallocates the memory
for the superhero objects themselves and sets their pointers to `NULL`.
Finally, it frees the array of pointers and sets it to `NULL`
to prevent dangling references.
*/
void freeSuperheroes(Superhero** superheroes);

/*
loadSuperheroes() reads superhero data from a specified file and 
returns a dynamically allocated array of pointers to Superhero structures.
It also updates the size variable to reflect the number of superheroes read.
The function handles memory allocation, resizing the array as needed, and 
ensures proper error handling in case of memory allocation failures.
It returns NULL if an error occurs during file reading or memory allocation,
and the size parameter is set to 0 in that case.
*/
Superhero** loadSuperheroes(FILE *file, int *size);

#endif