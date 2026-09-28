#include "general-tools\datasets-implementation-array.hpp"
#include "general-tools/datasets-implementation-singly-linked-list.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int selection = -1;
    arrayDataset dataset;
    dataLoadingArray(dataset);

    do
    {
        cout << "\nWelcome to XXX Data System" << endl;
        cout << "Functions Provided: " << endl;
        cout << "[1] Display all data with array" << endl;
        cout << "[2] Sorting with Array" << endl;
        cout << "[0] Exit the System" << endl;
        cout << "\nInsert a number to select a function to execute: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case 1:
        {
            dataLoadingArray(dataset);
            printAllRecords(dataset);
            break;
        }
            // The further switches......

        case 0:
        {
            cout << "Bye Bye" << endl;
            break;
        }
        default:
        {
            cout << "[!] Execution Error......\nPlease Enter a Valid Number......";
        }
        }
    } while (selection != 0);

    return 0;
}