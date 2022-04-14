//taken from CS204 lecture notes and adjusted
#ifndef USERQUEUE_H
#define USERQUEUE_H
#include <string>
using namespace std;

//To store request informations, user struct has created
struct user {
	string name;
	int ID;
	string func_name;
};

class userQueue
{
private:
	user *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	userQueue(int);  //constructor, parameter is capacity
  	void enqueue(user); 
  	void dequeue(user &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif