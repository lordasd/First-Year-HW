/* Ex6c: Finding a pattern with rules
*========================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is reading an array of 5X17, and searches in each row a pattern.
* Pattern have 3 rules, that needs to be followed the index amount of times
* that is saved in another array - rule_arr.
* We compare the input/values with enum type vaiables EVEN_PT = Checks for
* even numbers, POSITIVE_PT = Checks for positive numbers,
* and DIVIDE_BY_3_MPT = Checks for numbers divided by 3.
* We have 3 functions.
*
* main - reads all 3 functions and prints out the result:
* amount of patters, summed highest valued pattern.
*
* input_arr - takes input into arr - big array of 5X17
*
* rules_arr - takes input into rule_arr - array of N = 6.
* the inputs are valid only for 0-2 digits and the first
* index is skipped because the rule must be fulfilled the
* index amount of times.
* 
* find_patterns - takes both arrays and goes into a loop of ROW*COL*COL(3).
* it will check each column until third so if there are 3 starting points of
* a pattern so it will save all 3 of them.
* it will also sum up the highest valued pattern.
* if there are no patterns, return 0 of course and the value of the highest
* valued pattern will "-1".
*
*/
//--------Include Section---------//
#include <iostream>
#include <cstdlib>

//---------Using Section----------//
using std::cout;
using std::cin;
using std::endl;

//----------Constants-------------//
const int ROWS = 5;
const int COLS = 17;
const int N = 6;

//----------Prototypes------------//
void input_arr(int arr[][COLS]);
void rules_arr(int rule_arr[]);
int find_patterns(const int arr[][COLS], const int rule_arr[], int& max_sum);

//-----------Global---------------//
//variables automaticaly get 0, 1 , 2.
enum patterns_t{EVEN_PT, POSITIVE_PT, DIVIDE_BY_3_MPT};

//Main section is calling for 3 functions:
//Input_arr to read the input into the main array.
//Rules_arr to read value(0-2) into rule_arr.
//at the end it prints how many cells does the longest
//pattern have and the sum of the values in the pattern.
//-----------Main Section---------//
int main(){

    //Main array
    int arr[ROWS][COLS];
    //array of rule(0-2)
    int rule_arr[N];
    //Max sum of a pattern
    int max_sum = 0;
    //Amount of patterns
    int patterns;

    //Function to read input into an array of 5x17
    input_arr(arr);

    //Function to read input into array of rules N = 6
    rules_arr(rule_arr);

    //Find the patterns threw the array and return the amount of patterns.
    patterns = find_patterns(arr, rule_arr, max_sum);
    
    //print out the amount of patterns and the sum of
    //the highest valued pattern.
    cout << patterns << " " << max_sum << endl; 

    return EXIT_SUCCESS;
}

//Input values into the main array 5x17
void input_arr(int arr[][COLS]){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cin >> arr[i][j];
        }
    }
}

//Input values into a pattern_t array N = 6-1 because 
//index 0 is 0 times to complete a rule so we start from 1.
//Values of 0-2 to differ between the variable
//of the type pattern_t
void rules_arr(int rule_arr[]){

    for(int i = 1; i <= N-1; i++)
    {   
        int input;

        cin >> input;
        //EVEN_PT = 0
        if(input == EVEN_PT){
            rule_arr[i] = input;
        }
        //POSITIVE_PT = 1
        else if(input == POSITIVE_PT){
            rule_arr[i] = input;
        }
        //DIVIDE_BY_3_MPT = 2
        else if(input == DIVIDE_BY_3_MPT){
            rule_arr[i] = input;
        }
    }
}

//Find all the patterns that are followed by the rule_arr and return the
//amount of patterns and the sum of the highest valued pattern
int find_patterns(const int arr[][COLS], const int rule_arr[], int& max_sum)
{
    //Indexes
    int i, j, k;
    //Patterns amount
    int patterns = 0;
    //Boolian that checks if the pattern is complete
    bool pattern_occured = false;
    int sum;
    //Counter to follow how many times the same rule happend
    int counter;
    //rule = the value in the array of rules | rule_index = index for the
    //array of rules
    int rule, rule_index;
    //Boolian array to save the occured starting points of a pattern.
    bool start_occured[ROWS][COLS] = {false};
    
    //For loop of the arr
    for(i = 0; i < ROWS; i++)
    {
        //Reset of the values after each row
        pattern_occured = false;
        sum = 0;
        counter = 0;
        rule_index = 1;
        rule = rule_arr[rule_index];

        for(j = 0; j < COLS; j++)
        {
            //reset of the values after each sub-column
            pattern_occured = false;
            sum = 0;
            counter = 0;
            rule_index = 1;
            rule = rule_arr[rule_index];
            
            //3 time loop for each row to get all the possible patterns
            //that can occure between 0-15|1-16|2-17
            for(k = j; k < COLS; k++){
                //If j > 2 or a starting point already occured, break.
                if(j > 2 || start_occured[i][k])
                {
                    break;
                }
                //Switch for the rules
                switch(rule)
                {
                case EVEN_PT:
                    //Even numbers
                    if(arr[i][k] % 2 == 0)
                    {   
                        //sum of the values
                        sum += arr[i][k];
                        //counter for the amount of times the rule occured
                        counter++;
                    }
                    //Else reset values
                    else
                    {
                        rule_index = 1;
                        rule = rule_arr[rule_index];
                        counter = 0;
                    }
                    break;

                case POSITIVE_PT:
                    //Positive numbers
                    if(arr[i][k] > 0)
                    {
                        sum += arr[i][k];
                        counter++;
                    }
                    else
                    {
                        rule_index = 1;
                        rule = rule_arr[rule_index];
                        counter = 0;
                    }
                    break;

                case DIVIDE_BY_3_MPT:
                    //Can be divided by 3
                    if(arr[i][k] % 3 == 0)
                    {
                        sum += arr[i][k];
                        counter++;
                    }
                    else
                    {
                        rule_index = 1;
                        rule = rule_arr[rule_index];
                        counter = 0;
                    }
                    break;
                
                default:
                    rule_index = 1;
                    rule = rule_arr[rule_index];
                    counter = 0;
                    break;
                }
                //If counter got to the maximum amount of times it needs
                //to happen, continue and add +1 to the rule index.
                if(counter == rule_index)
                {  
                    counter = 0;
                    rule_index++;
                    rule = rule_arr[rule_index];

                    //If the rule index got to N = 6, which means he did
                    //1,2,3,4,5(15 numbers) time of each rule, then
                    //a pattern is complete
                    if(rule_index == N)
                    {
                        //calculation for the starting point of the pattern
                        //to set the value true so it won't start from this
                        //point again.
                        start_occured[i][k-14] = true;
                        pattern_occured = true;
                        break;
                    }      
                }  
            }
            //If pattern occured, change the max sum.
            if(pattern_occured)
            {
                patterns++;
                if(sum > max_sum)
                {
                    max_sum = sum;
                }
            }  
        }
    }
    //If no patterns found, max_sum = -1
    if(patterns == 0)
    {
        max_sum = -1;
    }
    return patterns;
}