#ifndef __UsefulFunctions
#define __UsefulFunctions

#include <iostream>
#include "book.h"
using namespace std;
#define MAX_LENGTH 1024

void copyString(char*& destination, char* source);
int sortPredicate(); 
int findPredicate();
bool sortPredicateAscension();
bool validateCriterion(char* inputCriterion, const char** criteriaToCheck, int criteriaCount);
char* criterionInput(const char** criteriaToCheck, int criteriaCount);
void readByPages(istream& file);
void readBySentences(istream& file);
char toLowerChar(char c);
char* toLowerString(char* input);
void readSentence(istream& file);
void setField(Book& book,const char* fieldName, void (Book::* function)(char* input));
bool authorize(const char* pass);

#endif