#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'plusMinus' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void plusMinus(int arr_count, int* arr) {
    // Set the three counts positive, negative and zero elements.
    int positive_count = 0;
    int negative_count = 0;
    int zero_count = 0;

    // Count positive, negative, and zero elements.
    for (int i = 0; i < arr_count; i++) {
        if (arr[i] > 0) {
            positive_count++;
        } else if (arr[i] < 0) {
            negative_count++;
        } else {
            zero_count++;
        }
    }

    // Calculate proportions.
    double positive_proportion = (double)positive_count / arr_count;
    double negative_proportion = (double)negative_count / arr_count;
    double zero_proportion = (double)zero_count / arr_count;

    // Print proportions with 6 decimal places.
    printf("%.6lf\n", positive_proportion);
    printf("%.6lf\n", negative_proportion);
    printf("%.6lf\n", zero_proportion);
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    plusMinus(n, arr);

    return 0;
}

char* readline() {
    // Allocate initial buffer size
    size_t alloc_length = 1024;         // Set initial buffer size to 1024 characters
    size_t data_length = 0;             // Initialize the length of data read to 0

    char* data = malloc(alloc_length);  // Allocate memory for data buffer

    while (true) {                                                      // Start an infinite loop
        char* cursor = data + data_length;                              // Set the cursor to the end of data buffer
        char* line = fgets(cursor, alloc_length - data_length, stdin);  // Read input line all in Once from 'stdin' consol

        if (!line) {            // Check if end of file or error
            break;              // Exit the loop
        }

        data_length += strlen(cursor); // Update the length of data read

        // Check if more space is needed or end of line is reached
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;      // Exit the loop
        }

        alloc_length <<= 1;                     // Double the buffer size for more data if needed
        data = realloc(data, alloc_length);     // Reallocate memory for data buffer

        if (!data) {        // Check if memory allocation failed
            data = '\0';    // Set data to NULL
            break;          // Exit the loop
        }
    }

    // Replace newline with null terminator if present
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';               // Replace newline with null terminator
        data = realloc(data, data_length);          // Reallocate memory to trim excess
        if (!data) {                                // Check if memory reallocation failed
            data = '\0';                            // Set data to NULL
        }
    } else {
        data = realloc(data, data_length + 1);      // Reallocate memory to include null terminator
        if (!data) {                                // Check if memory reallocation failed
            data = '\0';                            // Set data to NULL
        } else {
            data[data_length] = '\0';               // Add null terminator
        }
    }

    return data; // Return the input string
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';        // Return NULL if input string is NULL
    }

    if (!*str) {
        return str;         // Return input string if it's empty
    }

    // Remove leading whitespace characters
    while (*str != '\0' && isspace(*str)) {
        str++;              // Move pointer to the next character
    }

    return str;             // Return pointer to the first non-whitespace character
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';        // Return NULL if input string is NULL
    }

    if (!*str) {
        return str;         // Return input string if it's empty
    }

    char* end = str + strlen(str) - 1;  // Pointer to the last character

    // Remove trailing whitespace characters
    while (end >= str && isspace(*end)) {
        end--;              // Move pointer backwards to the previous character
    }

    *(end + 1) = '\0';      // Add null terminator after the last non-whitespace character

    return str;             // Return input string
}

char** split_string(char* str) {
    char** splits = NULL;               // Initialize array of substrings to NULL
    char* token = strtok(str, " ");     // Split the input string by spaces that are a delimiters

    int spaces = 0;                     // Initialize count of substrings to 0

    while (token) {                     // Loop until strtok returns NULL
        splits = realloc(splits, sizeof(char*) * ++spaces);     // Reallocate memory for array of substrings

        if (!splits) {
            return splits;              // Return NULL if memory allocation fails
        }

        splits[spaces - 1] = token;     // Store current substring in the array

        token = strtok(NULL, " ");      // Get next substring
    }

    return splits;                      // Return array of substrings
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);       // Convert string to integer with base 10 'decimal'

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);                     // Exit program if conversion fails
    }

    return value;                               // Return integer value
}


/*
    NOTE:

    1. char* readline():

        This function reads a line of input from the standard input (stdin) and returns it as a string. 
        It dynamically allocates memory to accommodate the input string. 
        It keeps reading characters until it encounters a newline character or reaches the end of the file.
    
    2. char* ltrim(char* str):

        This function removes leading whitespace characters (spaces, tabs, etc.) 
        from the given string str and returns a pointer to the first non-whitespace character. 
        It returns the original string if it contains no leading whitespace.
    
    3. char* rtrim(char* str):

        This function removes trailing whitespace characters 
        from the given string str and returns the modified string. 
        It works by finding the last non-whitespace character in the string and appending a null terminator ('\0') after it.
    
    4. char** split_string(char* str):
    
        This function splits the given string str into an array of substrings based on the delimiter " ". 
        It returns a dynamically allocated array of strings (char**), where each element points to a substring. 
        It uses strtok() function for splitting.
    
    5. int parse_int(char* str):
    
        This function converts the given string str to an integer using strtol() function. 
        It returns the integer value if conversion is successful; otherwise, it exits the program with failure status.
*/