#pragma once
#include <iostream>
#include <vector>
#include "dataset.h"
#include "crab.h"
#include <unordered_map>
#include <climits>

class Dataset {
private:
	std::vector<Crab> crabs;
	int minAge = INT_MAX;
	int maxAge = 0;
	

public:
	Dataset(std::vector<Crab> vec);
	void sexStats();
	void ageStats();
	void similarityCheck();
};
