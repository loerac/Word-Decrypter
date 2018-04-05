/*
 * Desc: Decrypts a substitution word by entering known letters.
 *
 * Author: Christian Loera
 * Date: 05.04.2018
 */
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std; 

//Functions
bool commonLetters(string &common, string in, string out);
bool forgetWord(string line, string letter);
bool checkWord(string line, string letter);
bool amountLetters(string line, string cypher);
void sequence(string word, vector<string>& wordList);
string letterPlacement(string currentWord, vector<string>& wordList, char letter, char resp);
void placement(int place, vector<string>& wordList, string currentWord);

int main(int argc, char* argv[]) {
    // Iterating through given input
    string en, in, out;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-e")==0)  { en = argv[++i]; }
        else if(strcmp(argv[i], "-i")==0) { in = argv[++i]; }
        else if(strcmp(argv[i], "-o")==0) { out = argv[++i]; }
        else { cout << "Error: unknown command : [ " << argv[i] << " ]\n"; return 2; }
    }
    
    // Check if there are common letters
    if(in != "" && out != "") {
        string common = "";
        while(commonLetters(common, in, out)) {
            cout << "Error: common letters : [ " << common << " ]\n";
            printf("Enter letters to decrpyt the word >> ");
            cin >> in;
            printf("Enter letters that are not used to decrpyt the word >> ");
            cin >> out;
            common = "";
        }
    }

	vector<string> wordList;
    string line, resp, en_letter;

	ofstream fout;
	ifstream fin;

	int wordCount = 0, run = 1;
	
    fin.open("wordList.txt");
	if (!fin) { cout << "Cannot find wordList.txt" << endl; return 2; }
	while (!(run & 8)) {
        run = 0;
		cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please wait..." << endl;
    	while (getline(fin, line)) { wordCount++; }
	    fin.close();

		fin.open("wordList.txt");
		string filename = en + ".txt";
		fout.open(filename.c_str());
		while (getline(fin, line)) {
			if (((line.size()-1)==en.size()) && amountLetters(line, en) && forgetWord(line, out) && checkWord(line, in)) {
				wordList.push_back(line);
				cout << "Found: " << line << '\r';
			}
		}
		fin.close();
        cout << "\n============================================================\n" << endl;
		cout << "Current word: " << en << endl;
		cout << "Amount of words: " << wordList.size() << endl;
	    cout << "\n============================================================\n" << endl;
		cout << "I can shorten the list down if you know where the letter(s) go." << endl;
		cout << "I can also find look for sequence of letters that you know." << endl;
		cout << "Do you know where any of the letter(s) go in the word or a sequence [y/n] >> ";
		cin >> resp;
        resp = tolower(resp[0]);
	    if (resp == "y") {
    		cout << "\n============================================================\n" << endl;
	    	while (resp == "y") {
				cout << "Enter the letter from the current word and then the letter it goes with >> ";
				cin >> en_letter >> resp;
				en = letterPlacement(en, wordList, en_letter[0], resp[0]);

                cout << "\n============================================================\n" << endl;
				cout << "Current word: " << en << endl;
				cout << "Amount of words: " << wordList.size() << endl;
				cout << "\n============================================================\n" << endl;

				if (wordList.size() == 0) {
					cout << "Cannot find word from input you gave me...." << endl;
					resp = "n";
				} else {
					if (wordList.size() <= 10) {
						cout << "Current word list..." << endl;
						for (int i = 0; i < wordList.size(); i++)
							cout << i + 1 << ": " << wordList[i] << endl;
							cout << "\n============================================================\n" << endl;
					}

				    cout << "Do you know any other letter or sequence [y/n] >> ";
					cin >> resp;
					if (resp == "y") { cout << "\n============================================================\n" << endl; }
				}
		    }
        }
		cout << "\n============================================================\n" << endl;
		for (int i = 0; i < wordList.size(); i++) {
			if ((i + 1) == wordList.size()) { fout << wordList[i]; }
			else { fout << wordList[i] << "\n"; }
        }
		fout.close();
		
        while(!(run & 4) && !(run & 8)) {
            if(!(run & 2)) { cout << "Would you like to open the file or enter a new word or exit [o/w/e] >> "; }
            else { cout << "Would you like to enter a new word or exit [w/e] >> "; }
		    cin >> resp;
            resp = tolower(resp[0]);
    		if (resp == "o" && !(run & 2)) {
    			for (int i = 0; i < wordList.size(); i++) { cout << i + 1 << ": " << wordList[i] << endl; }
                run |= 2;
    		} else if (resp == "w") {
    			cout << "\n============================================================\n" << endl;
    			cout << "\t\t\t\t\t\t\t    Please wait..." << endl;
    			wordList.erase(wordList.begin(), wordList.end());
                cout << "Enter encrypted word >> ";
                cin >> en;
                cout << "Enter known letters in the encrypted word >> ";
                cin >> in;
                cout << "Enter known letters that aren't in the encrypted word >> ";
                cin >> out;
                run |= 4;
    		} else { run |= 8; }
        }
	    cout << "Look in the " << filename << " for the decrypted word(s)." << endl;
    }

    return 0;
}

// Finding all the common letters in both strings
bool commonLetters(string &common, string in, string out) {
    string temp_in = in;
    string temp_out = out;
    sort(begin(temp_in), end(temp_in));
    sort(begin(temp_out), end(temp_out));
    set_intersection(begin(temp_in), end(temp_in), begin(temp_out), end(temp_out), back_inserter(common));
    return common.size();
}

// Checks the word to see if it has the letter that I know for sure isn't in the phrase
bool forgetWord(string line, string letter) {
	int count = 0, i = 0, j = 0;
	bool found = true;

	while (letter.size() != count) {
		while (found) {
			if (line[i] == letter[j]) { return false; }
			if (i == line.size() && count < letter.size()) { found = false; }
			i++;
		}
		count++;
		i = 0;
		j++;
		found = true;
	} return true;
}

// Check all the words to see if it has the letters in the word
bool checkWord(string line, string letter) {
	int count = 0, i = 0, j = 0;
	bool found = true;

	while (letter.size() != count) {
		while (found) {
			if (line[i] == letter[j]) { found = false; }
			if (i == line.size() && count < letter.size()) { return false; }
			i++;
		}
		count++;
		i = 0;
		j++;
		found = true;
	} return true;
}

//Checks to see if the word from the file has the same amount of characters in each
bool amountLetters(string line, string cypher) {
	int cypherCount = 0, lineCount = 0;
	char cypherLetter, lineLetter;

	for (int i = 0; i < cypher.size(); i++) {
		cypherLetter = cypher[i];
		for (int j = 1; j < cypher.size(); j++) {
			if (cypher[j] == cypherLetter) { cypherCount++; }
        }

		lineLetter = line[i];
		for (int j = 1; j < line.size(); j++) {
			if (line[j] == lineLetter) {lineCount++; }
        }
	}
	if (cypherCount == lineCount) {	return true; }
	return false;
}

// Checks to see if the replacing of the letters won't effect the other letters
string letterPlacement(string currentWord, vector<string>& wordList, char letter, char resp) {
	string word;
	char temp = '0';
	bool valid = true;
	int i = 0, place = 0, count = 0, lCount = 0;

	for (int m = 0; m < currentWord.size(); m++) {
		if (currentWord[m] == resp) {
			currentWord[m] = temp;
			place = i;
			count++;
		} else if (currentWord[m] == letter) {
			currentWord[m] = resp;
			place = i;
			placement(place, wordList, currentWord);
		} i++;
	}
	for (int j = 0; j < currentWord.size(); j++) {
		if (currentWord[j] == '0') { currentWord[j] = letter; }
    } return currentWord;
}

// Removing the words that don't have the letter in the correct spot
void placement(int place, vector<string>& wordList, string currentWord) {
	string word;
	for (int i = 0; i < wordList.size(); i++) {
		if (i < 0) { i = 0; }
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
	int intTemp = 0, sequenceSize = word.size(), flag = 0;

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
