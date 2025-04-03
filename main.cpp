#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Monoalphabetic
bool alphabetChecker(char letter) {
	// Simply check's a letters alphabetic status.
	int letterOrder = int(letter);
	if (letterOrder >= 65 && letterOrder <= 90) { return true; }
	else if (letterOrder >= 97 && letterOrder <= 122) { return true; }
	return false;
}
string ShiftCipher(int shift, string Message) {
	string cipherText = "";
	char letter;

	// Thresholds are:
	// A-Z = 65 - 90, start here, can't go past 90!
	// a-z = 97 - 122, start here, can't go past 122!
	// Only shifting alphabetical characters!

	for (int i = 0; i < Message.length(); i++) {
		letter = Message[i];

		// a - z Check
		if (letter <= 122 && letter >= 97) {
			int cipherLetter = shift + int(letter);
			if (cipherLetter > 122) {
				int rem = cipherLetter % 122;
				cipherLetter = 96 + rem;
			}
			cipherText.push_back(char(cipherLetter));
		}
		else if (letter <= 90 && letter >= 65) {
			int cipherLetter = shift + int(letter);
			if (cipherLetter > 90) {
				int rem = cipherLetter % 90;
				cipherLetter = 64 + rem;
			}
			cipherText.push_back(char(cipherLetter));
		}

	}		

	return cipherText;
}
int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
string AffineCipher(int multiplier, int shift, string Message) {
	// Must check if multiplier is valid, C++ has built in func.
	if (gcd(multiplier, 26) != 1) { return false; }

}


int main() {
	string Message;

	cout << "Type in your message: ";
	getline(cin, Message);
	cout << endl << ShiftCipher(1, Message);

	return 0;
}