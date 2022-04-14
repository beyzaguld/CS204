//taken from CS204 lecture notes and adjusted
#include <iostream>
#include <string>
#include "dynstringstack.h"
#include "UserQueue.h"

using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynStringStack::DynStringStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynStringStack::push(string command)
{
	StackNode *newNode;

	// Allocate a new node & store command
	newNode = new StackNode;
	newNode->command = command;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynStringStack::pop(string &command)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		command = top->command;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynStringStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

void DynStringStack::clear()
{
	string value;   // Dummy variable for dequeue

	while(!isEmpty())
		pop(value); //delete all elements
	/*#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif*/
}

//destructor calls the clear function and clear all the elements in this stack.
DynStringStack::~DynStringStack() {
	clear();
}