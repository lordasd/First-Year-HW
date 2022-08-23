/*
file: Course.h
*/
#ifndef COURSE_H
#define COURSE_H

//-------Include_Section---------//
#include <iostream>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;

//-------------Const_Section----------------//
const int NUM_OF_COURSES = 10;

//-------------Struct_Section---------------//
struct Course{
    int _course_id;                    //מזהה הקורס
    double _credit_points;             //כמה נ"ז מקנה הקורס
    unsigned int _hours_of_course;     //כמה שעות כולל הקורס
};

//---------------Prototype_Section---------------//
void course_info_input(Course courses[]);
double avg_credit_points(void*, int&);
double avg_course_length(void*, int&);

#endif