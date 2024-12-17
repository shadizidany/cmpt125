/*
name: Shadi Zidany
student ID:
computing-id:
*/
#ifndef _A4_SUPERHEROLIB_HPP_
#define _A4_SUPERHEROLIB_HPP_

#include <string> //needed for some string functions
#include <iostream> //to be able to print things
using namespace std; //so you don't have to use std:: all the time

// Macro to calculate total height in inches
#define HEIGHT(hero) ((hero)->feetInHeight * 12 + (hero)->inchesInHeight)

//the structure used for holding one superhero entry
typedef struct {
	string name;
	short feetInHeight;
	short inchesInHeight;
	string superpower;
	string traits;
} Superhero;

//Creates a Superhero struct variable storing a string
// representing a name, two shorts representing feet in height and inches
// in height respectively, a string representing a superpower,
// and a string representing an the traits.
//Returns the address of the dynamically (i.e., uses new) created variable
//For example:
//Given the code 
// (name, superpower, and traits are strings storing the proper information):
//Superhero*  superhero = createSuperhero(name, 6, 0, superpower, traits);
//cout << superhero->name << endl << superhero->feetInHeight << "\'"
//     << superhero->inchesInHeight << "\"" << endl << superhero->superpower
//     << ": " << superhero->traits << endl;
//will result in an output like this (superpower and traits are in one line):
//Thunderstrike
//6'0"
//Weather Control: Harnessing storms, Thunderstrike commands thunder and 
//lightning, using nature's fury to protect the innocent and fight against evil
Superhero* createSuperhero(const string name, 
                            short feetInHeight, short inchesInHeight,
                            const string superpower, const string traits);

//In contrast to Assignment 3, the clearSuperhero function is not needed
// because the string member fields have their own destructor to release memory

//In contrast to Assignment 3, the helper function to look up a superhero entry
// by title is moved to a4_superheroList, refer to a4_superheroList.hpp for
// details.

//helper function printing a superhero entry nicely
void printSuperhero(const Superhero* pSuperhero);

//In contrast to Assignment 3, we will be using stable_sort from <algorithm>
// to do the sorting.
// This function takes in a helper function returning a bool value indicating
// whether the element passed as first argument is considered to go before the
// second.
//This is the helper function for stable_sort to compare superheroes by height
bool compareSuperheroesByHeight(const Superhero* p1, const Superhero* p2);

//This is the helper function for stable_sort to compare superheroes by name
bool compareSuperheroesByName(const Superhero* p1, const Superhero* p2);

#endif