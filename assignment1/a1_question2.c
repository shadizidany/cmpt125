/*
name: Shadi Zidany
student ID:
computing-id:
*/
#include <stdbool.h> //for the bool type
/*
A function that checks if the elements between the left and right index
(inclusive) in the int array are sorted in ascending order.
Fixes the left and right indexes first if any of them are invalid.
Input: array - the array to be checked
       size - the size of the array (assumed to be correct)
       leftIndex - the left boundary of the check
       rightIndex - the right boundary of the check
Returns: whether the range is sorted or not
*/
bool rangedCheckforSorted(int array[], unsigned int size, int leftIndex,
                                                            int rightIndex) {
    // Swap indices if leftIndex is greater than rightIndex
    if (leftIndex > rightIndex) {
        int temp = leftIndex;
        leftIndex = rightIndex;
        rightIndex = temp;
    }
    // Adjust leftIndex if it is out of bounds
    if (leftIndex < 0 || leftIndex >= size) {
        leftIndex = 0;
    }
    // Adjust rightIndex if it is out of bounds
    if (rightIndex < 0 || rightIndex >= size) {
        rightIndex = size-1;
    }
    /* Check if the elements from leftIndex to rightIndex
       are sorted in ascending order */
    while (leftIndex < rightIndex) {
        if (array[leftIndex] > array[leftIndex+1]) {
            // Found an unsorted pair
            return false;
        }
        leftIndex++;
    }
    // The range is sorted
    return true;
}