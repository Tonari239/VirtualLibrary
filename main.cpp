#define DOCTEST_CONFIG_IMPLEMENT
#include  "doctest.h"
#include "library.h"
#include <iostream>
#include <fstream>
#include "usefulFunctions.h"
#include "userList.h"


using namespace std;
#define MAX_LENGTH 1024
int main(int argc, char** argv)
{
	//doctest
	/*doctest::Context context; context.addFilter("test-case-exclude", "*math*");
	context.setOption("abort-after", 5);              
	context.setOption("order-by", "name");            

	context.applyCommandLine(argc, argv);
	
	context.setOption("no-breaks", true);     

	int res = context.run(); 

	if (context.shouldExit()) 
		return res;         

	int client_stuff_return_code = 0;
	

	return res + client_stuff_return_code;*/

	User admin("admin", "123");
	admin.setAdminStatus(true);
	UserList registeredUsers((char*)"registeredUsers.txt");
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
			cout << "1.login\n2.register\n3.sort\n4.find\n5.add\n6.remove\n7.display\n8.exit\n";
		}
		else if (strcmp(command, "login") == 0)
		{
			cout << "Enter username: ";
			char* userNameInput = nullptr;
			cin.getline(input, MAX_LENGTH);
			copyString(userNameInput, input);
			if (registeredUsers.findIndex(userNameInput) == -1)
			{
				cout << "No such user exists! Operation failed" << endl;
				continue;
			}
			cout << "Enter password: ";
			char passwordInput[MAX_LENGTH];
			enterPassword(passwordInput, '*');
			User u(userNameInput, passwordInput);
			
			currentUser=u; 
			if (currentUser == admin)
			{
				currentUser.setAdminStatus(true);
			}
			delete[] userNameInput;
		}
		else if (strcmp(command, "register") == 0)
		{
			cout << "Enter username: ";
			char* userNameInput = nullptr;
			cin.getline(input, MAX_LENGTH);
			copyString(userNameInput, input);
			if (registeredUsers.findIndex(userNameInput)!=-1)
			{
				cout << "User with this name already exists! Operation failed" << endl;
				continue;
			}
			cout << "Enter password: ";
			char passwordInput[MAX_LENGTH];
			enterPassword(passwordInput, '*');
			User u(userNameInput, passwordInput);
			
			registeredUsers.addUser(u);
			delete[] userNameInput;
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
			if (currentUser.getAdminStatus() || authorize(admin.getPassword()))
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
		else if (strcmp(command, "exit") != 0)
		{
			cout << "Invalid command, enter \"help\"\n";
		}
		
	} while (strcmp(command, "exit") != 0);
	delete[] command;
}


