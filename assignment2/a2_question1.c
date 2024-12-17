/*
name: Shadi Zidany
student ID:
computing-id:
*/
#define BASE 10
/*
Replaces all occurrences of a target digit in a given number with
a replacement digit recursively.
number: The number in which digits are to be replaced.
target: The digit to be replaced.
replacement: The digit to replace the target with.
return: The new number with the target digits replaced by
the replacement digit.
*/
int replaceDigitsRecursiveHelper(int number, int target, int replacement) {
    // Base case: return 0 if the number is fully processed (no digits left)
    if (!number) {
        return 0;
    }
    // Recursive case: replace the target digit with the replacement
    if (number % BASE == target) {
        return replaceDigitsRecursiveHelper(number/BASE, target, replacement)
                                                        * BASE + replacement;
    }
    // Keep the current digit and continue recursion
    return replaceDigitsRecursiveHelper(number/BASE, target, replacement)
                                                * BASE + (number % BASE);
}
/*
A function that replaces a specific digit in an int number with another digit
and returns the result as an int.
return the same number if the target/replacement character is not a digit
Input: number - the number to be modified
       target - the digit to be replaced
       replacement - the digit used for replacement
Returns: the modified number
*/
int replaceDigitsRecursive(int number, char target, char replacement) {
    /*  Validate input: return the original number if inputs are invalid
        or if target equals replacement */
    if (target < '0' || target > '9' ||
        replacement < '0' || replacement > '9' || target == replacement) {
        return number;
    }
    // Handle edge case: return replacement if number=target=0
    if (!(number || target - '0')) {
        return replacement - '0';
    }
    /*  Handle negative numbers by processing the absolute value
        and negating the result */
    if (number < 0) {
        return -replaceDigitsRecursiveHelper(-number, target - '0',
                                                      replacement - '0');
    }
    // Initiate the recursive digit replacement process
    return replaceDigitsRecursiveHelper(number, target - '0',
                                                replacement - '0');
}