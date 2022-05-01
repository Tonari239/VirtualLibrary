#include "library.h"
#include "usefulFunctions.h"
#include <fstream>
#include <iostream>
#include "usefulFunctions.cpp"
using namespace std;

void Library::copy(const Library& other)
{
	mCount = other.mCount;
	mCapacity = other.mCapacity;
	mBooks = new Book*[mCapacity];
	for (int i = 0; i < mCount; i++)
	{
		mBooks[i] = new Book(*(other.mBooks[i]));
	}
	
}
void Library::free()
{
	delete[] mBooks;
}
void Library::resize()
{
	if (mCount >=3.0/4*mCapacity)
	{
		mCapacity *= 2;
		Book** newArr = new Book*[mCapacity];
		for (int i = 0; i < mCount; i++)
		{
			newArr[i] = new Book(*mBooks[i]);
		}
		for (int i = 0; i < mCount; i++)
		{
			delete mBooks[i];
		}
		delete[] mBooks;
		mBooks = newArr;
	}
}
void Library::sortByString(char* (Book::* function)() const) // 1-> ascending 0 -> descending
{
	int mode = sortPredicateAscension();
	for (int j = 1; j < mCount; j++)
	{
		for (int i = 0; i < mCount; i++)
		{
			if (mode && strcmp((*mBooks[i].*function)(), (*mBooks[j].*function)()) > 0)
			{
				swap(mBooks[j], mBooks[i]);
			}
			else if (!mode && strcmp((*mBooks[i].*function)(), (*mBooks[j].*function)()) < 0)
			{
				swap(mBooks[j], mBooks[i]);
			}
		}
	}
}
void Library::sortByRating()
{
	int mode = sortPredicateAscension();
	for (int j = 1; j < mCount; j++)
	{
		for (int i = 0; i < mCount; i++)
		{
			if (mode && (*mBooks[i]).getRating() < (*mBooks[j]).getRating())
			{
				swap(mBooks[j], mBooks[i]);
			}
			else if (!mode && (*mBooks[i]).getRating() > (*mBooks[j]).getRating())
			{
				swap(mBooks[j], mBooks[i]);
			}
		}
	}

}

//TODO: ignore caps and small letters ; ask if we can use cstring
int Library::findByString(char* input, char* (Book::* function)() const) const
{
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp(((*mBooks[i]).*function)(), input) == 0)
		{
			return i;
		}
	}
}
int Library::findByISBN(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if ((*mBooks[i]).getISBN() == atoi(input))
		{
			return i;
		}
	}

}
int Library::findByDescription(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if (strstr((*mBooks[i]).getDescription(), input) != nullptr)
		{
			return i;
		}
	}

}

Library::Library()
{
	mCapacity = START_CAPACITY;
	mCount = 0;
	mBooks = new Book*[mCapacity];
}
Library::Library(const Library& other)
{
	copy(other);
}
Library::~Library()
{
	for (int i = 0; i < mCount; i++)
	{
		remove((*mBooks[i]).getFileName());
		delete mBooks[i];
	}
	delete[] mBooks;
}
Library& Library::operator=(const Library& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
Book** Library::getBooks() const
{
	return mBooks;
}


void Library::sort()
{
	int predicateResult = sortPredicate(); // 1->Title; 2->Author; 3->Rating
	if (predicateResult == 1)
	{
		sortByString(&(Book::getTitle));
	}
	else if (predicateResult == 2)
	{
		sortByString(&(Book::getAuthor));
	}
	else
	{
		sortByRating();
	}
	print();
}
void Library::addBook(const Book& bookToAdd)
{
	resize();
	mBooks[mCount] = new Book(bookToAdd);
	ofstream outputFile(bookToAdd.getFileName());
	if (outputFile)
	{
		outputFile << bookToAdd;
	}
	++mCount;
	outputFile.close();
}
void Library::removeBook(Book bookToRemove)
{
	int removeIndex = 0;
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp((*mBooks[i]).getTitle(), bookToRemove.getTitle()) == 0)
		{
			removeIndex = i;
		}
	}
	delete mBooks[removeIndex];
	for (int i = removeIndex; i < mCount; i++)
	{
		mBooks[i] = mBooks[i+1];
	}
	--mCount;
	cout << "Would you like to delete file associated with the book? \nY/N\n";
	char input;
	cin >> input;
	while(input != 'Y' && input != 'N')
	{
		cout << "Wrong input!Press Y/N";
		cin >> input;
	}
	if (input == 'Y')
	{
		remove(bookToRemove.getFileName());
	}
}
void Library::print()
{
	for (int i = 0; i < mCount; i++)
	{
		(*mBooks[i]).print();
	}
}
Book& Library::findBy(char* input) const
{
	int criterion = findPredicate();
	int bookIndex;
	if (criterion == 1)
	{
		bookIndex=findByString(input,&Book::getTitle);
	}
	else if (criterion == 2)
	{
		bookIndex=findByString(input, &Book::getAuthor);
	}
	else if (criterion == 3)
	{
		bookIndex=findByISBN(input);
	}
	else
	{
		bookIndex=findByDescription(input);
	}
	return *mBooks[bookIndex];
}
void Library::find(char* input) const
{
	findBy(input).print();
}
void Library::displayBook(const Book& book) const
{
	int mode; //1->by pages 2->by sentences;
	cout <<"Enter \"1\" to read in page mode and \"2\" to read in sentence mode\n";
	cin >> mode;
	while (mode!=1 && mode!=2)
	{
		cout << "Wrong input! Enter \"1\" or \"2\"";
		cin >> mode;
	}
	ofstream file(book.getFileName());
	if (mode == 1)
	{
		readByPages(file);
	}
	else
	{
		readBySentences(file);
	}
}

