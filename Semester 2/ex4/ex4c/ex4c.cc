/* Ex4c: Operations on a generic dynamic array
*=============================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay

The goal of this program is to create (initialize) dynamic array, sort it,
print it and add new elements to it.

The array can be of any type. Specific in this exercise, Date or Time.

Program take input of 0/1(Date/Time).
After choosing the type to work with we get a menu of 5 options:
0 - Initialize - input Dates/Times.
1 - Print all the input.
2 - Sort all the input by year->month->day
3 - Add another item.
4 - Exit

Compile: g++ -Wall ex4c.cc ex4c_given.cc ex4c_given.h –o ex4c
Run: ./ex4c
Input: Program take input of 0/1(Date/Time).
After choosing the type to work with we get a menu of 5 options:
0 - Initialize - input Dates/Times.
1 - Print all the input.
2 - Sort all the input by year->month->day
3 - Add another item.
4 - Exit

*============================================*/
#include "ex4c_given.h"

void my_exit(int line, const char* msg)
{
  cerr << "internal error in line " << line 
       << " ; " << msg << endl;
  exit(1);
}

// ***  Generic functions and types  ***
typedef bool  (*read_item)  (void*);
typedef void  (*print_item) (void*);
typedef int   (*comp_items) (const void*, const void*);
typedef void  (*swap_items) (void*, void*);
typedef void  (*copy_item)  (void*, const void*); // first arg is destination
typedef void* (*alloc_arr)  (int size);
typedef void* (*alloc_item) ();
typedef void  (*delete_arr) (void*&);
typedef void  (*delete_item)(void*&);
typedef void* (*item_at)    (void* ptr, int index);


//*** Struct declarations ***

// structure to hold generic functions
struct Functions{
  read_item   _read_item;
  print_item  _print_item;
  comp_items  _comp_item;
  swap_items  _swap_item;
  copy_item   _copy_item;
  alloc_arr   _alloc_arr;
  alloc_item  _alloc_item;
  delete_arr  _delete_arr;
  delete_item _delete_item;
  item_at     _item_at;
};

struct Arr_Struct{
  int   _size;
  int   _capacity;
  void  *_arr;
};

/*===================================================
==  Date functions and Date Wrap Functions        ==*  
===================================================*/
bool read_date(void* item)
{
  return read_date(*(Date *)item);
}
//==================================================
void print_date(void *item)
{
  return print_date(*(Date *)item);
}
//==================================================
int comp_date(const void *it1, const void *it2)
{
  return comp_date(*(Date *)it1, *(Date *)it2);
}
//==================================================
void swap_date(void *it1, void *it2)
{
  swap_date(*((Date *)it1), *((Date *)it2));
}
//==================================================
void* alloc_date_arr(int size)
{
  void *arr = new (nothrow) Date[size];

  if(!arr)
  {
    cerr << "Cannot allocate memory\n";
    exit(EXIT_FAILURE);
  }
  
  return arr;
}
//==================================================
void* alloc_date_item()
{
  void *item = new (nothrow) Date;

  if(!item)
  {
    cerr << "Cannot allocate memory\n";
    exit(EXIT_FAILURE);
  }
  
  return item;
}
//==================================================
void copy_date(void *dest, const void *src)
{
  copy_date(*(Date *)dest, *(Date *)src);
}
//==================================================
void* date_at(void *item, int index)
{
  return (Date *)item + index;
}
//==================================================
void delete_date(void *&date)
{
  delete (Date *)date;
}
//==================================================
void delete_date_arr(void *&arr)
{
  delete[] (Date *)arr;
}
//==================================================
/*===================================================
==  Time functions and Time Wrap Functions        ==*  
===================================================*/
//==================================================
bool read_time(void* item)
{
  return read_time(*(Time *)item);
}
//==================================================
void print_time(void *item)
{
  return print_time(*(Time *)item);
}
//==================================================
int comp_time(const void *it1, const void *it2)
{
  return comp_time(*(Time *)it1, *(Time *)it2);
}
//==================================================
void swap_time(void *it1, void *it2)
{
  swap_time(*(Time *)it1, *(Time *)it2);
}
//==================================================
void* alloc_time_arr(int size)
{
  void *arr = new (nothrow) Time[size];

  if(!arr)
  {
    cerr << "Cannot allocate memory\n";
    exit(EXIT_FAILURE);
  }
  
  return arr;
}
//==================================================
void* alloc_time_item()
{
  void *item = new (nothrow) Time;

  if(!item)
  {
    cerr << "Cannot allocate memory\n";
    exit(EXIT_FAILURE);
  }
  
  return item;
}
//==================================================
void copy_time(void *dest, const void *src)
{
  copy_time(*(Time *)dest, *(Time *)src);
}
//==================================================
void* time_at(void *item, int index)
{
  return (Time *)item + index;
}
//==================================================
void delete_time(void *&date)
{
  delete (Time *)date;
}
//==================================================
void delete_time_arr(void *&arr)
{
  delete[] (Time *)arr;
}
//==================================================
/*===================================================
==         ex4c generic functions                 ==*  
===================================================*/

//  ****  global variables ***
const Functions DATE_FUNCS = {  
  read_date, 
  print_date, 
  comp_date,
  swap_date,
  copy_date,
  alloc_date_arr,
  alloc_date_item,
  delete_date_arr,
  delete_date,
  date_at
};

const Functions TIME_FUNCS = {  
  read_time, 
  print_time, 
  comp_time,
  swap_time,
  copy_time,
  alloc_time_arr,
  alloc_time_item,
  delete_time_arr,
  delete_time,
  time_at
};

//==================Fucntions=======================
//==================================================
void resize_arr(Arr_Struct& arr, const Functions* functions)
{
  void *new_arr;

  //Multiply the capacity each resize.
  arr._capacity *= 2;
  //Allocate memory to an array with new capacity.
  new_arr = functions->_alloc_arr(arr._capacity);

  //Copy old values to new array until old size.
  for(int i = 0; i < arr._size; i++)
  {
    functions->_copy_item(functions->_item_at(new_arr, i),
                          functions->_item_at(arr._arr, i));
  }
  //Remove old array, and reasign the pointer to the new array.
  functions->_delete_arr(arr._arr);
  arr._arr = new_arr;
}

//==================================================
bool add_item(Arr_Struct& arr, const Functions* functions)
{
  void *temp = functions->_alloc_item();
  bool valid = false; //validity of assigning an item

  if(functions->_read_item(temp))
  { //Reached the limit of the array capacity
    valid = true;
    if(arr._size == arr._capacity)
      resize_arr(arr, functions);
    
    functions->_copy_item(functions->_item_at(arr._arr, arr._size), temp);
    arr._size++;
  }
  //remove temporary allocation
  functions->_delete_item(temp);

  return valid;
}

//==================================================
void init_arr(Arr_Struct& arr, const Functions* functions)
{
  //If initialization is called again, delete memory.
  if(arr._size != 0)
    functions->_delete_arr(arr._arr);
  //Default Cap by the assignment
  arr._capacity = 2;
  //Array allocation
  arr._arr = functions->_alloc_arr(arr._capacity);
  arr._size = 0;

  while(add_item(arr, functions))
  {
    //Input items until -1/negative
  }
}

//==================================================
void print_arr(const Arr_Struct& arr, const Functions* functions)
{
  cout << "Size = " << arr._size 
       << " Capacity = " << arr._capacity << endl;
  for (int j=0 ; j < arr._size; j++)
  {
    //Prints an item[j] from the array
    functions->_print_item(functions->_item_at(arr._arr, j));
    cout << endl;
  }
}

//==================================================
void sort_arr(Arr_Struct& arr, const Functions* functions)
{
  for(int i = 0; i < arr._size-1; i++)
  {
    for(int j = 0; j < arr._size-i-1; j++)
    {
      if(functions->_comp_item(functions->_item_at(arr._arr, j),
                               functions->_item_at(arr._arr, j+1)) == 1)
      {     //Swap values if compare is true.
            functions->_swap_item(functions->_item_at(arr._arr, j),
                                functions->_item_at(arr._arr, j+1));
      }                          
    }
  }
}

//==================================================
void copy_date(Date &dest, const Date &src)
{ 
  dest._year  = src._year;
	dest._month = src._month;
	dest._day   = src._day;
}

//==================================================
void copy_time(Time &dest, const Time &src)
{
  dest._hour   = src._hour;
	dest._minute = src._minute;
	dest._second = src._second;
}

//==================================================
int main(int argc, char** argv)
{ 
  const Functions* func_ptr = nullptr;
  Arr_Struct arr;
  //Set 0 to all parameters
  arr._size = arr._capacity = 0;
  arr._arr = nullptr;
  
  Type type = select_type();
    
  switch (type)
  {
    case DATE:  func_ptr = &DATE_FUNCS;
                break;
    case TIME:  func_ptr = &TIME_FUNCS;
                break;
    default: my_exit(__LINE__, "bad Type");
  };
  
  while(true)
  {
    Action act = select_action();  
     
    switch (act)
    {
      case INIT:  init_arr(arr, func_ptr);
                  break;
      case PRINT: print_arr(arr, func_ptr);
                  break;
      case SORT:  sort_arr(arr, func_ptr);
                  break;
      case ADD:   add_item(arr, func_ptr);
                  break;
      case EXIT:  func_ptr->_delete_arr(arr._arr);
                  exit(0);
      default: my_exit(__LINE__, "bad action code");
    };
  }
}