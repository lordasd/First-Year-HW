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
#include <iostream>
#include <cmath>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

//-------------Const_Section----------------//
const int NUM_OF_GRADES = 7;
const int CLASS_SIZE = 10;
const int NUM_OF_COURSES = 10;

//-------------Struct_Section---------------//
struct Stud{
    int _stud_id;                      //מזהה התלמיד
    int _grades[NUM_OF_GRADES];        //ציוניו של התלמיד
    double _height;                    //גובהו של התלמיד
};

struct Course{
    int _course_id;                    //מזהה הקורס
    double _credit_points;             //כמה נ"ז מקנה הקורס
    unsigned int _hours_of_course;     //כמה שעות כולל הקורס
};

struct Result{
    double _average;
    int _index;
};

//---------------Prototype_Section---------------//
void stud_info_input(Stud studs[]);
void grades_input(Stud studs[], int index);
void course_info_input(Course courses[]);

void print_averages(Stud studs[], Course courses[]);
Result find_avg(void*, double(*func)(void*, int&));

double total_avg_grades(void*, int&);
double stud_avg_grade(Stud*, int);
double avg_height(void*, int&);
double avg_credit_points(void*, int&);
double avg_course_length(void*, int&);

//Calls input and print functions
int main()
{
    Stud studs[CLASS_SIZE] = {0};
    Course courses[NUM_OF_COURSES] = {0};

    stud_info_input(studs);
    course_info_input(courses);

    print_averages(studs, courses);

    return EXIT_SUCCESS;
}

//Input ID and height for students.
void stud_info_input(Stud studs[])
{
    int id;
    cin >> id;
    for(int stud = 0; stud < CLASS_SIZE && id != 0; stud++)
    {
        studs[stud]._stud_id = id;
        grades_input(studs, stud);
        cin >> studs[stud]._height;
        cin >> id;
    }
}

//Input grades for student[stud].
void grades_input(Stud studs[], int stud)
{
    int grade;
    cin >> grade;
    for(int grad = 0; grad < NUM_OF_GRADES; grad++)
    {
        studs[stud]._grades[grad] = grade;
        if(grade == -1)
            break;
        cin >> grade;
    }
}

//Input course ID, credit_points & hourse_of_course.
void course_info_input(Course courses[])
{
    int id;
    cin >> id;
    for(int course = 0; course < NUM_OF_COURSES && id != 0; course++)
    {
        courses[course]._course_id = id;
        cin >> courses[course]._credit_points;
        cin >> courses[course]._hours_of_course;
        cin >> id;
    }
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
Result find_avg(void* arr, double(*func)(void*, int&))
{
    Result res; //Create a temp result
    res._average = res._index = 0;
    res._average = func(arr, res._index);
    return res;
}

//Finding the average grade of all average grade of all students
//+ the highest avg student grade(index)
double total_avg_grades(void* arr, int& index_max)
{
    Stud *studs = (Stud*)arr; //Struct type cast for void* array
    double total_avg = 0, stud_avg, max_avg = 0;//Averages
    int students = 0; //Amount of students
    //finding the avg of all avg of students
    for(int stud = 0; studs[stud]._stud_id != 0 && stud < CLASS_SIZE; stud++)
    {   //avg of a student
        stud_avg = stud_avg_grade(studs, stud);
        if(stud_avg > max_avg)//Found highest avg student
        {
            max_avg = stud_avg;
            index_max = stud+1;
        }
        total_avg += stud_avg;
        students++;
    }
    if(total_avg == 0)
        return 0;
    return total_avg / students;
}

//Finding the grade avg of a student
double stud_avg_grade(Stud* studs, int student)
{
    double avg = 0;
    int grades = 0;
    for(int grade = 0; studs[student]._grades[grade] != -1 &&
        grade < CLASS_SIZE; grade++)
    {
        avg += studs[student]._grades[grade];
        grades++;
    }
    return avg / grades;
}

//Finding Average height of all students
double avg_height(void* arr, int& index_max)
{
    Stud *studs = (Stud*)arr;
    double height = 0;
    int students = 0;
    for(int stud = 0; studs[stud]._stud_id != 0 && stud < CLASS_SIZE; stud++)
    {
        height += studs[stud]._height;
        students++;
    }
    if(height == 0)
        return 0;
    return height / students;
}

//Calculates average credit points from all courses
double avg_credit_points(void* arr, int& index_max)
{
    Course *courses = (Course*)arr;
    double points = 0;
    int courses_amount = 0;
    for(int course = 0; courses[course]._course_id != 0 &&
        course < NUM_OF_COURSES; course++)
    {
        points += courses[course]._credit_points;
        courses_amount++;
    }
    if(points == 0)
        return 0;
    return points / courses_amount;
}

//Calculates average course length and saves the
//course id of the longest course.
double avg_course_length(void* arr, int& index_max)
{
    Course *courses = (Course*)arr;
    double total_course_len = 0, course_len, longest_course_len = 0;
    int courses_amount = 0;
    for(int course = 0; courses[course]._course_id != 0 &&
        course < NUM_OF_COURSES; course++)
    {
        course_len = courses[course]._hours_of_course;
        if(course_len > longest_course_len)//Found longest course
        {
            longest_course_len = course_len;
            index_max = courses[course]._course_id;
        }
        total_course_len += course_len;
        courses_amount++;
    }
    if(total_course_len == 0)
        return 0;
    return total_course_len / courses_amount;
}