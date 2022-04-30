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

void Library::Sort()
{
	int predicateResult = sortPredicate(); // 1->Author; 2->Title; 3->Rating
	if (predicateResult == 1)
	{
		sortByTitle();
	}
	else if (predicateResult == 2)
	{
		sortByAuthor();
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

void Library::sortByTitle() // 1-> ascending 0 -> descending
{
	int mode = sortPredicateAscension();
	for (int j = 1; j < mCount; j++)
	{
		for (int i = 0; i < mCount; i++)
		{
			if (mode && strcmp((*mBooks[i]).getTitle(), (*mBooks[j]).getTitle()) > 0)
			{
				swap(mBooks[j], mBooks[i]);
			}
			else if (!mode && strcmp((*mBooks[i]).getTitle(), (*mBooks[j]).getTitle()) < 0)
			{
				swap(mBooks[j], mBooks[i]);
			}
		}
	}
}
void Library::sortByAuthor()
{
	int mode = sortPredicateAscension();
	for (int j = 1; j < mCount; j++)
	{
		for (int i = 0; i < mCount; i++)
		{
			if (mode && strcmp((*mBooks[i]).getAuthor(), (*mBooks[j]).getAuthor()) > 0)
			{
				swap(mBooks[j], mBooks[i]);
			}
			else if (!mode && strcmp((*mBooks[i]).getAuthor(), (*mBooks[j]).getAuthor()) < 0)
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

int Library::findByTitle(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp((*mBooks[i]).getTitle(), input) == 0)
		{
			return i;
		}
	}
}
int Library::findByAuthor(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp((*mBooks[i]).getAuthor(), input) == 0)
		{
			return i;
		}
	}
}
int Library::findByISBN(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if ((*mBooks[i]).getISBN()==atoi(input))
		{
			return i;
		}
	}

}
int Library::findByDescription(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		if (strstr((*mBooks[i]).getDescription(), input) !=nullptr)
		{
			return i;
		}
	}

}
void Library::displayBook(const Book& book) const
{

}
Book& Library::findBy(char* input) const
{
	int criterium = findPredicate();
	int bookIndex=1;
	if (criterium == 1)
	{
		findByTitle(input);
	}
	else if (criterium == 2)
	{
		findByAuthor(input);
	}
	else if (criterium==3)
	{
		findByISBN(input);
	}
	else
	{
		findByDescription(input);
	}
	(*mBooks[bookIndex]).print();
	return *mBooks[bookIndex];
}
