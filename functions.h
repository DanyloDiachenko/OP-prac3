#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./constants.h"
#include "./libraries.h"

inline int getDecimalPlaces(double accuracy) {
	int decimalPlaces = 0;

	while (accuracy < 1.0 && decimalPlaces < 15) {
		accuracy *= 10;
		decimalPlaces++;
	}

	return decimalPlaces;
}

inline double getRoot(const double root, const int exponent, const double accuracy) {
	if (exponent < 0) {
		const double positiveExponent = -exponent;
		const double positiveRoot = getRoot(root, positiveExponent, accuracy);

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

inline int getAndValidateExponent() {
	int exponent;

	do {
		printf("Enter the value of exponent: ");
		if (scanf("%d", &exponent) != 1) {
			printf("Invalid input. Please enter an integer.\n");
			fflush(stdin);

			continue;
		}
		fflush(stdin);

		if (exponent > MAX_EXPONENT || exponent < MIN_EXPONENT) {
			printf("Exponent value is too large or too small. Please enter a value between %d and %d.\n", MIN_EXPONENT, MAX_EXPONENT);
		}
	} while (exponent > MAX_EXPONENT || exponent < MIN_EXPONENT);

	return exponent;
}

inline double getAndValidateRoot(const int exponent) {
	double root;
	bool inputValidity = false;

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

		inputValidity = true;

	} while (!inputValidity);

	return root;
}

inline double getAndValidateAccuracy() {
	double accuracy;
	bool validInput = false;

	do {
		printf("Enter the accuracy (e.g., 0.0001): ");
		if (scanf("%lf", &accuracy) != 1 || accuracy <= 0) {
			printf("Invalid input for accuracy. Please enter a positive number and not zero.\n");
			fflush(stdin);
			continue;
		}
		fflush(stdin);

		if (accuracy < MIN_ACCURACY || accuracy > MAX_ACCURACY) {
			printf("Accuracy value is out of range. Please enter a value between %.1e and %.1e.\n", MIN_ACCURACY, MAX_ACCURACY);
			continue;
		}

		const double logarithmValue = log10(accuracy);
		const double roundedLogarithm = round(logarithmValue);

		if (fabs(logarithmValue - roundedLogarithm) > MIN_ACCURACY) {
			printf("Accuracy should be a power of 10 (e.g., 1, 0.1, 0.01, etc.)\n");
			continue;
		}

		validInput = true;

	} while (!validInput);

	return accuracy;
}

#endif //FUNCTIONS_H
