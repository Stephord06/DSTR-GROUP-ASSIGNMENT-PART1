#pragma once
#include <iostream>

using namespace std;
using namespace std::chrono;

//only for medicalCostDataset temporary
void receiveResponse(const medicalCostDataset& arr);
medicalCostDataset search(const medicalCostDataset& arr, const auto& x, const string& type );


medicalCostDataset ageGroup(const int& first, const int& second, const medicalCostDataset& arr);
void visitDurationThreshold(const int& hours);
