#pragma once
#include <iostream>
#include <vector>

class Crab {
private: 
	char sex = 'U'; //For unset
	double length = 0;
	double diameter = 0;
	double height = 0;
	double weight = 0; //Total
	double shuckedWeight = 0; //Edible Meat
	double visceraWeight = 0; //Organs
	double shellWeight = 0; //Shell 
	int age = 0;

public:
	Crab(std::vector<std::string> params);
	void printCrab() const;
	char getSex() const;
	double getLength() const;
	double getDiameter() const;
	double getHeight() const;
	double getWeight() const;
	double getShuckedWeight() const;
	double getVisceraWeight() const;
	double getShellWeight() const;
	int getAge() const;
};
