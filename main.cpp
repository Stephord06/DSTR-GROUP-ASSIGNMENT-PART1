#include "general-tools/datasets-implementation-array.hpp"
#include "Array sorting and searching/sortArrayByMedicalCost.hpp"
#include "Array sorting and searching/searchArray.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;

int main()
{
    int selection = -1;
    arrayDataset dataset;

    //global variable for array bubble sort and linear search

    medicalCostDataset costDataset;
    medicalCostDataset bubbleSortData;
    int choice ;
    

    do
    {
        cout << "\nWelcome to XXX Data System" << endl;
        cout << "Functions Provided: " << endl;
        cout << "[1] Display all data with array" << endl;
        cout << "[2] Display all data with the TotalCost " << endl;
        cout << "[3] Display all data with the TotalCost sort by Bubblesort" << endl;
        cout << "[0] Exit the System" << endl;
        cout << "\nInsert a number to select a function to execute: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
            case 3:
            {
                costDataset = addMedicalCost();

                //calculate execution time start point;
                auto start = std::chrono::high_resolution_clock::now();
                bubbleSortData = bubbleSort(costDataset);
                //calculate execution time end point;
                auto end = chrono::high_resolution_clock::now();
                //calculate duration between end&start;
                auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);
                printAllAddedRecords(bubbleSortData);
                cout << "Bubble Sorting Algorithm execution time: " << duration.count() << "ms" << endl; 
                cout << "Dataset Sorted!!!" << endl;
                
                cout << "Enter any for Exit or  Enter 2 Search Data" << endl;
                cin >> choice;
                if (choice == 2)
                {
                    receiveResponse(bubbleSortData);
                    break;
                }

                else{
                    break;
                }
                break;
            }
            case 2:
            {
                auto start = std::chrono::high_resolution_clock::now();
                costDataset = addMedicalCost();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration<double,std::milli>(end-start);
                printAllAddedRecords(costDataset);
                cout << "execution time: " << duration.count() << "ms" << endl; 

                
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