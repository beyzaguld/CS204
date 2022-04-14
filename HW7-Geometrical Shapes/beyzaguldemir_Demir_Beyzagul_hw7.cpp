//Student Name: Beyzagul Demir
//Student ID: 28313
//CS204 - HW7
#include <iostream>
#include <string>
using namespace std;
/**Artrim Kjamilji, 20.12.2021**/

/*include all the necessary files, libraries, etc. here, if any*/

/*if you choose not to write the 5 required classes in seperate .h and .cpp files, then write them here*/

class shape {
public:
	shape(string n) : myName(n) {}; //constructor
	virtual ~shape() {}; //destructor
	virtual float perimeter() = 0 {}; //purely virtual function
	virtual float area() = 0 {};      //purely virtual function
	virtual float volume() = 0 {};    //purely virtual function
	string getName();
protected:
	string myName;
};


string shape::getName() {
	return myName;
}

class TwoDShape: public shape {
public:
	TwoDShape(string n) :shape(n) {}; //constructor
	virtual ~TwoDShape() {}; //destructor
	virtual float volume();
protected:
	float volume1;
};

float TwoDShape:: volume() {
	return 0; //set volume as 0
}


class ThreeDShape: public shape {
public:
	ThreeDShape(string n) :shape(n) {}; //constructor
	virtual ~ThreeDShape() {};  //destructor
	virtual float perimeter();
protected:
	float perimeter1;
};

float ThreeDShape:: perimeter() {
	return 0; //set perimeter as 0
}

class rectangle: public TwoDShape {
public:
	rectangle(string n, float w, float l) :TwoDShape(n), width(w), length(l) {};  //constructor
	~rectangle() {};  //destructor
	float perimeter();
	float area();
protected:
	float width;
	float length;
};



float rectangle:: perimeter() {
	return (2*(width + length));
}

float rectangle:: area() {
	return width*length;
}


class box: public ThreeDShape {
public:
	box(string n, float l, float h, float w) : ThreeDShape(n), length(l), height(h), width(w) {}; //constructor
	~box() {}; //destructor
	float area();
	float volume();
protected:
	float length;
	float height;
	float width;
};


float box:: area() {
	float area = ( 2* ((width * length) + (width * height) + (length * height)));
	return area;
}

float box:: volume() {
	float volume = (width * height * length);
	return volume;
}

shape *getShape() {
	/*write the getShape() function body here*/
	int option;
	bool flag = true;
	float width, length, height;
	string name;
	
	while (flag) {
		cout << endl << "Choose an option (1 or 2):" << endl
			<< "1. Rectangle" << endl << "2. Box" << endl;
		cin >> option;


		if (option == 1) {

			cout << "You chose rectangle. Give it's width, length and name:" << endl;
			cin >> width >> length >> name;
			flag = false;
		
			rectangle *myRec = new rectangle(name, width, length);
			return myRec;

		}


		else if (option == 2) {
			cout << "You chose box. Give it's width, length, height and name:" << endl;
			cin >> width >> length >> height >> name;
			flag = false;
			
			box *myBox = new box(name, length, height, width);
			return myBox;
		}


		else {
			cout << "UNAVAILABLE OPTION CHOSEN. Try Again." << endl;
		}

	}
	
}//getShape()


int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}