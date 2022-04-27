#include "usefulFunctions.h"

void copyString(char*& source,char*& destination)
{
	int length = strlen(source) + 1;
	delete[] destination;
	destination = new char[length];
	strcpy(destination, source);
}