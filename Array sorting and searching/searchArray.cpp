#include <iostream>
#include "sortArrayByMedicalCost.hpp"
#include "searchArray.hpp"
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

    
medicalCostDataset search(const medicalCostDataset& arr, const auto& x, const string& type) {
    medicalCostDataset results ;
    results.clear();
    
    for (int i = 0; i < arr.size; i++) {
        bool matches = false;

        if (type == "PatientID") {
            matches = (arr.data[i].patientID == x);
        } 
        else if (type == "CareType") {
            matches = (arr.data[i].careType == x);
        } 
        else if (type == "Age") {
            matches = (arr.data[i].age == stoi(x));
        } 
        else if (type == "LengthOfStay") {
            matches = (arr.data[i].lengthOfStay == stoi(x));
        } 
        else if (type == "BaseCostPerHour") {
            matches = (arr.data[i].baseCostPerHour == stoi(x));
        } 
        else if (type == "DaysVisitsPerYear") {
            matches = (arr.data[i].daysVisitsPerYear == stoi(x));
        } 
        else if (type == "TotalmedicalCost") {
            matches = (arr.data[i].medicalCost == stod(x));
        }

        // If a match is found, append to the output dataset
        if (matches) {
            results.data[results.size] = arr.data[i];
            results.size++;
        }
    }

    return results;    
}

void receiveResponse(const medicalCostDataset& arr) {
    string searchingType ;
    string searchingTarget;
    medicalCostDataset result;
    int searchingGroup;

    int minV;
    int maxV;

    cout << "Enter searching type:" << endl;
    cin >> searchingType;
    cout << "Enter 1 for Search in group data or Enter 2 for specific data" << endl;
    cin >> searchingGroup;
    if (searchingGroup == 1){
        cout << "Give the Age group (e.g. 61-100 or 20-40) :" << endl;
        cout << "first Number :";
        cin >> minV ;
        cout << "SecondNumber:";
        cin >> maxV;

        auto start = std::chrono::high_resolution_clock::now();
        result = ageGroup(minV,maxV,arr);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double,std::nano>(end-start);
        printAllAddedRecords(result,duration.count());
    }
    else if (searchingGroup == 2)
    {
        cout << "Enter searching specific target:" << endl;
        cin >> searchingTarget;
        auto start = std::chrono::high_resolution_clock::now();
        result = search(arr,searchingTarget,searchingType);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double,std::nano>(end-start);
        printAllAddedRecords(result,duration.count());
    }
}

medicalCostDataset ageGroup(const int& minV, const int& maxV,const medicalCostDataset& arr ){
    medicalCostDataset results ;
    results.clear();

    for(int i = 0; i < arr.size ; i++){
        int value = arr.data[i].age;
        if( minV <= value && value <= maxV){
            results.data[results.size] = arr.data[i];
            results.size++;
        }
    }
    return results;
}

void visitDurationThreshold(const int& hours){

}