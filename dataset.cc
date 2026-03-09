#include "dataset.h"
#include <unordered_map>
#include "/public/colors.h"

using namespace std;

Dataset::Dataset(vector<Crab> vec) {
	crabs = vec;
}

void Dataset::sexStats() {
	int females = 0;
	int males = 0;
	int intersex = 0;
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
	cout << "Total Males: " << males << " at a concentration of " << males << "/" << crabs.size() << " (" << (100.0 * males) / crabs.size() << "%)" << endl; 
	cout << "Total Females: " << females << " at a concentration of " << females << "/" << crabs.size() << " (" << (100.0 * females) / crabs.size() << "%)" << endl; 
	cout << "Total Intersex: " << intersex << " at a concentration of " << intersex << "/" << crabs.size() << " (" << (100.0 * intersex) / crabs.size() << "%)" << endl; 
}


void Dataset::ageStats() {
	unordered_map<int, int> ages;
	for (const Crab& c : crabs) {
		int currAge = c.getAge();
		if (minAge > currAge) {
			minAge = currAge;
		} 
		if (maxAge < currAge) {
			maxAge = currAge;
		}	
	
		//cout << "Age at " << c.getAge() << " before was " << ages[c.getAge()] << endl;
		ages[currAge]++;
		//cout << "Age  after was " << ages[c.getAge()] << endl;
	}
	for (int i = minAge; i <= maxAge; i++) {
		if (ages.find(i) != ages.end()) { //Print the data and have the actual numbers colored different to be read easier
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


void Dataset::similarityCheck() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			cout << "dog collar" << endl;
		}
	}
}

