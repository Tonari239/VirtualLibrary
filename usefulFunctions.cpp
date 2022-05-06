#include "usefulFunctions.h"
#include <fstream>
#include <iostream>
#include "book.h"
#include <conio.h>
using namespace std;


void copyString(char*& destination,char* source)
{
	if (source == nullptr)
	{
		destination = nullptr;
		return;
	}
	int length = strlen(source) + 1;
	delete[] destination;
	destination = new char[length];
	strcpy(destination, source);
}

int sortPredicate()
{
	cout << "What criterion would you like to sort by?\n 1.Author 2.Title 3.Rating\n";
	const char* criteria[] = { "Title","Author","Rating"};
	char* criterion = criterionInput(criteria, 3);
	
	int result;
	if (strcmp(criterion, "Title") == 0)
	{
		result= 1;
	}
	else if (strcmp(criterion, "Author") == 0)
	{
		result= 2;
	}
	else
	{
		result= 3;
	}
	delete[] criterion;
	return result;
}

int findPredicate()
{
	cout << "What criterion would you like to search by?\n 1.Title 2.Author 3.ISBN 4.Description\n";
	const char* criteria[] = { "Title","Author","ISBN","Description"};
	char* criterion = criterionInput(criteria, 4);

	int result;
	if (strcmp(criterion, "Title") == 0)
	{
		result = 1;
	}
	else if (strcmp(criterion, "Author") == 0)
	{
		result = 2;
	}
	else if (strcmp(criterion, "ISBN") == 0)
	{
		result = 3;
	}
	else
	{
		result = 4;
	}
	delete[] criterion;
	return result;
}

bool sortPredicateAscension()
{
	cout << "What second criterion would you like to sort by?\n 1.Ascending 2.Descending\n";
	const char* criteria[] = { "Ascending","Descending"};
	char* criterion = criterionInput(criteria, 2);
	bool result = strcmp(criterion, "Ascending") == 0;
	delete[] criterion;
	return result;
}

bool validateCriterion(char* inputCriterion,const char** criteriaToCheck, int criteriaCount)
{
	bool isValidInput = false;
	for (int i = 0; i < criteriaCount; i++)
	{
		if (strcmp(inputCriterion, criteriaToCheck[i]) == 0)
		{
			isValidInput = true;
		}
	}
	return isValidInput;
}

char* criterionInput(const char** criteriaToCheck,int criteriaCount)
{
	char input[MAX_LENGTH];
	char* criterion=nullptr;
	do
	{
		delete[] criterion;
		cin.getline(input, MAX_LENGTH);
		int length = strlen(input) + 1;
		criterion = new char[length];
		strcpy(criterion, input);

	} while (!validateCriterion(criterion, criteriaToCheck, criteriaCount));
	return criterion;
}

void readByPages(istream& file)
{
	int pageCount;
	cout<<"Enter how many pages you would like to read.\n";
	cin >> pageCount;
	int counter = 0;
	while (!file.eof() && counter<pageCount)
	{
		char buff[MAX_LENGTH];
		file.getline(buff, MAX_LENGTH);
		cout << buff;
		++counter;
	}
	cout << " "; // printing the pause
}

void readSentence(istream& file)
{
	char c;
	if (!file.eof() && (file.peek() != '!' && file.peek() != '?' && file.peek() != '.'))
	{
		file.get(c);
		cout << c;
	}
	file.get(c); // reading the delimiter
	cout << c;
	file.get(c); //reading the interval
	cout << c;
}

void readBySentences(istream& file)
{
	int sentenceCount;
	cout << "Enter how many sentences you would like to read.\n";
	cin >> sentenceCount;
	for (int i = 0; i < sentenceCount; i++)
	{
		readSentence(file);
	}
}

char toLowerChar(char& c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + ('a'-'A');
	}
	return c;
}

char* toLowerString(char* input)
{
	int length = strlen(input) + 1;
	for (int i = 0; i < length; i++)
	{
		input[i] = toLowerChar(input[i]);
	}
	return input;
}

void setField(Book& book,const char* fieldName,void (Book::*function)(char* input)) 
{
	cout << "Enter input for " << fieldName << endl;
	char buffer[MAX_LENGTH];
	cin.getline(buffer, MAX_LENGTH);
	char* input=nullptr;
	copyString(input, buffer);
	(book.*function)(input);
	cout << endl;
	delete[] input;
}

//идеята е взаимствана от  https ://www.dreamincode.net/forums/topic/238072-censor-password-in-c/ , отговор на потребител "staycrisp"
void enterPassword(char* input,char encryptChar)
{
	char inputChar='0';
	int counter = 0;
	while (inputChar != '\r')
	{ 
		inputChar = _getch(); // used with  #include <conio.h>
		if (inputChar == '\b' && counter != 0)
		{
			input[counter] = '\0';
			--counter;
			cout << "\b";
			cout << " "; // idea from https://stackoverflow.com/questions/3745861/how-to-remove-last-character-put-to-stdcout
			cout << "\b";
		}
		else if (inputChar != '\r')
		{
			input[counter] = inputChar;
			std::cout << encryptChar;
			++counter;
		}
	}
	input[counter] = '\0';
	cout << endl;
}

bool authorize(const char* pass)
{
	bool isAuthorized = false;
	cout << "Enter admin password:\n";
	char input[MAX_LENGTH];
	enterPassword(input, '*');
	if (strcmp(pass,input)!=0)
	{
		cout << "Wrong password! Operation failed\n";
		return isAuthorized;
	}
	isAuthorized = true;
	return isAuthorized;
}

bool charsAreOnlySpaces(char* buffer, int count)
{
	for(int i=0;i<count;i++)
	{
		if (buffer[i] != ' ')
		{
			return false;
		}
	}
	return true;
}