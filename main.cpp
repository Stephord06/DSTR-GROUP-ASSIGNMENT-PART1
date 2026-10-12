#include "simplifyMain.cpp"
#include <iostream>
#include <limits> 

using namespace std;



int main()
{
    int selection = -1;
    arrayDataset dataset;
    

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
            option4(dataset);
            break;
        case 3:
            option3(dataset);
            break;
        case 2:
            option2(dataset);
            break;
        case 1:
            option1(dataset);
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
