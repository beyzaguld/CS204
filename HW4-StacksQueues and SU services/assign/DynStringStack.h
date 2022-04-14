//taken from CS204 lecture notes and adjusted
#ifndef DYNSTRINGSTACK_H
#define DYNSTRINGSTACK_H
#include <string>
#include "UserQueue.h"
using namespace std;


struct StackNode
{
	string command;
	StackNode *next;
};

class DynStringStack
{
private:
	StackNode *top; //top element of the stack

public:
	DynStringStack(void); //constructor
	~DynStringStack(); //destructor
	void clear(); //removes all elements
	void push(string);
	void pop(string &);
	bool isEmpty(void);
};
#endif
