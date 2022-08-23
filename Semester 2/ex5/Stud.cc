#include "Stud.h"

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