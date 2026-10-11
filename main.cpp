#include "general-tools/datasets-implementation-array.hpp"
#include "Array sorting and searching/bubbleSortAge.hpp"
#include "Array sorting and searching/searchArray.hpp"
#include "Array sorting and searching/mergeSortAge.hpp"
#include "analysis.hpp"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <limits> 

using namespace std;
using namespace std::chrono;

void option1();
void option2();
void option3();
void option4();

int selection = -1;
arrayDataset dataset;
int choice;

size_t getMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        return pmc.PagefileUsage;
    }
    return 0;
}

int main()
{
    do
    {
        cout << "\nArray Program Implementation" << endl;
        cout << "Functions Provided: " << endl;
        cout << "[1] Display all data unsorted with array" << endl;
        cout << "[2] Display all data sort by Age using Bubble Sort" << endl;
        cout << "[3] Display all data sort by Age using Merge Sort" << endl;
        cout << "[4] Display Age Group Medical Cost Analysis" << endl;
        cout << "[0] Exit the System" << endl;
        cout << "\nInsert a number to select a function to execute: ";
        cin >> selection;
        cout << endl;

        // validation
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            selection = -1;
            continue;
        }

        switch (selection)
        {
        case 4:
            option4();
            break;
        case 3:
            option3();
            break;
        case 2:
            option2();
            break;
        case 1:
            option1();
            break;
        case 0:
            cout << "Bye Bye" << endl;
            break;
        default:
            cout << "[!] Execution Error......\nPlease Enter a Valid Number......" << endl;
            break;
        }
    } while (selection != 0);

    return 0;
}

void option1()
{
    dataset.clear();
    dataLoadingArray(dataset);
    printAllRecords(dataset);

    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Returning to menu." << endl;
        return; 
    }

    if (choice == 2)
    {
        receiveResponse(dataset);
    }
}

void option2()
{
    dataset.clear();
    arrayDataset bubbleSortData;

    if (dataset.size == 0)
    {
        dataLoadingArray(dataset);
    }

    auto start = std::chrono::high_resolution_clock::now();
    size_t memBefore = getMemoryUsage();
    bubbleSortData = bubbleSort(dataset);
    auto end = chrono::high_resolution_clock::now();
    size_t memAfter = getMemoryUsage();

    printAllRecords(bubbleSortData);

    long long deltaBytes = static_cast<long long>(memAfter) - static_cast<long long>(memBefore);
    auto duration = chrono::duration<double, std::milli>(end - start);

    cout << "Memory Gap: " << deltaBytes / 1024 << " KB\n";
    cout << "Bubble Sort (Age) execution time: " << duration.count() << " ms" << endl;
    cout << "Dataset Sorted!!!" << endl;
    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Returning to menu." << endl;
        return; 
    }

    if (choice == 2)
    {
        receiveResponse(bubbleSortData);
    }
}

void option3()
{
    if (dataset.size == 0)
    {
        dataLoadingArray(dataset);
    }

    arrayDataset sortedCopy;
    copyDataset(dataset, sortedCopy);

    size_t memBefore = getMemoryUsage();
    auto start = chrono::high_resolution_clock::now();

    mergeSortByAge(sortedCopy);

    auto end = chrono::high_resolution_clock::now();
    size_t memAfter = getMemoryUsage();

    printAllRecords(sortedCopy);

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    long long deltaBytes = static_cast<long long>(memAfter) - static_cast<long long>(memBefore);

    cout << "Memory Gap: " << deltaBytes / 1024 << " KB\n";
    cout << "Merge Sort (Age) execution time: " << duration.count() << " ms" << endl;
    cout << "Records before: " << dataset.size << " | after: " << sortedCopy.size << endl;

    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Returning to menu." << endl;
        return; 
    }

    if (choice == 2)
    {
        receiveResponse(sortedCopy);
    }
}

void option4()
{
    dataset.clear();
    if (dataset.size == 0)
    {
        dataLoadingArray(dataset);
    }

    int subChoice = 0;
    cout << "--- Age Group Analysis Sub-Menu ---" << endl;
    cout << "[1] Display ALL Age Categories Summary" << endl;
    cout << "[2] 0-17 (Children & Adolescents)" << endl;
    cout << "[3] 18-25 (Young Adults / University Students)" << endl;
    cout << "[4] 26-40 (Adults)" << endl;
    cout << "[5] 41-60 (Middle-Aged Adults)" << endl;
    cout << "[6] 61-100 (Seniors / Elderly)" << endl;
    cout << "Select Category (1-6): ";
    cin >> subChoice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Returning to menu." << endl;
        return; 
    }

    size_t memBefore = getMemoryUsage();
    auto start = chrono::high_resolution_clock::now();

    switch (subChoice)
    {
    case 1:
        analyzeAllAgeGroups(dataset);
        break;
    case 2:
        analyzeAgeGroup(dataset, 0, 17, "Children & Adolescents");
        break;
    case 3:
        analyzeAgeGroup(dataset, 18, 25, "Young Adults / University Students");
        break;
    case 4:
        analyzeAgeGroup(dataset, 26, 40, "Adults");
        break;
    case 5:
        analyzeAgeGroup(dataset, 41, 60, "Middle-Aged Adults");
        break;
    case 6:
        analyzeAgeGroup(dataset, 61, 100, "Seniors / Elderly");
        break;
    default:
        cout << "[!] Invalid category selected." << endl;
        break;
    }

    auto end = chrono::high_resolution_clock::now();
    size_t memAfter = getMemoryUsage();

    auto duration = chrono::duration<double, std::milli>(end - start);
    long long deltaBytes = static_cast<long long>(memAfter) - static_cast<long long>(memBefore);

    cout << "\nMemory Gap: " << deltaBytes / 1024 << " KB\n";
    cout << "Analysis Execution Time: " << duration.count() << " ms" << endl;
}