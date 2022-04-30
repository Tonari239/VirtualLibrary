#ifndef __UsefulFunctions
#define __UsefulFunctions

#include <iostream>
using namespace std;
#define MAXLENGTH 1024

void copyString(char*& destination, char*& source);
int sortPredicate(); 
int findPredicate();
bool sortPredicateAscension();
bool validateCriterion(char* inputCriterion, const char** criteriaToCheck, int criteriaCount);
char* criterionInput(const char** criteriaToCheck, int criteriaCount);

#endif