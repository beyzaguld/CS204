#include <iostream>
#include <string>
#include <fstream>
#include "UserQueue.h"
#include "DynUserQueue.h"
#include "dynstringstack.h"
using namespace std;

//store processes to be implemeneted as a linked list
struct process {
	string processName;
	process *down;
};

//store functions with linked processes as a linked linked list
struct functions {
	string funcName;
	functions *right;
	process *process;
};



//global variables, call it without initializa again
functions* head = nullptr; //all of the functions will be mainly stored here
DynUserQueue studentQue; //student requests will be dynamically stored there
userQueue instructorQue(5); // instructor requests from 5 different instructors, will be stored there.
DynStringStack CommonStack; // processes coming from the requests from students and instructors, will be commonly and dynamically stored there.

//take first process and print all of them from left to right 
void printProcesses(process * Process) {
	process *ptr = Process;
	while (ptr != NULL) {
		if (ptr == Process) {
			cout << ptr->processName;
		}
		else {
			cout << ", " << ptr->processName;
		}
		ptr = ptr->down;
	}
	cout << ".";
}

// take first function as ptr, print it and change it with it's next until the end.
void printFunctions() {
	functions *ptr = head;
	while(ptr != NULL) {
		cout << ptr->funcName << ": " << endl;
		printProcesses(ptr->process);
		cout << endl;
		ptr = ptr->right;
	}
}

//Check whether entered searchValue is in functions linked list or not. If it is, return true. Otherwise, return false.
bool SearchListOfFunc( string searchValue)
{
	bool flag = false;
	functions *ptr = head;
	while (ptr != NULL)
	{
		if(ptr->funcName == searchValue)
			flag = true;			
		ptr = ptr->right;
	}
	return flag;
}

//take function name and return corresponding functions pointer.
functions * findFunc(string funcName) {
	functions *temp = head;
	while (temp != NULL) {
		if (temp->funcName == funcName) {
			return temp;
		}
		temp = temp->right;
	}
}

//Add a request to queue which is named as instructorQue.
void addInstructorRequest() {
	string func_name, name;
	int ID;
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	cin >> func_name;

	//If entered function name is not in functions pointer list, go back to main menu.
	if (!SearchListOfFunc(func_name))
		cout << "The requested service (function) does not exist." <<  "\n"
		<< "GOING BACK TO MAIN MENU" << endl;

	//Otherwise
	else {
		cout << "Give instructor's name: ";
		cin >> name;
		cout << "Give instructor's ID (an int): ";
		cin >> ID;

		//user struct is initialized at "userQueue.h"
		//create a user struct for entered instructor
		user ins;
		ins.ID = ID;
		ins.name = name;
		ins.func_name = func_name;

		//after adding informations about this instructor, add this user instructor to instructorQue
		instructorQue.enqueue(ins);
		cout << "Prof. " << name << "'s service request of " << func_name << "\n"
			<< "has been put in the instructor's queue." << "\n" 
			<< "Waiting to be served..." << endl;
	}
}

//Add a request to queue which is named as studentQue.
void addStudentRequest() {
	string func_name, name;
	int ID;
	cout << "Add a service (function) that the student wants to use:" << endl;
	cin >> func_name;

	//If entered function name is not in functions pointer list, go back to main menu.
	if (!SearchListOfFunc(func_name))
		cout << "The requested service (function) does not exist." <<  "\n"
		<< "GOING BACK TO MAIN MENU" << endl;

	//Otherwise
	else {
		cout << "Give student's name: ";
		cin >> name;
		cout << "Give student's ID (an int): ";
		cin >> ID;

		//create a user struct for entered student
		user stu;
		stu.ID = ID;
		stu.name = name;
		stu.func_name = func_name;

		//after adding informations about this student, add this user student to studentQue
		studentQue.enqueue(stu);
		cout << name << "'s service request of " << func_name
			<< " has been put in the student's queue." << "\n" 
			<< "Waiting to be served..." << endl;
	}
}

//
void processARequest(string functionName)
{
	functions *func = findFunc(functionName); 
	process *temp = func->process ;
	string dummy;
	DynStringStack tempStack;
	//while there is a process to read
	while (temp != NULL) {

		//find the first word of the process name to identif it is define, call, or print.
		int idx = temp->processName.find(" ");
		string currCommand = temp->processName.substr(0, idx);

		// if current command is define, add this process name with it's function name to common stack.
		if(currCommand == "define")
		{
			CommonStack.push(functionName + ": " + temp->processName);
		}

		// if current command is call, call this function again, recursion will happen.
		else if (currCommand =="call")
		{
			// the recursion goes here
			//identify function name to be called
			string calledFunc = temp->processName.substr(idx + 1);
			cout << "Calling " << calledFunc << " from " << functionName << endl;
			processARequest(calledFunc);
		}
		//if current command is print, print the stack. Since stacks have FILO order, print it in reverse order.
		else {
			cout << "PRINTING THE STACK TRACE:" << endl;

			//if stack is empty
			if (CommonStack.isEmpty())
				cout << "The stack is empty" << endl;

			//if stack is not empty
			else {

				//send elements from the CommonStack to tempstack, elements aill be reversed.
				while (!CommonStack.isEmpty()) {
					CommonStack.pop(dummy);
					tempStack.push(dummy);
				}

				//Now print them and to not change original stack, add elements back.
				while (!tempStack.isEmpty()) {
					tempStack.pop(dummy);
					cout << dummy << endl;
					CommonStack.push(dummy);
				}
			}
		}
		temp = temp->down;
	}

	// delete this function’s data from the top of the stack
	while (!CommonStack.isEmpty()) {
		CommonStack.pop(dummy);

		//find function name
		int idx = dummy.find(" ");
		string currFunc = dummy.substr(0, idx-1);

		//if founded function name from stack and entered function name to this function are not the same, stop popping elements. Push back the last one.
		if (currFunc != functionName) {
			CommonStack.push(dummy);
			break;
		}
	}

	cout << functionName << " is finished. Clearing the stack from it's data... "
	 <<endl;
	system("pause");

	if (CommonStack.isEmpty()) 
		cout << "The stack is empty." << endl;
}


void processARequest()
{
	if (!instructorQue.isEmpty()) {

		 //if instructors queue is not empty, process the next request
		user instructorUser;

		//dequeue one instructor User according to FIFO order.
		instructorQue.dequeue(instructorUser);

		//take requested function name of current instructor
		string functionName = instructorUser.func_name;
		cout << "Processing instructors queue..." << endl;
		cout << "Processing prof." << instructorUser.name << "'s request (with ID " << instructorUser.ID 
			<< ") of service (function):" << endl;
		cout << instructorUser.func_name << endl;

		//enter requested function name found above and process the requests.
		processARequest(functionName);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentQue.isEmpty()) {

		 //if instructors queue is empty and student’s not,
		 //then process the next student request
		user studentUser;

		//dequeue one student User according to FIFO order.
		studentQue.dequeue(studentUser);

		//take requested function name of current student
		string functionName = studentUser.func_name;
		cout << "Instructors queue is empty. Proceding with students queue..." << endl;
		cout << "Processing " << studentUser.name << "'s request (with ID " << studentUser.ID 
			<< ") of service (function):" << endl;
		cout << functionName << endl;
		cout << "-----------------------------------------------------------------" << endl;

		//enter requested function name found above and process the requests.
		processARequest(functionName);
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else {
		// otherwise…
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<<"GOING BACK TO MAIN MENU"<<endl;
	}
}

void mainProgram() {
	while (true) {
		cout << endl;
		cout<<"**********************************************************************"<<endl
			<<"**************** 0 - EXIT PROGRAM                        *************"<<endl 
			<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
			<<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl 
			<<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl 
			<<"**********************************************************************"<<endl;
		cout << endl;
		int option; cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option;
		switch (option) {
			case 0:
				cout<<"PROGRAM EXITING ... "<<endl;
				system("pause");
				exit(0);
			case 1:
				addInstructorRequest();
				break;
			case 2:
				addStudentRequest();
				break;
			case 3:
				processARequest();
				break;
			default:
				cout<<"INVALID OPTION!!! Try again"<<endl;
		}
	}
}

int main() {
	bool flag = true;
	head = new functions;
	functions *ptr = head;
	string choice, filename, line, function, Process;
	cout << "If you want to open a service (function) defining file," << 
		"\n" << "then press (Y/y) for 'yes', otherwise press any single key" << endl;
	cin >> choice;

	//if choice is y oy Y, take the filename
	if (choice == "y" || choice == "Y") {
		cout << "Enter the input filename: ";
		cin >> filename;
	}

	//Otherwise, exit program
	else {
		flag = false;
		cout << "Program exiting..." << endl;
	}

	//while entered input is yes (y or Y):
	while (choice == "y" || choice == "Y") {

		//open file
		ifstream input;
		input.open(filename.c_str());

		//if file has successfully opened
		if (!input.fail()) {
			process *tProcess = new process;
			process *temp = tProcess;
			int count = 0;

			//read file line by line
			while(getline(input, line)) {

				//if count is zero, that means it is first line, which has function name. 
				if (count == 0) {
					function = line;
					function = function.substr(0, function.length()-1);	
					count++;
				}

				//Otherwise, save the line to process pointer list. After adding, update temp process pointer with the next one. 
				//In that way we can create and fill process linked list.
				else {
					line = line.substr(0, line.length()-1);
					temp->processName = line;
					if (!input.eof()) {
						temp->down = new process;
						temp = temp->down;
					}			
				}
			}
			temp->down = nullptr;

			//save process pointer list to functions pointer list.
			ptr->process = tProcess;

			//save function name to functions pointer list.
			ptr->funcName = function;
			cin.get();
			cin.clear();

			cout << "Do you want to open another service defining file?" << "\n" 
				<< "Press (Y/y) for 'yes', otherwise press anykey" << endl;
			cin >> choice;

			//if choice is yes, update temporary functions pointer with next one. 
			//In that way we can create and fill functions linked list.
			if (choice == "y" || choice == "Y") {
				ptr->right = new functions;
				ptr = ptr->right;
				cout << "Enter the input filename: ";
				cin >> filename;
			}
		}

		//if file has failed to open, print appropriate message and exit the program.
		else {
			cout << "Input file failed to open." << endl;
			cout << "Program exiting..." << endl;
			flag = false;
			choice = "n";
		}
	}

	//if flag is true (if all of the input files has successfully opened)
	if (flag) {
		ptr->right = nullptr;
		cout << "-------------------------------------------------------------------" << endl;
		cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
		cout << "-------------------------------------------------------------------" << endl;

		//print functions linked linked list with their informations (function names and processes)
		printFunctions();
		mainProgram();
	}

	return 0;
}