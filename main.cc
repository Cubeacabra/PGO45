#include "crab.h"
#include "dataset.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ratio>
#include <vector>
#include <sstream>
#include "/public/colors.h"
#include <chrono>

using namespace std;
using namespace std::chrono;
using sc = steady_clock;

int main() {
	vector<Crab> allCrabs;

	//ifstream file("CrabAgePrediction.csv");
	ifstream file("train_extended.csv");
	string currLine;

	/*if(file) {
		cout << "IT OPENED GOOOD CHAT" << endl;
	} else {
		exit(EXIT_FAILURE);
	}*/

	getline(file, currLine); //Skip 1st line, just labels the values
	int currID = 0;
	auto start = sc::now(); //start logging time
	while(getline(file, currLine)) {
	//	cout << "this line reached" << endl;
		vector<string> params;
		stringstream workingLine(currLine);
		string currParam;
		while (getline(workingLine, currParam, ',')) { //Read 1 parameter from the line
			params.push_back(currParam); //Add parameter to vector
	//	cout << "this line reached" << endl;
		}
//		if (currID == 0) {
//			for (string p : params) {
//				cout << p << endl;
//			}
//		}
		if (params.size() == 10) { //Safety check in case broken row
			allCrabs.push_back(Crab(params/*, currID*/)); //push a new crab into the crabb vector
			//allCrabs.at(allCrabs.size() - 1).printCrab();
			currID++;
		}

	}
	auto end = sc::now(); //end logging time
	cerr << "Loop_1:" << (duration<double, milli>(end - start)).count() << "ms" << endl; //print time of this loop

	
	Dataset crabSet(allCrabs);



	setcolor(255,215,0);
	cout << "Welcome to the Crab Stats!" << endl;
	setcolor(190,135,160);
	cout << "Calculating Crab Stats..." << endl;

	//Run The Data Analysis Functions

	auto start_2 = sc::now(); //start logging time

	crabSet.sexStats();
	crabSet.ageStats();
	//for (int i = 0; i < 10; i++) {
		crabSet.sizeSimilarityCheck(allCrabs);
	//	crabSet.weightSimilarityCheck(allCrabs);
	
//	}
	auto end_2 = sc::now(); //end logging time
	cerr << "Loop_2:" << (duration<double, milli>(end_2 - start_2)).count() << "ms:" << endl; //print time of this loop


	//Print The Data
	setcolor(255,215,0);
	cout << "Amount of Crabs by Sex: " << endl;
	setcolor(130,230,170);
	crabSet.printSexStats();

	setcolor(255,215,0);
	cout << "Amount of Crabs by Age" << endl;
	setcolor(130,230,170);
	crabSet.printAgeStats();

	setcolor(255,215,0);
	cout << "Crab Similarity" << endl;
	setcolor(130,230,170);
	crabSet.printSimilarity();

	setcolor(255,255,255);
	return 0;

}
