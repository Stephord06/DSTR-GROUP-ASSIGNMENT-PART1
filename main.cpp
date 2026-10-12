#include "csv_implement.cpp"
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
            cout << "[0] Exit the System" << endl;
            cout << "Your selection: ";
            cin >> selection;

            if (cin.fail() || (selection < 0 || selection > 2))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 0, 1, or 2." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "Functionality Provided: " << endl;
                cout << "[1] Display all data unsorted with array" << endl;
                cout << "[2] Display all data sort by Age using Bubble Sort" << endl;
                cout << "[3] Display Age Group Medical Cost Analysis" << endl;
                cout << "[0] Return to Main Menu" << endl;
                cout << "\nInsert a number: ";
                cin >> subSelection;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;

                switch (subSelection)
                {
                case 3:
                    csv_reader(retrieve_relative_path0(), 3, 1);
                    csv_reader(retrieve_relative_path1(), 3, 1);
                    csv_reader(retrieve_relative_path2(), 3, 1);
                    break;
                case 2:
                    csv_reader(retrieve_relative_path0(), 2, 1);
                    csv_reader(retrieve_relative_path1(), 2, 1);
                    csv_reader(retrieve_relative_path2(), 2, 1);
                    break;
                case 1:
                    csv_reader(retrieve_relative_path0(), 1, 1);
                    csv_reader(retrieve_relative_path1(), 1, 1);
                    csv_reader(retrieve_relative_path2(), 1, 1);
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
            bool stayInSubmenu = true;
            while (stayInSubmenu)
            {
                int subSelection = -1;
                cout << "\nArray List Program Implementation" << endl;
                cout << "Functionality Provided: " << endl;
                cout << "[1] Display all data unsorted with array" << endl;
                cout << "[2] Display all data sort by Age using Bubble Sort" << endl;
                cout << "[3] Display all data sort by Age using Merge Sort" << endl;
                cout << "[4] Display Age Group Medical Cost Analysis" << endl;
                cout << "[0] Return to Main Menu" << endl;
                cout << "\nInsert a number: ";
                cin >> subSelection;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;

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
                    stayInSubmenu = false;
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