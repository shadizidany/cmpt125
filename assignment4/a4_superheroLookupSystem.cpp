/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a4_superheroList.hpp"

// Macro to list superheroes either by name or by height
#define LIST_HEROES(opt) ((opt) == 3 ? superheroes.listSuperheroesByName():\
                                       superheroes.listSuperheroesByHeight())

// Function to load a list of superheroes from a file
void loadSuperheroes(SuperheroList& superheroes, const string filename) {
    // Open the file for reading
    ifstream fin(filename);
    if (!fin) {
        cout << "Error in opening the file, check if it is available." << endl;
        return;
    }
    // Destroy existing list of superheroes
    superheroes.~SuperheroList();
    string name, feetInHeight, inchesInHeight, superpower, traits;
    // Read superheroes' information from the file
    while (!fin.eof()) {
        fin.ignore(10); // **Name:**<space>
        getline(fin, name);
        fin.ignore(12); // **Height:**<space>
        getline(fin, feetInHeight, '\'');
        getline(fin, inchesInHeight, '\"');
        fin.ignore(17); // <newline>**Superpower:**<space>
        getline(fin, superpower);
        getline(fin, traits);
        fin >> ws;
        // Insert superhero entry into the list
        superheroes.insertSuperhero(name, stoi(feetInHeight),
                                     stoi(inchesInHeight), superpower, traits);
    }
    // Close the file after reading all data
    fin.close();
    // Output the number of superheroes read from the file
    cout << superheroes.getSize() << " entries read." << endl;
}

// Function to add a new superhero to the list
void addSuperhero(SuperheroList& superheroes) {
    string name, superpower, traits;
    int feetInHeight = -1, inchesInHeight = -1;
    // Prompt the user for the superhero's name
    cout << "What is the name of the superhero? ";
    getline(cin >> ws, name);
    // Prompt the user for the superhero's height, ensuring it's valid
    while (feetInHeight < 0) {
        cout << "What is the feet part of the height "
             << "(input 0 or more and press enter)? ";
        cin >> feetInHeight;
        if (feetInHeight < 0) {
            cout << "Invalid input." << endl;
        }
    }
    while (inchesInHeight < 0) {
        cout << "What is the inches part of the height "
             << "(input 0 or more and press enter)? ";
        cin >> inchesInHeight;
        if (inchesInHeight < 0) {
            cout << "Invalid input." << endl;
        }
    }
    // Prompt the user for the superhero's superpower and traits
    cout << "What is the superpower of the superhero? ";
    getline(cin >> ws, superpower);
    cout << "What are the traits of the superhero? ";
    getline(cin >> ws, traits);
    // Display the entered superhero data for confirmation
    cout << "You have entered:" << endl
         << name << endl
         << feetInHeight << "\'" << inchesInHeight << "\"" << endl
         << superpower << ": " << traits << endl;
    // Insert the new superhero data into the list
    superheroes.insertSuperhero(name, feetInHeight, inchesInHeight, superpower,
                                                                       traits);
    cout << "Entry added." << endl;
}

// Main function: entry point of the program
int main() {
    // Display program header/banner
    cout <<"=========================================================="<< endl
         <<"================Superheroes Lookup System================="<< endl
         <<"=======================Shadi Zidany======================="<< endl
         <<"========================000000000========================="<< endl
         <<"=======================cmptid@sfu.ca======================"<< endl;
    SuperheroList superheroes;
    int option = 0;
    do {
        // Display main menu with available options
        cout << "=========================================================="
             << endl
             << "Press numbers 1-7 for the following options and then enter:"
             << endl << "1) to load a superheroes file." << endl
             << "2) to list superheroes sorted by height." << endl
             << "3) to list superheroes sorted by name." << endl
             << "4) to look up a superhero." << endl
             << "5) to add a superhero." << endl
             << "6) to save a suoerheroes file." << endl
             << "7) to terminate the program." << endl
             << "Option: ";
        // Read user's menu option selection
        cin >> option;
        switch (option) {
            case 1: {
                // Load superheroes from a file
                string filename;
                cout << "Enter the full name of the superheroes file "
                     << "(with extension): ";
                cin >> filename;
                loadSuperheroes(superheroes, filename);
                break;
            }

            case 2:
            case 3: {
                // List superheroes sorted by either height or name
                if (superheroes.getSize()) {
                    LIST_HEROES(option);
                    break;
                }
            }

            case 4: {
                if (!superheroes.getSize()) {
                    cout <<"No superheroes file loaded. Load one first."<<endl;
                    break;
                }
                // Look up a superhero by their superpower
                string superpower;
                cout << "What is the superpower, enter in part or as a whole "
                     << "(50 character max.)? ";
                cin >> superpower;
                superheroes.listSuperheroesContainingSuperpower(superpower);
                break;
            }

            case 5: {
                // Add a new superhero to the list
                addSuperhero(superheroes);
                break;
            }

            case 6: {
                // Save superheroes list to a file
                string filename;
                cout << "Enter the full name of the save file "
                     << "(with extension): ";
                cin >> filename;
                superheroes.saveSuperheroesToFile(filename);
            }

            case 7: {
                // Exit the program
                break;
            }

            default: {
                cout << "Unrecognized option." << endl;
            }
        }
    } while (option != 7);
    // Display program termination message
    cout << "The program has been terminated." << endl;
    return 0;
}