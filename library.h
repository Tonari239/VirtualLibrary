#ifndef __Library_H
#define __Library_H
#include "book.h"

#define START_CAPACITY 4

class Library
{
	Book** mBooks;
	int mCount;
	int mCapacity;
	char* mAssociatedFile;

	void copy(const Library& other);
	void free();
	void resize();
	
	void sortByRating();
	void sortByString(char* (Book::* function)() const);
	int findByString(char* input, char* (Book::* function)() const) const;
	int findByISBN(char* input) const;
	int findByDescription(char* input) const;

public:
	Book** getBooks() const;
	char* getFileName() const;
	int getCount() const;

	Library()=delete;
	Library(char* fileName);
	Library(const char* fileName);
	Library(const Library& other);
	Library(Library&& other);
	~Library();
	Library& operator=(const Library& other);
	Library& operator=(Library&& other);
	
	
	void addBook(const Book& bookToAdd); 
	void removeBook(const Book& bookToRemove);
	void sort();
	Book& findBy() const;
	void find() const;
	void displayBook(const Book& book) const;
	void print() const;
	
};
#endif
