#include <stdio.h>

int main() {
	int choice = 0, bufferEmpty;
	while (choice != 7) {
		printf("\tChoose an option:\n");
		printf("\t1. Happy Face\n");
		printf("\t2. Balanced Number\n");
		printf("\t3. Generous Number\n");
		printf("\t4. Circle Of Joy\n");
		printf("\t5. Happy Numbers\n");
		printf("\t6. Festival Of Laughter\n");
		printf("\t7. Exit\n");

		scanf("%d", &choice);
		// Clear buffer
		do {
			// Separated these to two lines, since putting them in one line causes an infinite loop when only
			// \n is entered
			bufferEmpty = scanf("%*[^\n]");
			scanf("%*c");
		} while (bufferEmpty == -1);
		// Using "if" instead of "switch" since CLion does not know how to fold the code, and indent comments correctly,
		// making it uncomfortable to use. (Reported in RSCPP-35914)
		// -----------------------------
		// Case 1: Draw Happy Face with given symbols for eyes, nose and mouth
		/* Example:
		* n = 3:
		* 0   0
		*   o
		* \___/
		*/
		if (choice == 1) {
			char eyes, nose, mouth;
			int faceSize;
			printf("Enter symbols for the eyes, nose, and mouth:\n");
			scanf(" %c %c %c", &eyes, &nose, &mouth);

			printf("Enter face size:\n");
			scanf("%d", &faceSize);

			// Ensure faceSize is odd and positive
			while (faceSize < 1 || faceSize % 2 == 0) {
				printf("The face's size must be an odd and positive number, please try again:\n");
				scanf("%d", &faceSize);
			}

			// Print the eyes. Adding +1 to face size since %*c tells us the amount of padding,
			// not the amount of spaces
			printf("%c%*c\n", eyes, faceSize + 1, eyes);

			// Width of the face: faceSize + 2(eyes)
			// Padding for the nose from the left: half of the face width, +1 since it's padding.
			printf("%*c\n", ((faceSize + 1) / 2) + 1, nose);
			printf("\\");

			// Print the mouth <faceSize> times.
			for (int i = 0; i < faceSize; ++i) {
				printf("%c", mouth);
			}
			printf("/\n");
		}

		// Case 2: determine whether the sum of all digits to the left of the middle digit(s)
		// and the sum of all digits to the right of the middle digit(s) are equal
		/* Examples:
		Balanced: 1533, 450810, 99
		Not blanced: 1552, 34
		Please notice: the number has to be bigger than 0.
		*/
		else if (choice == 2) {
			int number;
			printf("Enter a number:\n");
			scanf("%d", &number);

			// input validation
			while (number < 1) {
				printf("Only positive number is allowed, please try again:\n");
				scanf("%d", &number);
			}
			// We know how many digits the number has by dividing it by 10 each time.
			int digitCounter = 0, i = number;
			while (i > 0) {
				++digitCounter;
				i = i / 10;
			}
			if (digitCounter == 1) {
				printf("This number is balanced and brings harmony!\n");
			} else {
				// Create the "divider" (10^[digitCounter/2])
				int divider = 10;
				for (int j = 1; j < digitCounter / 2; ++j) {
					divider = divider * 10;
				}

				// Get the halves. The number in the middle can be ignored.
				int rightHalf = number % divider;

				// If the amount of digits is odd, we need to add another zero to the divider (we want to remove more
				// than "half" of the numbers
				if (digitCounter % 2 == 1) {
					divider = divider * 10;
				}
				int leftHalf = number / divider;
				int leftSum = 0, rightSum = 0;

				// Get each digit. Add it to the relevant sum. Remove said digit from the half
				while (leftHalf != 0) {
					leftSum += leftHalf % 10;
					leftHalf = leftHalf / 10;
				}
				while (rightHalf != 0) {
					rightSum += rightHalf % 10;
					rightHalf = rightHalf / 10;
				}
				if (leftSum == rightSum) {
					printf("This number is balanced and brings harmony!\n");
				} else {
					printf("This number isn't balanced and destroys harmony.\n");
				}
			}
		}
		// Case 3: determine whether the sum of the proper divisors (od an integer) is greater than the number itself
		/* Examples:
		Abudant: 12, 20, 24
		Not Abudant: 3, 7, 10
		Please notice: the number has to be bigger than 0.
		*/
		else if (choice == 3) {
			int number;
			printf("Enter a number:\n");
			scanf("%d", &number);

			// input validation
			while (number < 1) {
				printf("Only positive number is allowed, please try again:\n");
				scanf("%d", &number);
			}

			// We can start with 1, since all numbers are dividable by 1.
			int divisorsSum = 1;
			for (int i = 2; i < number; ++i) {
				if (number % i == 0) {
					divisorsSum += i;
				}
			}
			if (divisorsSum > number) {
				printf("This number is generous!\n");
			} else {
				printf("This number does not share.\n");
			}
		}
		// Case 4: determine whether a number - and it's reverse number - are primes.
		/* Examples:
		This one brings joy: 3, 5, 11
		This one does not bring joy: 15, 8, 99
		Please notice: the number has to be bigger than 0.
		*/
		else if (choice == 4) {
			int number, tempNumber, reverseNumber = 0, digit;
			printf("Enter a number:\n");
			scanf("%d", &number);

			// input validation
			while (number < 1) {
				printf("Only positive number is allowed, please try again:\n");
				scanf("%d", &number);
			}
			// Calc the reverse number.
			tempNumber = number;
			while (tempNumber > 0) {
				reverseNumber = reverseNumber * 10;

				// Get the last digit
				digit = tempNumber % 10;

				// Add the digit to the end of our reverse number
				reverseNumber += digit;

				// Remove the last digit.
				tempNumber = tempNumber / 10;
			}
			char isPrime = 1;

			// To make the code fast, check if number is even, and then skip all even numbers.
			if (number % 2 == 0 && reverseNumber % 2 == 0 && number != 2) {
				printf("The circle remains incomplete.\n");
				isPrime = 0;
			}
			// Check if the given number is a prime:
			if (isPrime) {
				// We can stop at number / 2 (since after that, i*2 will be bigger than the given number)
				for (int i = 3; i < number / 2; i += 2) {
					if (number % i == 0) {
						isPrime = 0;
						printf("The circle remains incomplete.\n");
						break;
					}
				}
				// Check if the reverse number is a prime. Same logic as before.
				if (isPrime) {
					for (int i = 3; i < reverseNumber / 2; i += 2) {
						if (reverseNumber % i == 0) {
							isPrime = 0;
							printf("The circle remains incomplete.\n");
							break;
						}
					}
				}
			}
			if (isPrime) {
				printf("This number completes the circle of joy!\n");
			}
		}
		// Happy numbers: Print all the happy numbers between 1 to the given number.
		// Happy number is a number which eventually reaches 1 when replaced by the sum of the square of each digit
		/* Examples:
		Happy :) : 7, 10
		Not Happy :( : 5, 9
		Please notice: the number has to be bigger than 0.
		*/
		else if (choice == 5) {
			int number, tempNumber, digit, sum;
			printf("Enter a number:\n");
			scanf("%d", &number);

			// input validation
			while (number < 1) {
				printf("Only positive number is allowed, please try again:\n");
				scanf("%d", &number);
			}
			printf("Between 1 and %d only these numbers bring happiness: 1 ", number);

			// Go over all numbers from 2 to number
			for (int i = 2; i < number; ++i) {
				tempNumber = i;
				do {
					sum = 0;

					// Go over all the digits in our new number and sum their squares.
					while (tempNumber != 0) {
						digit = tempNumber % 10;
						sum += digit * digit;

						// Remove the last digit
						tempNumber = tempNumber / 10;
					}
					// The next number that we want to check is the current iteration's sum
					tempNumber = sum;

					// Stop at a digit that we recognize as either happy or sad, or at the original digit.
				} while (sum != 1 && sum != 4 && sum != i);
				if (sum == 1) {
					printf("%d ", i);
				}
			}
			printf("\n");
		}
		// Festival of Laughter: Prints all the numbers between 1 the given number:
		// and replace with "Smile!" every number that divided by the given smile number
		// and replace with "Cheer!" every number that divided by the given cheer number
		// and replace with "Festival!" every number that divided by both of them
		/* Example:
		6, smile: 2, cheer: 3 : 1, Smile!, Cheer!, Smile!, 5, Festival!
		*/
		else if (choice == 6) {
			char isInputValid = 0;
			int smileNumber, cheerNumber, maxNumber;

			printf("Enter a smile and cheer number:\n");
			while (!isInputValid) {

				// Get the two numbers in the expected format.
				int goodValues = scanf("smile: %d , cheer: %d", &smileNumber, &cheerNumber);

				// Clear buffer
				do {
					// Separated these to two lines, since putting them in one line causes an infinite loop when only
					// \n is entered
					bufferEmpty = scanf("%*[^\n]");
					scanf("%*c");
				} while (bufferEmpty == -1);

				// Input was invalid
				if (goodValues != 2) {
					printf("Only 2 different positive numbers in the given format are allowed for the festival,"
						" please try again:\n");
				}

				// Two identical numbers were entered
				else if (smileNumber == cheerNumber) {
					printf("Only 2 different positive numbers in the given format are allowed for the festival,"
						" please try again:\n");
				} else {
					// No errors found. break the loop
					// (would have used "break" here, but using "while(1)" is a bad practice)
					isInputValid = 1;
				}
			}
			printf("Enter maximum number for the festival:\n");
			scanf("%d", &maxNumber);

			// input validation
			while (maxNumber < 1) {
				printf("Only positive maximum number is allowed, please try again:\n");
				scanf("%d", &maxNumber);
			}
			for (int i = 1; i <= maxNumber; ++i) {
				// Check if number is dividable by both numbers...
				if (i % smileNumber == 0) {
					if (i % cheerNumber == 0) {
						printf("Festival!\n");
					} else {
						// ... Or just by the smile number.
						printf("Smile!\n");
					}
				}
				// Check only cheer number
				else if (i % cheerNumber == 0) {
					printf("Cheer!\n");
				}
				// Else, print the number itself.
				else {
					printf("%d\n", i);
				}
			}
		} else if (choice == 7) {
			printf("Thank you for your journey through Numeria!\n");
		} else {
			printf("This option is not available, please try again.\n");
		}
	}
	return 0;
}
