#include "doctest.h"
#include "userList.h"

TEST_SUITE("User List Tests")
{

	TEST_CASE("Copy constructor test")
	{
		UserList l1("file.txt");
		UserList l2(l1);
		CHECK(CHECK(strcmp(l1.getAssociatedFile(), l2.getAssociatedFile()) == 0));
		CHECK(l2.getAssociatedFile() != nullptr);
	}

	TEST_CASE("Move constructor test")
	{
		UserList ul1("users.txt");
		UserList ul2(std::move(ul1));

		//checks for created object
		CHECK(strcmp(ul2.getAssociatedFile(),"users.txt")==0);

		//checks for moved object
		CHECK(ul1.getAssociatedFile() == nullptr);
		CHECK(ul1.getUsers() == nullptr);
	}

	TEST_CASE("Getters")
	{
		UserList l1("file.txt");
		CHECK(strcmp(l1.getAssociatedFile(), "file.txt") == 0);
		CHECK(l1.getUsers() != nullptr);
		CHECK(l1.getCount() == 0);
	}

	TEST_CASE("Operator =")
	{
		UserList l1("file.txt");
		UserList l2("neshtosi.txt");
		l2 = l1;
		CHECK(CHECK(strcmp(l1.getAssociatedFile(), l2.getAssociatedFile()) == 0));
		CHECK(l2.getUsers() != nullptr);
	}

	TEST_CASE("Operator = for moving ojects")
	{
		UserList ul1("users.txt");
		UserList ul2("other.txt");
		ul2=(std::move(ul1));
		
		CHECK(strcmp(ul2.getAssociatedFile(), "users.txt") == 0);

		CHECK(ul1.getAssociatedFile() == nullptr);
		CHECK(ul1.getUsers() == nullptr);
	}

	TEST_CASE("Add user")
	{
		UserList l1("file.txt");
		CHECK(l1.getCount() == 0);
		l1.addUser(User("gosho"));
		l1.addUser(User("admin", "123"));
		l1.addUser(User("Pencho"));
		CHECK(l1.getCount() == 3);
		l1.addUser(User("guest"));
		l1.addUser(User("another"));
		CHECK(l1.getCount() == 5);
		l1.addUser(User("toon239"));
		l1.addUser(User("new", "user"));
		CHECK(l1.getCount() == 7);
	}
	
	TEST_CASE("Find")
	{
		UserList l1("file.txt");
		l1.addUser(User("gosho"));
		l1.addUser(User("admin", "123"));
		l1.addUser(User("Pencho"));
		l1.addUser(User("guest"));
		l1.addUser(User("another"));
		l1.addUser(User("toon239"));
		l1.addUser(User("new", "user"));
		User user1 = l1.find((char*)"Pencho");
		CHECK(strcmp("Pencho", user1.getUsername())==0);
		User user2 = l1.find((char*)"toon239");
		CHECK(strcmp("toon239", user2.getUsername()) == 0);

		DOCTEST_CHECK_THROWS(l1.find((char*)"No such user"));
	}

}