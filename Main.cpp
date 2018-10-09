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

void SubBytes(){}
void ShiftRows(string* File,string block[]) {
	string placeHolder[16];

	for (int i = 0; i < 4; i++) {		// row 0: no elements shift place
		
		placeHolder[i] = File[i];
	}
	for (int i = 4; i < 7; i++) {		// row 1: elements 5,6,7 shift left so element 4 can shift right

		placeHolder[i] = File[i + 1];
	}

	placeHolder[7] = File[4];			// row 1: 1st elements shifts all the way right


	for (int i = 8; i < 10; i++) {		// row 2: 1st 2 elements shift left 2nd two shift right

		placeHolder[i] = File[i+2];
	}
	for (int i = 10; i < 12; i++) {

		placeHolder[i] = File[i - 2];
	}

	placeHolder[12] = File[15];			// row 3: first 3 elements shift right this sets the last element to the 12th position to make room

	for (int i = 13; i < 16; i++) {

		placeHolder[i] = File[i + 1];
	}

	for (int i = 0; i < 16; i++) {		// repopulate File with the 

		File[i] = placeHolder[i].c_str;
	}
}
void MixColumns() {}
void AddRoundKey() {}
void KeyExpansion(string Password) //Generates all keys that will be used and stores them into an array.
{
	for (int i = 0; i < 16; i++) //store first 16 bytes into the beginning of the expanded key array
	{
		GeneratedKeys[i] = Password[i];
	}

	int NrGenKeys = 1; //used as control variable in loop to ensure we don't generate more than the 11 needed
	int NrGenBytes = 16; //used to count number of bytes, 16  bytes denotes generation of 1 key. Initialized to 16 to 
	char tmp[4];
	int count; //Used to check which rcon value needs to be used
	for (NrGenKeys; NrGenKeys<11; NrGenKeys++)
	{
		//takes chunk of previously generated key to be used for generation of new key
		for (int i = 0; i < 4; i++)
		{
			tmp[i] = GeneratedKeys[i + (NrGenBytes)-4];
		}
		if (NrGenBytes % 16 == 0) //This denotes a new key has been made, then takes chunk of recently made key
		{
			RotWord(tmp, count);
			count += 1;
			NrGenKeys += 1;
		}
		for (char a = 0; a < 4; a++)
		{
			GeneratedKeys[NrGenBytes] = GeneratedKeys[NrGenBytes - 16] ^ tmp[a];
			NrGenBytes++;
		}
	}

}
void RotWord(string tmp, int count)
{
	char start;
	start = tmp[0];
	tmp[1] = tmp[2];
	tmp[2] = tmp[3];
	tmp[3] = start;
	tmp[3] = s_box[tmp[3]];
	tmp[2] = s_box[tmp[2]];
	tmp[1] = s_box[tmp[1]];
	tmp[0] = s_box[tmp[0]];
	tmp[0] ^= rcon[count];
}
void aesEncrypt(string GlobalFile[], string *paddedmsg, int repeat) 
{
	string block[16];
	int start;

	for (int i = 0; i < repeat; i++) {
		for (int j = 0; j < 16; j++) {
			
			block[j] = paddedmsg[];
		}
	}

		for (int rounds = 0; rounds < 10; rounds++)
		{

			if (rounds < 9) {
				SubBytes();
				ShiftRows(File, block);
				MixColumns();
				AddRoundKey();
			}
			if (rounds == 9) {
				SubBytes();
				ShiftRows(File, block);
				AddRoundKey();
			}
		}
}
int padMessage(string File, string * paddedmsg)
{
	int fileLen = File.length();			// Get the length of the text file. 
	int remainder = fileLen % 16;			// This 128 bit encryption requires 16 byte blocks
	int pad;								// Integer that will populate the padding
	int repeat;
	int padmsglen;

	ofstream myfile;						// output of the file for testing purposes
	myfile.open("testpad.txt");
	if (remainder == 0) {

		cout << "True";						// test that if the file is  multiple of 16 code will do nothing

	}
	else {

		pad = 16 - remainder;;				// determine size and content
		padmsglen = fileLen + pad;		// of the padding

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

	repeat = padmsglen / 16;
	

	myfile.close();
	return repeat;
}
int main()
{
	string Password;
	string FileName;
	string FileContents;
	string globalFile[2048];
	string *paddedmsg;
	int repeat;

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
	repeat = padMessage(FileContents, paddedmsg);

	aesEncrypt(globalFile,paddedmsg,repeat);

	MyFile.close();

	return 0;
}

