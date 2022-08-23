#include "Course.h"

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