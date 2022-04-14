/********************************
Beyzagul Demir
CS204 Homework 3 - Bus Lines
Date: 07.11.2021
********************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//store bus stops as linked list
struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;
};

//store bus lines with linked bus stops as linked linked list
struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;
};

//global variable, call it without initializa again
busLine* head = nullptr;


//This function opens txt file, reads line by line, word by word, and creates 2D pointer. 
void createLinkedLinkedList() {
	string line, stop, bus;

	busLine *busLines = new busLine;
	busStop *busStops = new busStop;

	ifstream input;
	string filename = "busLines.txt";
	input.open(filename.c_str());

	head = new busLine;
	busLine *ptr = head;

	//take txt file line by line
	while (getline(input, line)) {

		istringstream sstream(line);
		//first word of every line is bus line name.
		sstream >> bus;
		// delete comma from the bus line name.
		bus = bus.substr(0, bus.length()-1);

		busStop *headd = new busStop, *tail = nullptr;
		busStop *temp = headd;

		//read bus stops and create doubly linked list
		while (sstream >> stop) {
			temp->busStopName = stop;
			temp->left = tail;
			if (tail != nullptr) 
				tail->right = temp;
			tail = temp;
			temp = new busStop;
		}

		tail->right = nullptr;

		//fill ptr with bus line name, bus stops, next infos which points to head, and head will be filled.
		ptr->busLineName = bus;
		ptr->busStops = headd;
		if (!input.eof()) {
			ptr->next = new busLine;
			ptr = ptr->next;
		}
	}
	ptr->next = nullptr;
}

void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

//check whether you create 2D pointer list in a correct way
bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS;
			rightBS = currBS->right;
			if(rightBS && (rightBS->left != currBS)) {
				cout << "Inconsistency for " << currBL->busLineName
				<< " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

//take first bus stop and print all of them from left to right 
void printBusStops(busStop * busStops) {
	busStop *ptr = busStops;
	while (ptr != NULL) {
		if (ptr == busStops) {
			cout << ptr->busStopName;
		}
		else {
			cout << " <-> " << ptr->busStopName;
		}
		ptr = ptr->right;
	}
}

// take first line as ptr, print it and change it with it's next until the end.
void printBusLines() {
	busLine *ptr = head;
	while(ptr != NULL) {
		cout << ptr->busLineName << ": ";
		printBusStops(ptr->busStops);
		cout << endl;
		ptr = ptr->next;
	}
}

// search whether bus line name is in the linked list or not. Return true if bus line name is in the list, otherwise return false.
// Taken from CS204 course materials and edited.
bool SearchListLine(busLine *head, string searchValue)
{
	bool flag = false;
	while (head != NULL)
	{
		if(head->busLineName== searchValue)
			flag = true;			
		head = head->next;
	}
	return flag;
}

// search whether bus stop name is in the linked list or not. Return true if bus stop name is in the list, otherwise return false.
// Taken from CS204 course materials and edited.
bool SearchListStop(busStop *head, string searchValue)
{
	busStop *temp = head;
	bool flag = false;
	while (temp != NULL)
	{
		if(temp->busStopName== searchValue)
			flag = true;			
		temp = temp->right;
	}
	return flag;
}

//take one line name and find corresponding bus line. After that print bus line name it's bus stops.
void printOneLine(string busLineName) {
	busLine *temp = head;
	while (temp != NULL) {
		if (temp->busLineName == busLineName) {
			cout << temp->busLineName << ": ";
			printBusStops(temp->busStops);
		}
		temp = temp->next;
	}
}

//take bus line name and return corresponding bus line pointer.
busLine * findBusLine(string busLineName) {
	busLine *temp = head;
	while (temp != NULL) {
		if (temp->busLineName == busLineName) {
			return temp;
		}
		temp = temp->next;
	}
}

//take line to add new stop and name of the new stop, create new busStop and add it to the beginning of the busStop linked list.
void Add2Beginning(busLine * line, string newStop) {
	busLine *tempLine = line;
	busStop *temp = tempLine->busStops;
	busStop *newBusStop = new busStop;
	newBusStop->busStopName = newStop;
	newBusStop->right = temp;
	temp->left = newBusStop;
	newBusStop->left = nullptr;
	temp = newBusStop;
	busLine *headtemp = head;
	while (headtemp != NULL) {
		if (headtemp == line) {
			headtemp->busStops = temp;
		}
		headtemp = headtemp->next;		
	}
}

// take the busLine to add busStop, previous bus stop and the name of the new stop. Create new busStop with newStop info, add this bus stop after the previous stop.
// Connect this new bus stop to left and right bus stops.
void AddAfterPrevious(busLine * line, string previousStop, string newStop) {
	busLine *tempLine = line;
	busStop *temp = tempLine->busStops;
	busStop *newBusStop = new busStop;
	newBusStop->busStopName = newStop;
	while (temp != NULL) {
		if (temp->busStopName == previousStop) {
			newBusStop->right = temp->right;
			if (temp->right != nullptr)
				temp->right->left = newBusStop;
			temp->right = newBusStop;
			newBusStop->left = temp;
		}
		temp = temp->right;
	}
	busLine *headtemp = head;
	while (headtemp != NULL) {
		if (headtemp == line) {
			headtemp = tempLine;
		}
		headtemp = headtemp->next;		
	}
}

//take the name of the line, find it in the linked linked list, and delete it from list.
void DeleteOneLine (string line) {
	busLine * toBeDeleted = findBusLine(line);
	busLine *temp = head;	
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else 
	{
		temp = head;
		while (temp->next != toBeDeleted)
			temp = temp->next;
		temp->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}

//check whether given bus line is empty or not.
bool ifEmptyBusLine(busLine *line) {
	if (line->busStops == NULL) {
		return true;
	}
	return false;
}

//take corresponding bus line and the name of the bus stop to be deleted. Find given busstop, delete it from the bus line.
void deleteOneBusStop(busLine * line, string StopToBeDeleted) {
	busLine *templine = line;
	busStop *temp = templine->busStops;
	if (line->busStops->busStopName == StopToBeDeleted) {
		line->busStops = line->busStops->right;
	}
	else {
		while (temp->right->busStopName != StopToBeDeleted) {
			temp = temp->right;
		}
		busStop *tobedeleted = temp->right;
		temp->right = tobedeleted->right;
		if (tobedeleted->right != NULL)
			tobedeleted->right->left = temp;
		delete tobedeleted;
	}
	busLine *headtemp = head;
	while (headtemp != NULL) {
		if (headtemp == line) {
			headtemp = templine;
		}
		headtemp = headtemp->next;		
	}
	//after deleting bus stop, if bus line is empty delete it.
	if (ifEmptyBusLine(line)) {
		DeleteOneLine(line->busLineName);
	}
}

//take bus stop name as a position and corresponding busline as a line. Find given bus stop and return it.
busStop *findBusStop(string position, busLine * line) {
	busStop * temp = line->busStops;
	while (temp->busStopName != position) {
		temp = temp->right;
	}
	return temp;
}

//take entered current position and entered target position as parameter, find which one is at left and which one is at right side.
bool isLeftToRight(busStop * curr, busStop * target) {
	busStop *newcur = curr;
	while (newcur->right != NULL) {
		if (newcur->right == target)
			return true;
		newcur = newcur->right;
	}
	return false;
}


//check whether busline of the entered target position and busline of the entered current position have same bus stop to see the possibility of interchange.
bool checkIfExistSameStop(busLine *targetLine, busLine *currentLine) {
	busStop *targetTempStop = targetLine->busStops;
	while (targetTempStop != NULL) {
		busStop *temp = currentLine->busStops;
		while (temp != NULL) { 
			if (targetTempStop->busStopName == temp->busStopName) {
				return true;
			}
			temp = temp->right;
		}

		targetTempStop = targetTempStop->right;
	}
	return false;
}

//After finding interchange stop exist in given two line, find the current line's interchange stop and return it.
busStop *FindChangeStopCurrent(busLine *targetLine, busLine *currentLine) {
	busStop *targetTempStop = targetLine->busStops;
	while (targetTempStop != NULL) {
		busStop *temp = currentLine->busStops;
		while (temp != NULL) { 
			if (targetTempStop->busStopName == temp->busStopName) {
				return temp;
			}
			temp = temp->right;
		}

		targetTempStop = targetTempStop->right;
	}
}

//After finding interchange stop exist in given two line, find the target line's interchange stop and return it.
busStop *FindChangeStopTarget(busLine *targetLine, busLine *currentLine) {
	busStop *targetTempStop = targetLine->busStops;
	while (targetTempStop != NULL) {
		busStop *temp = currentLine->busStops;
		while (temp != NULL) { 
			if (targetTempStop->busStopName == temp->busStopName) {
				return targetTempStop;
			}
			temp = temp->right;
		}

		targetTempStop = targetTempStop->right;
	}
}

//take two bus stop from same line, check which one is coming before the other one. According to that enter if or else statement and print the bus stop path.
void printPath(busStop *curr, busStop *target) {
	if (isLeftToRight(curr, target)) {
		busStop *tempp = curr->right;
		while (tempp != target->right) {
			cout << "->" << tempp->busStopName;
			tempp = tempp->right;
		}
	}
	else {
		busStop *tempp = curr->left;
		while (tempp != target->left) {
			cout << "->" << tempp->busStopName;
			tempp = tempp->left;
		}
	}
}

//save path to a string value
void savePath(busStop *curr, busStop *target, string & output) {
	if (isLeftToRight(curr, target)) {
		busStop *tempp = curr->right;
		while (tempp != target->right) {
			output += "->" + tempp->busStopName;
			tempp = tempp->right;
		}
	}
	else {
		busStop *tempp = curr->left;
		while (tempp != target->left) {
			output += "->" + tempp->busStopName;
			tempp = tempp->left;
		}
	}
}

//Add one busline to linked linked list.
void addBusLine() {
	string busLineName, choice;
	string busStopName = "";
	int count = 0;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> busLineName;
	busLine *newLine = new busLine;
	newLine->busLineName = busLineName;
	busStop *newStop = new busStop;
	newStop->busStopName = "";
	newStop->right = nullptr;
	busStop *temp = newStop;
	busStop *tail = nullptr;
	//if buslineName is 0, return to main menu, otherwise continue.
	if (busLineName != "0") {
		//while busLineName is in the linked list, ask for new busline name.
		while (SearchListLine(head, busLineName)) {
			cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
			cin >> busLineName;
		}
		//if new entered busLineName is not 0, continue.
		if (busLineName != "0") {
			//busStopName is initialized to empty string. While user don't enter 0, ask for the bus stop name.
			while (busStopName != "0") {
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> busStopName;
				//if entered stop is in corresponding busline, display appropriate message. Otherwise, continue.
				if (SearchListStop(newStop, busStopName)) {
					cout << "Bus stop already exists in the line" << endl;
				}

				else {
					//if bus stop name is not 0, add it to the bus line.
					if (busStopName != "0") {
						count++;
						temp->busStopName = busStopName;
						temp->left = tail;
						if (tail != nullptr) {
							tail->right = temp;
						}
						tail = temp;
						temp = new busStop;	
						tail->right = nullptr;
					}
				}
			}
		
			//count zero means no bus stop added. If count is zero, don't add busline to linked linked list.
			if (count == 0) {
				cout << "You are not allowed to add an empty bus line" << endl;
			}
			
			else {
				//create a new line and print it's information.
				newLine->busStops = newStop;
				cout << "The bus line information is shown below" << endl;
				cout << newLine->busLineName << ": ";
				printBusStops(newLine->busStops);
				cout << endl << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
				cin >> choice;
				//if choice is yes, add this line to bus lines list, and print the whole list.
				if (choice == "y" || choice == "Y") {
					busLine *temp = head;
					newLine->next = temp;
					head = newLine;
					printBusLines();
				}

			}
		}
	}
}

//Add one bus stop to given bus line.
void addBusStop() {
	string busLinename, newBusStop, previous;
	//take busline to add new bus stop.
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> busLinename;
	if (busLinename != "0") {
		//if busline is not in the bus lines list
		if (!SearchListLine(head, busLinename)) {
			cout << "Bus line cannot be found. Going back to previous menu." << endl;
		}
		//if busline is in the bus lines list
		else {
			cout << "The bus line information is shown below" << endl;
			printOneLine(busLinename);
			cout << endl << "Enter the name of the new bus stop" << endl;
			cin >> newBusStop;
			if (newBusStop != "0") {
				//if bus stop name exits in given bus line
				if (SearchListStop(findBusLine(busLinename)->busStops, newBusStop)) {
					cout << "Bus stop already exists. Going back to previous menu." << endl;
				}
				else {
					cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
					cin >> previous;
					//if previous is entered as zero, add new bus stop to the beginning of the bus stop list.
					if (previous == "0") {
						Add2Beginning(findBusLine(busLinename), newBusStop);
						printBusLines();
					}
					else {
						//while previous stop name is not valid, ask until it is valid or user enter 0.
						while (!SearchListStop(findBusLine(busLinename)->busStops, previous) && previous != "0") {
							cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
							cin >> previous;
						}
						// if previous is not zero, add bus stop after given previous bus stop.
						if (previous != "0") {
							AddAfterPrevious(findBusLine(busLinename), previous, newBusStop);
							//print whole list.
							printBusLines();
						}
					}
					
				}
			}
		}
	}
}

//delete one bus line from the bus line's list.
void deleteBusLine() {
	string deleteLine;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> deleteLine;
	//if line to be deleted is not in the list
	if (!SearchListLine(head, deleteLine)) {
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
	}
	else {
		DeleteOneLine(deleteLine);
		printBusLines();
	}
}

//delete one bus stop from entered bus line.
void deleteBusStop() {
	string buslinename, StopToBeDeleted;
	//take busline name to delete bus stop
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> buslinename;
	if (buslinename != "0") {
		//if given bus line name is not in the list
		if (!SearchListLine(head, buslinename)) {
			cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
		}
		else {
			cout << "The bus line information is shown below" << endl;
			//print bus line information which has bus stop to be deleted
			printOneLine(buslinename);
			cout << endl << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
			cin >> StopToBeDeleted;
			if (StopToBeDeleted != "0") {
				//while bus stops list do not have entered bus stop and bus stop to be deleted is not zero
				while (!SearchListStop(findBusLine(buslinename)->busStops, StopToBeDeleted) && StopToBeDeleted != "0") {
					cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
					cin >> StopToBeDeleted;
				}
				if (StopToBeDeleted != "0") {
					deleteOneBusStop(findBusLine(buslinename), StopToBeDeleted);
					printBusLines();
				}
			}
		}
	}
}

//take current and target position and print the path.
void pathfinder() {
	bool flag = false, mark = false, indicator = false;
	string current, targetPos;
	cout << "Where are you now?" << endl;
	cin >> current;
	cout << "Where do you want to go?" << endl;
	cin >> targetPos;
	busLine *temp = head; //take the head of the linked list to implement
	busLine *temp2 = head; //take the head of the linked list to implement
	busLine *targetLine; // this line will be the line that has target bus Stop position
	busStop * changestop = nullptr; // this bus stop will indicate interchange stops.
	busLine *temphead = head; //take the head of the linked list to implement
	busLine *temphead2 = head; //take the head of the linked list to implement

	//in this while loop check whether given current position exists in the linked linked list
	while(temphead != NULL) {
		if (SearchListStop(temphead->busStops, current))
			indicator = true;
		temphead = temphead->next;
	}

	//in this while loop check whether given target position exists in the linked linked list
	while(temphead2 != NULL) {
		if (SearchListStop(temphead2->busStops, targetPos))
			mark = true;
		temphead2 = temphead2->next;
	}

	//if indicator is false, current position does not exist in the list.
	if (indicator == false) {
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	}
	else {
		//if mark iis false, target position does not exist in the list.
		if (mark == false) {
			cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		}
		else {
			while (temp != NULL) {

				//if line we are checking has the current bus stop
				if (SearchListStop(temp->busStops, current)) {
					busStop * curr = findBusStop(current, temp);
				
					// if same line has target bus stop
					if (SearchListStop(temp->busStops, targetPos)) {
						cout << "You can go there by " << temp->busLineName << ": " << current;
						busStop * target = findBusStop(targetPos, temp);

						//check from current and target bus stops, which one is at right and which one is at left, after that print the path.
						if (isLeftToRight(curr, target)) {
							busStop *tempp = curr->right;
							while (tempp != target->right) {
								cout << "->" << tempp->busStopName;
								tempp = tempp->right;
							}
						}
						else {
							busStop *tempp = curr->left;
							while (tempp != target->left) {
								cout << "->" << tempp->busStopName;
								tempp = tempp->left;
							}
						}
						break;
					}

					// if the line which has current bus stop, does not have the target bus stop
					else {
						while (temp2 != NULL) {

							//check which line has target bus stop, save it as a targetline.
							if (SearchListStop(temp2->busStops, targetPos)) {
								
								targetLine = temp2;

								// temp is the line which has current bus stop. Check if current bus line and target bus line have same bus stop to do interchange.
								//here is for the bonus part of the homework (1 interchange case)
								if (checkIfExistSameStop(targetLine, temp)) {
									flag = true;
									changestop = FindChangeStopCurrent(targetLine, temp); // save this interchange stop which is in currentline 
									busStop * target = findBusStop(targetPos, targetLine); //using targetline, save the target bus stop
									cout << "You can go there by " << temp->busLineName << ": " << current;
									printPath(curr, changestop);
									changestop = FindChangeStopTarget(targetLine, temp); // save this interchange stop which is in targetline 
									cout << endl << "                    " << targetLine->busLineName << ": " << changestop->busStopName;
									printPath(changestop, target);
									cout << endl;
								}
							}
							temp2 = temp2->next;
						}				

						busLine *currentLine = temp; //temp was keeping the line of current bus Stop, give the name as currentLine.
						busLine *line = head;
						busStop *secondchangestop = nullptr;
						string output = ""; // to print path info first be sure that we can go target position. So, before printing them keep them in one string variable.

						//here is for the challenge part of the homework (2 or more interchange case)
						//take list line by line. if current line and the line we are checking have mutual bus stop, save line's bus Stop infos, change line as currentline. 
						//Keep doing until line is targetline. After ensuring we can go to targetline, print all of the path.
						while (flag == false && line != NULL){
							// if taken line is not currentline
							if (currentLine != line) {

								//if given line and currentline have same bus stop to do interchange
								if(checkIfExistSameStop(line, currentLine)) {
									busStop *firstchangestop = FindChangeStopCurrent(line, currentLine); //find interchange stop from the currentline bus stop's
									//if currentline is not updated, we are in starting point, so save them to output.
									if (currentLine == temp) {
										output = "You can go there by " + temp->busLineName + ": " + current;
										savePath(curr, firstchangestop, output);
										output += "\n";
									}
									//if currentline is updated, save this paths to the output 
									else {
										output += "                    " + currentLine->busLineName + ": ";
										output += secondchangestop->busStopName;
										savePath(secondchangestop, firstchangestop, output);
										output += "\n";
									}

									secondchangestop = FindChangeStopTarget(line, currentLine); //find interchange stop from the targetline bus stop's (not final targetline)

									//if line is targetline, we have a path to go. Print them.
									if (line == targetLine) {
										busStop * target = findBusStop(targetPos, line);
										cout << output;
										cout << "                    " << line->busLineName << ": ";
										cout << secondchangestop->busStopName;
										printPath(secondchangestop, target);
										cout << endl;
										flag = true;
										break;							
									}
									else {
										currentLine = line;
										if (line->next != currentLine) {
											line = line->next;
											if(line->next == NULL) {
												break;
											}
										}
										else {
											line = currentLine->next;
											if (currentLine->next == NULL) {
												break;
											}
										}
									}
								}
								else {
									line = line->next;
								}
							}
							else {
								line = line->next;
							}
						}
						// if flag is false, there is no path with interchange.
						if (flag == false)
							cout << "Sorry no path from " << current << " to " << targetPos << " could be found." << endl;
					}

				}
				temp = temp->next;
			}



		}
	}

}


void processMainMenu() {
	char input;
	do
	{
		if(!consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
			case '0':
				cout << "Thanks for using our program" << endl;
				return;
			case '1':
				printBusLines();
				break;
			case '2':
				addBusLine();
				break;
			case '3':
				addBusStop();
				break;
			case '4':
				deleteBusLine();
				break;
			case '5':
				deleteBusStop();
				break;
			case '6':
				pathfinder();
				break;
			default:
				cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu


int main() {
	//first call linked linked list and create busLine 2D pointer.
	createLinkedLinkedList();
	processMainMenu();
	return 0;
}