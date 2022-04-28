#include "library.h"
#include "usefulFunctions.h"

void Library::copy(const Library& other)
{
	mCount = other.mCount;
	mCapacity = other.mCapacity;
	mBooks = new Book[mCapacity];
	for (int i = 0; i < mCount; i++)
	{
		mBooks[i] = other.mBooks[i];
	}
	
}
void Library::free()
{
	delete[] mBooks;
}
void Library::resize()
{
	if (mCount + 1 >= 3 / 4 * mCapacity)
	{
		mCapacity *= 2;
		Book* newArr = new Book[mCapacity];
		for (int i = 0; i < mCount; i++)
		{
			newArr[i] = mBooks[i];
		}
		delete[] mBooks;
		mBooks = newArr;
	}
}
Library::Library()
{
	mCapacity = START_CAPACITY;
	mCount = 0;
	mBooks = new Book[mCapacity];
}
Library::Library(const Library& other)
{
	copy(other);
}
Library::~Library()
{
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
Book* Library::getBooks() const
{
	return mBooks;
}
void Library::Sort()
{
	
	int predicateResult =sortPredicate(); // 1->Author; 2->Title; 3->Rating
	for (int j = 0; j < mCount; j++)
	{
		for (int i = 1; i < mCount; i++)
		{
			if (predicateResult == 1)
			{
				if (strcmp(mBooks[j].getAuthor(), mBooks[i].getAuthor()) > 0)
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			else if (predicateResult == 2)
			{
				if (strcmp(mBooks[j].getTitle(), mBooks[i].getTitle()) > 0)
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			else
			{
				if (mBooks[j].getRating()< mBooks[i].getRating())
				{
					swap(mBooks[j], mBooks[i]);
				}
			}
			
		}
	}
}
void Library::addBook(Book bookToAdd)
{
	resize();
	mBooks[mCount] = bookToAdd;
	++mCount;
}
void Library::removeBook(Book bookToRemove)
{
	int removeIndex = 0;
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp(mBooks[i].getTitle(), bookToRemove.getTitle()) == 0)
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


