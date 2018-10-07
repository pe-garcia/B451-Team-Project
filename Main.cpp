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
	int pad;								// Integer that will populate the padding

	string *paddedmsg;						// Dynamic string that will house the contents of the file plus the padding
	ofstream myfile;						// output of the file for testing purposes
	myfile.open("testpad.txt");
	if (remainder == 0) {

		cout << "True";						// test that if the file is  multiple of 16 code will do nothing

	}
	else {

		pad = 16 - remainder;;				// determine size and content
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
	myfile.close();
}

void SubBytes(){}
void ShiftRows() {}
void MixColumns() {}
void AddRoundKey() {}
void aesEncrypt() 
{

	for (int rounds = 0; rounds < 10; rounds++)
	{
		if (rounds < 9) {
			SubBytes();
			ShiftRows();
			MixColumns();
			AddRoundKey();
		}
		if (rounds == 9) {
			SubBytes();
			ShiftRows();
			AddRoundKey();
		}
	}
}
void aesDecrypt() {}

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

	MyFile.close();

	return 0;
}

