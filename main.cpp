#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Helper Functions
bool alphabetChecker(char letter) {
	// Simply check's a letters alphabetic status.
	int letterOrder = int(letter);
	if (letterOrder >= 65 && letterOrder <= 90) { return true; }
	else if (letterOrder >= 97 && letterOrder <= 122) { return true; }
	return false;
}
int LowerOrCapital(char letter) {
	// Will be used as the base of the alphabet.

	// a - z Check
	if (int(letter) <= 122 && int(letter) >= 97) {
		return 97;
	}
	// A - Z Check
	else if (int(letter) <= 90 && int(letter) >= 65) {
		return 65;
	}
}
int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
int makeIntoNum(char letter) {
	int num = int(letter) % LowerOrCapital(letter);
	return num;
}

// Cipher Functions
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
		else {
			cipherText.push_back(Message[i]);
		}
	}		

	return cipherText;
}
string AffineCipher(int multiplier, int shift, string Message) {
	// Must check if multiplier is valid, C++ has built in func.
	if (gcd(multiplier, 26) != 1) { return "Invalid Multiplier"; }

	int numLetter;
	string cipherText = "";

	// Will have to reduce the real value to 0-25
	for (int i = 0; i < Message.length(); i++) {
		if (alphabetChecker(Message[i])) {
			numLetter = Message[i];
			numLetter = numLetter % LowerOrCapital(Message[i]);
			int cipherChar = ((numLetter * multiplier) + shift) % 26;
			cipherText.push_back(char(cipherChar + LowerOrCapital(Message[i])));
		}
		else {
			cipherText.push_back(Message[i]);
		}
	}

	return cipherText;
}
string VigenereCipher(string Key, string Message) {
	// Ensure Key is only alphabetic!
	for (int i = 0; i < Key.length(); i++) {
		if (alphabetChecker(Key[i]) != true) {
			return "Invalid key, make sure only alphabet chars are a part of key.";
		}
	}
	string cipherText = "";
	int KeyCount = 0;

	for (int i = 0; i < Message.length(); i++) {
		if (alphabetChecker(Message[i]) != true) { cipherText.push_back(Message[i]); }
		else {
			int letterNum = int(Message[i]) % LowerOrCapital(Message[i]);
			int vShift = makeIntoNum(Key[KeyCount]);

			KeyCount++; if (KeyCount == Key.length()) { KeyCount = 0; }

			letterNum += vShift; letterNum = letterNum % 26;
			char letter = char(letterNum + LowerOrCapital(Message[i])); // Converting back into ASCII char.
			cipherText.push_back(letter);
		}
	}
	return cipherText;
}

// Main Function
int main() {
	string Message;

	cout << "Type in your message: ";
	getline(cin, Message);
	cout << endl << AffineCipher(25, 1, Message);
	cout << endl << ShiftCipher(2, Message);
	cout << endl << VigenereCipher("Key", Message);

	return 0;
}