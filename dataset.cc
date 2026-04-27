#include "dataset.h"
#include <cstddef>
#include <unordered_map>
#include "/public/colors.h"
#include <cmath>
#include "node.h"
#include <algorithm>
#include <omp.h>

using namespace std;

Dataset::Dataset(vector<Crab> vec) {
	crabs = vec;
}

//Find How Many Crabs There Are Of Each Sex
void Dataset::sexStats() {
	for (const Crab& c : crabs) {
		//cout << c.getSex() << endl;
		if (c.getSex() == 'M') {
			males++;
		} else if (c.getSex() == 'F') {
			females++;
		} else if (c.getSex() == 'I') {
			intersex++;
		} else {
	//		cout << "This was bad input we weren't supposed to get here" << endl;
	//		cout << "input was " << c.getSex() << " on crab number " << c.getCrabID() << endl;
		}
	}
}


//Find How Many Crabs There Are At Each Age
void Dataset::ageStats() {
	for (const Crab& c : crabs) {
		int currAge = c.getAge();
		if (minAge > currAge) {//Change minAge If Needed
			minAge = currAge;
		} 
		if (maxAge < currAge) { //Change maxAge If Needed
			maxAge = currAge;
		}	
		ages[currAge].push_back(c);
	}
	//checkSimilaritiesByAge();
}

void Dataset::checkSimilaritiesByAge() {
	for (int i = minAge; i <= maxAge; i++) {
		if (ages.find(i) != ages.end()) {
			sizeSimilarityCheck(ages[i]);
			weightSimilarityCheck(ages[i]);
		}
		//cout << "cow" << endl;
	}
}

//Find What Crabs Are Closest In Size (Least Difference Between Their Heights, Diameters, And Lengths)
void Dataset::sizeSimilarityCheck(vector<Crab>& crabsOneAge) {
	size_t crabCount = min(crabsOneAge.size(),static_cast<size_t>(20000));
	

	if (crabCount < 2) return;
	SizeNode result;
	
	if (crabCount < 15000) {
		result.minAge = crabsOneAge.at(0).getAge();
		result.maxAge = crabsOneAge.at(0).getAge();
	}

	

	//DEBUG: For the for loop at the bottom
	//int currRun = 0;
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < crabCount; i++) {
		for (int j = 0; j < crabCount; j++) {
			//Reference the crabs so not making unneccesary copies
			Crab& crab1 = crabsOneAge.at(i);
			Crab& crab2 = crabsOneAge.at(j);
			if (crab1 != crab2) { //Don't check crab with itself
				double currDiff = abs(crab1.getLength() - crab2.getLength()) + abs(crab1.getHeight() - crab2.getHeight()) + abs(crab1.getDiameter() - crab2.getDiameter());
				if (result.minSizeDiff > currDiff) { //Update minDiff if needed
					result.minSizeDiff = currDiff;
					result.minSizeDiffID1 = crab1.getCrabID();
					result.minSizeDiffID2 = crab2.getCrabID();
				} 
				if (result.maxSizeDiff < currDiff) { //Update maxDiff if needed
					result.maxSizeDiff = currDiff;
					result.maxSizeDiffID1 = crab1.getCrabID();
					result.maxSizeDiffID2 = crab2.getCrabID();
				}
			}
			//DEBUG: To see if it's running all trials, but be warned, this heeeeeecka slows runtime
			//currRun++;
			/*if (currRun % 1000 == 0) {
				cout << "Trial " << currRun << "/" << crabCount*crabCount << endl;
			}*/
		}
	}
	sizeSimilarityResults.push_back(result);
}

//Find What Crabs Are Closest In Weight (Their Total Weight, Not Shucked Weight/Viscera Weight/Shell Weight)
void Dataset::weightSimilarityCheck(vector<Crab>& crabsOneAge) {
	size_t crabCount = min(crabsOneAge.size(),static_cast<size_t>(20000));

	if (crabCount < 2) return;
	WeightNode result;
	if (crabCount < 15000) {
		result.minAge = crabsOneAge.at(0).getAge();
		result.maxAge = crabsOneAge.at(0).getAge();
	}

	//DEBUG: For the for loop at the bottom
	//int currRun = 0;
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < crabCount; i++) {
		for (int j = 0; j < crabCount; j++) {
			//Reference the crabs so not making unneccesary copies
			Crab& crab1 = crabs.at(i);
			Crab& crab2 = crabs.at(j);
			if (crab1 != crab2) { //Don't check crab with itself
				double currDiff = abs(crab1.getWeight() - crab2.getWeight()); 
				if (result.minWeightDiff > currDiff) { //Update minDiff if needed
					result.minWeightDiff = currDiff;
					result.minWeightDiffID1 = crab1.getCrabID();
					result.minWeightDiffID2 = crab2.getCrabID();
						
				} 
				if (result.maxWeightDiff < currDiff) { //Update maxDiff if needed
					result.maxWeightDiff = currDiff;
					result.maxWeightDiffID1 = crab1.getCrabID();
					result.maxWeightDiffID2 = crab2.getCrabID();
						
				}
			}
			//DEBUG: To see if it's running all trials, but be warned, this heeeeeecka slows runtime
			//currRun++;
			/*if (currRun % 1000 == 0) {
				cout << "Trial " << currRun << "/" << crabCount*crabCount << endl;
			}*/
		}
	}
	weightSimilarityResults.push_back(result);
}


void Dataset::printSexStats() {
	//Printing is split up so important values stand out
	//Males
	setcolor(130,230,170);
	cout << "Total Males: "; 
	setcolor(110, 215, 225);
	cout << males;
	setcolor(130,230,170);
	cout << " at a concentration of ";
	setcolor(110, 215, 225);
	cout << males << "/" << crabs.size() << " (" << (100.0 * males) / crabs.size() << "%)" << endl; 
	setcolor(130,230,170);

	//Females
	setcolor(130,230,170);
	cout << "Total Females: "; 
	setcolor(110, 215, 225);
	cout << females;
	setcolor(130,230,170);
	cout << " at a concentration of ";
	setcolor(110, 215, 225);
	cout << females << "/" << crabs.size() << " (" << (100.0 * females) / crabs.size() << "%)" << endl; 
	setcolor(130,230,170);

	//Intersex
	setcolor(130,230,170);
	cout << "Total Intersex: "; 
	setcolor(110, 215, 225);
	cout << intersex;
	setcolor(130,230,170);
	cout << " at a concentration of ";
	setcolor(110, 215, 225);
	cout << intersex << "/" << crabs.size() << " (" << (100.0 * intersex) / crabs.size() << "%)" << endl; 
	setcolor(130,230,170);
}


void Dataset::printAgeStats() {
	//Printing is split up so important values stand out
	for (int i = minAge; i <= maxAge; i++) {
		if (ages.find(i) != ages.end()) { //Print the data and have the actual numbers colored different to be read easier
			setcolor(130,230,170);
			cout << "There are "; 
			setcolor(110, 215, 225);
			cout << ages[i].size();
			setcolor(130,230,170);
			cout << " Crabs that are ";

			setcolor(110, 215, 225);
			cout << i;
			setcolor(130,230,170);

			cout << " years old at a concentration of ";

			setcolor(110, 215, 225);
			cout << ages[i].size() << "/" << crabs.size() << " (" << (100.0 * ages[i].size()) / crabs.size() << "%)" << endl; 
			setcolor(130,230,170);
		}
	}
}

//Print the size and Weight Similarity Data
void Dataset::printSimilarity() {
	//Printing is split up so important values stand out
	//	cout << sizeSimilarityResults.size() << " SIZE OF SIM RESULTS " << endl;
	//	cerr << "b4 loop, minAge is " << minAge << " and maxAge is " << maxAge << endl;



	int resultIndex = 0;
	bool seenAllCrabs = false;
	for (int i = minAge; i <= maxAge; i++) {
		if (ages.find(i) != ages.end()) {
			if (resultIndex >= sizeSimilarityResults.size()) break;
			setcolor(255,215,0);
			if (sizeSimilarityResults.at(resultIndex).maxAge == -1) {
				if (!seenAllCrabs) {
					cout << "Similarity Between First 20k Crabs" << endl;
					seenAllCrabs = true;
				} else {
					continue;
				}
			} else {
				cout << "Similarity of Crabs Aged " << sizeSimilarityResults.at(resultIndex).maxAge << endl;
			}
			//cout << "Similarity of Crabs Aged " << sizeSimilarityResults.at(resultIndex).minAge << endl;
			//Min Difference For Size
			setcolor(130,230,170);
			cout << "The minimum difference";
			setcolor(110, 215, 225);
			cout << " (in size) " ;
			setcolor(130,230,170);
			cout << " between crabs is ";
			setcolor(110, 215, 225);
			cout << sizeSimilarityResults.at(resultIndex).minSizeDiff;
			setcolor(130,230,170);
			cout << " between crabs " ;
			setcolor(110, 215, 225);
			cout <<  sizeSimilarityResults.at(resultIndex).minSizeDiffID1;
			setcolor(130,230,170);
			cout << " and ";
			setcolor(110, 215, 225);
			cout << sizeSimilarityResults.at(resultIndex).minSizeDiffID2 << endl;


			//Max Difference For Size
			setcolor(130,230,170);
			cout << "The maximum difference";
			setcolor(110, 215, 225);
			cout << " (in size) " ;
			setcolor(130,230,170);
			cout << " between crabs is ";
			setcolor(110, 215, 225);
			cout << sizeSimilarityResults.at(resultIndex).maxSizeDiff;
			setcolor(130,230,170);
			cout << " between crabs " ;
			setcolor(110, 215, 225);
			cout <<  sizeSimilarityResults.at(resultIndex).maxSizeDiffID1;
			setcolor(130,230,170);
			cout << " and ";
			setcolor(110, 215, 225);
			cout << sizeSimilarityResults.at(resultIndex).maxSizeDiffID2 << endl;

	/*		//Min Difference For Weight
			setcolor(130,230,170);
			cout << "The minimum difference";
			setcolor(110, 215, 225);
			cout << " (in weight) " ;
			setcolor(130,230,170);
			cout << " between crabs is ";
			setcolor(110, 215, 225);
			cout << weightSimilarityResults.at(resultIndex).minWeightDiff;
			setcolor(130,230,170);
			cout << " between crabs " ;
			setcolor(110, 215, 225);
			cout <<  weightSimilarityResults.at(resultIndex).minWeightDiffID1;
			setcolor(130,230,170);
			cout << " and ";
			setcolor(110, 215, 225);
			cout << weightSimilarityResults.at(resultIndex).minWeightDiffID2 << endl;


			//Max Difference For Weight
			setcolor(130,230,170);
			cout << "The maximum difference";
			setcolor(110, 215, 225);
			cout << " (in weight) " ;
			setcolor(130,230,170);
			cout << " between crabs is ";
			setcolor(110, 215, 225);
			cout << weightSimilarityResults.at(resultIndex).maxWeightDiff;
			setcolor(130,230,170);
			cout << " between crabs " ;
			setcolor(110, 215, 225);
			cout <<  weightSimilarityResults.at(resultIndex).maxWeightDiffID1;
			setcolor(130,230,170);
			cout << " and ";
			setcolor(110, 215, 225);
			cout << weightSimilarityResults.at(resultIndex).minWeightDiffID2 << endl;
	*/		resultIndex++;
		}
	}
}
