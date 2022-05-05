#ifndef __UserList_H
#define __UserList_H
#include "user.h"
#include <ostream>

using namespace std;
#define START_CAPACITY 4;

class UserList
{
	User** mUsers;
	int mCount;
	int mCapacity;
	char* mAssociatedFile;

	void copy(const UserList& other);
	void free();
	void resize();

public:
	User** getUsers() const;
	int getCount() const;
	char* getAssociatedFile() const;

	UserList() = delete;
	UserList(char* associatedFile);
	UserList(const char* fileName);
	UserList(const UserList& other);
	~UserList();
	UserList& operator=(const UserList& other);

	void addUser(const User& userToAdd);
	User& find(char* userName) const;
	friend ostream& operator<<(ostream& out, const UserList& list);
};



#endif