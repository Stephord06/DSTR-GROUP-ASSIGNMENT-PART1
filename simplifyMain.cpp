#include <windows.h>
#include <psapi.h>
#include "Array sorting and searching/bubbleSortAge.hpp"
#include "Array sorting and searching/mergeSortAge.hpp"
#include "Array sorting and searching/searchArray.hpp"
#include "analysis.hpp"
#include "general-tools/datasets-implementation-array.hpp"
#include <chrono>
#include <iostream>
#include <limits>

using namespace std;

size_t getMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        return pmc.PeakPagefileUsage;
    }
    return 0;
}

bool isValidInput()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    return true;
}

void option1(arrayDataset &dataset)
{
    int choice;

    dataset.clear();
    dataLoadingArray(dataset);
    printAllRecords(dataset);

    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (!isValidInput())
    {
        cout << "Returning to menu." << endl;
        return;
    }

    if (choice == 2)
    {
        receiveResponse(dataset);
    }
}

void option2(arrayDataset &dataset)
{
    int choice;
    arrayDataset bubbleSortData;

    dataset.clear();
    dataLoadingArray(dataset);

    auto start = std::chrono::high_resolution_clock::now();
    size_t memBefore = getMemoryUsage();
    bubbleSortData = bubbleSort(dataset);
    auto end = chrono::high_resolution_clock::now();
    size_t memAfter = getMemoryUsage();

    printAllRecords(bubbleSortData);

    long long deltaBytes =
        static_cast<long long>(memAfter) - static_cast<long long>(memBefore);
    auto duration = chrono::duration<double, std::milli>(end - start);

    cout << "Memory Usage: " << deltaBytes / 1024 << " KB\n";
    cout << "Bubble Sort (Age) execution time: " << duration.count() << " ms"
         << endl;
    cout << "Dataset Sorted!!!" << endl;
    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (!isValidInput())
    {
        cout << "Returning to menu." << endl;
        return;
    }

    if (choice == 2)
    {
        receiveResponse(bubbleSortData);
    }
}

void option3(arrayDataset &dataset)
{
    int choice;

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

    auto duration = chrono::duration<double, std::milli>(end - start);
    long long deltaBytes =
        static_cast<long long>(memAfter) - static_cast<long long>(memBefore);

    cout << "Memory Usage: " << deltaBytes / 1024 << " KB\n";
    cout << "Merge Sort (Age) execution time: " << duration.count() << " ms"
         << endl;
    cout << "Records before: " << dataset.size << " | after: " << sortedCopy.size
         << endl;

    cout << "Enter 2 to Search Data or any other number to Exit: " << endl;
    cin >> choice;

    if (!isValidInput())
    {
        cout << "Returning to menu." << endl;
        return;
    }

    if (choice == 2)
    {
        receiveResponse(sortedCopy);
    }
}

void option4(arrayDataset &dataset)
{
    dataset.clear();
    dataLoadingArray(dataset);

    int subChoice = 0;
    while (true)
    {
        cout << "--- Age Group Analysis Sub-Menu ---" << endl;
        cout << "[1] Display ALL Age Categories Summary" << endl;
        cout << "[2] 0-17 (Children & Adolescents)" << endl;
        cout << "[3] 18-25 (Young Adults / University Students)" << endl;
        cout << "[4] 26-40 (Adults)" << endl;
        cout << "[5] 41-60 (Middle-Aged Adults)" << endl;
        cout << "[6] 61-100 (Seniors / Elderly)" << endl;
        cout << "Select Category (1-6): ";
        cin >> subChoice;

        if (!isValidInput())
        {
            continue;
        }

        if (subChoice < 1 || subChoice > 6)
        {
            cout << "[!] Invalid category selected. Please enter 1 to 6." << endl;
            continue;
        }

        break;
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
    }

    auto end = chrono::high_resolution_clock::now();
    size_t memAfter = getMemoryUsage();

    auto duration = chrono::duration<double, std::milli>(end - start);
    long long deltaBytes =
        static_cast<long long>(memAfter) - static_cast<long long>(memBefore);

    cout << "\nMemory Usage: " << deltaBytes / 1024 << " KB\n";
    cout << "Analysis Execution Time: " << duration.count() << " ms" << endl;
}