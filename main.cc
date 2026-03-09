#include "crab.h"
#include "dataset.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "/public/colors.h"

using namespace std;


int main() {
	vector<Crab> allCrabs;

	ifstream file("CrabAgePrediction.csv");
	string currLine;

	getline(file, currLine); //Skip 1st line, just labels the values

	while(getline(file, currLine)) {
		vector<string> params;
		stringstream workingLine(currLine);
		string currParam;
		while (getline(workingLine, currParam, ',')) { //Read 1 parameter from the line
			params.push_back(currParam); //Add parameter to vector
		}
		if (params.size() == 9) { //Safety check in case broken row
			allCrabs.push_back(Crab(params)); //push a new crab into the crabb vector
			//allCrabs.at(allCrabs.size() - 1).printCrab();
		}

	}
	
	Dataset crabSet(allCrabs);

	setcolor(255,215,0);
	cout << "Welcome to the Crab Stats!" << endl;

	cout << "Amount of Crabs by Sex: " << endl;
	setcolor(130,230,170);

	crabSet.sexStats();


	setcolor(255,215,0);
	cout << "Amount of Crabs by Age" << endl;
	setcolor(130,230,170);
	crabSet.ageStats();


	setcolor(255,215,0);
	cout << "A Crab's similarity is determined by how far close their height, diameter, and length are" << endl;


	setcolor(130,230,170);
	crabSet.similarityCheck();


	setcolor(255,255,255);
	return 0;

}
