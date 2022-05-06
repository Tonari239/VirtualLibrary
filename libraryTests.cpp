
#include <fstream>

#include "doctest.h"
#include "library.h"
#include "userList.h"

#include <iostream>
using namespace std;
TEST_SUITE("Library Tests")
{
		
	TEST_CASE("Copy constructor")
	{
		Library l1("file.txt");
		Library l2(l1);
		CHECK(CHECK(strcmp(l1.getFileName(), l2.getFileName()) == 0));
		CHECK(l2.getBooks() != nullptr);
	}

	TEST_CASE("Move constructor")
	{
		Library l1("books.txt");
		Library l2(std::move(l1));

		//checks for created object
		CHECK(strcmp(l2.getFileName(), "books.txt") == 0);

		//checks for moved object
		CHECK(l1.getFileName() == nullptr);
		CHECK(l1.getBooks() == nullptr);
	}

	TEST_CASE("Getters")
	{
		Library l("file.txt");
		CHECK(strcmp(l.getFileName(), "file.txt") == 0);
		CHECK(l.getBooks() != nullptr);
	}

	TEST_CASE("Operator =")
	{
		Library l1("file.txt");
		Library l2("neshtosi.txt");
		l2 = l1;
		CHECK(CHECK(strcmp(l1.getFileName(), l2.getFileName()) == 0));
		CHECK(l2.getBooks() != nullptr);
	}

	TEST_CASE("Operator = for moving ojects")
	{
		Library l1("books.txt");
		Library l2("other.txt");
		l2 = (std::move(l1));

		CHECK(strcmp(l2.getFileName(), "books.txt") == 0);

		CHECK(l1.getFileName() == nullptr);
		CHECK(l1.getBooks() == nullptr);
	}

	TEST_CASE("Add book")
	{
		/*Library l1("file.txt");
		CHECK(l1.getCount() == 0);
		l1.addBook(Book("Agatha Christie", "ABC murders", "murders.txt", "Murder mystery"));
		l1.addBook(Book("Mikhail Bulgakov", "Master and margarita", "master.txt", "A story about a witch, the devil and his subordinates"));
		l1.addBook(Book("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love"));
		CHECK(l1.getCount() == 3);
		l1.addBook(Book("Jonas Jonasson", "The girl who saved the king of sweden", "sweden.txt", "A humorous story about a nigerian girl"));
		l1.addBook(Book("Luke Rhinehart", "The dice man", "dice.txt", "A story of a bored psychiatrist who seeks to break the norm and succumbs to insanity"));
		CHECK(l1.getCount() == 5);
		l1.addBook(Book("Agatha Christie", "The murder of Roger Ackroyd", "roger.txt", "A wealthy man is murdered"));
		l1.addBook(Book("Charles Dickens", "Great expectations", "expectations.txt", "Young pip is seduced by the riches the high-life offers him"));
		CHECK(l1.getCount() == 7);*/
	}

	TEST_CASE("Remove")
	{
		//this test works with user input which is why its commented, uncomment to check
		/*Library l1("file.txt");
		l1.addBook(Book("Agatha Christie", "ABC murders", "murders.txt", "Murder mystery"));
		l1.addBook(Book("Mikhail Bulgakov", "Master and margarita", "master.txt", "A story about a witch, the devil and his subordinates"));
		
		Book b1("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love");
		Book b2("Luke Rhinehart", "The dice man", "dice.txt", "A story of a bored psychiatrist who seeks to break the norm and succumbs to insanity");
		l1.addBook(b2);
		l1.addBook(b1);
		l1.addBook(Book("Jonas Jonasson", "The girl who saved the king of sweden", "sweden.txt", "A humorous story about a nigerian girl"));
		l1.addBook(Book("Agatha Christie", "The murder of Roger Ackroyd", "roger.txt", "A wealthy man is murdered"));
		l1.removeBook(b2);
		CHECK(l1.getCount() == 5);
		l1.addBook(Book("Charles Dickens", "Great expectations", "expectations.txt", "Young pip is seduced by the riches the high-life offers him"));
		l1.removeBook(b1);
		CHECK(l1.getCount() == 5);*/
		
	}

	TEST_CASE("Sort")
	{
		//this test works with user imput which is why its commented, uncomment to check
		/*Library l1("file.txt");
		l1.addBook(Book("Agatha Christie", "ABC murders", "murders.txt", "Murder mystery"));
		l1.addBook(Book("Mikhail Bulgakov", "Master and margarita", "master.txt", "A story about a witch, the devil and his subordinates"));

		Book b1("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love");
		Book b2("Luke Rhinehart", "The dice man", "dice.txt", "A story of a bored psychiatrist who seeks to break the norm and succumbs to insanity");
		l1.addBook(b2);
		l1.addBook(b1);
		l1.addBook(Book("Jonas Jonasson", "The girl who saved the king of sweden", "sweden.txt", "A humorous story about a nigerian girl"));
		l1.addBook(Book("Agatha Christie", "The murder of Roger Ackroyd", "roger.txt", "A wealthy man is murdered"));
		l1.addBook(Book("Charles Dickens", "Great expectations", "expectations.txt", "Young pip is seduced by the riches the high-life offers him"));
		l1.sort();*/
	}

	TEST_CASE("Find By")
	{
		//this test works with user imput which is why its commented, uncomment to check
		//Library l1("file.txt");
		//l1.addBook(Book("Agatha Christie", "ABC murders", "murders.txt", "Murder mystery"));
		//l1.addBook(Book("Mikhail Bulgakov", "Master and margarita", "master.txt", "A story about a witch, the devil and his subordinates"));
		//
		//Book b1("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love");
		//Book b2("Luke Rhinehart", "The dice man", "dice.txt", "A story of a bored psychiatrist who seeks to break the norm and succumbs to insanity");
		//l1.addBook(b2);
		//l1.addBook(b1);
		//l1.addBook(Book("Jonas Jonasson", "The girl who saved the king of sweden", "sweden.txt", "A humorous story about a nigerian girl"));
		//l1.addBook(Book("Agatha Christie", "The murder of Roger Ackroyd", "roger.txt", "A wealthy man is murdered"));
		//l1.addBook(Book("Charles Dickens", "Great expectations", "expectations.txt", "Young pip is seduced by the riches the high-life offers him"));
		//Book b = l1.findBy();
		//DOCTEST_CHECK_THROWS(l1.find());// check with wrong input
	}

	TEST_CASE("Remove deletes book name from file with available books")
	{
		Library l1("file.txt");
		Book b1("Luke Rhinehart", "The dice man", "dice.txt", "A story of a bored psychiatrist who seeks to break the norm and succumbs to insanity");
		l1.addBook(Book("Agatha Christie", "ABC murders", "murders.txt", "Murder mystery"));
		l1.addBook(b1);
		l1.addBook(Book("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love"));
		l1.removeBook(b1);
		l1.addBook(Book("Agatha Christie", "Murder on Orient Express", "orientExpress.txt", "A wealthy mafioso is murdered on a train"));
		ifstream file(l1.getFileName());
		bool nameIsContained = false;
		if (file.is_open())
		{
			char buffer[1024];
			while (!file.eof())
			{
				file.getline(buffer, 1024);
				if (strcmp(buffer,b1.getTitle())==0)
				{
					nameIsContained = true;
					break;
				}
			}
		}
		CHECK(nameIsContained == false);
	}
}