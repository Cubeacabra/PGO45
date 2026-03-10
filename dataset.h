#pragma once
#include <iostream>
#include <vector>
#include "dataset.h"
#include "crab.h"
#include <unordered_map>
#include <climits>
#include <cfloat>
#include <unordered_map>

class Dataset {
private:
	//Holds All Crabs
	std::vector<Crab> crabs;
	//Amount of Each Sex of Crab
	int females = 0;
	int males = 0;
	int intersex = 0;
	//Age Extremes
	int minAge = INT_MAX;
	int maxAge = 0;
	//Key is age, valye is how many crabs at that age 
	std::unordered_map<int, int> ages;
	//Size Diffs For The Extremes
	double minSizeDiff = DBL_MAX;
	double maxSizeDiff = -DBL_MIN;
	//Weight Diffs For The Extremes
	double minWeightDiff = DBL_MAX;
	double maxWeightDiff = -DBL_MIN;
	//Size ID's For The Extremes
	int minSizeDiffID1 = -1;
	int minSizeDiffID2 = -1;
	int maxSizeDiffID1 = -1;
	int maxSizeDiffID2 = -1;
	//Weight ID's For The Extremes
	int minWeightDiffID1 = -1;
	int minWeightDiffID2 = -1;
	int maxWeightDiffID1 = -1;
	int maxWeightDiffID2 = -1;
	

public:
	Dataset(std::vector<Crab> vec);
	//Data Analysis
	void sexStats();
	void ageStats();
	void sizeSimilarityCheck();
	void weightSimilarityCheck();
	
	//Print Functions
	void printSexStats();
	void printAgeStats();
	void printSimilarity();
};
