#pragma once
#include "../general-tools/datasets-implementation-array.hpp"

// Copy data from source to destination
void copyDataset(const arrayDataset &source, arrayDataset &destination);

// Use merge sort to sort dataset by Age
void mergeSortByAge(arrayDataset &dataset);
