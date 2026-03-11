#pragma once
#include <iostream>
#include <cfloat>
#include <vector>


struct SizeNode {
	//Size Diffs For The Extremes
	double minSizeDiff = DBL_MAX;
	double maxSizeDiff = -DBL_MIN;
	//Size ID's For The Extremes
	int minSizeDiffID1 = -1;
	int minSizeDiffID2 = -1;
	int maxSizeDiffID1 = -1;
	int maxSizeDiffID2 = -1;
	int minAge = -1;
	int maxAge = -1;
};


struct WeightNode {
	//Weight Diffs For The Extremes
	double minWeightDiff = DBL_MAX;
	double maxWeightDiff = -DBL_MIN;
	//Weight ID's For The Extremes
	int minWeightDiffID1 = -1;
	int minWeightDiffID2 = -1;
	int maxWeightDiffID1 = -1;
	int maxWeightDiffID2 = -1;
	int minAge = -1;
	int maxAge = -1;
};
