#include "general-tools/datasets-implementation-array.hpp"
#include "Array sorting and searching/sortArrayByMedicalCost.hpp"
#include "Array sorting and searching/searchArray.hpp"
#include "Array sorting and searching/sortArrayByAge.hpp"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h> 

using namespace std::chrono;

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        // PagefileUsage represents Private Bytes, which is sensitive to exact byte allocations
        return pmc.PagefileUsage; 
    }
    return 0;
}


int main()
{
    int selection = -1;
    arrayDataset dataset;

    // global variable for array bubble sort and linear search

    medicalCostDataset costDataset;
    medicalCostDataset bubbleSortData;
    int choice;

    do
    {
        cout << "\nWelcome to XXX Data System" << endl;
        cout << "Functions Provided: " << endl;
        cout << "[1] Display all data with array" << endl;
        cout << "[2] Display all data with the TotalCost " << endl;
        cout << "[3] Display all data with the TotalCost sort by Bubblesort" << endl;
        cout << "[4] Display all data sort by Age using Merge Sort" << endl;
        cout << "[0] Exit the System" << endl;
        cout << "\nInsert a number to select a function to execute: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case 4:
        {
            // load data at once
            if (dataset.size == 0)
            {
                dataLoadingArray(dataset);
            }

            arrayDataset *sortedCopy = new arrayDataset;
            copyDataset(dataset, *sortedCopy);

            size_t memBefore = getMemoryUsage();
            auto start = chrono::high_resolution_clock::now();
            mergeSortByAge(*sortedCopy);
            auto end = chrono::high_resolution_clock::now();
            size_t memAfter = getMemoryUsage();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

            long long deltaBytes = static_cast<long long>(memAfter) - static_cast<long long>(memBefore);
            
            printAllRecords(*sortedCopy);
            cout << "Memory Gap: " << deltaBytes / 1024 << " KB\n"; // Output explicitly in KB
            cout << "Merge Sort (Age) execution time: " << duration.count() << " us" << endl;
            cout << "Records before: " << dataset.size << " | after: " << sortedCopy->size << endl;

            delete sortedCopy;
            break;
        }

        case 3:
        {
            costDataset = addMedicalCost();

            // calculate execution time start point;
            auto start = std::chrono::high_resolution_clock::now();
            size_t memBefore = getMemoryUsage();
            bubbleSortData = bubbleSort(costDataset);
            size_t memAfter = getMemoryUsage();
            // calculate execution time end point;
            auto end = chrono::high_resolution_clock::now();
            // calculate duration between end&start;
            long long deltaBytes = static_cast<long long>(memAfter) - static_cast<long long>(memBefore);
            auto duration = chrono::duration<double, std::micro>(end - start);
            printAllAddedRecords(bubbleSortData);
            cout << "Memory Gap: " << deltaBytes / 1024 << " KB\n";
            cout << "Bubble Sorting Algorithm execution time: " << duration.count() << " us" << endl;
            cout << "Dataset Sorted!!!" << endl;

            cout << "Enter any for Exit or  Enter 2 Search Data" << endl;
            cin >> choice;
            if (choice == 2)
            {
                receiveResponse(bubbleSortData);
                break;
            }

            else
            {
                break;
            }
            break;
        }

        case 2:
        {
            auto start = std::chrono::high_resolution_clock::now();
            costDataset = addMedicalCost();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration<double, std::micro>(end - start);
            printAllAddedRecords(costDataset);
            cout << "execution time: " << duration.count() << " us" << endl;

            break;
        }

        case 1:
        {
            dataLoadingArray(dataset);
            printAllRecords(dataset);
            break;
        }

        case 0:
        {
            cout << "Bye Bye" << endl;
            break;
        }

        default:
        {
            cout << "[!] Execution Error......\nPlease Enter a Valid Number......" << endl;
            break;
        }
        }
    } while (selection != 0);

    return 0;
}