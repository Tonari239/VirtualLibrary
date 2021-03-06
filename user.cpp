#include "user.h"
#include "usefulFunctions.h"

void User::setStringValuesToNullptr()
{
	mPassword = nullptr;
	mUserName = nullptr;
}

void User::copy(const User& other)
{
	setStringValuesToNullptr();
	setUsername(other.getUsername());
	setPassword(other.getPassword());
	mIsAdmin = other.getAdminStatus();
}

void User::free()
{
	delete[] mUserName;
	delete[] mPassword;
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
	if (userName == nullptr || (mUserName != nullptr && strcmp(this->getUsername(), userName) == 0))
	{
		return;
	}
	copyString(mUserName, userName);
}

void User::setPassword(char* password)
{
	if (password == nullptr || (mPassword != nullptr && strcmp(this->getPassword(), password) == 0))
	{
		return;
	}
	copyString(mPassword, password);
}




User::User() : mUserName(nullptr),mPassword(nullptr)
{
	mIsAdmin = false;
}

User::User(char* userName, char* password)
{
	setStringValuesToNullptr();
	mIsAdmin = false;
	setUsername(userName);
	setPassword(password);
}

User::User(char* userName) :mPassword(nullptr)
{
	setStringValuesToNullptr();
	setUsername(userName);
	mIsAdmin = false;
}

User::User(const char* userName) : mPassword(nullptr)
{
	setStringValuesToNullptr();
	setUsername((char*)userName);
	mIsAdmin = false;
}

User::User(const char* userName, const char* password)
{
	setStringValuesToNullptr();
	mIsAdmin = false;
	setUsername((char*)userName);
	setPassword((char*)password);
}

User::User(const User& other)
{
	setStringValuesToNullptr();
	mIsAdmin = false;
	copy(other);
}

User::User(User&& other)
{
	mPassword = other.mPassword;
	mIsAdmin = other.getAdminStatus();
	mUserName = other.mUserName;
	other.mPassword = nullptr;
	other.mUserName = nullptr;
}

User::~User()
{
	free();
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

User& User::operator=(User&& other)
{
	if (this!=&other)
	{
		free();
		mPassword = other.mPassword;
		mIsAdmin = other.getAdminStatus();
		mUserName = other.mUserName;
		other.mPassword = nullptr;
		other.mUserName = nullptr;
	}
	return *this;
}

bool User::operator==(const User& other) const
{
	return strcmp(this->getUsername(),other.getUsername())==0 && strcmp(this->getPassword(),other.getPassword()) == 0;
}

ostream& operator<<(ostream& out, const User& user)
{
	out << user.getUsername() << endl;
	return out;
}
