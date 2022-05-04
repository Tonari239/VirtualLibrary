#include "library.h"
#include "usefulFunctions.h"
#include <fstream>
#include <iostream>
using namespace std;

void Library::copy(const Library& other)
{
	mCount = other.mCount;
	mCapacity = other.mCapacity;
	mBooks = new Book*[mCapacity];
	for (int i = 0; i < mCount; i++)
	{
		mBooks[i] = new Book(*(other.mBooks[i])); // count is always less than capacity so no overflow will occur
	}
	copyString(mAssociatedFile, other.getFileName());
}
void Library::free()
{
	for (int i = 0; i < mCount; i++)
	{
		delete mBooks[i];
	}
	remove(getFileName());
	delete[] mBooks;
	delete[] mAssociatedFile;
}
void Library::resize()
{
	if (mCount >=3.0/4*mCapacity)
	{
		mCapacity *= 2;
		Book** newArr = new Book*[mCapacity];
		for (int i = 0; i < mCount; i++)
		{
			newArr[i] = mBooks[i];
		}
		delete[] mBooks;
		mBooks = newArr;
	}
}


Book** Library::getBooks() const
{
	return mBooks;
}
char* Library::getFileName() const
{
	return mAssociatedFile;
}

Library::Library(char* fileName)
{
	mCapacity = START_CAPACITY;
	mCount = 0;
	mBooks = new Book*[mCapacity];
	copyString(mAssociatedFile, fileName);
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


int Library::findByString(char* input, char* (Book::* function)() const) const
{

	for (int i = 0; i < mCount; i++)
	{
		char* compareString = toLowerString(((*mBooks[i]).*function)());
		if (strcmp(compareString, input) == 0)
		{
			delete[] compareString;
			return i;
		}
		delete[] compareString;
	}
	return -1;
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
	return -1;
}
int Library::findByDescription(char* input) const
{
	for (int i = 0; i < mCount; i++)
	{
		char* compareString = toLowerString((*mBooks[i]).getDescription());
		if (strstr(compareString, input) != nullptr)
		{
			delete[] compareString;
			return i;
		}
		delete[] compareString;
	}
	return -1;
}
Book& Library::findBy() const
{
	int criterion = findPredicate();
	int bookIndex;
	cout << "Enter the contents of the field:\n";
	char buffer[MAX_LENGTH];
	char* input = nullptr;
	cin.getline(buffer, MAX_LENGTH);
	copyString(input, buffer);

	if (criterion == 1)
	{
		bookIndex = findByString(input, &Book::getTitle);
	}
	else if (criterion == 2)
	{
		bookIndex = findByString(input, &Book::getAuthor);
	}
	else if (criterion == 3)
	{
		bookIndex = findByISBN(input);
	}
	else
	{
		bookIndex = findByDescription(input);
	}
	if (bookIndex == -1)
	{
		throw "Book not found!";
	}
	delete[] input;
	return *mBooks[bookIndex];
}
void Library::find() const
{
	findBy().printDetailed();
}


void Library::addBook(const Book& bookToAdd)
{
	resize();
	mBooks[mCount] = new Book(bookToAdd);
	ofstream bookOutputFile(bookToAdd.getFileName());
	cout << "Add contents of the book\n";
	
	if (bookOutputFile)
	{
		char line[MAX_LENGTH];
		cin.ignore();
		cin.getline(line, MAX_LENGTH);
		bookOutputFile << line;
	}
	try
	{
		bookOutputFile.close();
	}
	catch (const std::exception&)
	{

	}
	
	ofstream savedBooks(getFileName());
	if (savedBooks)
	{
		savedBooks << bookToAdd.getTitle() << endl;
	}
	++mCount;
	
}
void Library::removeBook(const Book& bookToRemove)
{
	int removeIndex = 0;
	for (int i = 0; i < mCount; i++)
	{
		if ((*mBooks[i])==bookToRemove)
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

	fstream booksList(this->getFileName());
	char buffer[MAX_LENGTH];
	while (!booksList.eof())
	{
		booksList.getline(buffer, MAX_LENGTH);
		if (strcmp(buffer, bookToRemove.getTitle()) == 0)
		{
			int currGetPosition = booksList.tellg();
			int currPutPosition = booksList.tellp();
			int offSetCount = strlen(bookToRemove.getTitle());
			int putPosition = currGetPosition - offSetCount;
			booksList.seekp(currPutPosition);
			for (int i = 0; i < offSetCount; i++)
			{
				booksList << " "; // instead of the name of the book, we write empty space;
			}
			booksList.seekg(ios::beg);
			booksList.seekp(ios::beg);
			break;
		}
	}
	try
	{
		booksList.close();
	}
	catch (const std::exception&)
	{
		throw "Cannot close file!";
	}
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
	ifstream file(book.getFileName());
	if (mode == 1)
	{
		readByPages(file);
	}
	else
	{
		readBySentences(file);
	}
}
void Library::print() const
{
	for (int i = 0; i < mCount; i++)
	{
		(*mBooks[i]).print();
	}
}

