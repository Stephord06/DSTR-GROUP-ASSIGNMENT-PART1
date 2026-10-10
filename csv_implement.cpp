#include "linked_list.cpp"
#include <cerrno>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::filesystem;
using namespace std::chrono;

int main() {
  path dataset0 = path("datasets/dataset1 facility_a.csv");
  path dataset1 = path("datasets/dataset2 facility_b.csv");
  path dataset2 = path("datasets/dataset3_facility_c.csv");

  string data;

  LinkedList values_0;
  LinkedList values_1;
  LinkedList values_2;

  for (int i = 0; i < 3; i++) {
    path &current_dataset = (i == 0)   ? dataset0
                            : (i == 1) ? dataset1
                                       : dataset2;
    LinkedList &current_values = (i == 0)   ? values_0
                                 : (i == 1) ? values_1
                                            : values_2;

    ifstream file(current_dataset);
    if (!file.is_open()) {
      cerr << "Error: This file cannot be opened due to '" << strerror(errno)
           << "' Reason\n";
      return 1;
    }

    getline(file, data);

    auto start_time = steady_clock::now();

    do {
      getline(file, data);
      if (file.good()) {
        size_t start = 0;
        size_t end = 0;
        string fields[6];

        for (int j = 0; j < 6; j++) {
          if (j == 5) {
            fields[j] = data.substr(start);
            while (!fields[j].empty() &&
                   (fields[j].back() == '\r' || fields[j].back() == '\n')) {
              fields[j].pop_back();
            }
          } else {
            end = data.find(',', start);
            fields[j] = data.substr(start, end - start);
            start = end + 1;
          }
        }

        Node *heap_node = new Node;
        heap_node->patientID = fields[0];
        heap_node->careType = fields[2];
        heap_node->age = stoi(fields[1]);
        heap_node->lengthOfStay = stoi(fields[3]);
        heap_node->baseCostPerHour = stoi(fields[4]);
        heap_node->daysVisitsPerYear = stoi(fields[5]);
        heap_node->next = nullptr;

        current_values.push(*heap_node);

        current_values.bubble_sort(AGE);
        current_values.bubble_sort(BASE_COST_PER_HOUR);
        delete heap_node;
      }
    } while (file.good()  ? true
             : file.eof() ? ([&]() {
                 cout << "\n Finished reading: " << current_dataset << "\n";
                 cout << "Total items loaded into this list: "
                      << current_values.length << "\n";
                 return false;
               })()
                          : false);
    file.close();

    auto end_time = steady_clock::now();
    auto elapsed = duration_cast<microseconds>(end_time - start_time);
    cout << "Dataset " << i << " processing took: " << elapsed.count()
         << " us\n\n";
  }

  return 0;
}
