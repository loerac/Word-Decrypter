/*
* Input whole string
* Solve it by entering one word at a time
*/
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

//Functions
bool forgetWord(string line, string letter);
bool checkWord(string line, string letter);
bool amountLetters(string line, string cypher);
void sequence(string word, vector<string>& wordList);
string letterPlacement(string currentWord, vector<string>& wordList, char letter, char resp);
void placement(int place, vector<string>& wordList, string currentWord);

int main() {
    //Variables
	string line, currentWord, word, forget, stringTemp, folder;
	vector<string> wordList;
	ofstream fout;
	ifstream fin;
	char letter, resp, swap;

	int wordSize, place;
	float findCount = 0;
	int wordCount = 0;
	float progress;
	int lCount = 0;
	int count = 0;
	float size;
	int x = 0;

	bool val = true;
	bool run = true;

	while (run) {
		fin.open("wordList.txt");

		if (!fin)
			cout << "Cannot find wordList.txt" << endl;
		else {
			cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please wait..." << endl;
			while (getline(fin, line))
				wordCount++;
			fin.close();
			//system("CLS");

			fin.open("wordList.txt");
			cout << "Enter the word and then the known letter(s) and known letter(s) that aren't in the word." << endl;
			cout << "If there's no knowledge of known letter(s), enter 0 for either or both >> ";
			cin >> currentWord >> word >> forget;
			folder = currentWord;
			wordSize = currentWord.size();

			if (word != "0" && forget != "0") {
				while (val) {
					for (int j = 0; j < forget.size(); j++) {
						if (word[x] == forget[j]) {
							val = false;
							letter = word[x];
						}
					}

					if (val == false) {
						cout << "\n============================================================\n" << endl;
						cout << "You have \'" << letter << "\' in known letter(s) and in known letter(s) to forget." << endl;
						cout << "Please enter known letter(s) and known letter(s) to forget again >> ";
						cin >> word >> forget;
						val = true;
						x = 0;
					}

					if (x == forget.size() || x == word.size())
						val = false;
					x++;
				}
			}
			string filename = currentWord + ".txt";
			fout.open(filename.c_str());
			if (word == "0" && forget == "0") {
				while (getline(fin, line)) {
					if (line.size() == wordSize && amountLetters(line, currentWord) == true) {
						wordList.push_back(line);
						cout << "Found: " << line << '\r';
					}
				}
			}
			else if (word != "0" && forget == "0") {
				while (getline(fin, line)) {
					if (line.size() == wordSize && amountLetters(line, currentWord) == true && checkWord(line, word) == true) {
						wordList.push_back(line);
						cout << "Found: " << line << '\r';
					}
				}
			}
			else if (word == "0" && forget != "0") {
				while (getline(fin, line)) {
					if (line.size() == wordSize && amountLetters(line, currentWord) == true && checkWord(line, word) == true) {
						wordList.push_back(line);
						cout << "Found: " << line << '\r';
					}
				}
			}
			else {
				while (getline(fin, line)) {
					if (line.size() == wordSize && amountLetters(line, currentWord) == true && forgetWord(line, forget) == true && checkWord(line, word) == true) {
						wordList.push_back(line);
						cout << "Found: " << line << '\r';
					}
				}
			}
			fin.close();
			cout << "Amount of words: " << wordList.size() << endl;

			cout << "\n============================================================\n" << endl;
			cout << "I can shorten the list down if you know where the letter(s) go." << endl;
			cout << "I can also find look for sequence of letters that you know." << endl;
			cout << "Do you know where any of the letter(s) go in the word or a sequence [y/n] >> ";
			cin >> resp;

			if (resp == 'y') {
				cout << "\n============================================================\n" << endl;
				while (resp == 'y') {
					cout << "Known letters or sequence [l/s] >> ";
					cin >> resp;

					if (resp == 'l') {
						cout << "Enter the letter from the current word and then the letter it goes with >> ";
						cin >> letter >> resp;
						currentWord = letterPlacement(currentWord, wordList, letter, resp);
					}
					else if (resp == 's') {
						cout << "Enter the sequence of letters in the word >> ";
						cin >> stringTemp;
						sequence(stringTemp, wordList);
					}
					else
						resp = 'y';

					cout << "\n============================================================\n" << endl;
					cout << "Current word: " << currentWord << endl;
					cout << "Amount of words: " << wordList.size() << endl;
					cout << "\n============================================================\n" << endl;

					if (wordList.size() == 0) {
						cout << "Cannot find word from input you gave me...." << endl;
						resp = 'n';
					}
					else {
						if (wordList.size() <= 10) {
							cout << "Current word list..." << endl;
							for (int i = 0; i < wordList.size(); i++)
								cout << i + 1 << ": " << wordList[i] << endl;
							cout << "\n============================================================\n" << endl;
						}

						cout << "Do you know any other letter or sequence [y/n] >> ";
						cin >> resp;
						if (resp == 'y')
							cout << "\n============================================================\n" << endl;
					}
				}
			}
			cout << "\n============================================================\n" << endl;
			for (int i = 0; i < wordList.size(); i++)
				if ((i + 1) == wordList.size())
					fout << wordList[i];
				else
					fout << wordList[i] << endl;
			fout.close();
			if (wordList.size() <= 10) {
				cout << "Would you like to enter a new word or exit [w/e] >> ";
				cin >> resp;
				if (resp == 'w') {
					cout << "\n============================================================\n" << endl;
					cout << "\t\t\t\t\t\t\t    Please wait..." << endl;
					wordList.erase(wordList.begin(), wordList.end());
				}
				else
					run = false;
			}
			else {
				cout << "Would you like to open the file to see the words, enter a new word or exit [o/w/e] >> ";
				cin >> resp;
				if (resp == 'o') {
					for (int i = 0; i < wordList.size(); i++)
						cout << i + 1 << ": " << wordList[i] << endl;
					//system("PAUSE");
				}
				else if (resp == 'w') {
					cout << "\n============================================================\n" << endl;
					cout << "\t\t\t\t\t\t\t    Please wait..." << endl;
					wordList.erase(wordList.begin(), wordList.end());
				}
				else
					run = false;
			}
			cout << "Look in the " << folder << ".txt for the word(s)." << endl;
		}
	}
	cout << "\n============================================================\n" << endl;
	cout << "Thank you for using Cepcihrhisr-2.2" << endl;
	//system("PAUSE");

	return 0;
}

// Checks the word to see if it has the letter that I know for sure isn't in the phrase
bool forgetWord(string line, string letter) {
	int count = 0;
	int i = 0;
	int j = 0;
	bool found = true;

	while (letter.size() != count) {
		while (found) {
			if (line[i] == letter[j])
				return false;
			if (i == line.size() && count < letter.size())
				found = false;
			i++;
		}
		count++;
		i = 0;
		j++;
		found = true;
	}

	return true;
}

// Check all the words to see if it has the letters in the word
bool checkWord(string line, string letter) {
	int count = 0;
	int i = 0;
	int j = 0;
	bool found = true;

	while (letter.size() != count) {
		while (found) {
			if (line[i] == letter[j]) {
				found = false;
			}
			if (i == line.size() && count < letter.size())
				return false;
			i++;
		}
		count++;
		i = 0;
		j++;
		found = true;
	}

	return true;
}

//Checks to see if the word from the file has the same amount of characters in each
bool amountLetters(string line, string cypher) {
	int cypherCount = 0;
	int lineCount = 0;
	char cypherLetter, lineLetter;

	for (int i = 0; i < cypher.size(); i++) {
		cypherLetter = cypher[i];
		for (int j = 1; j < cypher.size(); j++)
			if (cypher[j] == cypherLetter)
				cypherCount++;

		lineLetter = line[i];
		for (int j = 1; j < line.size(); j++)
			if (line[j] == lineLetter)
				lineCount++;
	}
	if (cypherCount == lineCount)
		return true;

	return false;
}

// Checks to see if the replacing of the letters won't effect the other letters
string letterPlacement(string currentWord, vector<string>& wordList, char letter, char resp) {
	string word;
	char temp = '0';
	bool valid = true;
	int i = 0;
	int place;
	int count = 0;
	int lCount = 0;

	for (int m = 0; m < currentWord.size(); m++) {
		if (currentWord[m] == resp) {
			currentWord[m] = temp;
			place = i;
			count++;
		}
		else if (currentWord[m] == letter) {
			currentWord[m] = resp;
			place = i;
			placement(place, wordList, currentWord);
		}
		i++;
	}
	for (int j = 0; j < currentWord.size(); j++)
		if (currentWord[j] == '0')
			currentWord[j] = letter;

	return currentWord;
}

// Removing the words that don't have the letter in the correct spot
void placement(int place, vector<string>& wordList, string currentWord) {
	string word;
	for (int i = 0; i < wordList.size(); i++) {
		if (i < 0)
			i = 0;
		word = wordList[i];
		if (word[place] != currentWord[place]) {
			cout << "Removed: " << word << '\r';
			wordList.erase(wordList.begin() + i);
			i--;
		}
	}
}

//Checks to see if the known sequence is in the word
void sequence(string word, vector<string>& wordList) {
	string stringTemp, wordTemp;
	int intTemp = 0;
	int sequenceSize = word.size();
	int flag = 0;

	for (int i = 0; i < wordList.size(); i++) {
		stringTemp = wordList[i];
		cout << "Vector: " << stringTemp << endl;
		for (int j = 0; j < stringTemp.size(); j++) {
			if (intTemp <= stringTemp.size() - sequenceSize) {
				for (int k = 0; k < sequenceSize; k++) {
					wordTemp += stringTemp[intTemp];
					intTemp++;
				}
			}
			cout << "Currently: " << wordTemp << endl;
			intTemp -= sequenceSize - 1;
			if (wordTemp == word) {
				cout << wordTemp << " " << word << endl;
				flag = 1;
			}
			wordTemp = "";
		}
		if (flag == 0) {
			cout << "Removed: " << wordList[i] << endl;
			wordList.erase(wordList.begin() + i);
		}
		intTemp = 0;
		flag = 0;
	}
}
