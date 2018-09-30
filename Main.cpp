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
#include "AES.h"

using namespace std;

int main()
{
	string Password;
	string FileName;

	cout << "Enter the name of the file to be read..." << endl;
	cin >> FileName;
	cout << "Enter the 16 character password to be used as the encryption key..." << endl;
	cin >> Password;

	ifstream MyFile;

	MyFile.open(FileName);



	return 0;
}
