#include "linked_list.cpp"
#include <cctype>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::filesystem;

int main() {
  path dataset0 = path("datasets/dataset1 facility_a.csv");
  path dataset1 = path("datasets/dataset2 facility_b.csv");
  path dataset2 = path("datasets/dataset3_facility_c.csv");

  string data;

  LinkedList values_0;
  LinkedList values_1;
  LinkedList values_2;

  ifstream file0(dataset0);
  if (!file0.is_open()) {
    cerr << "Error: This file cannot be opened due to '" << strerror(errno)
         << "' Reason\n";
    return 1;
  }

  getline(file0, data);

  do {
    getline(file0, data);
    if (file0.good()) {
      size_t start = 0;
      size_t end = 0;
      string fields[6];

      for (int i = 0; i < 6; i++) {
        if (i == 5) {
          fields[i] = data.substr(start);
          while (!fields[i].empty() &&
                 (fields[i].back() == '\r' || fields[i].back() == '\n')) {
            fields[i].pop_back();
          }
        } else {
          end = data.find(',', start);
          fields[i] = data.substr(start, end - start);
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

      values_0.push(*heap_node);
      delete heap_node;
    }
  } while (file0.good()  ? true
           : file0.eof() ? ([&]() {
               cout << "\n Finished reading: " << dataset0 << "\n";
               cout << "Total items loaded into this list: " << values_0.length
                    << "\n";
               return false;
             })()
                         : false);
  file0.close();

  ifstream file1(dataset1);
  if (!file1.is_open()) {
    cerr << "Error: This file cannot be opened due to '" << strerror(errno)
         << "' Reason\n";
    return 1;
  }

  getline(file1, data);

  do {
    getline(file1, data);
    if (file1.good()) {
      size_t start = 0;
      size_t end = 0;
      string fields[6];

      for (int i = 0; i < 6; i++) {
        if (i == 5) {
          fields[i] = data.substr(start);
          while (!fields[i].empty() &&
                 (fields[i].back() == '\r' || fields[i].back() == '\n')) {
            fields[i].pop_back();
          }
        } else {
          end = data.find(',', start);
          fields[i] = data.substr(start, end - start);
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

      values_1.push(*heap_node);
      delete heap_node;
    }
  } while (file1.good()  ? true
           : file1.eof() ? ([&]() {
               cout << "\n Finished reading: " << dataset1 << "\n";
               cout << "Total items loaded into this list: " << values_1.length
                    << "\n";
               return false;
             })()
                         : false);
  file1.close();

  ifstream file2(dataset2);
  if (!file2.is_open()) {
    cerr << "Error: This file cannot be opened due to '" << strerror(errno)
         << "' Reason\n";
    return 1;
  }

  getline(file2, data);

  do {
    getline(file2, data);
    if (file2.good()) {
      size_t start = 0;
      size_t end = 0;
      string fields[6];

      for (int i = 0; i < 6; i++) {
        if (i == 5) {
          fields[i] = data.substr(start);
          while (!fields[i].empty() &&
                 (fields[i].back() == '\r' || fields[i].back() == '\n')) {
            fields[i].pop_back();
          }
        } else {
          end = data.find(',', start);
          fields[i] = data.substr(start, end - start);
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

      values_2.push(*heap_node);
      delete heap_node;
    }
  } while (file2.good()  ? true
           : file2.eof() ? ([&]() {
               cout << "\n Finished reading: " << dataset2 << "\n";
               cout << "Total items loaded into this list: " << values_2.length
                    << "\n";
               return false;
             })()
                         : false);
  file2.close();

  return 0;
}
