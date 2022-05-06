#include "book.h"
#include "usefulFunctions.h"

int Book::count = 0;

char* Book::getAuthor() const
{
	return mAuthor;
}

char* Book::getTitle() const
{
	return mTitle;
}

char* Book::getFileName() const
{
	return mFileName;
}

char* Book::getDescription() const
{
	return mDescription;
}

Rating Book::getRating() const
{
	return mRating;
}

unsigned Book::getISBN() const
{
	return mISBN;
}



void Book::setAuthor(char* author)
{
	if (author==nullptr || (mAuthor!=nullptr && strcmp(this->getAuthor(),author)==0))
	{
		return;
	}
	copyString(mAuthor, author);
}

void Book::setTitle(char* title)
{
	if (title == nullptr || (mTitle != nullptr && strcmp(this->getTitle(), title) == 0))
	{
		return;
	}
	copyString(mTitle, title);
}

void Book::setFileName(char* fileName)
{
	if (fileName == nullptr || (mFileName != nullptr && strcmp(this->getFileName(), fileName) == 0))
	{
		return;
	}
	copyString(mFileName, fileName);
}

void Book::setDescription(char* description)
{
	if (description == nullptr || (mDescription != nullptr && strcmp(this->getDescription(), description) == 0))
	{
		return;
	}
	copyString(mDescription, description);
}

void Book::setRating(int rating)
{
	if (rating >= 1 && rating <= 5)
	{
		mRating = (Rating)rating;
	}
	else
	{
		mRating = Rating::UNRATED;
	}
}

void Book::setISBN(unsigned ISBN)
{
	mISBN =ISBN;
}

void Book::setStringValuesToNullptr()
{
	mAuthor = nullptr;
	mTitle = nullptr;
	mFileName = nullptr;
	mDescription = nullptr;
}



void Book::free()
{
	delete[] mAuthor;
	delete[] mTitle;
	delete[] mFileName;
	delete[] mDescription;
}

void Book::copy(const Book& other)
{
	setStringValuesToNullptr();
	setAuthor(other.getAuthor());
	setTitle(other.getTitle());
	setFileName(other.getFileName());
	setDescription(other.getDescription());
	setRating(other.getRating());
	setISBN(other.getISBN());
}



Book::Book() :mAuthor(nullptr), mTitle(nullptr), mFileName(nullptr), mDescription(nullptr),mRating(Rating::UNRATED)
{
	++count;
	setISBN(count);
}

Book::Book(char* author, char* title, char* fileName, char* description) : mRating(Rating::UNRATED)  
{
	setStringValuesToNullptr();
	setAuthor(author);
	setTitle(title);
	setFileName(fileName);
	setDescription(description);
	setISBN(count);
	++count;
}

Book::Book(const char* author, const char* title, const char* fileName, const char* description) :mRating(Rating::UNRATED)
{
	setStringValuesToNullptr();
	++count;
	setAuthor((char*)author);
	setTitle((char*)title);
	setFileName((char*)fileName);
	setDescription((char*)description);
	setISBN(count);
}

Book::Book(const char* author, const char* title, const char* fileName, const char* description,Rating rating)
{
	setStringValuesToNullptr();
	++count;
	setAuthor((char*)author);
	setTitle((char*)title);
	setFileName((char*)fileName);
	setDescription((char*)description);
	setRating(rating);
	setISBN(count);
}

Book::Book(char* author, char* title, char* fileName, char* description, Rating rating)
{
	setStringValuesToNullptr();
	++count;
	setAuthor(author);
	setTitle(title);
	setFileName(fileName);
	setDescription(description);
	setRating(rating);
	setISBN(count);
}

Book::Book(const Book& other)
{
	copy(other);
}

Book::Book(Book&& other)
{
	mAuthor = other.mAuthor;
	mFileName = other.mFileName;
	mDescription = other.mDescription;
	mTitle = other.mTitle;
	mRating = other.mRating;
	mISBN = other.mISBN;
	other.mAuthor = nullptr;
	other.mFileName = nullptr;
	other.mDescription = nullptr;
	other.mTitle = nullptr;
}

Book::~Book()
{
	free(); 
	// count won't be reduced because we use it only to generate a unique ISBN
}



Book& Book::operator=(Book&& other)
{
	if (this != &other)
	{
		free();

		mAuthor = other.mAuthor;
		mFileName = other.mFileName;
		mDescription = other.mDescription;
		mTitle = other.mTitle;
		mRating = other.mRating;
		mISBN = other.mISBN;
		other.mAuthor = nullptr;
		other.mFileName = nullptr;
		other.mDescription = nullptr;
		other.mTitle = nullptr;
	}
	return *this;
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

bool Book::operator==(const Book& other) const
{
	return this->getISBN() == other.getISBN();
}

ostream& operator<<(ostream& out,const Book& book)
{
	int authorLength = strlen(book.getAuthor());
	out << authorLength;
	out.write(book.getAuthor(), authorLength);
	int titleLength = strlen(book.getTitle());
	out << titleLength;
	out.write(book.getTitle(), titleLength);
	int descriptionLength = strlen(book.getDescription());
	out << descriptionLength;
	out.write(book.getDescription(), descriptionLength);
	out << book.getISBN();
	out << book.getRating();
	return out;
}



void Book::print() const
{
	cout << getTitle() << ", " << getAuthor() << ", " << getISBN() << endl;
}

void Book::printDetailed() const
{
	cout << "____________" << endl;
	cout << "Title: " <<getTitle() << endl;
	cout << "Author: " << getAuthor() << endl;
	cout << "ISBN: " << getISBN() << endl;
	cout << "Description: " << getDescription() << endl;
	cout << "Rating: " << getRating() << endl;
}

