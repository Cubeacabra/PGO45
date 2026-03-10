#include "dataset.h"
#include <unordered_map>
#include "/public/colors.h"
#include <cmath>

using namespace std;

Dataset::Dataset(vector<Crab> vec) {
	crabs = vec;
}

//Find How Many Crabs There Are Of Each Sex
void Dataset::sexStats() {
	for (const Crab& c : crabs) {
		if (c.getSex() == 'M') {
			males++;
		} else if (c.getSex() == 'F') {
			females++;
		} else if (c.getSex() == 'I') {
			intersex++;
		} else {
			cout << "This was bad input we weren't supposed to get here" << endl;
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
		ages[currAge]++;
	}
}

//Find What Crabs Are Closest In Size (Least Difference Between Their Heights, Diameters, And Lengths)
void Dataset::sizeSimilarityCheck() {
	size_t crabCount = crabs.size();

	//DEBUG: For the for loop at the bottom
	//int currRun = 0;

	for (int i = 0; i < crabCount; i++) {
		for (int j = 0; j < crabCount; j++) {
			//Reference the crabs so not making unneccesary copies
			Crab& crab1 = crabs.at(i);
			Crab& crab2 = crabs.at(j);
			if (crab1 != crab2) { //Don't check crab with itself
				double currDiff = abs(crab1.getLength() - crab2.getLength()) + abs(crab1.getHeight() - crab2.getHeight()) + abs(crab1.getDiameter() - crab2.getDiameter());
				if (minSizeDiff > currDiff) { //Update minDiff if needed
					minSizeDiff = currDiff;
					minSizeDiffID1 = crab1.getCrabID();
					minSizeDiffID2 = crab2.getCrabID();

				} 
				if (maxSizeDiff < currDiff) { //Update maxDiff if needed
					maxSizeDiff = currDiff;
					maxSizeDiffID1 = crab1.getCrabID();
					maxSizeDiffID2 = crab2.getCrabID();
				}
			}

			//DEBUG: To see if it's running all trials, but be warned, this heeeeeecka slows runtime
			//currRun++;
			/*if (currRun % 1000 == 0) {
				cout << "Trial " << currRun << "/" << crabCount*crabCount << endl;
			}*/
		}
	}
}

//Find What Crabs Are Closest In Weight (Their Total Weight, Not Shucked Weight/Viscera Weight/Shell Weight)
void Dataset::weightSimilarityCheck() {
	size_t crabCount = crabs.size();

	//DEBUG: For the for loop at the bottom
	//int currRun = 0;

	for (int i = 0; i < crabCount; i++) {
		for (int j = 0; j < crabCount; j++) {
			//Reference the crabs so not making unneccesary copies
			Crab& crab1 = crabs.at(i);
			Crab& crab2 = crabs.at(j);
			if (crab1 != crab2) { //Don't check crab with itself
				double currDiff = abs(crab1.getWeight() - crab2.getWeight()); 
				if (minWeightDiff > currDiff) { //Update minDiff if needed
					minWeightDiff = currDiff;
					minWeightDiffID1 = crab1.getCrabID();
					minWeightDiffID2 = crab2.getCrabID();

				} 
				if (maxWeightDiff < currDiff) { //Update maxDiff if needed
					maxWeightDiff = currDiff;
					maxWeightDiffID1 = crab1.getCrabID();
					maxWeightDiffID2 = crab2.getCrabID();
				}
			}
			//DEBUG: To see if it's running all trials, but be warned, this heeeeeecka slows runtime
			//currRun++;
			/*if (currRun % 1000 == 0) {
				cout << "Trial " << currRun << "/" << crabCount*crabCount << endl;
			}*/
		}
	}
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
			cout << ages[i];
			setcolor(130,230,170);
			cout << " Crabs that are ";

			setcolor(110, 215, 225);
			cout << i;
			setcolor(130,230,170);

			cout << " years old at a concentration of ";

			setcolor(110, 215, 225);
			cout << ages[i] << "/" << crabs.size() << " (" << (100.0 * ages[i]) / crabs.size() << "%)" << endl; 
			setcolor(130,230,170);
		}
	}
}

//Print the size and Weight Similarity Data
void Dataset::printSimilarity() {
	//Printing is split up so important values stand out
	
	//Min Difference For Size
	setcolor(130,230,170);
	cout << "The minimum difference";
	setcolor(110, 215, 225);
	cout << " (in size) " ;
	setcolor(130,230,170);
	cout << " between crabs is ";
	setcolor(110, 215, 225);
	cout << minSizeDiff;
	setcolor(130,230,170);
	cout << " between crabs " ;
	setcolor(110, 215, 225);
	cout <<  minSizeDiffID1;
	setcolor(130,230,170);
	cout << " and ";
	setcolor(110, 215, 225);
	cout << minSizeDiffID2 << endl;

	//Max Difference For Size
	setcolor(130,230,170);
	cout << "The maximum difference";
	setcolor(110, 215, 225);
	cout << " (in size) " ;
	setcolor(130,230,170);
	cout << " between crabs is ";
	setcolor(110, 215, 225);
	cout << maxSizeDiff;
	setcolor(130,230,170);
	cout << " between crabs " ;
	setcolor(110, 215, 225);
	cout <<  maxSizeDiffID1;
	setcolor(130,230,170);
	cout << " and ";
	setcolor(110, 215, 225);
	cout << maxSizeDiffID2 << endl;


	//Min Difference For Weight
	setcolor(130,230,170);
	cout << "The minimum difference";
	setcolor(110, 215, 225);
	cout << " (in weight) " ;
	setcolor(130,230,170);
	cout << " between crabs is ";
	setcolor(110, 215, 225);
	cout << minWeightDiff;
	setcolor(130,230,170);
	cout << " between crabs " ;
	setcolor(110, 215, 225);
	cout <<  minWeightDiffID1;
	setcolor(130,230,170);
	cout << " and ";
	setcolor(110, 215, 225);
	cout << minWeightDiffID2 << endl;

	//Max Difference For Weight
	setcolor(130,230,170);
	cout << "The maximum difference";
	setcolor(110, 215, 225);
	cout << " (in weight) " ;
	setcolor(130,230,170);
	cout << " between crabs is ";
	setcolor(110, 215, 225);
	cout << maxWeightDiff;
	setcolor(130,230,170);
	cout << " between crabs " ;
	setcolor(110, 215, 225);
	cout <<  maxWeightDiffID1;
	setcolor(130,230,170);
	cout << " and ";
	setcolor(110, 215, 225);
	cout << minWeightDiffID2 << endl;
}
