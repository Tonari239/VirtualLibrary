#include "library.h"
#include <iostream>
#include <fstream>
#include "usefulFunctions.h"
using namespace std;
#define MAX_LENGTH 1024
int main()
{
	const char* adminPassword = "IDK123!";
	char input[MAX_LENGTH];
	char* command;
	cout << "Enter \"help\" for list of commands\n";
	Library library;
	do
	{
		cin.getline(input, MAX_LENGTH);
		int length = strlen(input) + 1;
		command = new char[length];
		strcpy(command, input);
		if (strcmp(command, "help") == 0)
		{
			cout << "1.sort\n2.find\n3.add\n4.remove\n5.display\n6.exit\n";
		}
		else if (strcmp(command, "sort") == 0)
		{
			library.sort();
			delete[] command;
		}
		else if (strcmp(command, "find") == 0)
		{
			library.find();
			delete[] command;
		}
		else if (strcmp(command, "add") == 0)
		{
			if (authorize(adminPassword))
			{
				Book book;
				setField(book, "Title", &(Book::setTitle));
				setField(book, "Author", &(Book::setAuthor));
				setField(book, "Description", &(Book::setDescription));
				setField(book, "File Name", &(Book::setFileName));
				//Rating
				cout << "Enter Rating: 1-5.";
				int rating;
				cin >> rating;
				book.setRating(rating);
				library.addBook(book);
			}
			delete[] command;
		}
		else if (strcmp(command, "remove") == 0)
		{
			if (authorize(adminPassword))
			{
				library.removeBook(library.findBy());
			}
			delete[] command;
		}
		else if (strcmp(command, "display") == 0)
		{
			library.displayBook(library.findBy());
			delete[] command;
		}
		
	} while (strcmp(command, "exit") != 0);
}


