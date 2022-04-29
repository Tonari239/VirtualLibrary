#ifndef __Book_H
#define __Book_H

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
	static int count;
	char* mAuthor;
	char* mTitle;
	char* mFileName;
	char* mDescription;
	Rating mRating;
	unsigned mISBN; //ISBN should be 10 digits long and unique
	void copy(const Book& other);
	void free();
public:
	char* getAuthor() const;
	char* getTitle() const;
	char* getFileName() const;
	char* getDescription() const;
	Rating getRating() const;
	unsigned getISBN() const;

	void setAuthor(char* author);
	void setTitle(char* title);
	void setFileName(char* fileName);
	void setDescription(char* description);
	void setRating(Rating rating);
	void setISBN(int isbn);

	Book();
	Book(char* author, char* title, char* fileName, char* description);  
	Book(char* author, char* title, char* fileName, char* description, Rating rating);
	Book(const char* author, const char* title, const char* fileName, const char* description);
	Book(const char* author, const char* title, const char* fileName, const char* description, Rating rating);
	Book(const Book& other);
	~Book();
	Book& operator=(const Book& other);
	friend ostream& operator<<(ostream& out, Book& book);
	void print();



};
#endif