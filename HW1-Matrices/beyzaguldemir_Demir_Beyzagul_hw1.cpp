/****************************************
Course: CS204
Assignment: HW1
Project Name: Minesweeper Game
Name: Beyzagul Demir
ID: 28313
Date: 14/10/2021
Purpose: This code is the simplified version of minesweeper game. 
It enables you to display or open a position. At the end, you can win or lose.
****************************************/

#include <iostream>
#include <string>
#include <vector> 
#include "randgen.h"
#include <iomanip>

using namespace std;

void printMatrix(vector<vector<char> > & matrix, int rows, int cols) { // This function prints the given matrix which is vector of character vector.
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) { // these 2 for loops of this function opens the elements of the matrix one by one.
			cout << matrix[i][j] << setw(4);
		}
		cout << "\n";
	}
	cout << endl;
}


bool checkPlace(int row, int col, int rows, int cols) { // This function checks whether the given position is in the borders of given matrix or not.
	bool flag = false;

	if (row >= 0 && row < rows && col >= 0 && col < cols) { // check whether the position is in the borders or not.
		flag = true;
	}

	return flag;
}

vector<vector<int> > setNumBombs(vector<vector<char> > & matrix, vector<vector<int> > & new_mat, int rows, int cols) { // This function sets (return) a matrix that gives the number of bombs around a position. 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) { // first 2 for loops of this function opens the elements of the matrix one by one.
			for (int k = -1; k <= 1; k++) {
				for (int n = -1; n <= 1; n++) { // 3rd and 4th for loops are to open the positions around a spesific position in the matrix.

					if (checkPlace(i+k, j+n, rows, cols)) { // this if condition checks whether the positions around the spesific point are in the borders or not.

						if (matrix[i + k][j + n] == 'B') { // check if this position has a mine.
							new_mat[i][j]++;
						}
					}
				}
			}
			if (matrix[i][j] == 'B') { // if the position itself has a mine, substract it.
				new_mat[i][j]--;
			}
		}
	}
	return new_mat;
}


void displaySurr(vector<vector<int> > new_mat, vector<vector<char> > matrix, int inputRow, int inputCol, int rows, int cols) { // This function prints the output of option 1. Option 1 is a choice that just displays one position's number of mines around it. 
	cout << endl << "Displaying the surrounding of (" << inputRow << "," << inputCol << "):" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) { // first 2 for loops of this function opens the elements of the matrix one by one.

			if (i == inputRow && j == inputCol) { // if the input row and column entered by the user are same with opened element, then change it with the number that shows the mines around it. new_mat matrix is a matrix that has these mine numbers.
				cout << new_mat[i][j] << setw(4);
			}

			else { // otherwise print point from the 'matrix' matrix.
				cout << matrix[i][j] << setw(4);
			}
		}
		cout << "\n";
	}
	cout << "Around (" << inputRow << "," << inputCol << ") you have " << new_mat[inputRow][inputCol] << " bomb(s)" << endl << endl;
}


void ArrOfMines(vector<vector<char> > matBombs, vector<vector<int> > new_mat, int rows, int cols) { // This function shows all of the mine's positions and for the other points that don't have mine, shows the number of mines around them.
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			if (matBombs[i][j] == 'B') {
				cout << matBombs[i][j] << setw(4); // matBombs matrix has B letter for the mines and has X letter for all of the other points.
			}
			else { // if matBombs matrix does not have B letter, then print new_mat matrix element for this position since new_mat matrix has number of mines.
				cout << new_mat[i][j] << setw(4); 
			}
		}
		cout << "\n";
	}
}


// This function print the output of option 2. It opens the entered position and if it is a mine, game ends. If it is not, then the opened position will be saved for the 'matrix' matrix.
void openCell(vector<vector<char> > & matrix, vector<vector<char> > matBombs, vector<vector<int> > new_mat, int inputRow, int inputCol, int rows, int cols) {
	cout << endl << "Opening cell (" << inputRow << "," << inputCol << "):" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if ((i == inputRow) && (j == inputCol)) {

				if (matBombs[i][j] == 'B') { // if the opened posiiton is a mine, game will over, matrix with new form and appropriate messages will be showed.
					matrix[i][j] = matBombs[i][j];
					printMatrix(matrix, rows, cols); // calls the printMatrix function and prints the matrix with new opened form.
					cout << "Unfortunately, you stepped on a mine" << endl;
					cout << "Arrangement of mines:" << endl;
					ArrOfMines(matBombs, new_mat, rows, cols);
					cout << endl << ">>>>> Game Over! <<<<<" << endl;
				}

				else { // if the opened posiiton is not a mine, game will continue, matrix wil new form will be showed.
					matrix[i][j] = '0' + new_mat[i][j];
					printMatrix(matrix, rows, cols);
				}
			}
		}
	}
}


int main() {
	int rows, cols, bombs, row_Coord, col_Coord;
	int inputRow, inputCol;
	int counter = 0;
	bool flag = true;
	string choice;

	cout << "Give the dimensions of the matrix: ";
	cin >> rows >> cols; // rows is the number of rows entered by the user and cols is the number of columns entered by the user.

	vector<vector<char> > matrix(rows, vector<char>(cols, 'X')); // this matrix has X letter for it's each element and it will change to open or display positions according to the options entered by the user.
	vector<vector<char> > matBombs(rows, vector<char>(cols, 'X')); // this matrix has X letter for it's each element. It will show the mine's positions with letter B.
	vector<vector<int> > new_mat(rows, vector<int>(cols, 0)); // this matrix will show the  number of mines around a position.

	cout << "How many bombs: ";
	cin >> bombs;

	while (((rows * cols) <= bombs) || (bombs < 1)) { // while the bomb number(s) are not in the specified border (greater than or equal to 1 and smaller than total elements of matrix) display appropriate messages.

		if ((rows * cols) <= bombs) {
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> bombs;
		} 
		
		else if (bombs < 1) {
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> bombs;
		}
	}

	printMatrix(matrix, rows, cols);


	RandGen rand;
	for (int i = 1; i <= bombs; i++) { // this for loop appoints the positions of mines randomly.
		row_Coord = rand.RandInt(rows);
		col_Coord = rand.RandInt(cols);
		while (matBombs[row_Coord][col_Coord] == 'B') { // while the point already has a mine, change the point.
			row_Coord = rand.RandInt(rows);
			col_Coord = rand.RandInt(cols);
		}
		matBombs[row_Coord][col_Coord] = 'B'; // give letter B for each point which has a mine in the matrix matBombs.
	}


	setNumBombs(matBombs, new_mat, rows, cols);

	cout << "Press:" << "\n" << "1. If you want to find out the surrounding of a cell" << "\n" << 
		"2. If you want to open the cell" << "\n" << "3. If you want to exit." << endl;

	choice = "a"; // to be able to enter while loop, assign a random letter for variable 'choice'.

// This while loop works for the options entered by the user and outputs that should be showed according to options.
	while ((choice != "3") && (flag == true) && (counter < (rows * cols))) {
		cin >> choice;


		if (choice == "1") { // if choice is 1, the output will be displaying the matrix. Specified position's number of mines around it will be displayed in the matrix even if the position has a mine.
			cout << "Give the coordinates:";
			cin >> inputRow >> inputCol; // inputRow is the row and inputCol is the column entered by the user.

			while (inputRow >= rows || inputCol >= cols || inputRow < 0 || inputCol < 0) { // check until the given position is a valid coordinate.
				cout << "It is out of range. Please give a valid coordinates:";
				cin >> inputRow >> inputCol;
			}

			displaySurr(new_mat, matrix, inputRow, inputCol, rows, cols);
			cout << "Press:" << "\n" << "1. If you want to find out the surrounding of a cell" << "\n" << 
			"2. If you want to open the cell" << "\n" << "3. If you want to exit." << endl;
		}


		else if (choice == "2") { // if choice is 2, the specified position will be opened, matrix will be showed, and if it is a bomb, user will lose.
			cout << "Give the coordinates:";
			cin >> inputRow >> inputCol; // inputRow is the row and inputCol is the column entered by the user.

			while (inputRow >= rows || inputCol >= cols || inputRow < 0 || inputCol < 0) { // check until the given position is a valid coordinate.
				cout << "It is out of range. Please give a valid coordinates:";
				cin >> inputRow >> inputCol;
			}

			openCell(matrix, matBombs, new_mat, inputRow, inputCol, rows, cols);
			counter = 0; // this counter will count number of different elements between 'matBombs' and 'matrix' matrices. By this way we will be enable to understand are there any 'unopened - not bomb' position in the matrix.


			for (int i = 0; i < rows; i++) {

				for (int j = 0; j < cols; j++) {

					if (matrix[i][j] == 'B') {
						flag = false; // if the opened position is bomb, then flag will be false. While condition will not be provided and game will over.
					}

					if (matBombs[i][j] != matrix[i][j]) { // check if all of the elements of this 2 matrices are different.
						counter++;
					}

				}
			}

			if (counter == (rows * cols)) { // if all of the elements of 'matBombs' and 'matrix' matrices are different, this means all of the non-bomb positions are opened and user win the game.
				cout << "Congratulations! All the non-mined cells opened successfully" << endl
					<< "You won!" << endl << endl << ">>>>> Game Over! <<<<<" << endl;
			}

			else if (flag == true) { // if flag is true, any bomb is opened and user can continue to the game.
				cout << "Press:" << "\n" << "1. If you want to find out the surrounding of a cell" << "\n" << 
				"2. If you want to open the cell" << "\n" << "3. If you want to exit." << endl;
			}			

		}

		else if (choice == "3") { // this condition exits the game.
			cout << "Program exiting ..." << endl;
		}

		else { // if input is not valid.
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
		}
	}

	return 0;
}