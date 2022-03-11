/*
  This is a simplified interface to create histograms and print them
  on the terminal.
  
  how to use this interface:
  1. Create a new histogram, by calling create_hist(...).
    Note, that if there's already a histogram that you created before,
    it is erased.
  2. Fill the columns of the histogram, by calling add_col(...) - as many times as needed.
  3. Finally - print it by calling draw_hist().
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>
#include <string.h>

//---------------------------------------------
using std::cin ;
using std::cout ;
using std::cerr ;
using std::endl ;
using std::rand ;
using std::srand ;
using std::string ;
using std::to_string ;
using std::setw ;

//---------------------------------------------
// types and typedef
typedef unsigned int uint;

//---------------------------------------------
// Note: the alignment of the values in these 
//       declarations make is more readable.
const int HIST_MIN_HEIGHT   = 20;
const int HIST_MIN_WIDTH    = 36;
const int TITLE_MAX_LEN     = HIST_MIN_WIDTH - 10;
const int HIST_MIN_NUM_COLS = 2;
const int COL_MIN_WIDTH     = 3;
const int COL_MIN_SPACE     = 6;
const int COL_TITLE_MAX_LEN     = 9;

//---------------------------------------------
// *** header function prototypes ***

/*
create histogram: 
  ideally, this should return a pointer to the histogram.  
  However, since we don't with pointers in semester #1, 
  this is a global variable, hiddent from  the student (user).
*/
bool create_hist(
  int height, 
  int width, 
  int num_cols,     // max number of columns in the histogram
  const char title[TITLE_MAX_LEN], 
  char fill = '#',  // default char for this column
  int col_width = COL_MIN_WIDTH, 
  int col_space = COL_MIN_SPACE
); 

bool add_col(
  int col_indx, 
  uint value,  
  int lo,             // low value of range.  used for col title.
  int hi,             // high value of range. used for col title.
  const char* col_title,    // alternative to lo-hi.  You can send null-pointer 
                      // or an empty string (i.e. "").
  char fill = ' '     // if space, then use the hist char fill
);

void draw_hist();     // draw the histogram on the screen


