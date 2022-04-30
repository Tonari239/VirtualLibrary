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
	cout << "What criterium would you like to search by?\n 1.Title 2.Author 3.ISBN 4.Description\n";
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
	cout << "What second criterium would you like to sort by?\n 1.Ascending 2.Descending\n";
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
	char input[MAXLENGTH];
	char* criterion=nullptr;
	do
	{
		delete[] criterion;
		cin.getline(input, MAXLENGTH);
		int length = strlen(input) + 1;
		criterion = new char[length]; // check if there is a memory leak here
		strcpy(criterion, input);

	} while (!validateCriterion(criterion, criteriaToCheck, criteriaCount));
	return criterion;
}