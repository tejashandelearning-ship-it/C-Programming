#include <stdio.h>
#include <stdlib.h>

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

double pow_int(double base, int exp) {
    if (base == 0.0 && exp < 0) {
        return 0.0; /* undefined, return 0 to avoid div-by-zero */
    }
    double result = 1.0;
    int i;
    if (exp < 0) {
        for (i = 0; i < -exp; ++i) result *= base;
        if (result == 0.0) return 0.0;
        return 1.0 / result;
    }
    for (i = 0; i < exp; ++i) result *= base;
    return result;
}

int main(void) {
    int choice = 0;
    while (1) {
        printf("\nSimple C Calculator\n");
        printf("1) Add\n2) Subtract\n3) Multiply\n4) Divide\n5) Power (integer exponent)\n6) Modulo (integers)\n7) Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number 1-7.\n");
            clear_stdin();
            continue;
        }
        if (choice == 7) {
            printf("Goodbye.\n");
            break;
        }

        if (choice >= 1 && choice <= 5) {
            double a, b;
            if (choice == 5) {
                int exp;
                printf("Enter base (floating point): ");
                if (scanf("%lf", &a) != 1) { printf("Invalid number.\n"); clear_stdin(); continue; }
                printf("Enter integer exponent: ");
                if (scanf("%d", &exp) != 1) { printf("Invalid exponent.\n"); clear_stdin(); continue; }
                double res = pow_int(a, exp);
                printf("Result: %g\n", res);
                continue;
            }
            printf("Enter first number: ");
            if (scanf("%lf", &a) != 1) { printf("Invalid number.\n"); clear_stdin(); continue; }
            printf("Enter second number: ");
            if (scanf("%lf", &b) != 1) { printf("Invalid number.\n"); clear_stdin(); continue; }

            if (choice == 1) printf("Result: %g\n", a + b);
            else if (choice == 2) printf("Result: %g\n", a - b);
            else if (choice == 3) printf("Result: %g\n", a * b);
            else if (choice == 4) {
                if (b == 0.0) printf("Error: Division by zero.\n");
                else printf("Result: %g\n", a / b);
            }
        } else if (choice == 6) {
            long long x, y;
            printf("Enter first integer: ");
            if (scanf("%lld", &x) != 1) { printf("Invalid integer.\n"); clear_stdin(); continue; }
            printf("Enter second integer: ");
            if (scanf("%lld", &y) != 1) { printf("Invalid integer.\n"); clear_stdin(); continue; }
            if (y == 0) printf("Error: Modulo by zero.\n");
            else printf("Result: %lld\n", x % y);
        } else {
            printf("Please choose a valid option (1-7).\n");
        }
        clear_stdin();
    }
    return 0;
}