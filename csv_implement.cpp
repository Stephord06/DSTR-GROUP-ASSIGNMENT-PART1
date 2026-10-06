#include <cctype>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  char dataset0[105] =
      "/home/noumanamaanfouzaneshaanuzair/DSTR-GROUP-ASSIGNMENT-PART1/datasets/"
      "dataset1 facility_a.csv";
  char dataset1[105] =
      "/home/noumanamaanfouzaneshaanuzair/DSTR-GROUP-ASSIGNMENT-PART1/datasets/"
      "dataset2 facility_b.csv";
  char dataset2[105] =
      "/home/noumanamaanfouzaneshaanuzair/DSTR-GROUP-ASSIGNMENT-PART1/datasets/"
      "dataset3_facility_c.csv";

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

    do {
      getline(file, data);
      if (file.good()) {
        // Append in Linked_List, Return Linked_List
        ;
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
