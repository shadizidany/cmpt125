/*
name: Shadi Zidany
student ID:
computing-id:
*/
/*
A function that reverses the polarity of every element in a 2D int array.
Accomplished using on pointers.
Input: row - number of rows in the array
       col - number columns in the array
       array - reference to the 2D array (pointer to int pointers)
Returns: nothing
*/
void reversePolarity(unsigned int row, unsigned int col, int** array) {
  // Iterate over each row of the array
  for (int r = 0; r < row; r++) {
    // Iterate over each column of the current row
    for (int c = 0; c < col; c++) {
      // Multiply array[r][c] by -1 to reverse its polarity
      *(*(array+r)+c) *= -1;
    }
  }
  return;
}