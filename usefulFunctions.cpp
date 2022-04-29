#include "usefulFunctions.h"

void copyString(char*& destination,char*& source)
{
	int length = strlen(source) + 1;
	delete[] destination;
	destination = new char[length];
	strcpy(destination, source);
}
int sortPredicate()
{
	cout << "What criterium would you like to sort by?\n 1.Author 2.Title 3.Rating\n";
	char input[MAXLENGTH];
	char* criterium;
	do
	{
		cin.getline(input, MAXLENGTH);
		int length = strlen(input) + 1;
		criterium = new char[length];
		strcpy(criterium, input);

	} while (strcmp(criterium, "Author") != 0 && strcmp(criterium, "Title") != 0 && strcmp(criterium, "Rating") != 0);
	if (strcmp(criterium, "Author") == 0)
	{
		return 1;
	}
	else if (strcmp(criterium, "Title") == 0)
	{
		return 2;
	}
	else
	{
		return 3;
	}
	delete[] criterium;
}
bool sortPredicateAscension()
{
	cout << "What second criterium would you like to sort by?\n 1.Ascending 2.Descending\n";
	char input[MAXLENGTH];
	char* criterium;
	do
	{
		cin.getline(input, MAXLENGTH);
		int length = strlen(input) + 1;
		criterium = new char[length];
		strcpy(criterium, input);

	} while (strcmp(criterium, "Ascending") != 0 && strcmp(criterium, "Descending") != 0);
	return strcmp(criterium, "Ascending") == 0;

}