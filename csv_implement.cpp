#include "linked_list.cpp"
#include <cctype>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  const char *dataset0 =
      "DSTR-GROUP-ASSIGNMENT-PART1/datasets/dataset1 facility_a.csv";
  const char *dataset1 =
      "DSTR-GROUP-ASSIGNMENT-PART1/datasets/dataset2 facility_b.csv";
  const char *dataset2 =
      "DSTR-GROUP-ASSIGNMENT-PART1/datasets/dataset3_facility_c.csv";
  bool stop = false;
  string data;
  int step = 0;

  while (step < 3 && !stop) {
    const char *path = nullptr;

    if (step == 0)
      path = dataset0;
    else if (step == 1)
      path = dataset1;
    else if (step == 2)
      path = dataset2;

    ifstream file(path);
    if (!file.is_open()) {
      cerr << "Error: This file cannot be opened due to '" << strerror(errno)
           << "' Reason\n";
      return 1;
    }

    LinkedList values;
    do {
      getline(file, data);
      if (file.good()) {
        // Node *values = nullptr;
        // push(values)
        // Bubble Sort
        // Linear Search
      }
    } while (
        file.good()  ? true
        : file.eof() ? ([&]() {
            cout << "\n Finished reading: " << path << "\n";

            if (step < 2) {
              char choice;
              cout << "Would you like to proceed to the next file? (y/n): ";
              cin >> choice;
              if (tolower(static_cast<unsigned char>(choice)) != 'y') {
                stop = true;
              }
            }
            return false;
          })()
                     : false);

    file.close();
    step++;
  }

  return 0;
}
