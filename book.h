#ifndef __Book
#define __Book

#include <iostream>
using namespace std;

enum Rating
{
	UNRATED=0,
	BAD,
	OKAY,
	GOOD,
	VERY_GOOD,
	EXCELLENT
};

class Book
{
	char* mAuthor;
	char* mTitle;
	char* mFileName;
	char* mDescription;
	Rating mRating;
	int mISBN;
	void copy(const Book& other);
	void free();
public:
	char* getAuthor() const;
	char* getTitle() const;
	char* getFileName() const;
	char* getDescription() const;
	Rating getRating() const;
	int getISBN() const;

	void setAuthor(char* author);
	void setTitle(char* title);
	void setFileName(char* fileName);
	void setDescription(char* description);
	void setRating(Rating rating);
	void setISBN(int isbn);

	//constructors and big four
	Book(char* author, char* title, char* fileName, char* description);  //TODO: check how to make unique ISBN
	Book(char* author, char* title, char* fileName, char* description, Rating rating);
	Book(const Book& other);
	~Book();
	Book& operator=(const Book& other);
	friend ostream& operator<<(ostream& out, Book& book);




};
#endif