/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a4_superheroList.hpp"

//constructor
SuperheroList::SuperheroList() {}

//destructor: free up all the Superhero* items
SuperheroList::~SuperheroList() {
    // Loop through all Superhero* entries and free memory
    for (Superhero* superhero : superheroEntries) {
        delete superhero;
    }
    // ensuring no dangling pointers remain
    superheroEntries = vector<Superhero*>();
}

//return the size of the list (i.e., number of superheros)
int SuperheroList::getSize() {
    return superheroEntries.size();
}

//list superheroes sorted by height
void SuperheroList::listSuperheroesByHeight() {
    // Sort superheroEntries by height
    stable_sort(superheroEntries.begin(),
                superheroEntries.end(), compareSuperheroesByHeight);
    // Print each superhero in the sorted list
    for (size_t i = 0; i < superheroEntries.size(); i++) {
        cout << "=========================================================="
             << endl << "Superhero #" << i+1 << endl;
        printSuperhero(superheroEntries[i]);
    }
}

//list superheroes sorted by name
void SuperheroList::listSuperheroesByName() {
    // Sort superheroEntries by name
    stable_sort(superheroEntries.begin(),
                superheroEntries.end(), compareSuperheroesByName);
    // Print each superhero in the sorted list
    for (size_t i = 0; i < superheroEntries.size(); i++) {
        cout << "=========================================================="
             << endl << "Superhero #" << i+1 << endl;
        printSuperhero(superheroEntries[i]);
    }
}

//create and insert a Superhero entry to the list
void SuperheroList::insertSuperhero(const string name,
                                short feetInHeight, short inchesInHeight,
                                const string superpower, const string traits) {
    // Create a new Superhero
    Superhero* superhero = createSuperhero(name, feetInHeight, inchesInHeight,
                                                           superpower, traits);
    // Check if memory allocation succeeded
    if (!superhero) {
        return;
    }
    // Add the newly created Superhero to the superheroEntries list
    superheroEntries.push_back(superhero);
}

//list superheros that have superpower containing the keySuperpower
void SuperheroList::listSuperheroesContainingSuperpower(
                                                  const string keySuperpower) {
    int count = 0;
    // Loop through all superheroes in the list
    for (Superhero* superhero : superheroEntries) {
        // Check if the superhero's superpower contains the keySuperpower
        if (superhero->superpower.find(keySuperpower) != string::npos) {
            cout <<"=========================================================="
                 << endl << "Superhero #" << ++count << endl;
            printSuperhero(superhero);
        }
    }
    // If no superheroes match the search, print a message indicating no match
    if (!count) {
        cout << "No such superhero on record." << endl;
    }
}

//save all the superheroes into a file using the sample format
void SuperheroList::saveSuperheroesToFile(const string filename) {
    // Open the output file stream for writing
    ofstream fout(filename);
    if (!fout) {
        cout << "Error in opening/creating the file." << endl;
        return;
    }
    // Loop through all superheroes and write their details to the file
    for (size_t i = 0; i < superheroEntries.size(); i++) {
        fout << "**Name:** " << superheroEntries[i]->name << endl
             << "**Height:** " << superheroEntries[i]->feetInHeight << "\'"
             << superheroEntries[i]->inchesInHeight << "\"" << endl
             << "**Superpower:** " << superheroEntries[i]->superpower << endl
             << superheroEntries[i]->traits << endl;
        if (i != superheroEntries.size() - 1) {
            fout << endl;
        }
    }
    // Close the output file stream and confirm the number of entries saved
    fout.close();
    cout << superheroEntries.size() << " entries saved." << endl;
}