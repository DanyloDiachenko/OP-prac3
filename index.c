#include <stdio.h>
#include <math.h>

double computeRoot(const double value, const int exponent, const double accuracy) {
    double y = value;

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

    printf("Enter the value of sqrtValue: ");
    scanf("%lf", &sqrtValue);

    printf("Enter the value of exponent: ");
    scanf("%d", &exponent);

    printf("Enter the accuracy (e.g., 0.0001): ");
    scanf("%lf", &accuracy);

    const double result = computeRoot(sqrtValue, exponent, accuracy);

    printf("The %d-th root of %.2f is approximately: %.5f\n", exponent, sqrtValue, result);

    return 0;
}
