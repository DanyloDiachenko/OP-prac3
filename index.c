#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ROOT 1e+10
#define MIN_ROOT -1e+10
#define MAX_EXPONENT 1000
#define MIN_EXPONENT -1000
#define MAX_ACCURACY 1e-1
#define MIN_ACCURACY 1e-15

int getDecimalPlaces(double accuracy);
double calculateRoot(double root, int exponent, double accuracy);

int main() {
	double root, accuracy;
	int exponent;
	bool inputValidity = false;

	do {
		printf("Enter the value of exponent: ");
		if (scanf("%d", &exponent) != 1) {
			printf("Invalid input. Please enter an integer.\n");
			fflush(stdin);
			exponent = 0;

			continue;
		}
		fflush(stdin);

		if (exponent == 0) {
			printf("Exponent cannot be equal to 0\n");
		}

		if (exponent > MAX_EXPONENT || exponent < MIN_EXPONENT) {
			printf("Exponent value is too large or too small. Please enter a value between %d and %d.\n", MIN_EXPONENT, MAX_EXPONENT);
			exponent = 0;
		}

	} while (exponent == 0);

	do {
		printf("Enter the value of root: ");
		if (scanf("%lf", &root) != 1) {
			printf("Invalid input for root. Please enter a valid number.\n");
			fflush(stdin);

			continue;
		}
		fflush(stdin);

		if (root > MAX_ROOT || root < MIN_ROOT) {
			printf("Root value is too large or too small. Please enter a value between %.0lf and %.0lf.\n", MIN_ROOT, MAX_ROOT);

			continue;
		}

		if (exponent > 0) {
			if (root < 0 && exponent % 2 == 0) {
				printf("Root value cannot be less than 0 for even exponents\n");

				continue;
			}
		} else {
			if (root <= 0 && (-exponent) % 2 == 0) {
				printf("Root value must be greater than 0 for even negative exponents\n");

				continue;
			}

			if (root == 0) {
				printf("Root value cannot be 0 for negative exponents\n");

				continue;
			}
		}

		inputValidity = 1;

	} while (!inputValidity);

	if (root == 0) {
		printf("The %d-th root of 0 is 0\n", exponent);

		return 0;
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

		if (accuracy < MIN_ACCURACY || accuracy > MAX_ACCURACY) {
			printf("Accuracy value is out of range. Please enter a value between %.1e and %.1e.\n", MIN_ACCURACY, MAX_ACCURACY);
			accuracy = 0;
		}

		const double logarithmValue = log10(accuracy);
		const double roundedLogarithm = round(logarithmValue);

		if (fabs(logarithmValue - roundedLogarithm) > MIN_ACCURACY) {
			printf("Accuracy should be a power of 10 (e.g., 1, 0.1, 0.01, etc.)\n");
			accuracy = 0;
		}

	} while (accuracy == 0);

	const double result = calculateRoot(root, exponent, accuracy);
	const int decimalPlaces = getDecimalPlaces(accuracy);

	if (!isnan(result)) {
		printf("The %d-th root of %.lf is approximately: %.*lf\n", exponent, root, decimalPlaces, result);
	} else {
		printf("Failed to compute the root with this numbers.\n");
	}

	return 0;
}

int getDecimalPlaces(double accuracy) {
	int decimalPlaces = 0;

	while (accuracy < 1 && decimalPlaces < 15) {
		accuracy *= 10;
		decimalPlaces++;
	}

	return decimalPlaces;
}

double calculateRoot(const double root, const int exponent, const double accuracy) {
	if (exponent < 0) {
		const double positiveExponent = -exponent;
		const double positiveRoot = calculateRoot(root, positiveExponent, accuracy);

		return 1.0 / positiveRoot;
	}

	double result = root;
	double delta;

	do {
		delta = (1.0 / (double) exponent) * (root / pow(result, (double) exponent - 1.0) - result);
		result = result + delta;
	} while (fabs(delta) >= accuracy);

	return result;
}