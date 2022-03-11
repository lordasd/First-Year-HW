#include "histogram.h"


//---------------------------------------------
// ****  Type declarations   ***
struct col{
  int col_indx;  // not a must. we could use the location in the array
  uint value;
  int lo;  //  low value of range
  int hi;  //  high value of range
  char fill;    // if space, then use the hist char fill
  char col_title[COL_TITLE_MAX_LEN+1];  // alternative to lo-hi
  bool valid;
};

struct hist {
  bool valid;
  int height;
  int width;
  int num_cols;
  int col_width;
  int col_space;
  char title[TITLE_MAX_LEN+1] ;
  col* cols;
  char fill ;
  uint max_val;
  char ** canvas;
  // char** canvas;  // for drawing - actually, 
                     // this can be created dynamically, when needed
};

//---------------------------------------------
// *** Global Variables ***
hist histo {false};  // histo.false designates invalidity
                     // is should also nullify other pointers, like canvas, 

//---------------------------------------------
// *** function prototypes ***
char** create_canvas();
void free_canvas();
void print_canvas();
void histo_debug();  // for debugging
void cols_debug();   // for debugging



//---------------------------------------------
// *** function code ***


//---------------------------------------------
void err_msg(const char* func, const string msg)
{
  cerr << "Error in function " << func << " : " << msg << endl;
  exit(EXIT_FAILURE);
}

//---------------------------------------------
void warn_msg(const char* func, string msg)
{
  cerr << "Warning in function " << func << " : " << msg << endl;
}

//---------------------------------------------
bool create_hist(
  int height, 
  int width, 
  int num_cols,
  const char title[TITLE_MAX_LEN], 
  char fill, // default char for the columns
  int col_width, 
  int col_space)
{
  // start with sanity/error checks
  if (height < HIST_MIN_HEIGHT)
    err_msg(__func__, "Height is less than minimal height " + to_string(HIST_MIN_HEIGHT));
  if (width < HIST_MIN_WIDTH)
    err_msg(__func__, "Width is less than minimal width " + to_string(HIST_MIN_WIDTH));
  if (num_cols < HIST_MIN_NUM_COLS)
    err_msg(__func__, "Num of Cols is less than minimum " + to_string(HIST_MIN_NUM_COLS));
  int effective_min_width = num_cols * (col_width + col_space) - col_space;
  if (width < effective_min_width)
    err_msg(__func__, "Width is less than effectively required width " + to_string(effective_min_width));
    
  // histogram seems to be OK. Create a new one.
  if (histo.valid)
  {
    delete[] histo.cols;
    free_canvas();
  }
  histo.valid = false;  // for future additions. 
                        // We are in a temporary state were the histogram is not valid.
  histo.height = height;
  histo.width = width;
  histo.num_cols = num_cols;
  histo.fill = fill;
  histo.col_width = col_width;
  histo.col_space = col_space;
  strncpy(histo.title, title, TITLE_MAX_LEN);

  histo.cols = new col[num_cols];
  if (! histo.cols) // the allocation failed
  {
    err_msg(__func__, "allocation of Columns array failed");
    return false;    
  }
  histo.valid = true;
  histo.canvas = create_canvas();
  histo.max_val = 0;
  
// print_canvas();
  return true;
}

//---------------------------------------------
void clear_col(int col_indx)
{
  col temp_col = {}; // this should set all the defaults.
                // if we need non default values, set them here. 
                // the assignment copies them. 
  
  histo.cols[col_indx] = temp_col;
}

//---------------------------------------------
bool add_col(
  int col_indx, 
  uint value,
  int lo,  //  low value of range
  int hi,  //  high value of range
  const char* col_title,    // alternative to lo-hi.  You can send null-pointer 
                      // or an empty string (i.e. "").
  char fill)   // if space, then use the hist char fill
{
  if (col_indx > histo.num_cols)
  {
    err_msg(__func__, "col index is too big");
    return false;        
  }
  if (histo.cols[col_indx].valid)
  {
    warn_msg(__func__, "col num is already initialized - Replacing it.");
    clear_col(col_indx);
  }
  histo.cols[col_indx].col_indx = col_indx;
  histo.cols[col_indx].value = value;
  if (value > histo.max_val)
    histo.max_val = value;
  histo.cols[col_indx].lo = lo;
  histo.cols[col_indx].hi = hi;
  histo.cols[col_indx].fill = fill == ' ' ? histo.fill : fill;
  if (col_title != nullptr)
    strncpy(histo.cols[col_indx].col_title, col_title, COL_TITLE_MAX_LEN);  
  histo.cols[col_indx].valid = true;
  return true;
}

//---------------------------------------------
char** create_canvas()
{
  int j;
  char** canvas = new char*[histo.height];
  for (j=0; j < histo.height; j++)
  {
    canvas[j] = new char[histo.width];
    for (int k = 0; k < histo.width; k++)
      canvas[j][k] = ' ';
  }
  return canvas;
}
//---------------------------------------------
void free_canvas()
{
  int j;
  for (j=0; j < histo.width; j++)
  {
    delete [] histo.canvas[j];
  }
  delete [] histo.canvas;
  histo.canvas = nullptr;
}


//---------------------------------------------
void print_line(char c, int len, int spaces_before, bool print_eol = true)
{
  for (int k = 0; k < spaces_before; k++)
    cout << ' ';
  for (int k = 0; k < len; k++)
    cout << c;
  if (print_eol)
    cout << endl;
}

//---------------------------------------------
void print_canvas()
{
  print_line('+', 1, 4, false);
  print_line('-', histo.width + 1, 0, false);
  cout << '+' << endl;
  for (int j=0; j < histo.height; j++)
  {
    cout << setw(4) << j << "| ";
    for (int k = 0; k < histo.width; k++)
      cout << histo.canvas[j][k];
    cout << '|' << endl;
  }
  print_line('+', 1, 4, false);
  print_line('-', histo.width + 1, 0, false);
  cout << '+' << endl;
}

//---------------------------------------------
void fill_col(int h, int start, int end, char fill)
{
  int h_end = histo.height - 3;  // last row is histo.height -1, and leave two rows at the bottom;
  int h_start = h_end - h + 1;
  for (int k = start; k <= end; k++)
    for(int j = h_start; j <= h_end; j++)
      histo.canvas[j][k] = fill;
}
// histogram.c - 
// draw simple text based histogram.
// code by Tzvi Melamed, Nov-2020
//---------------------------------------------
/*
  fill_col_title:
  This is not perfect, but Ok for now. We need the title to be evenly
  spread around the center of the column, including the spaces.  
  I leave it like that for now. (TzviM).
*/
void fill_col_title(int start, int end, int col_indx)
{
  int len;
  if ((len = strlen(histo.cols[col_indx].col_title)) > 0 ) // column title is not empty
    strncpy(&histo.canvas[histo.height - 1][start], histo.cols[col_indx].col_title, len);
  else
  sprintf(&histo.canvas[histo.height - 1][start], "%d-%d", histo.cols[col_indx].lo, histo.cols[col_indx].hi);
}
  
//---------------------------------------------
void fill_canvas_with_col()
{
  int h = histo.height - 5; // top 3 rows for the title
                            // bottom 2 rows for labels 
  if (histo.max_val == 0)
    return;  // othewise we're getting divide by zero
  for (int j=0; j < histo.num_cols; j++)
  {
    double col_h = ((double) histo.cols[j].value / histo.max_val) * h;
    int col_start = (histo.col_width + histo.col_space) * j;
    int col_end = col_start + histo.col_width;
    fill_col(int (col_h), col_start, col_end, histo.cols[j].fill);
    fill_col_title(col_start, col_end, j);
  }
}

//---------------------------------------------
void fill_canvas_bottom()
{
  char** canvas = histo.canvas;
  for (int j=0; j < histo.width; j++)
    canvas[histo.height - 2][j] = '-';
}

//---------------------------------------------
void fill_canvas_main_title()
{
  char** canvas = histo.canvas;
  int len = strlen(histo.title);
  strncpy(&canvas[1][(histo.width - len)/2], histo.title, TITLE_MAX_LEN);
}

//---------------------------------------------
void fill_canvas()
{
  fill_canvas_with_col();
  fill_canvas_bottom();
  fill_canvas_main_title();
}

//---------------------------------------------
/*
 draw_hist: 
  Create a canvas (matrix) with histogram size. 
  Fill it with blanks.
  then fill it with columns and title.
  Finally - print it to the screen.
*/
void draw_hist()
{
  if (! histo.valid)
    err_msg(__func__, "Creating canvas on non-valid histogram");
  fill_canvas();
  print_canvas();
}

/***************************************************************
      You can use the following for 
      debugging purpose if you need
***************************************************************/

//---------------------------------------------
//*** DEBUGGING MACRO / Definitions
int const DEB = 1;
#define FUNC if(DEB) cerr << "function: " << __func__ <<  " ** line: " << __LINE__ << "  file: " << __FILE__ << "  ** " << endl;
#define LINE if(DEB) cerr << "### line: " << __LINE__ << "  File: " << __FILE__ << "  ###" << endl;
#define LINE1 if(DEB) cerr << " line: " << __LINE__ << "  ";
#define PV(var) if(DEB) cout << #var << " = " << var << "  ";
#define PVE(var) if(DEB) cout << #var << " = " << var << "  " << endl;



/********************************************
  The following two functions - cols_debug and histo_debug are for debugging
  purpose only.
  They are using the debugging macro's defined in the header file.
*********************************************/
void cols_debug()
{
  for (int j = 0; j < histo.num_cols; j++)
  {
    cerr << "&&&&&&&&&&&&&&&&&&&&\n**** Col #" << j << " : ****" << endl;
    PV(histo.cols[j].col_indx)  
    PV(histo.cols[j].value)  
    PV(histo.cols[j].lo)  
    PV(histo.cols[j].hi)  
    PV(histo.cols[j].fill)  
    PV(histo.cols[j].col_title)  
    PVE(histo.cols[j].valid)
  }    
}

void histo_debug()
{
  cerr << "Data about Global variable **** Histo ****" << endl;
  PVE(histo.valid)
  PVE(histo.height)
  PVE(histo.width)
  PVE(histo.num_cols)
  PVE(histo.col_width)
  PVE(histo.col_space)
  cerr << "histo.title[TITLE_MAX_LEN+1] = " << histo.title  << endl;
  PVE(histo.title)
  PVE(histo.cols)
  PVE(histo.fill )
  PVE(histo.max_val)
  PVE(histo. canvas)
  cols_debug();
  cerr << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}





