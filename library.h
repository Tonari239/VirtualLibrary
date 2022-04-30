#ifndef __Library_H
#define __Library_H
#include "book.h"

#define START_CAPACITY 4
class Library
{
	Book** mBooks;
	int mCount;
	int mCapacity;
	void copy(const Library& other);
	void free();
	void resize(); 
	void print();
	void sortByTitle();
	void sortByAuthor(); // TODO: check if you can optimise a sort function accepting parameter -get function:char(*getFunction())
	void sortByRating();

	int findByTitle(char* input) const;
	int findByAuthor(char* input) const;
	int findByISBN(char* input) const;
	int findByDescription(char* input) const;
public:
	Library();
	Library(const Library& other);
	~Library();
	Library& operator=(const Library& other);
	Book** getBooks() const;
	void Sort();
	void addBook(const Book& bookToAdd);
	Book& findBy(char* input) const;
	void removeBook(Book bookToRemove);
	void displayBook(const Book& book) const;
};
#endif
