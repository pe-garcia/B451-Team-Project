#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "AES.h"

using namespace std;

void writetoFile(char block[])
{
	ofstream myfile;						// output of the file for testing purposes
	myfile.open("encryptedfile.txt");
	if (!myfile) {
		cout << " Unable to open file." << endl;
		exit(1);
	}
	for (int j = 0; j < 16; j++) {

		myfile << block[j];

	}

	myfile.close;
}
void SubBytes(char state[]){

	for (int k = 0; k < 16; k++)
	{
		state[k] = s_box[state[k]];
	}
		
}
void ShiftRows(char File[]) {
	char hold[16];
	
	hold[0] = state[0];
	hold[1] = state[5];
	hold[2] = state[10];
	hold[3] = state[15];

	hold[4] = state[4];
	hold[5] = state[9];
	hold[6] = state[14];
	hold[7] = state[3];

	hold[8] = state[8];
	hold[9] = state[13];
	hold[10] = state[2];
	hold[11] = state[7];

	hold[12] = state[12];
	hold[13] = state[1];
	hold[14] = state[6];
	hold[15] = state[11];

	for (int i = 0; i < 16; i++) {		// repopulate File with the 

		state[i] = hold[i];
	}
}
void MixColumns(char state[]) {

	char hold[16];

	hold[0] = (2* state[0]) ^ (state[1] * 3) ^ (state[2]) ^ (state[3]);
	hold[1] = state[0] ^ (state[1] * 2) ^ (state[2] * 3) ^ (state[3]);
	hold[2] = (state[0]) ^ (state[1]) ^ (state[2] * 2) ^ (state[3] * 3);
	hold[3] = (state[0] * 3) ^ (state[1]) ^ (state[2]) ^ (state[3] * 2);

	hold[4] = (state[4] * 2) ^ (state[5] * 3) ^ (state[6]) ^ (state[7]);
	hold[5] = state[4] ^ (state[5] * 2) ^ (state[6] * 3) ^ (state[7]);
	hold[6] = (state[4]) ^ (state[5]) ^ (state[6] * 2) ^ (state[7] * 3);
	hold[7] = (state[4] * 3) ^ (state[5]) ^ (state[6]) ^ (state[7] * 2);

	hold[8] = (2 * state[8]) ^ (state[9] * 3) ^ (state[10]) ^ (state[11]);
	hold[9] = state[8] ^ (state[9] * 2) ^ (state[10] * 3) ^ (state[11]);
	hold[10] = (state[8]) ^ (state[9]) ^ (state[10] * 2) ^ (state[11] * 3);
	hold[11] = (state[8] * 3) ^ (state[9]) ^ (state[10]) ^ (state[11] * 2);

	hold[12] = (state[12] * 2) ^ (state[13] * 3) ^ (state[14]) ^ (state[15]);
	hold[13] = state[12] ^ (state[13] * 2) ^ (state[14] * 3) ^ (state[15]);
	hold[14] = (state[12]) ^ (state[13]) ^ (state[14] * 2) ^ (state[15] * 3);
	hold[15] = (state[12] * 3) ^ (state[13]) ^ (state[14]) ^ (state[15] * 2);

	for (int i = 0; i < 16; i++) {

		state[i] = hold[i];
	}

}
void AddRoundKey(char state[]) {
	for (int i = 0; i < 16; i++)
	{
		state[i] ^= GeneratedKeys[i];
	}
}
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
void aesEncrypt(string GlobalFile[], char *paddedmsg, int repeat) 
{
	char block[16];
	int start;

	for (int i = 0; i < repeat; i++) {

		start = 16 * i;

		for (int j = start; j < start + 16; j++) {

			block[j] = paddedmsg[j];
		}


		for (int rounds = 0; rounds < 10; rounds++)
		{

			if (rounds < 9) {
				SubBytes(block);
				ShiftRows(block);
				MixColumns(block);
				AddRoundKey(block);
			}
			if (rounds == 9) {
				SubBytes(block);
				ShiftRows(block);
				AddRoundKey(block);
			}
		}
		writetoFile(block);
	}
}

int padMessage(string File, char * paddedmsg)
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

		paddedmsg = new char[padmsglen];	// Dynamically allocate size of the new string

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
	char * paddedmsg;
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

