#include "general-tools/datasets-implementation.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int selection = -1;
    vector<record> myRecords;
    dataLoading(myRecords);

    do
    {
        cout << "\nWelcome to XXX Data System" << endl;
        cout << "Functions Provided: " << endl;
        cout << "[1] Display all implemented data from datasets" << endl;
        cout << "[2] Sorting with Array" << endl;
        cout << "[0] Exit the System" << endl;
        cout << "\nInsert a number to select a function to execute: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case 1:
        {
            printAllRecords(myRecords);
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