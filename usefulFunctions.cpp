#include "usefulFunctions.h"
#include <fstream>
#include <iostream>
#include "book.h"
#include <conio.h>
using namespace std;


void copyString(char*& destination,char* source)
{
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
		cout << buff << endl;
		++counter;
	}
}
void readSentence(istream& file)
{
	char c;
	if (!file.eof() && (file.peek() != '!' && file.peek() != '?' && file.peek() != '.'))
	{

		file.get(c);
		cout << c;
	}
	file.get(c);
	cout << c << " ";
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
char toLowerChar(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c + 32;
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
	char* input;
	copyString(input, buffer);
	(book.*function)(input);
	delete[] input;
}
void enterPassword(char* input,char encryptChar)
{
	char inputChar='0';
	int counter = 0;
	while (inputChar != '\r')
	{
		inputChar = _getch(); // used with  #include <conio.h>

		if (inputChar != '\r')
		{
			input[counter] = inputChar;
			std::cout << encryptChar;
			++counter;
		}
	}
}
bool authorize(const char* pass)
{
	bool isAuthorized = false;
	cout << "Enter admin password:\n";
	char input[MAX_LENGTH];
	enterPassword(input, '*');
	char* inputPassword;
	copyString(inputPassword, input);
	while (strcmp(pass,input)!=0)
	{
		cout << "Wrong password! Try again or enter \"Exit\" ";
		enterPassword(input, '*');
		copyString(inputPassword, input);
		if (strcmp(input, "Exit") == 0)
		{
			return isAuthorized;
		}
	}
	isAuthorized = true;
	return isAuthorized;
	delete[] inputPassword;
}