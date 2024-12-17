/*
name: Shadi Zidany
student ID:
computing-id:
*/
#define BASE 10 // Define the base for decimal numbers (base 10)
#define POSITIVE 1 // Define a constant for positive sign
#define NEGATIVE -1 // Define a constant for negative sign
/*
A function that replaces a specific digit in an int number with another digit
and returns the result as an int.
return the same number if the target/replacement character is not a digit
Input: number - the number to be modified
       target - the digit to be replaced
       replacement - the digit used for replacement
Returns: the modified number
*/
int replaceDigits(int number, char target, char replacement) {
    /* Check if target and replacement characters are valid digits (0-9)
       and not the same */
    if (target < '0' || target > '9' || replacement < '0' || replacement > '9'
                                                    || target == replacement) {
        // return the original number if invalid
        return number;
    }
    // Convert target and replacement characters to their integer values
    int targetDigit = target - '0';
    int replacementDigit = replacement - '0';
    // Initialize sign as positive
    int sign = POSITIVE;
    /* If the number is negative set sign to negative 
       and convert number to positive for processing */
    if (number < 0) {
        sign = NEGATIVE;
        number = -number;
    }
    // Handle special case where number is zero
    else if (number == 0 && targetDigit == 0) {
        return replacementDigit;
    }
    // Initialize place value (units, tens, hundreds, etc.)
    int place = 1;
    // Temporary variable to hold the original number
    int temp = number;
    // Loop to traverse each digit of the number
    while (temp > 0) {
        /* Check if the current least significant digit
           matches the target digit */
        if (temp % BASE == targetDigit) {
            /* Replace the target digit with the replacement digit
               at the current place value */
            number += (replacementDigit - targetDigit) * place;
        }
        // Move to the next digit's place (tens, hundreds, etc.)
        place *= BASE;
        // Remove the least significant digit from temp
        temp /= BASE;
    }
    // Return the modified number with the original sign
    return sign * number;
}