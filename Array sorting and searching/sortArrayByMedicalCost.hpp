#pragma once
#include <iostream>

using namespace std;

struct RecordWithCost
{
    string patientID;
    string careType;
    int age;
    int lengthOfStay;
    int baseCostPerHour;
    int daysVisitsPerYear;
    double medicalCost;
};

struct medicalCostDataset
{
    int size;
    RecordWithCost data[1000]; 
    void clear() { size = 0; }
};

medicalCostDataset addMedicalCost();
void printAllAddedRecords(const medicalCostDataset newdataset);