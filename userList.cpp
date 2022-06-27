#include "userList.h"
#include "usefulFunctions.h"
#include <fstream>
using namespace std;


void UserList::copy(const UserList& other)
{
	mAssociatedFile = nullptr;
	mCount = other.mCount;
	mCapacity = other.mCapacity;
	mUsers = new User * [mCapacity];
	for (int i = 0; i < mCount; i++)
	{
		mUsers[i] = new User(*(other.mUsers[i])); // count is always less than capacity so no overflow will occur
	}
	copyString(mAssociatedFile,other.getAssociatedFile());
}

void UserList::free()
{
	for (int i = 0; i < mCount; i++)
	{
		delete mUsers[i];
	}
	delete[] mUsers;
	delete[] mAssociatedFile;
}

void UserList::resize()
{
	if (mCount >= 3.0 / 4 * mCapacity)
	{
		mCapacity *= 2;
		User** newArr = new User * [mCapacity];
		for (int i = 0; i < mCount; i++)
		{
			newArr[i] = mUsers[i];
		}
		delete[] mUsers;
		mUsers = newArr;
	}
}



User** UserList::getUsers() const
{
	return mUsers;
}

int UserList::getCount() const
{
	return mCount;
}

char* UserList::getAssociatedFile() const
{
	return mAssociatedFile;
}



UserList::UserList(char* associatedFile)
{
	mCapacity = START_CAPACITY;
	mCount = 0;
	mUsers = new User*[mCapacity];
	copyString(mAssociatedFile, associatedFile);
}

UserList::UserList(const char* fileName)
{
	mCapacity = START_CAPACITY;
	mCount = 0;
	mUsers = new User * [mCapacity];
	mAssociatedFile = nullptr;
	copyString(mAssociatedFile, (char*)fileName);
}

UserList::UserList(const UserList& other)
{
	copy(other);
}

UserList::UserList(UserList&& other)
{
	mAssociatedFile = other.mAssociatedFile;
	other.mAssociatedFile = nullptr;
	mCapacity = other.mCapacity;
	mCount = other.mCount;
	for (int i = 0; i < mCount; i++)
	{
		mUsers[i] = other.mUsers[i];
		other.mUsers[i] = nullptr;
	}
	mUsers = other.mUsers;
	other.mUsers = nullptr;
}

UserList::~UserList()
{
	free();
}



UserList& UserList::operator=(const UserList& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

UserList& UserList::operator=(UserList&& other)
{
	if (this!=&other)
	{
		free();
		mAssociatedFile = other.mAssociatedFile;
		other.mAssociatedFile = nullptr;
		mCapacity = other.mCapacity;
		mCount = other.mCount;
		for (int i = 0; i < mCount; i++)
		{
			mUsers[i] = other.mUsers[i];
			other.mUsers[i] = nullptr;
		}
		mUsers = other.mUsers;
		other.mUsers = nullptr;
	}
	return *this;
}



int UserList::findIndex(char* userName) const
{
	int foundIndex = -1;
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp(userName, (*mUsers[i]).getUsername()) == 0)
		{
			foundIndex = i;
		}
	}
	return foundIndex;
}

int UserList::findUserFromFile(char* userName) const
{
	char buffer[MAX_LENGTH];
	ifstream file(getAssociatedFile());
	int count = 0;
	while (file && !file.eof())
	{
		file >> buffer;
		if (strcmp(buffer, userName) == 0)
		{
			return count;
		}
		++count;
	}
	try
	{
		file.close();
	}
	catch (ios::failure)
	{
		throw "Problem closing file";
	}
	count = -1;
	return count;
}

void UserList::addUser(const User& userToAdd)
{
	resize();
	mUsers[mCount] = new User(userToAdd);
	ofstream outputFile(getAssociatedFile());;

	if (outputFile)
	{
		outputFile << userToAdd;
	}
	try
	{
		outputFile.close();
	}
	catch (ios::failure)
	{
		throw "Problem closing file";
	}
	++mCount;
}

ostream& operator<<(ostream& out, const UserList& list)
{
	for (int i = 0; i < list.mCount; i++)
	{
		out << *(list.mUsers[i]);
	}
	return out;
 }
