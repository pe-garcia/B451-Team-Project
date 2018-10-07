/**************************************************************
File:          Main.cc
Description:
Authors:       Daniel Gutierrez, Pedro Garcia
Class:         Security In Computing
Date:          September 2018
***************************************************************/


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
//#include "AES.h"

using namespace std;

void padMessage(string File)
{
	int fileLen = File.length();			// Get the length of the text file. 
	int remainder = fileLen % 16;			// This 128 bit encryption requires 16 byte blocks
	int pad;					// Integer that will populate the padding

	string *paddedmsg;				// Dynamic string that will house the contents of the file plus the padding
	ofstream myfile;				// output of the file for testing purposes
	myfile.open("testpad.txt");
	if (remainder == 0) {

		cout << "True";				// test that if the file is  multiple of 16 code will do nothing

	}
	else {

		pad = 16 - remainder;;			// determine size and content
		int padmsglen = fileLen + pad;		// of the padding

		paddedmsg = new string[padmsglen];	// Dynamically allocate size of the new string
			
		for (int i = 0; i < fileLen; i++) {	// copy contents

			paddedmsg[i] = File[i];
			myfile << paddedmsg[i];

		}
		for (int j = fileLen; j < padmsglen; j++) {// add padding

			paddedmsg[j] = pad;
			myfile << paddedmsg[j];

		}

	}
	for (int i = 0; i < 16; i++) {

		File[i] = paddedmsg[i].c_str;
	}

	myfile.close();
}

void SubBytes(){}
void ShiftRows(string File) {
	string placeHolder[16];

	for (int i = 0; i < 4; i++) {		// row 0: no elements shift place
		
		placeHolder[i] = File[i];
	}
	for (int i = 4; i < 7; i++) {		// row 1: elements 5,6,7 shift left so element 4 can shift right

		placeHolder[i] = File[i + 1];
	}

	placeHolder[7] = File[4];		// row 1: 1st elements shifts all the way right


	for (int i = 8; i < 10; i++) {		// row 2: 1st 2 elements shift left 2nd two shift right

		placeHolder[i] = File[i+2];
	}
	for (int i = 10; i < 12; i++) {

		placeHolder[i] = File[i - 2];
	}

	placeHolder[12] = File[15];		// row 3: first 3 elements shift right this sets the last element to the 12th position to make room

	for (int i = 13; i < 16; i++) {

		placeHolder[i] = File[i + 1];
	}

	for (int i = 0; i < 16; i++) {		// repopulate File with the shifted array

		File[i] = placeHolder[i].c_str;
	}
}
void MixColumns() {}
void AddRoundKey() {}
void aesEncrypt(string File) 
{

	for (int rounds = 0; rounds < 10; rounds++)
	{
		if (rounds < 9) {
			SubBytes();
			ShiftRows(File);
			MixColumns();
			AddRoundKey();
		}
		if (rounds == 9) {
			SubBytes();
			ShiftRows(File);
			AddRoundKey();
		}
	}
}

int main()
{
	string Password;
	string FileName;
	string FileContents;

	cout << "Enter the name of the file to be read..." << endl;
	cin >> FileName;
	cout << "Enter the 16 character password to be used as the encryption key..." << endl;
	cin >> Password;

	ifstream MyFile;

	MyFile.open(FileName);

	if (!MyFile) {
		cout << " Unable to open file." << endl;
		exit(1);
	}

	getline(MyFile, FileContents, '\0');
	cout << FileContents << endl;
	padMessage(FileContents);

	aesEncrypt(FileContents);

	MyFile.close();

	return 0;
}

