#include "crab.h"

using namespace std;

Crab::Crab(vector<string> params) {
	//TODO
	sex = params.at(0)[0];
	length = stod(params.at(1));
	diameter = stod(params.at(2));
	height = stod(params.at(3));
	weight = stod(params.at(4)); //Total
	shuckedWeight = stod(params.at(5)); //Edible Meat
	visceraWeight = stod(params.at(6)); //Organs
	shellWeight = stod(params.at(7)); //Shell
	age = stoi(params.at(8));

}

void Crab::printCrab() const {
	cout << "Crab Sex: " << sex << endl;
	cout << "Crab Length: " << length << endl;
	cout << "Crab Diameter: " << diameter << endl;
	cout << "Crab Height: " << height << endl;
	cout << "Crab Weight: " << weight << endl;
	cout << "Crab ShuckedWeight: " << shuckedWeight << endl;
	cout << "Crab VisceraWeight: " << visceraWeight << endl;
	cout << "Crab ShellWeight: " << shellWeight << endl;
	cout << "Crab Age: " << age << endl << endl;
}


char Crab::getSex() const{return sex;}
double Crab::getLength()const {return length;}
double Crab::getDiameter() const{return diameter;}
double Crab::getHeight() const{return height;}
double Crab::getWeight()const { return weight;}
double Crab::getShuckedWeight() const{return shuckedWeight;}
double Crab::getVisceraWeight() const{return visceraWeight;}
double Crab::getShellWeight()  const{ return shellWeight;}
int Crab::getAge() const{ return age;}
