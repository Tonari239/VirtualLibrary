#include "doctest.h"
#include "usefulFunctions.h"

#include <iostream>
using namespace std;
TEST_SUITE("Useful functions")
{
	TEST_CASE("Copy string accepting nullptr as source")
	{
		char* destination=nullptr;
		char* source = nullptr;
		copyString(destination, source);

		CHECK(destination == nullptr);
		
	}

	TEST_CASE("Copy string accepting nullptr as destination")
	{
		char* destination = nullptr;
		char* source = new char[9];
		strcpy(source, "neshtosi");
		copyString(destination, source);

		CHECK(destination != nullptr);
		CHECK(strcmp(destination, source) == 0);
		delete[] destination;
		delete[] source;
	}
		
	TEST_CASE("Copy string with dynamic char* source")
	{
		char* destination = new char[11];
		strcpy(destination, "neshtosinz");
		char* source = new char[9];
		strcpy(source, "neshtosi");
		copyString(destination, source);

		CHECK(destination != nullptr);
		CHECK(strcmp(destination, source) == 0);
		delete[] destination;
		delete[] source;
	}

	TEST_CASE("Copy string with const char* source")
	{
		char* destination = new char[11];
		strcpy(destination, "neshtosinz");
		const char* source = "neshtosi";
		copyString(destination, (char*)source);

		CHECK(destination != nullptr);
		CHECK(strcmp(destination, source) == 0);
		delete[] destination;
	}

	TEST_CASE("Validate criterion")
	{
		const char* inputCriterion = "CriterionThree";
		const char* criteriaToCheck[] = { "Ascending", "Descending","CriterionThree","CriterionFour"};
		int criteriaCount = 4;
		bool result = validateCriterion((char*)inputCriterion, criteriaToCheck, criteriaCount);
		CHECK(result == true);
		inputCriterion = "NeshtoSi";
		result = validateCriterion((char*)inputCriterion, criteriaToCheck, criteriaCount);
		CHECK(result == false);
	}

	TEST_CASE("To lower char")
	{
		char c = 'A';
		c = toLowerChar(c);
		CHECK(c == 'a');
	}

	TEST_CASE("To lower string")
	{
		char* test = nullptr;
		copyString(test, (char*)"rAgPeAcAtTEFVAa");
		toLowerString((char*)test);
		CHECK(strcmp(test, "ragpeacattefvaa") == 0);
	}
	
}
