/*
name: Shadi Zidany
student ID:
computing-id:
*/
#ifndef _A4_SUPERHEROLIST_HPP_
#define _A4_SUPERHEROLIST_HPP_

#include "a4_superherolib.hpp" //to recognize and use all the superhero code

#include <vector> //to store Superhero* as items & provide array-like functions
#include <string> //to handle string variables like name, superpower and traits
#include <algorithm> //to be able to sort things
#include <iostream> //to be able to do console I/O
#include <fstream> //to be able to do file I/O
using namespace std; //so you don't have to use std:: all the time

//The definition of the SuperheroList class
class SuperheroList {
    private:
        vector<Superhero*> superheroEntries; //storing the Superheroes*

    public:
        //constructor
        SuperheroList();
        //destructor
        // use this to free up all the Superhero* items
        ~SuperheroList();
        //return the size of the list (i.e., number of superheros)
        int getSize();
        //list superheroes sorted by height
        // call the stable_sort function here and use the helper functions
        // from a4_superherolib
        void listSuperheroesByHeight();
        //list superheroes sorted by name
        // call the stable_sort function here and use the helper functions
        // from a4_superherolib
        void listSuperheroesByName();
        //create and insert a Superhero entry to the list
        // first use createSuphero to create a Superhero entry,
        // then use the push_back method of vector to insert as Superhero*
        void insertSuperhero(const string name,
                            short feetInHeight, short inchesInHeight,
                            const string superpower, const string traits);
        //list superheros that have superpower containing the keySuperpower
        // as substring, use the find method of string for matching,
        //look up string::npos
        // reference: https://cplusplus.com/reference/string/string/find/
        void listSuperheroesContainingSuperpower(const string keySuperpower);
        //save all the superheroes into a file using the sample format
        void saveSuperheroesToFile(const string filename);
};

#endif