#include <iostream>
#include "sortArrayByMedicalCost.hpp"
#include "searchArray.hpp"
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

    
medicalCostDataset searchTotalCost(const medicalCostDataset& arr, const string& x, const string& type) {
    medicalCostDataset results ;
    results.clear();
    
    for (int i = 0; i < arr.size; i++) {
        bool matches = false;
        if (type == "TotalmedicalCost") {
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
    int searching;

    int minV;
    int maxV;

    cout << "Your are searching data based on Total Cost" << endl;
    cout << "Enter 1 for Search in group data or Enter 2 for specific data" << endl;
    cin >> searching;
    if (searching == 1){
        cout << "Give the TotalCost group (e.g. 20000-50000, 30000-40000) :" << endl;
        cout << "first Number :";
        cin >> minV ;
        cout << "SecondNumber:";
        cin >> maxV;

        auto start = std::chrono::high_resolution_clock::now();
        result = totalCostGroup(minV,maxV,arr);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        double microseconds = duration.count() / 1000.0;

        printAllAddedRecords(result, microseconds);
        
    }
    else if (searching == 2)
    {
        cout << "Enter searching specific target:" << endl;
        cin >> searchingTarget;
        auto start = std::chrono::high_resolution_clock::now();
        result = searchTotalCost(arr, searchingTarget, "TotalmedicalCost");
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        double microseconds = duration.count() / 1000.0;
        printAllAddedRecords(result, microseconds);
    }
}        

medicalCostDataset totalCostGroup(const int& minV, const int& maxV,const medicalCostDataset& arr ){
    medicalCostDataset results ;
    results.clear();

    for(int i = 0; i < arr.size ; i++){
        int value = arr.data[i].medicalCost;
        if( minV <= value && value <= maxV){
            results.data[results.size] = arr.data[i];
            results.size++;
        }
    }
    return results;
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