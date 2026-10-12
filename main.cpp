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

        while (true)
        {
            cout << "\nChoose Between Two Implementations" << endl;
            cout << "[1] Linked List Implementation" << endl;
            cout << "[2] Array List Implementation" << endl;
            cout << "[0] Exit the system" << endl;
            cout << "Your selection: ";
            cin >> selection;

            // validation
            if (!isValidInput() || (selection != 0 && selection != 1 && selection != 2))
            {
                if (selection != 0 && selection != 1 && selection != 2)
                {
                    cout << "Invalid input. Please enter 0, 1 or 2." << endl;
                }
                continue;
            }

            break;
        }

        switch (selection)
        {
        case 1:
        {
            bool stayInSubmenu = true;
            while (stayInSubmenu)
            {
                int subSelection = -1;
                cout << "\nLinked List Program Implementation" << endl;
                cout << "functionality Provided: " << endl;
                cout << "[1] Display all data unsorted with array" << endl;
                cout << "[2] Display all data sort by Age using Bubble Sort" << endl;
                cout << "[3] Display Age Group Medical Cost Analysis" << endl;
                cout << "[0] Return to Menu" << endl;
                cout << "\nInsert a number: ";
                cin >> subSelection;

                // validation
                if (!isValidInput())
                {
                    continue;
                }

                switch (subSelection)
                {
                case 3:
                    // to be implemented
                    break;
                case 2:
                    // to be implemented
                    break;
                case 1:
                    // to be implemented
                    break;
                case 0:
                    cout << "Returning to Main Menu..." << endl;
                    stayInSubmenu = false;
                    break;
                default:
                    cout << "[!] Execution Error......\nPlease Enter a Valid Number......" << endl;
                    break;
                }
            }
            break;
        }
        case 2:
        {
            bool stayInSubMenu = true;
            while (stayInSubMenu)
            {
                int subSelection = -1;
                cout << "\nArray List Program Implementation" << endl;
                cout << "functionality Provided: " << endl;
                cout << "[1] Display all data unsorted with array" << endl;
                cout << "[2] Display all data sort by Age using Bubble Sort" << endl;
                cout << "[3] Display all data sort by Age using Merge Sort" << endl;
                cout << "[4] Display Age Group Medical Cost Analysis" << endl;
                cout << "[0] Return to Main Menu" << endl;
                cout << "\nInsert a number: ";
                cin >> subSelection;

                // validation
                if (!isValidInput())
                {
                    continue;
                }

                switch (subSelection)
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
                    cout << "Returning to Main Menu..." << endl;
                    stayInSubMenu = false;
                    break;
                default:
                    cout << "[!] Execution Error......\nPlease Enter a Valid Number......" << endl;
                    break;
                }
            }
            break;
        }
        case 0:
            cout << "Bye Bye" << endl;
            break;
        }

    } while (selection != 0);

    return 0;
}
