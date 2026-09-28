#pragma once
#include <string>

using namespace std;

struct record
{
    string patientID, careType;
    int age, lengthOfStay, baseCostPerHour, daysVisitsPerYear;
};

struct arrayDataset {
    record data[1000]; 
    int size = 0;
    void clear() { size = 0; }
};


void dataLoadingArray(arrayDataset &dataset);
arrayDataset returnDataset();
void printAllRecords(const arrayDataset &dataset);