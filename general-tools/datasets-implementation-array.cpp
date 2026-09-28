#include "datasets-implementation-array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void dataLoadingArray(arrayDataset &dataset)
{
    dataset.clear();
    
    cout << "Entered Data Loading Methodology" << endl;

    string filePath[3] = {
        "datasets/dataset1 facility_a.csv",
        "datasets/dataset2 facility_b.csv",
        "datasets/dataset3_facility_c.csv"};

    for (int i = 0; i < 3; i++)
    {
        ifstream file(filePath[i]);
        string line;

        if (!file.is_open())
        {
            cout << "[!] File Open Error: " << filePath[i] << endl;
            continue;
        }

        while (getline(file, line))
        {
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            if (line.empty())
            {
                continue;
            }

            if (line.size() >= 3 && (unsigned char)line[0] == 0xEF &&
                (unsigned char)line[1] == 0xBB &&
                (unsigned char)line[2] == 0xBF)
            {
                line.erase(0, 3);
            }

            stringstream ss(line);
            string patientField, ageField, careField, lengthField, baseField, dayField;

            if (getline(ss, patientField, ',') &&
                getline(ss, ageField, ',') &&
                getline(ss, careField, ',') &&
                getline(ss, lengthField, ',') &&
                getline(ss, baseField, ',') &&
                getline(ss, dayField, ','))
            {
                if (patientField == "patientID" || patientField == "PatientID" || ageField == "Age")
                {
                    continue;
                }
                try
                {
                    if (dataset.size >= 3000){
                        cout << "[!] Warning: Array Capacity limit (3000) reached......" << endl;
                        break;
                    }

                    record r;
                    r.patientID = patientField;
                    r.age = stoi(ageField);
                    r.careType = careField;
                    r.lengthOfStay = stoi(lengthField);
                    r.baseCostPerHour = stoi(baseField);
                    r.daysVisitsPerYear = stoi(dayField);
                    dataset.data[dataset.size++] = r;
                }
                catch (...)
                {
                }
            }
        }
    }
}

arrayDataset returnDataset()
{
    arrayDataset dataset;
    dataLoadingArray(dataset);
    return dataset;
}

void printAllRecords(const arrayDataset &dataset)
{
    cout << "Load Total Valid Records: " << dataset.size << "\n" << endl;

    cout << string(100, '=') << endl;
    cout << left << setw(10) << "PatientID" << " | "
         << left << setw(4) << "Age" << " | "
         << left << setw(16) << "CareType" << " | "
         << left << setw(12) << "LengthOfStay" << " | "
         << left << setw(16) << "BaseCostPerHour" << " | "
         << left << setw(18) << "DaysVisitsPerYear" << " | "
         << endl;
    cout << string(100, '=') << endl;

    for (int i = 0; i < dataset.size; ++i)
    {
        const auto &r = dataset.data[i];
        cout << left << setw(10) << r.patientID << " | "
             << left << setw(4) << r.age << " | "
             << left << setw(16) << r.careType << " | "
             << left << setw(12) << r.lengthOfStay << " | "
             << left << setw(16) << r.baseCostPerHour << " | "
             << left << setw(18) << r.daysVisitsPerYear << " | "
             << endl;
    }
}