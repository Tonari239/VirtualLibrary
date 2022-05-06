#ifndef __User_H
#define __User_H

#include <iostream>
using namespace std;
class User
{
	char* mUserName;
	char* mPassword;
	bool mIsAdmin;

	void setStringValuesToNullptr();
	void copy(const User& other);
	void free();
public:
	User();
	User(char* userName);
	User(char* userName, char* password);
	User(const char* userName);
	User(const char* userName, const char* password);
	User(const User& other);
	User(User&& other);
	User& operator=(User&& other);
	User& operator=(const User& other);
	bool operator==(const User& other) const;
	~User();

	char* getUsername() const;
	char* getPassword() const; 
	bool getAdminStatus() const;
	
	
	void setUsername(char* userName);
	void setPassword(char* password);
	void setAdminStatus(bool status);

	friend ostream& operator<<(ostream& out, const User& user);
};
#endif