#include <stdio.h>
#include <math.h>

#define EPSILON 1e-15

int getDecimalPlaces(double accuracy) {
    int decimalPlaces = 0;
    while (accuracy < 1 && decimalPlaces < 15) {
        accuracy *= 10;
        decimalPlaces++;
    }
    return decimalPlaces;
}

double calculateRoot(const double value, const int exponent, const double accuracy) {
    if (exponent == 0) {
        printf("Exponent cannot be zero.\n");
        return NAN;
    }

    if (exponent < 0) {
        if (value == 0) {
            printf("Cannot compute root for value 0 with negative exponent.\n");
            return NAN;
        }
        double positiveExponent = -exponent;
        double positiveRoot = calculateRoot(value, positiveExponent, accuracy);
        if (positiveRoot == 0) {
            printf("Division by zero encountered.\n");
            return NAN;
        }
        return 1.0 / positiveRoot;
    }

    double y = value;
    double delta;

    do {
        if (pow(y, exponent - 1) == 0) {
            printf("Division by zero encountered during iteration.\n");
            return NAN;
        }
        delta = (1.0 / exponent) * (value / pow(y, exponent - 1) - y);
        y = y + delta;
    } while (fabs(delta) >= accuracy);

    return y;
}

int main() {
    double root;
    int exponent;
    double accuracy;

    do {
        printf("Enter the value of exponent: ");
        if (scanf("%d", &exponent) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            fflush(stdin);
            exponent = 0;
            continue;
        }
        fflush(stdin);

        if(exponent == 0) {
            printf("Exponent cannot be equal to 0\n");
        }
    } while(exponent == 0);

    if (exponent > 0) {
        printf("Enter the value of root: ");
        if (scanf("%lf", &root) != 1) {
            printf("Invalid input for root.\n");
            fflush(stdin);
            return -1;
        }
        fflush(stdin);

        if (root < 0 && exponent % 2 == 0) {
            printf("Root value cannot be less than 0 for even exponents\n");
            return -1;
        }
    } else {
        printf("Enter the value of root: ");
        if (scanf("%lf", &root) != 1) {
            printf("Invalid input for root.\n");
            fflush(stdin);
            return -1;
        }
        fflush(stdin);

        if (root <= 0 && (-exponent) % 2 == 0) {
            printf("Root value must be greater than 0 for even negative exponents\n");
            return -1;
        }

        if (root == 0) {
            printf("Root value cannot be 0 for negative exponents\n");
            return -1;
        }
    }

    do {
        printf("Enter the accuracy (e.g., 0.0001): ");
        if (scanf("%lf", &accuracy) != 1 || accuracy <= 0) {
            printf("Invalid input for accuracy. Please enter a positive number and not zero.\n");
            fflush(stdin);
            accuracy = 0;
            continue;
        }
        fflush(stdin);

        double logarithmValue = log10(accuracy);
        double roundedLogarithm = round(logarithmValue);

        if (fabs(logarithmValue - roundedLogarithm) > EPSILON) {
            printf("Accuracy should be a power of 10 (e.g., 1, 0.1, 0.01, etc.)\n");
            accuracy = 0;
            continue;
        }

        if (accuracy < 1e-15) {
            printf("Accuracy cannot be more precise than 1e-15.\n");
            accuracy = 0;
        }
    } while(accuracy == 0);

    const int decimalPlaces = getDecimalPlaces(accuracy);

    const double result = calculateRoot(root, exponent, accuracy);

    if (!isnan(result)) {
        printf("The %d-th root of %.lf is approximately: %.*lf\n", exponent, root, decimalPlaces, result);
    } else {
        printf("Failed to compute the root due to invalid input or computation error.\n");
    }

    return 0;
}
