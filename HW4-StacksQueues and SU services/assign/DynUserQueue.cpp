//taken from CS204 lecture notes and adjusted
#include <iostream>
#include "DynUserQueue.h"
#include "UserQueue.h"

using namespace std;


//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynUserQueue::DynUserQueue()
{
	front = NULL;
	rear = NULL;   
	/*
	#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif */
}

//********************************************
// Function enqueue inserts the value in user*
// at the rear of the queue.                 *
//********************************************
void DynUserQueue::enqueue(user User)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(User);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(User);
		rear = rear->next;
	} 
	/*#ifdef _DEBUG
		cout << User.ID << " enqueued\n";
	#endif*/
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into User. *
//**********************************************
void DynUserQueue::dequeue(user &User)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		User = front->value;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynUserQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynUserQueue::clear()
{
	user value;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(value); //delete all elements
	/*#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif*/
}

//destructor calls the clear function and clear all the elements in this queue.
DynUserQueue::~DynUserQueue() {
	clear();
}