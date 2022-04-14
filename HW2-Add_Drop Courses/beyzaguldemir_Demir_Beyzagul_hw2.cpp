// Student Name: Beyzagul Demir
// Student ID: 28313
// CS204 - HW2 - Add Drop Courses
// Date: 30/10/2021
// The purpose of this homework is to get familiar with linked lists.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "strutils.h"
using namespace std;


// create a struct courseNode whish has courseCode, courseName, studentsAttendingIDs elements inside of it.
struct courseNode
{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;

	//defaul constructor
	courseNode::courseNode()
		:courseCode(""), courseName(""), studentsAttendingIDs(0,0), next(NULL)
	{}
	//constructor
	courseNode::courseNode(string c, string n, vector<int> ids, courseNode * node)
		:courseCode(c), courseName(n), studentsAttendingIDs(ids), next(node)
	{}
};

// print each element of the given vector
void printVector(vector<int> IDs) {
	for (int i = 0; i < IDs.size(); i++) {
		cout << " " << IDs[i];
	}
}

//print courseNode linked list 
// Taken from CS204 course materials and edited.
void printList (courseNode * head) {
	courseNode * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr->courseCode << " " <<  ptr->courseName << ":";
		printVector(ptr->studentsAttendingIDs);
		cout << endl;
		ptr = ptr->next;
	}
}

// search whether course name is in the linked list or not. Return true if course name is in the list, otherwise return false.
// Taken from CS204 course materials and edited.
bool SearchList(courseNode *head, string searchValue)
{
	bool flag = false;
	while (head != NULL)
	{
		if(head->courseName == searchValue)
			flag = true;			
		head = head->next;
	}
	return flag;
}

// Take linked list, course code, course name, student id; add this new course to linked list as a node. Return new linked list of course nodes.
// Taken from CS204 course materials and edited.
courseNode * AddInOrder(courseNode * head, string code, int id, string new_course)
{
	courseNode *  ptr = head; 

	// if list is empty or the correct position is first node.
	if (head == NULL || (new_course < head->courseName)) {   
		courseNode * temp = new courseNode;
		temp->courseName = new_course;
		temp->courseCode = code;
		(temp->studentsAttendingIDs).push_back(id);
		temp->next = head;
		return temp;
    }

	// find the correct position for node (alphabetical order)
    while (ptr->next != NULL && ((ptr->next->courseName < new_course))) {
	   ptr = ptr->next;
    }

	// add new course to the linked list at correct position.
    courseNode * tempp = new courseNode;
    tempp->courseName = new_course;
    tempp->courseCode = code;
    (tempp->studentsAttendingIDs).push_back(id);
    tempp->next = ptr->next;
    ptr->next = tempp;
    return head;
}

//Insert an integer to the sorted vector in a sorted way.
// taken from CS201 course materials (my previous semester notes taken from lecture slides).
void insert(vector<int> & a, int newnum)
{
   int count = a.size();
   a.push_back(newnum); 
   int loc = count;    
   while (loc > 0 && a[loc-1] > newnum){
	  a[loc] = a[loc-1]; 
      loc--; 
   }
   a[loc] = newnum;
}

// Sort given vector in ascending order.
// taken from CS201 course materials (my previous semester notes taken from lecture slides).
// pre: a contains a.size() elements
void SelectSort(vector<int> & a){
	int j, k, temp, minIndex, numElts = a.size();
    for(k=0; k < numElts - 1; k++) {   
		minIndex = k;
        for(j=k+1; j < numElts; j++){
			if (a[j] < a[minIndex]){
				minIndex = j;  
            }
        }
        temp = a[k]; 
        a[k] = a[minIndex];
        a[minIndex] = temp;
    }
}


//search whether given vector contains given element. If does not contain return -1.
// taken from CS201 course materials (my pevious semester notes taken from lecture slides).
// pre: entered vector should be sorted.
int bsearch(const vector<int> & list, const int & key) {
    int low = 0;                  
    int high = list.size()-1;     
    int mid;                     
    while (low <= high){
		mid = (low + high)/2;
        if (list[mid] == key) {
			return mid;
        }
        else if (list[mid] < key) {
			low = mid + 1;
        }
        else {   
			high = mid - 1;
        }
    }
	return -1;
}

// take vector and num that is supposed to be deleted. Find the index of num and erase from given vector.
void deleteFromVector(vector<int> & a, int num) {
	vector<int> new_v;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == num) {
			a.erase(a.begin()+i);
		}
	}
}

// take the linked list and delete to prevent memory leak.
// taken from CS204 course materials.
void ClearList(courseNode * &head)
{
	courseNode *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}

int main() {
	string filename, line, word, course_name, course_code, input_1, input_2, word1, co_code, co_name, id;
	int count, student_id, choice = 0;
	ifstream input;
	courseNode *myList; //All of the course informations will mainly be stored there.
	myList = NULL;
	courseNode *ptr = myList;
	cout << "Please enter file name: ";
	cin >> filename;
	input.open(filename.c_str());
	cout << "Successfully opened file " << filename << endl;

	//read the text file line by line, word by word and at the end store them to linkedlist using pointers and nodes.
	while (getline(input, line)) {
		istringstream StrStream(line);
		count = 1;
		while(StrStream >> word) {
			if (count == 1) {
				course_code = word; //take course code from the file.
			}
			else if (count == 2) {
				course_name = word; //take course name from the file.
			}
			else if (count == 3) {
				student_id = atoi(word); //take student id from the file.
			}
			count++;
		}

		//if the course is not in the the linkedlist(myList), add a node for the course. In this node, there will be course name, course code, and student id.
		if (!SearchList(myList, course_name)) {
			myList = AddInOrder(myList, course_code, student_id, course_name);
		}

		//if a node for the course already exists, find the course node, add the student id to corresponding course node.
		else {
			courseNode * temp = myList;
			while (temp != NULL) {
				if (temp->courseName == course_name) { //if the temp node is the one that we are searching
					if(bsearch(temp->studentsAttendingIDs, student_id) == -1) { //if the node does not have the student id
						insert(temp->studentsAttendingIDs, student_id); //add student id to IDs vector of the corresponding course node.
					}
				}
				temp = temp->next;
			}
		}
	}
	cout << "The linked list is created." << endl;
	cout << "The initial list is:" << endl;
	printList(myList); //print linkedList with all of its informations: course code, course name, students IDs.


	while (choice != 4) {

		//print selection output for the user and ask for a choice.
		cout << endl << "Please select one of the choices:" << "\n" << "1. Add to List"
			<< "\n" << "2. Drop from List" << "\n" << "3. Display List" << "\n" << "4. Finish Add/Drop and Exit" << endl;
		cin >> choice;
		count  = 1; //to determine which infromation is entered: course name, course code, or student id.
		vector<int> stu_id; // to store IDs of student from spesific course.

		//choice 1 means: add to list
		if (choice == 1) {
			cin.ignore();
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
			getline(cin, input_1);
			istringstream StStream(input_1);
			
			//enter this while until break
			while (true) {

				//take course code from the input
				if (count == 1) {
					StStream >> co_code;
					count++;
				}

				//take course name from the input
				else if (count == 2) {
					StStream >> co_name;
					count++;
				}

				//take first student id from the input (assume at least one student id will be entered) 
				else if (count == 3) {
					StStream >> id;
					stu_id.push_back(atoi(id));
					count++;
				}

				else {

					//if there is still input words to read enter this if condition
					if (!StStream.eof()) {
						StStream >> word;

						//if the first character of the word is numerical, that means user entered a stuent id. Add this ID to stu_id vector.
						if (word[0] >= '0' && word[0] <= '9') {
							stu_id.push_back(atoi(word));
						}
					}

					//if end of file or new course code is entered (the first character of the word is not numerical),
					//proceed with the current course information processes. Using co_code, co_name, stu_id; update linked course node list.
					if (StStream.eof() || !(word[0] >= '0' && word[0] <= '9')) {

						//if this course is in the linked list
						if (SearchList(myList, co_name)) {
							courseNode *temp_node = myList; 

							//find the position of the course node.
							while (temp_node != NULL) {
								if (temp_node->courseName == co_name) {
									break;
								}
								else {
									temp_node = temp_node->next;
								}
							}

							// for each student number if number is not in the vector of the node, add to the vector of the course node.
							for (int i = 0; i< stu_id.size(); i++) {			

								//if id is not in the course node
								if(bsearch(temp_node->studentsAttendingIDs, stu_id[i]) == -1) {
									temp_node->studentsAttendingIDs.push_back(stu_id[i]); // add id
									SelectSort(temp_node->studentsAttendingIDs); // sort studentsAttendingIDS vector.
									cout << "Student with id " << stu_id[i] << " is enrolled to " << co_code << "." << endl;
								}

								// if id is in the course node, just display a message.
								else {
									cout << "Student with id " << stu_id[i] << " already is enrolled to " << co_code << ". No action taken." << endl;
								}
							}
						}

						//if this course is not in the linked list
						else {
							cout << co_code << " does not exist in the list of Courses. It is added up." << endl;
							myList = AddInOrder(myList, co_code, stu_id[0], co_name); // add this course with first student id in the studentAttendingIDs vector. Now linked list has course node for corresponding course.
							courseNode *temp_node = myList; 

							//find the course node for corresponding course from myList
							while (temp_node != NULL) {
								if (temp_node->courseName == co_name) {
									break;
								}
								else {
									temp_node = temp_node->next;
								}
							}

							//add all of the IDs from stu_id vector to course node's student id vector (don't add first ID since it was added when AddINOrder() function called.)
							for (int i = 0; i < stu_id.size(); i++) {
								if ( i != 0) {
									temp_node->studentsAttendingIDs.push_back(stu_id[i]);
								}
								cout << "Student with id " << stu_id[i] << " is enrolled to " << co_code << "." << endl;
							}
	
							SelectSort(temp_node->studentsAttendingIDs); //sort IDs 
						}
						co_code = word; // since code of the course is taken to check whether it is an ID or not, equalize taken word to co_code
						count = 2; // since co_code is taken, continue from taking co_name. So, count should be 2.
						stu_id.clear(); // clear the vector for next course's student ID's.
					} 
					if (StStream.eof()) { // if end of file, exit from the while loop.
						break;
					}
				}
			}
		}

		// choice 2 means: drop from list
		else if (choice == 2) {
			stu_id.clear();
			count = 1;
			cin.ignore();
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
			getline(cin, input_2);
			istringstream sstream(input_2);

			//enter this while until break
			while (true) {

				//take course code from the input
				if (count == 1) {
					sstream >> co_code;
					count++;
				}

				//take course name from the input
				else if (count == 2) {
					sstream >> co_name;
					count++;
				}

				//take first student id from the input (assume at least one student id will be entered) 
				else if (count == 3) {
					sstream >> id;
					stu_id.push_back(atoi(id));
					count++;
				}

				else {

					//if there is still input words to read enter this if condition
					if (!sstream.eof()) {
						sstream >> word;
						//if the first character of the word is numerical, that means user entered a stuent id. Add this ID to stu_id vector.
						if (word[0] >= '0' && word[0] <= '9') {
							stu_id.push_back(atoi(word));
						}
					}

					//if end of file or new course code is entered (the first character of the word is not numerical),
					//proceed with the current course information processes. Using co_code, co_name, stu_id; update linked course node list.
					if (sstream.eof() || !(word[0] >= '0' && word[0] <= '9')) {

						//if this course is in the linked list
						if (SearchList(myList, co_name)) {
							courseNode *temp_node = myList; 

							//find the position of the course node.
							while (temp_node != NULL) {
								if (temp_node->courseName == co_name) {
									break;
								}
								else {
									temp_node = temp_node->next;
								}
							}

							// for each student number if number is in the vector of the node, delete from the vector of the course node.
							for (int i = 0; i< stu_id.size(); i++) {	

								//if id is in the course node
								if(bsearch(temp_node->studentsAttendingIDs, stu_id[i]) != -1) {
									cout << "Student with id " << stu_id[i] << " has dropped " << co_code << "." << endl;
									deleteFromVector(temp_node->studentsAttendingIDs, stu_id[i]);
								}

								//if id is not in the course node, just display a message.
								else {
									cout << "Student with id " << stu_id[i] << " is not enrolled to " << co_code << ", thus he can't drop that course." << endl;
								}
							}
						}

						//if this course is not in the linked list just display a message
						else {
							for (int i = 0; i < stu_id.size(); i++) {
								cout << "The " << co_code << " course is not in the list, thus student with id " << stu_id[i] << " can't be dropped" <<  endl;
							}						
						}
						co_code = word; // since code of the course is taken to check whether it is an ID or not, equalize taken word to co_code
						count = 2; // since co_code is taken, continue from taking co_name. So, count should be 2.
						stu_id.clear(); // clear the vector for next course's student ID's.
					}
					if (sstream.eof()) { // if end of file, exit from the while loop.
						break;
					}
				}
			}
		}

		// choice 3 means: display the linked list. (myList)
		else if (choice == 3) {
			cout << "The current list of course and the students attending them:" << endl;
			printList(myList); //prints the course codes, course names, and IDs of students attending courses.
		}

		//choice 4 means: print final list, close courses with less than 3 student, then delete the linked list.
		else if (choice == 4) {
			cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
			cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
			courseNode *temp_node = myList;

			// for each course node print node elements
			while (temp_node != NULL) {

				// if total student number taken this course is less than 3, display appropriate message.
				if (temp_node->studentsAttendingIDs.size() < 3) {
					cout << temp_node->courseCode << " " << temp_node->courseName;
					printVector(temp_node->studentsAttendingIDs);
					cout << " -> This course will be closed" << endl;
				}

				// if total student number taken this course is greater than or equal to 3.
				else {
					cout << temp_node->courseCode << " " << temp_node->courseName << ":";
					printVector(temp_node->studentsAttendingIDs);
					cout << endl;
				}
				temp_node = temp_node->next;
			}
			ClearList(myList); // delete and then 
			myList = NULL; //equalize to NULL all elements of the myList.
		}
	}

	cin.get();
	cin.ignore();
	input.close();
	system("pause");
	return 0;
}