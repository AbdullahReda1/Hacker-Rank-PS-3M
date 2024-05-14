//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for isspace()

// Function to check if a character is uppercase
int isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

// Function to convert a character to lowercase
char toLowerCase(char c) {
    if (isUpperCase(c)) {
        return c + 32; // ASCII conversion to lowercase
    }
    return c;
}

// Function to split a camel case string into words
void splitCamelCase(char* str) {
    int length = strlen(str);
    int lastCase = -1;
    
    for (int i = 0; i < length; i++) {
        if (isUpperCase(str[i])) { // Using ASCII values to check for uppercase
            if (lastCase == 0) {
                putchar(' ');
            }
            putchar(toLowerCase(str[i]));
            lastCase = 1;
        } else {
            putchar(str[i]);
            lastCase = 0;
        }
    }
    putchar('\n');
}

// Function to combine words into a camel case string
void combineCamelCase(char* str, int isClass) {
    int length = strlen(str);
    int lastSpace = 0;
    
    if (isClass) { // If it's a class name, capitalize the first letter
        putchar(str[0] >= 'a' && str[0] <= 'z' ? str[0] - 32 : str[0]); // Convert first letter to uppercase if it's lowercase
    } else { // Otherwise, keep the first letter as it is
        putchar(str[0]);
    }
    
    for (int i = 1; i < length; i++) {
        if (str[i] == ' ') {
            lastSpace = 1;
        } else {
            if (lastSpace) { // If it's the first letter after a space, capitalize it
                putchar(str[i] >= 'a' && str[i] <= 'z' ? str[i] - 32 : str[i]); // Convert letter to uppercase if it's lowercase
                lastSpace = 0;
            } else { // Otherwise, keep it lowercase
                putchar(toLowerCase(str[i]));
            }
        }
    }
    
    if (!isClass) { // If it's not a class name, print "()"
        printf("()\n");
    } else {
        putchar('\n');
    }
}

// Function to remove leading whitespace from a string
char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

// Function to remove trailing whitespace from a string
char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int main() {
    char operation;
    char type;
    char input[1000];
    
    while (scanf("%c;%c;%[^\n]%*c", &operation, &type, input) == 3) {
        char* trimmed_input = rtrim(ltrim(input));
        if (operation == 'S') {
            if (type == 'M' || type == 'C' || type == 'V') {
                splitCamelCase(trimmed_input);
            }
        } else if (operation == 'C') {
            if (type == 'M') {
                combineCamelCase(trimmed_input, 0);
            } else if (type == 'C' || type == 'V') {
                combineCamelCase(trimmed_input, type == 'C' ? 1 : 0);
            }
        }
    }
    
    return 0;
}