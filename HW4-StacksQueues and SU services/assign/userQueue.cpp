//taken from CS204 lecture notes and adjusted
#include <iostream>
#include "userQueue.h"
using namespace std;


//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
userQueue::userQueue(int s)
{
	queueArray = new user[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
	/*
	#ifdef _DEBUG
		cout << "A queue with " << s << " elements created\n";
	#endif */
}

//********************************************
// Function enqueue inserts the value in User *
// at the rear of the queue.                 *
//********************************************
void userQueue::enqueue(user User)
{
	if (isFull())
    { 
         cout << "The queue is full. " << User.ID << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = User;
		// Update item count.
		numItems++;
		/*
		#ifdef _DEBUG
			cout << User.ID << " enqueued\n";
		#endif */
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into User. *
//**********************************************
void userQueue::dequeue(user &User)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		User = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool userQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool userQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void userQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
	/*
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif */
}