#include "library.h"
#include <iostream>
#include <fstream>
#include "usefulFunctions.h"
#include "userList.h"
using namespace std;
#define MAX_LENGTH 1024
int main()
{
	User admin("admin", "123");
	admin.setAdminStatus(true);
	UserList registeredUsers((char*)"registeredUsers.txt");
	const char* adminPassword = "neshtositam";
	registeredUsers.addUser(admin);

	Library library((char*)"availableBooks.txt");

	char input[MAX_LENGTH];
	char* command=nullptr;
	cout << "Enter \"help\" for list of commands\n";
	
	
	User currentUser("guest");
	registeredUsers.addUser(currentUser);
	do
	{
		delete[] command;
		cin.getline(input, MAX_LENGTH);
		int length = strlen(input) + 1;
		command = new char[length];
		strcpy(command, input);
		if (strcmp(command, "help") == 0)
		{
			cout << "1.login\n2.sort\n3.find\n4.add\n5.remove\n6.display\n7.exit\n";
		}
		else if (strcmp(command, "login") == 0)
		{
			cout << "Enter username: ";
			char* userNameInput = nullptr;
			cin.getline(input, MAX_LENGTH);
			copyString(userNameInput, input);
			cout << endl;
			cout << "Enter password: ";
			char* passwordInput = nullptr;
			cin.getline(input, MAX_LENGTH);
			copyString(passwordInput, input);
			User u(userNameInput, passwordInput);
			if (u == admin)
			{
				u.setAdminStatus(true);
			}
			registeredUsers.addUser(u);
			delete[] userNameInput;
			delete[] passwordInput;
		}
		else if (strcmp(command, "sort") == 0)
		{
			library.sort();
			
		}
		else if (strcmp(command, "find") == 0)
		{
			library.find();
			
		}
		else if (strcmp(command, "add") == 0)
		{
			if (currentUser == admin || authorize(adminPassword))
			{
				Book book;
				setField(book, "Title", &(Book::setTitle));
				setField(book, "Author", &(Book::setAuthor));
				setField(book, "Description", &(Book::setDescription));
				setField(book, "File name", &(Book::setFileName));
				//Rating
				cout << "Enter Rating: 1-5\n";
				int rating;
				cin >> rating;
				book.setRating(rating);
				library.addBook(book);
			}
			
		}
		else if (strcmp(command, "remove") == 0)
		{
			if (currentUser==admin || authorize(admin.getPassword()))
			{
				library.removeBook(library.findBy());
			}
			
		}
		else if (strcmp(command, "display") == 0)
		{
			library.displayBook(library.findBy());
			
		}
		else
		{
			cout << "Invalid command, enter \"help\"\n";
		}
		
	} while (strcmp(command, "exit") != 0);
	delete[] command;
}


