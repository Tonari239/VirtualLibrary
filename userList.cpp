#include "userList.h"
#include "usefulFunctions.h"
#include <fstream>
using namespace std;


void UserList::copy(const UserList& other)
{
	mCount = other.mCount;
	mCapacity = other.mCapacity;
	mUsers = new User * [mCapacity];
	for (int i = 0; i < mCount; i++)
	{
		mUsers[i] = new User(*(other.mUsers[i])); // count is always less than capacity so no overflow will occur
	}
	copyString(mAssociatedFile, other.getAssociatedFile());
}
void UserList::free()
{
	for (int i = 0; i < mCount; i++)
	{
		delete mUsers[i];
	}
	delete[] mUsers;
	remove(getAssociatedFile());
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
UserList::UserList(const UserList& other)
{
	copy(other);
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




User& UserList::find(char* userName) const
{
	int foundIndex = -1;
	for (int i = 0; i < mCount; i++)
	{
		if (strcmp(userName, (*mUsers[i]).getUsername()) == 0)
		{
			foundIndex = i;
			return *mUsers[foundIndex];
		}
	}
	if (foundIndex == -1)
	{
		throw "Not found!";
	}
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
	catch (const std::exception&)
	{

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
