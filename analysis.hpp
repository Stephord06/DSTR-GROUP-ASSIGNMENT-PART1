#pragma once
#include "Array sorting and searching/sortArrayByMedicalCost.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

struct CareTypeSummary {
    string careType;
    int patientCount = 0;
    double totalCost = 0.0;
};

struct AgeCategory {
    int minAge;
    int maxAge;
    string label;
};

// Formats numbers into currency format (e.g., 25000.00 -> 25,000.00)
inline string formatCurrency(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    string str = ss.str();

    size_t dotPos = str.find('.');
    int insertPos = (dotPos == string::npos) ? (int)str.length() - 3 : (int)dotPos - 3;

    while (insertPos > 0) {
        str.insert(insertPos, ",");
        insertPos -= 3;
    }
    return str;
}

// Single Age Group Analysis
inline void analyzeAgeGroup(const medicalCostDataset& dataset, int minAge, int maxAge, const string& groupLabel) {
    CareTypeSummary summaries[100];
    int summaryCount = 0;
    double grandTotalBilling = 0.0;

    for (int i = 0; i < dataset.size; i++) {
        const auto& record = dataset.data[i];

        if (record.age >= minAge && record.age <= maxAge) {
            grandTotalBilling += record.medicalCost;

            int foundIndex = -1;
            for (int j = 0; j < summaryCount; j++) {
                if (summaries[j].careType == record.careType) {
                    foundIndex = j;
                    break;
                }
            }

            if (foundIndex != -1) {
                summaries[foundIndex].patientCount++;
                summaries[foundIndex].totalCost += record.medicalCost;
            } else {
                summaries[summaryCount].careType = record.careType;
                summaries[summaryCount].patientCount = 1;
                summaries[summaryCount].totalCost = record.medicalCost;
                summaryCount++;
            }
        }
    }

    cout << "\nAge Group: " << minAge << "-" << maxAge << " (" << groupLabel << ")" << endl;
    cout << string(80, '-') << endl;

    if (summaryCount == 0) {
        cout << "No patient records found for this age category." << endl;
        cout << string(80, '-') << endl;
        return;
    }

    cout << left << setw(20) << "Care Type"
         << left << setw(16) << "Patient Count"
         << left << setw(18) << "Total Cost ($)"
         << left << setw(26) << "Average Cost per Patient ($)" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < summaryCount; i++) {
        double avgCost = (summaries[i].patientCount > 0) ? (summaries[i].totalCost / summaries[i].patientCount) : 0.0;

        cout << left << setw(20) << summaries[i].careType
             << left << setw(16) << summaries[i].patientCount
             << left << setw(18) << formatCurrency(summaries[i].totalCost)
             << left << setw(26) << formatCurrency(avgCost) << endl;
    }

    cout << string(80, '-') << endl;
    cout << "Total Billing for Age Group: $" << formatCurrency(grandTotalBilling) << endl;
}

// Generates report for ALL age categories at once
inline void analyzeAllAgeGroups(const medicalCostDataset& dataset) {
    AgeCategory categories[] = {
        {0, 17, "Children & Adolescents"},
        {18, 25, "Young Adults / University Students"},
        {26, 40, "Adults"},
        {41, 60, "Middle-Aged Adults"},
        {61, 120, "Seniors / Elderly"}
    };
    int numCategories = sizeof(categories) / sizeof(categories[0]);

    for (int i = 0; i < numCategories; i++) {
        analyzeAgeGroup(dataset, categories[i].minAge, categories[i].maxAge, categories[i].label);
    }
}