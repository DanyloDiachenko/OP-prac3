#include <stdio.h>
#include <math.h>

double computeRoot(const double value, const int exponent, const double accuracy) {
    double y = value;

    if (exponent < 0) {
        return 1.0 / pow(value, -exponent);
    }

    do {
        const double sigma = (1.0 / exponent) * (value / pow(y, exponent - 1) - y);

        if (fabs(sigma) < accuracy) {
            return y;
        }

        y = y + sigma;
    } while (1);
}

int main() {
    double sqrtValue;
    int exponent;
    double accuracy;

    printf("Enter the value of exponent: ");
    scanf("%d", &exponent);

    if (exponent == 0) {
        printf("Exponent cannot be equal to 0\n");
        return -1;
    }

    if (exponent > 0) {
        printf("Enter the value of sqrtValue: ");
        scanf("%lf", &sqrtValue);

        if (sqrtValue < 0 && exponent % 2 == 0) {
            printf("sqrtValue cannot be less than 0 for even exponents\n");
            return -1;
        }
    } else {
        printf("Enter the value of sqrtValue: ");
        scanf("%lf", &sqrtValue);

        if (exponent < 0 && sqrtValue <= 0 && exponent % 2 == 0) {
            printf("sqrtValue must be greater than 0 for even negative exponents\n");
            return -1;
        }

        if (sqrtValue == 0) {
            printf("sqrtValue cannot be 0 for negative exponents\n");
            return -1;
        }
    }

    printf("Enter the accuracy (e.g., 0.0001): ");
    scanf("%lf", &accuracy);

    const double result = computeRoot(sqrtValue, exponent, accuracy);

    printf("The %d-th root of %.2f is approximately: %.7f\n", exponent, sqrtValue, result);

    return 0;
}