#pragma once
#include <iostream>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

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
    int size = 0;
    RecordWithCost data[1000]; 
    void clear() { size = 0; }
};

medicalCostDataset addMedicalCost();
void printAllAddedRecords(const medicalCostDataset& newdataset, const double& exeTime);
void printAllAddedRecords(const medicalCostDataset& newdataset);

medicalCostDataset bubbleSort(medicalCostDataset& arr);