#ifndef __Library_H
#define __Library_H
#include "book.h"

#define START_CAPACITY 4
class Library
{
	Book* mBooks;
	int mCount;
	int mCapacity;
	void copy(const Library& other);
	void free();
	void resize(); 
public:
	Library();
	Library(const Library& other);
	~Library();
	Library& operator=(const Library& other);
	Book* getBooks() const;
	void Sort();
	void addBook(Book bookToAdd);
	void removeBook(Book bookToRemove);
};
#endif
