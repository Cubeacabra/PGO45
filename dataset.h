#pragma once
#include <iostream>
#include <vector>
#include "dataset.h"
#include "crab.h"
#include <unordered_map>
#include <climits>
#include <cfloat>


class Dataset {
private:
	std::vector<Crab> crabs;
	int minAge = INT_MAX;
	int maxAge = 0;
	double minDiff = DBL_MAX;
	double maxDiff = -DBL_MIN;
	int maxDiffID1 = -1;
	int maxDiffID2 = -1;
	int minDiffID1 = -1;
	int minDiffID2 = -1;
	

public:
	Dataset(std::vector<Crab> vec);
	void sexStats();
	void ageStats();
	void similarityCheck();
	void printSimilarity();
};
