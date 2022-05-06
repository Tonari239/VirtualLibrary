#include "doctest.h"
#include "book.h"

TEST_SUITE("Book tests")
{
	TEST_CASE("Default constructor test")
	{
        Book b;
        CHECK(b.getAuthor() == nullptr);
        CHECK(b.getTitle() == nullptr);
        CHECK(b.getFileName() == nullptr);
        CHECK(b.getDescription() == nullptr);
        CHECK(b.getRating() == Rating::UNRATED);
	}

    TEST_CASE("Contructor with constant char* test")
    {
        Book b1("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        CHECK(strcmp(b1.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b1.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b1.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b1.getDescription(), "Murder mystery") == 0);
        CHECK(b1.getRating()!=Rating::BAD);
        CHECK(b1.getRating() == Rating::UNRATED);


        Book b2("Mikhail Bugakov", "Master and Margarita", "margarita.txt", "A story about a witch, the devil and his subordinates",Rating::EXCELLENT);
        CHECK(strcmp(b2.getAuthor(), "Mikhail Bugakov") == 0);
        CHECK(strcmp(b2.getTitle(), "Master and Margarita") == 0);
        CHECK(strcmp(b2.getFileName(), "margarita.txt") == 0);
        CHECK(strcmp(b2.getDescription(), "A story about a witch, the devil and his subordinates") == 0);
        CHECK(b2.getRating() == Rating::EXCELLENT);
    }

    TEST_CASE("Contructor with dynamic char* test")
    {
        char* author = new char[16];
        strcpy(author, "Agatha Christie");

        char* title = new char[12];
        strcpy(title, "ABC murders");

        char* fileName = new char[8];
        strcpy(fileName, "abc.txt");

        char* description = new char[15];
        strcpy(description, "Murder mystery");
        

        Book b1(author, title, fileName, description);
        CHECK(strcmp(b1.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b1.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b1.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b1.getDescription(), "Murder mystery") == 0);
        CHECK(b1.getRating() != Rating::BAD);
        CHECK(b1.getRating() == Rating::UNRATED);

        delete[] author;
        delete[] title;
        delete[] fileName;
        delete[] description;
        

		author = new char[16];
        strcpy(author, "Mikhail Bugakov");

        title = new char[21];
        strcpy(title, "Master and Margarita");

        fileName = new char[14];
        strcpy(fileName, "margarita.txt");

        description = new char[54];
        strcpy(description, "A story about a witch, the devil and his subordinates");

		Book b2(author, title, fileName, description, Rating::EXCELLENT);
        CHECK(strcmp(b2.getAuthor(), "Mikhail Bugakov") == 0);
        CHECK(strcmp(b2.getTitle(), "Master and Margarita") == 0);
        CHECK(strcmp(b2.getFileName(), "margarita.txt") == 0);
        CHECK(strcmp(b2.getDescription(), "A story about a witch, the devil and his subordinates") == 0);
        CHECK(b2.getRating() == Rating::EXCELLENT);

        delete[] author;
        delete[] title;
        delete[] fileName;
        delete[] description;
    }

    TEST_CASE("Copy contructor test")
    {
        Book b1("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        CHECK(strcmp(b1.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b1.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b1.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b1.getDescription(), "Murder mystery") == 0);
        CHECK(b1.getRating() != Rating::BAD);
        CHECK(b1.getRating() == Rating::UNRATED);

        Book b2(b1);
        CHECK(strcmp(b2.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b2.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b2.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b2.getDescription(), "Murder mystery") == 0);
        CHECK(b2.getRating() != Rating::BAD);
        CHECK(b2.getRating() == Rating::UNRATED);
    }

    TEST_CASE("Move contructor test")
	{
        Book b1("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        Book b2(std::move(b1));

        //checks for created object
        CHECK(strcmp(b2.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b2.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b2.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b2.getDescription(), "Murder mystery") == 0);
        CHECK(b2.getRating() != Rating::BAD);
        CHECK(b2.getRating() == Rating::UNRATED);

        //checks for moved object
        CHECK(b1.getAuthor() == nullptr);
        CHECK(b1.getTitle() == nullptr);
        CHECK(b1.getFileName() == nullptr);
        CHECK(b1.getDescription() == nullptr);
	}

    TEST_CASE("Operator = test")
    {
        Book b1;
        Book b2("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        b1 = b2;
        CHECK(b1 == b2);
    }

    TEST_CASE("Operator = test for moving objects")
	{
        Book b1("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        Book b2("Plato", "The symposium", "symposium.txt", "Philosophers' takes on love");
        b2 = std::move(b1);
        CHECK(strcmp(b2.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b2.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b2.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b2.getDescription(), "Murder mystery") == 0);
        CHECK(b2.getRating() != Rating::BAD);
        CHECK(b2.getRating() == Rating::UNRATED);

        //checks for moved object
        CHECK(b1.getAuthor() == nullptr);
        CHECK(b1.getTitle() == nullptr);
        CHECK(b1.getFileName() == nullptr);
        CHECK(b1.getDescription() == nullptr);
	}

    TEST_CASE("Operator == test")
    {
        Book b1;
		Book b2("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
        Book b3;
        CHECK((b1 == b2) == false);
        CHECK((b3 == b3) == true);
    }

    TEST_CASE("Setters test")
    {
        Book b1;
        b1.setAuthor((char*)"Agatha Christie");
        b1.setTitle((char*)"ABC murders");
        b1.setDescription((char*)"Murder mystery");
        b1.setFileName((char*)"abc.txt");
        b1.setRating(5);

        CHECK(strcmp(b1.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b1.getTitle(), "ABC murders") == 0);
		CHECK(strcmp(b1.getDescription(), "Murder mystery") == 0);
        CHECK(strcmp(b1.getFileName(), "abc.txt") == 0);
		CHECK(b1.getRating() != Rating::BAD);
        CHECK(b1.getRating() == Rating::EXCELLENT);
        b1.setRating(1000);
        CHECK(b1.getRating() == Rating::UNRATED);
    }

    TEST_CASE("Getters test")
    {
        Book b1("Agatha Christie", "ABC murders", "abc.txt", "Murder mystery");
		CHECK(strcmp(b1.getAuthor(), "Agatha Christie") == 0);
        CHECK(strcmp(b1.getTitle(), "ABC murders") == 0);
        CHECK(strcmp(b1.getFileName(), "abc.txt") == 0);
        CHECK(strcmp(b1.getDescription(), "Murder mystery") == 0);
		CHECK(b1.getRating() == Rating::UNRATED);
    }
}