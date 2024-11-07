#include <stdio.h>
#include <stdlib.h>

// Define operations as functions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; } // Ensure no division by zero

// Array of function pointers to match input characters to operations
int (*operations[])(int, int) = { add, subtract, multiply, divide };

int main() {
    int a = 6, b = 3;
    char choice;

    printf("Operand ‘a’ : %d | Operand ‘b’ : %d\n", a, b);
    printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : multiply | 3 : divide | 4 : exit): ");
    scanf(" %c", &choice);

    // Convert choice to integer
    int index = choice - '0';

    // Check for exit condition
    if (index == 4) {
        printf("Exiting program.\n");
        return 0;
    }

    // Perform the operation
    int result = operations[index](a, b);

    // Output the result
    switch (index) {
        case 0:
            printf("Adding ‘a’ and ‘b’\n");
            break;
        case 1:
            printf("Subtracting ‘b’ from ‘a’\n");
            break;
        case 2:
            printf("Multiplying ‘a’ and ‘b’\n");
            break;
        case 3:
            printf("Dividing ‘a’ by ‘b’\n");
            break;
    }

    printf("x = %d\n", result);
    return 0;
}