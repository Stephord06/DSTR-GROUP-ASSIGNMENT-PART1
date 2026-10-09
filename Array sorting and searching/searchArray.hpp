#pragma once
#include "general-tools/datasets-implementation-array.hpp"
#include <iostream>
#include <string>

using namespace std;

void receiveResponse(const arrayDataset& arr);
arrayDataset searchAge(const arrayDataset& arr, const string& x);
arrayDataset searchAgeGroup(const int& minV, const int& maxV,const arrayDataset& arr );

