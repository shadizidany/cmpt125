/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include "a4_superherolib.hpp"

//Creates a Superhero struct variable storing a string
// representing a name, two shorts representing feet in height and inches
// in height respectively, a string representing a superpower,
// and a string representing an the traits.
//Returns the address of the dynamically (i.e., uses new) created variable
Superhero* createSuperhero(const string name,
                           short feetInHeight, short inchesInHeight,
                           const string superpower, const string traits) {
    // Using new(std::nothrow) (returns nullptr if allocation fails)
    Superhero* superhero = new(nothrow) Superhero;
    // Check if memory allocation succeeded
    if (!superhero) {
        return nullptr;
    }
    // Set the values of the superhero fields
    superhero->name = name;
    superhero->feetInHeight = feetInHeight;
    superhero->inchesInHeight = inchesInHeight;
    superhero->superpower = superpower;
    superhero->traits = traits;
    return superhero;
}

//helper function printing a superhero entry nicely
void printSuperhero(const Superhero* pSuperhero) {
    // Print superhero name, height, superpower, and traits
    cout << pSuperhero->name << endl
         << pSuperhero->feetInHeight << "\'"
         << pSuperhero->inchesInHeight << "\"" << endl
         << pSuperhero->superpower << ": " << pSuperhero->traits << endl;
}

//This is the helper function for stable_sort to compare superheroes by height
bool compareSuperheroesByHeight(const Superhero* p1, const Superhero* p2) {
    // Compare superheroes first by height
    // and then by name if heights are equal
    if (HEIGHT(p1) == HEIGHT(p2)) {
        return p1->name < p2->name;
    }
    return HEIGHT(p1) < HEIGHT(p2);
}

//This is the helper function for stable_sort to compare superheroes by name
bool compareSuperheroesByName(const Superhero* p1, const Superhero* p2) {
    // Compare superheroes first by name
    // and then by height if names are equal
    if (p1->name == p2->name) {
        return HEIGHT(p1) < HEIGHT(p2);
    }
    return p1->name < p2->name;
}