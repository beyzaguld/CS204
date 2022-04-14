//taken from CS204 lecture notes and adjusted
#ifndef DYNUSERQUEUE_H
#define DYNUSERQUEUE_H
#include <string>
#include "UserQueue.h"
using namespace std;

struct QueueNode
{
	user value;
	QueueNode *next;
	QueueNode(user User, QueueNode *ptr = NULL)
	{
		value = User;
		next = ptr;
	}
};

class DynUserQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynUserQueue();
	~DynUserQueue();
	// Member functions.
	void enqueue(user);
	void dequeue(user &);
	bool isEmpty() const;     
	void clear();
};
#endif