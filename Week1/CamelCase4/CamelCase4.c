#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int isSpace(int c);
int isUpperCase(char c);
char toLowerCase(char c);
char* ltrim(char* str);
char* rtrim(char* str);
void splitCamelCase(char* str, int isMethod);
void combineCamelCase(char* str, int isClass, int variableClassNoneParentheses);


int main() {
    char operation, type;
    char input[1000];
    
    while (scanf("%c;%c;%[^\n]%*c", &operation, &type, input) == 3) {
        char* trimmedInput = rtrim(ltrim(input));
        if (operation == 'S') {
            if (type == 'C' || type == 'V') {
                splitCamelCase(trimmedInput, 0);
            } else if (type == 'M') {
                splitCamelCase(trimmedInput, 1);
            }
            
        } else if (operation == 'C') {
            if (type == 'M') {
                combineCamelCase(trimmedInput, 0, 0);
            } else if (type == 'C') {
                combineCamelCase(trimmedInput, 1, 1);
            } else if (type == 'V') {
                combineCamelCase(trimmedInput, 0, 1);
            }
        }
    }
    
    return 0;
}

// Function to check if a character is a space
int isSpace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

// Function to check if a character is uppercase
int isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

// Function to convert a character to lowercase
char toLowerCase(char c) {
    if (isUpperCase(c)) {
        return c + 32;
    }
    return c;
}

// Function to remove leading whitespace from a string
char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isSpace(*str)) {
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

    while (end >= str && isSpace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

// Function to split a camel case string into words
void splitCamelCase(char* str, int isMethod) {
    int length = strlen(str);
    int lastCase = -1;
    
    for (int i = 0; i < length; i++) {
        if (isMethod && str[i] == '(') {
            /* Skip parentheses if it's a method name */
            break;
        } else if (isUpperCase(str[i])) {
            /* Using ASCII values to check for uppercase */
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
void combineCamelCase(char* str, int isClass, int variableClassNoneParentheses) {
    int length = strlen(str);
    int lastSpace = 0;
    
    /* If it's a class name, capitalize the first letter */
    if (isClass) {
        /* Convert first letter to uppercase if it's lowercase */
        putchar(str[0] >= 'a' && str[0] <= 'z' ? str[0] - 32 : str[0]);
    } else if (!isClass || variableClassNoneParentheses){
        /* Otherwise, keep the first letter as it is */
        putchar(str[0]);
    }
    
    for (int i = 1; i < length; i++) {
        if (str[i] == ' ') {
            lastSpace = 1;
        } else {
            /* If it's the first letter after a space, capitalize it */
            if (lastSpace) {
                /* Convert letter to uppercase if it's lowercase */
                putchar(str[i] >= 'a' && str[i] <= 'z' ? str[i] - 32 : str[i]);
                lastSpace = 0;
            } else {
                /* Otherwise, keep it lowercase */
                putchar(toLowerCase(str[i]));
            }
        }
    }
    
    /* Not need Parentheses */
    if (!variableClassNoneParentheses) {
        printf("()\n");
    } else {
        putchar('\n');
    }
}