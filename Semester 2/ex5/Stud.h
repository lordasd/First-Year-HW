/*
file: Stud.h
*/
#ifndef STUD_H
#define STUD_H

//-------Include_Section---------//
#include <iostream>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;

//-------------Const_Section----------------//
const int NUM_OF_GRADES = 7;
const int CLASS_SIZE = 10;

//-------------Struct_Section---------------//
struct Stud{
    int _stud_id;                      //מזהה התלמיד
    int _grades[NUM_OF_GRADES];        //ציוניו של התלמיד
    double _height;                    //גובהו של התלמיד
};

//---------------Prototype_Section---------------//
void stud_info_input(Stud studs[]);
void grades_input(Stud studs[], int index);
double stud_avg_grade(Stud*, int);
double total_avg_grades(void*, int&);
double avg_height(void*, int&);

#endif