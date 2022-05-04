#include "user.h"
#include "usefulFunctions.h"

void User::copy(const User& other)
{
	setUsername(other.getUsername());
	setPassword(other.getPassword());
}
void User::free()
{
	delete[] mUserName;
	delete[] mPassword;
}

User::User() : mUserName(nullptr),mPassword(nullptr)
{
	mIsAdmin = false;
}
User::User(char* userName, char* password)
{
	mIsAdmin = false;
	setUsername(userName);
	setPassword(password);
}
User::User(char* userName) :mUserName(userName),mPassword(nullptr)
{
	mIsAdmin = false;
}

User::User(const char* userName) : mPassword(nullptr)
{
	setUsername((char*)userName);
	mIsAdmin = false;
}
User::User(const char* userName, const char* password)
{
	mIsAdmin = false;
	setUsername((char*)userName);
	setPassword((char*)password);
}
User::User(const User& other)
{
	mIsAdmin = false;
	copy(other);
}
User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
bool User::operator==(const User& other) const
{
	return this->getUsername() == other.getUsername() && this->getPassword() == other.getPassword();
}
User::~User()
{
	free();
}

char* User::getUsername() const
{
	return mUserName;
}
char* User::getPassword() const
{
	return mPassword;
}
bool User::getAdminStatus() const
{
	return mIsAdmin;
}
void User::setAdminStatus(bool status)
{
	mIsAdmin = status;
}

void User::setUsername(char* userName)
{
	copyString(mUserName, userName);
}
void User::setPassword(char* password)
{
	copyString(mPassword, password);
}

ostream& operator<<(ostream& out, const User& user)
{
	out << user.getUsername() << endl;
	return out;
}

