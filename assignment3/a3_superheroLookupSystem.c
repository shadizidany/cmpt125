/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a3_superherolib.h"
#define MAX_INPUT 51   // user input having at most 50 characters
/*
The `printSuperheroes` function displays a formatted list of superhero details.
It takes an array of pointers to `Superhero` structures and an integer
representing the number of superheroes. The function prints a header for
the "Superheroes Lookup System" and iterates through the array,outputting each
superhero's name, height, superpower, and traits in a structured format.
*/
void printSuperheroes(Superhero** superheroes) {
    // Iterate through the array of Superhero pointers and print their details
    for (int i = 0; superheroes[i]; i++) {
        printf("==========================================================\n");
        printf("Superhero #%d\n", i+1);
        printf("%s\n", superheroes[i]->name);
        printf("%d'%d\"\n", superheroes[i]->feetInHeight,
                            superheroes[i]->inchesInHeight);
        printf("%s: %s\n", superheroes[i]->superpower, superheroes[i]->traits);
    }
}
/*
The main function provides interactive menu for the Superheroes Lookup System.
It allows the user to:
1) Load a superheroes file from disk.
2) List superheroes sorted by height.
3) List superheroes sorted by name.
4) Look up superheroes by their superpower.
5) Terminate the program.
The program handles user input, performs actions based on the selected option,
and ensures proper memory management for loaded superheroes.
*/
int main() {
    // Print the header for the Superheroes Lookup System
    printf("==========================================================\n");
    printf("================Superheroes Lookup System=================\n");
    printf("=======================Shadi Zidany=======================\n");
    printf("========================000000000=========================\n");
    printf("=======================cmptid@sfu.ca======================\n");
    Superhero** superheroes = NULL;
    int option = 0, size = 0;
    do {
        // Print the menu options for the user
        printf("==========================================================\n");
        printf("Press number 1-5 for the following options and then enter:\n");
        printf("1) to load a superheroes file.\n");
        printf("2) to list superheroes sorted by height.\n");
        printf("3) to list superheroes sorted by name.\n");
        printf("4) to look up a superhero.\n");
        printf("5) to terminate the program.\n");
        // Get the user's choice of option
        if (!scanf("%d", &option)) {
            scanf("%*s"); // Flush invalid input
            printf("Invalid input.\n");
            continue;
        }
        printf("Option: %d\n", option);
        switch (option) {
            case 1:
                // Load the superheroes file
                printf(
                "Enter the full name of the superheroes file (with extension): ");
                char filename[MAX_INPUT] = {0};
                scanf(" %[^\n]", filename);
                // Open the file containing superhero data for reading
                FILE* file = fopen(filename, "r");
                if (!file) {
                    printf(
                    "Error in opening the file, check if it is available.\n");
                    break;
                }
                // Free any previously loaded superheroes
                freeSuperheroes(superheroes);
                // Attempt to load superhero data from a file. If successful,
                // print the number of entries read; if memory allocation fails,
                // print an error message. Then, close the file and break from the loop.
                if ((superheroes = loadSuperheroes(file, &size))) {
                    printf("%d entries read.\n", size);
                }
                else {
                    printf("Memory allocation failed.\n");
                }
                fclose(file); // Close the file after processing
                break;
            case 2:
            case 3:
                // Sort superheroes by height (case 2) or by name (case 3)
                if (size) {
                    qsort(superheroes, size,
                                       sizeof(Superhero*), COMPARE(option));
                    printSuperheroes(superheroes);
                    break;
                }
            case 4:
                // Look up a superhero by superpower
                if (!size) {
                    printf("No superheroes file loaded. Load one first.\n");
                    break;
                }
                char superpower[MAX_INPUT] = {0};
                printf(
                "What is the superpower, enter in part or as a whole (50 character max.)? ");
                scanf(" %[^\n]", superpower);
                // Attempt to lookup superheroes by their superpower. If found,
                // print the list of superheroes and free the allocated memory.
                // If no superheroes match found, display an error message.
                Superhero** heroes =
                    lookupSuperheroBySuperpower(superheroes, size, superpower);
                if (heroes) {
                    printSuperheroes(heroes);
                    free(heroes);
                }
                else {
                    printf("No such superhero on record.\n");
                }
            case 5:
                // Exit the program
                break;
            default:
                // Handle invalid options
                printf("Unrecognized option.\n");
        }
    } while (option != 5);
    // Free the memory allocated for the superheroes array,
    freeSuperheroes(superheroes);
    // print a termination message, and exit the program successfully.
    printf("The program has been terminated.\n");
    return 0;
}