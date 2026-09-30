#include "sortArrayByMedicalCost.hpp"
#include "../general-tools/datasets-implementation-array.hpp" 
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std::chrono;

medicalCostDataset addMedicalCost()
{
    arrayDataset rawDataset = returnDataset(); 
    medicalCostDataset calculatedDataset;
    calculatedDataset.clear();

    for (int i = 0; i < rawDataset.size; i++) {
        const auto &r = rawDataset.data[i];

        RecordWithCost newRecord;
        newRecord.patientID = r.patientID;
        newRecord.age = r.age;
        newRecord.careType = r.careType;
        newRecord.lengthOfStay = r.lengthOfStay;
        newRecord.baseCostPerHour = r.baseCostPerHour;
        newRecord.daysVisitsPerYear = r.daysVisitsPerYear;
        newRecord.medicalCost = (double)r.lengthOfStay * r.baseCostPerHour * r.daysVisitsPerYear;

        calculatedDataset.data[calculatedDataset.size++] = newRecord;
    }

    return calculatedDataset;
}

void printAllAddedRecords(const medicalCostDataset& newdataset, const double& exeTime)
{
    cout << "Load Total Valid Records: " << newdataset.size << "\n" << endl;

    cout << string(100, '=') << endl;
    cout << left << setw(10) << "PatientID" << " | "
         << left << setw(4) << "Age" << " | "
         << left << setw(16) << "CareType" << " | "
         << left << setw(12) << "LengthOfStay" << " | "
         << left << setw(16) << "BaseCostPerHour" << " | "
         << left << setw(18) << "DaysVisitsPerYear" << " | "
         << left << setw(18) << "TotalmedicalCost" << " | "
         << endl;
    cout << string(100, '=') << endl;

    for (int i = 0; i < newdataset.size; ++i)
    {
        const auto &r = newdataset.data[i];
        cout << left << setw(10) << r.patientID << " | "
             << left << setw(4) << r.age << " | "
             << left << setw(16) << r.careType << " | "
             << left << setw(12) << r.lengthOfStay << " | "
             << left << setw(16) << r.baseCostPerHour << " | "
             << left << setw(18) << r.daysVisitsPerYear << " | "
             << left << setw(18) << r.medicalCost << " | "
             << endl;
    }
    cout << " execution time: " << exeTime << " nanoseconds" << endl; 
}

void printAllAddedRecords(const medicalCostDataset& newdataset)
{
    cout << "Load Total Valid Records: " << newdataset.size << "\n" << endl;

    cout << string(100, '=') << endl;
    cout << left << setw(10) << "PatientID" << " | "
         << left << setw(4) << "Age" << " | "
         << left << setw(16) << "CareType" << " | "
         << left << setw(12) << "LengthOfStay" << " | "
         << left << setw(16) << "BaseCostPerHour" << " | "
         << left << setw(18) << "DaysVisitsPerYear" << " | "
         << left << setw(18) << "TotalmedicalCost" << " | "
         << endl;
    cout << string(100, '=') << endl;

    for (int i = 0; i < newdataset.size; ++i)
    {
        const auto &r = newdataset.data[i];
        cout << left << setw(10) << r.patientID << " | "
             << left << setw(4) << r.age << " | "
             << left << setw(16) << r.careType << " | "
             << left << setw(12) << r.lengthOfStay << " | "
             << left << setw(16) << r.baseCostPerHour << " | "
             << left << setw(18) << r.daysVisitsPerYear << " | "
             << left << setw(18) << r.medicalCost << " | "
             << endl;
    }
}

medicalCostDataset bubbleSort(medicalCostDataset& arr){
    int n = arr.size;
    bool swapped;

    for(int i=0 ; i<n-1; i++){
        swapped=false;
        for(int c = 0; c < n-i-1; c++){
            if(arr.data[c].medicalCost > arr.data[c + 1].medicalCost) {
                swap(arr.data[c],arr.data[c+1]);
                swapped = true;
            }
        }
        if(swapped == false){
            break;
        }
    }

    return arr;
}