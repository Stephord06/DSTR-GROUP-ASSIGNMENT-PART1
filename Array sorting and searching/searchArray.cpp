#include <iostream>
#include "bubbleSortAge.hpp"
#include "searchArray.hpp"
#include "general-tools/datasets-implementation-array.hpp"
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

    
arrayDataset searchAge(const arrayDataset& arr, const string& x) {
    arrayDataset results ;
    results.clear();
    
    for (int i = 0; i < arr.size; i++) {
        bool matches = false;
        matches = (arr.data[i].age == stoi(x));
        // If a match is found, append to the output dataset
        if (matches) {
            results.data[results.size] = arr.data[i];
            results.size++;
        }
    }

    return results;    
}

arrayDataset searchAgeGroup(const int& minV, const int& maxV,const arrayDataset& arr ){
    arrayDataset results ;
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

void receiveResponse(const arrayDataset& arr) {
    string searchingTarget;
    arrayDataset result;
    int searching;

    int minV;
    int maxV;

    cout << "Your are searching data based on Age" << endl;
    cout << "Enter 1 for searching by Age or 2 for searching by Age Group: ";
    cin >> searchingTarget;
    searching = stoi(searchingTarget);
    if(searching == 1){
        cout << "Give the Age to search: ";
        cin >> searchingTarget;
        auto start = std::chrono::high_resolution_clock::now();
        result = searchAge(arr, searchingTarget);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        double microseconds = duration.count() / 1000.0;

        printAllRecords(result);
        cout << "Linear Search execution time: " << microseconds << " us" << endl;
    }
    else if(searching == 2){
        cout << "Give the Age group (e.g. 20-40, 30-50) :" << endl;
        cout << "first Number :";
        cin >> minV ;
        cout << "SecondNumber:";
        cin >> maxV;

        auto start = std::chrono::high_resolution_clock::now();
        result = searchAgeGroup(minV,maxV,arr);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        double microseconds = duration.count() / 1000.0; 
        
        printAllRecords(result);
        cout << "Linear Search execution time: " << microseconds << " us" << endl;
    }
    else {
        cout << "Invalid selection. Please enter 1 or 2." << endl;
        return;
    } 
}        



