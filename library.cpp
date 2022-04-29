#include "library.h"
#include "usefulFunctions.h"

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
	int predicateResult =sortPredicate(); // 1->Author; 2->Title; 3->Rating
	for (int j = 1; j < mCount; j++)
	{
		for (int i = 0; i < mCount; i++)
		{
			if (predicateResult == 1)
			{
				if (strcmp((*mBooks[i]).getAuthor(), (*mBooks[j]).getAuthor()) > 0)
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			else if (predicateResult == 2)
			{
				if (strcmp((*mBooks[i]).getTitle(), (*mBooks[j]).getTitle()) > 0)
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			else
			{
				if ((*mBooks[i]).getRating()< (*mBooks[j]).getRating())
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			
		}
	}
	print();
}
void Library::addBook(const Book& bookToAdd)
{
	resize();
	mBooks[mCount] = new Book(bookToAdd);
	++mCount;
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
	for (int i = removeIndex+1; i < mCount; i++)
	{
		mBooks[i - 1] = mBooks[i];
	}
	--mCount;
	cout << "Would you like to delete file associated with the book? \nY/N\n";
	char input;
	cin >> input;
	while(input != 'y' && input != 'n' && input != 'Y')
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


