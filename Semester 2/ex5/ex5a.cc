/* Ex4b: Statistic info of students & coruses
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program has 2 structures of "students" and "courses".
* Program takes input for students and courses arrays:
* Students: student_id(until 0), array of grades(until -1), height.
* Courses: course_id(until 0), credit_points, hours_of_course.
*
* Program is calling for a generic function to calculate averages 
* which transfers and array of a struct(students/courses) and a function
* to work with.
*
* Program calculates 4 averages and prints out 6 tasks:
* 1)Average of all grade averages (+) number of the highest avg grade student
* 2)Average height of student
* 3)Average of credit points
* 4)Average course length (+) course_id of the longest course
*
* Program Prints the averages each time after calculating.
* A the end the side tasks are also printed (+).    
*
*==================================*/
//-------Include_Section---------//
#include <cstdlib>
#include "Stud.h"
#include "Course.h"

//-----------Using_Section---------//
using std::cout;
using std::endl;

//-------------Struct_Section---------------//
struct Result{
    double _average;
    int    _index;
};

//-----------------TypeDefs-----------------//
typedef double(*type)(void*, int&);

//---------------Prototype_Section---------------//
Result find_avg(void*, type);
void print_averages(Stud studs[], Course courses[]);

//Calls input and print functions
int main()
{
    Stud   studs[CLASS_SIZE] = {0};
    Course courses[NUM_OF_COURSES] = {0};

    stud_info_input(studs);
    course_info_input(courses);

    print_averages(studs, courses);

    return EXIT_SUCCESS;
}

//Calls find_avg functions by inserting different parameters
//Per wanted task/function.
void print_averages(Stud studs[], Course courses[])
{
    Result res; //Will hold average results
    int index_of_best_stud, id_of_longest_course;

    //Average of all grade averages
    res = find_avg(studs, total_avg_grades);
    index_of_best_stud = res._index;
    cout << res._average << " ";

    //Average height of students
    res = find_avg(studs, avg_height);
    cout << res._average << " ";

    //Average of credit points
    res = find_avg(courses, avg_credit_points);
    cout << res._average << " ";

    //Average course length
    res = find_avg(courses, avg_course_length);
    id_of_longest_course = res._index;
    cout << res._average << " ";

    cout << index_of_best_stud << " " << id_of_longest_course << endl;
}

//Prepare a temp struct and call the task that has been transfered.
Result find_avg(void* arr, type task)
{
    Result res; //Create a temp result
    res._average = res._index = 0;
    res._average = task(arr, res._index);
    return res;
}