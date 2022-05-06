#include "doctest.h"
#include "user.h"

TEST_SUITE("User tests")
{
    TEST_CASE("Default contructor test")
    {
        User u1;
        CHECK(u1.getUsername() == nullptr);
        CHECK(u1.getPassword() == nullptr);
        CHECK(u1.getAdminStatus() == false);
        
    }

    TEST_CASE("Contructor with constant char* test")
    {
        User u1("gost");
        CHECK(strcmp(u1.getUsername(),"gost")==0);
        CHECK(u1.getPassword() == nullptr);
        CHECK(u1.getAdminStatus() == false);

        User u2("guest", "123");
        CHECK(strcmp(u2.getUsername(), "guest") == 0);
        CHECK(strcmp(u2.getUsername(), "neshtosi") != 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);
        CHECK(strcmp(u2.getPassword(), "124") != 0);
        CHECK(u2.getAdminStatus() != true);
        CHECK(u2.getAdminStatus() == false);

    }

    TEST_CASE("Contructor with dynamic char* test")
    {
        char* userName = new char[5];
        strcpy(userName, "gost");
        char* password = new char[4];
        strcpy(password, "123");

        User u1(userName);
        CHECK(strcmp(u1.getUsername(), "gost") == 0);
        CHECK(u1.getPassword() == nullptr);
        CHECK(u1.getAdminStatus() == false);

        User u2(userName, password);
        CHECK(strcmp(u2.getUsername(), "gost") == 0);
        CHECK(strcmp(u2.getUsername(), "neshtosi") != 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);
        CHECK(strcmp(u2.getPassword(), "124") != 0);
        CHECK(u2.getAdminStatus() != true);
        CHECK(u2.getAdminStatus() == false);

        
       

        delete[] userName;
        delete[] password;

    }

    TEST_CASE("Copy contructor test")
    {
        User u1("guest", "123");
        User u2(u1);
        CHECK(strcmp(u2.getUsername(), "guest") == 0);
        CHECK(strcmp(u2.getUsername(), "neshtosi") != 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);
        CHECK(strcmp(u2.getPassword(), "124") != 0);
        CHECK(u2.getAdminStatus() != true);
        CHECK(u2.getAdminStatus() == false);
    }

    TEST_CASE("Move constructor test")
    {
        
        User u1("Admin", "123");
        User u2(std::move(u1));
        //checks for created object
        CHECK(strcmp(u2.getUsername(), "Admin") == 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);

        //checks for moved object
        CHECK(u1.getUsername() == nullptr);
        CHECK(u1.getPassword() == nullptr);
    }

    TEST_CASE("Operator = test")
    {
        User u1("guest", "123");
        User u2;
        u2 = u1;
        CHECK(strcmp(u2.getUsername(), "guest") == 0);
        CHECK(strcmp(u2.getUsername(), "neshtosi") != 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);
        CHECK(strcmp(u2.getPassword(), "124") != 0);
        CHECK(u2.getAdminStatus() != true);
        CHECK(u2.getAdminStatus() == false);

    }

    TEST_CASE("Operator = test for moving objects")
    {
        User u1("Admin", "123");
        User u2("guest");
        u2 = std::move(u1);
        CHECK(strcmp(u2.getUsername(), "Admin") == 0);
        CHECK(strcmp(u2.getPassword(), "123") == 0);

        //checks for moved object
        CHECK(u1.getUsername() == nullptr);
        CHECK(u1.getPassword() == nullptr);
    }

    TEST_CASE("Setters test")
    {
        User u("guest", "123");
        u.setUsername((char*)"Nqkuv");
        CHECK(strcmp(u.getUsername(), "Nqkuv") == 0);
        u.setPassword((char*)"");
        CHECK(strcmp(u.getPassword(), "") == 0);
        u.setAdminStatus(true);
        CHECK(u.getAdminStatus() == true);
    }

    TEST_CASE("Getters test")
    {
        User u("guest", "123");
        CHECK(strcmp(u.getUsername(), "guest") == 0);
        CHECK(strcmp(u.getPassword(), "123") == 0);
        CHECK(u.getAdminStatus() == false);

    }

}