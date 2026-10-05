#pragma once
#include <iostream>

using namespace std;
using namespace std::chrono;

//only for medicalCostDataset temporary
void receiveResponse(const medicalCostDataset& arr);
medicalCostDataset searchTotalCost(const medicalCostDataset& arr, const string& x);
medicalCostDataset totalCostGroup(const int& minV, const int& maxV,const medicalCostDataset& arr );

