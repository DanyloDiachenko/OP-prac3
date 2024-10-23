#include "./libraries.h";
#include "./functions.h";

double getRoot(double root, int exponent, double accuracy);
int getDecimalPlaces(double accuracy);
int getAndValidateExponent();
double getAndValidateRoot(int exponent);
double getAndValidateAccuracy();

int main() {
	const int exponent = getAndValidateExponent();

	if (exponent == 0) {
		printf("Any number raised to the power of 0 is 1.\n");

		return 0;
	}

	const double root = getAndValidateRoot(exponent);

	if (root == 0) {
		printf("The %d-th root of 0 is 0\n", exponent);

		return 0;
	}

	const double accuracy = getAndValidateAccuracy();

	const double result = getRoot(root, exponent, accuracy);
	const int decimalPlaces = getDecimalPlaces(accuracy);

	if (!isnan(result)) {
		printf("The %d-th root of %.lf is approximately: %.*lf\n", exponent, root, decimalPlaces, result);
	} else {
		printf("Failed to compute the root with these numbers.\n");
	}

	return 0;
}

