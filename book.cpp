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
	copyString(mAuthor, author);
}
void Book::setTitle(char* title)
{
	copyString(mTitle,title);
}
void Book::setFileName(char* fileName)
{
	copyString(mFileName, fileName);
}
void Book::setDescription(char* description)
{
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
void Book::setISBN(int isbn)
{
	mISBN = isbn;
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
Book::Book(char* author, char* title, char* fileName, char* description) :mAuthor(author), mTitle(title), mFileName(fileName), mDescription(description), mRating(Rating::UNRATED)  
{
	++count;
	setISBN(count);
}
Book::Book(const char* author, const char* title, const char* fileName, const char* description) :mRating(Rating::UNRATED)
{
	++count;
	setAuthor((char*)author);
	setTitle((char*)title);
	setFileName((char*)fileName);
	setDescription((char*)description);
	setISBN(count);
}
Book::Book(const char* author, const char* title, const char* fileName, const char* description,Rating rating)
{
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
Book::~Book()
{
	free(); 
	--count;
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
void Book::print()
{
	cout << getTitle() << ", " << getAuthor() << ", " << getISBN() << endl;
}