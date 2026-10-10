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

struct Path_ID_Map {
  path file_path;
  int assigned_id;
};

string csv_row_data;
steady_clock::time_point all_starts[3];
steady_clock::time_point all_ends[3];
long long all_linear_durations[3];
int all_execution_cycles[3];

Path_ID_Map retrieve_relative_path0() {
  return {path("datasets/dataset1 facility_a.csv"), 0};
}

Path_ID_Map retrieve_relative_path1() {
  return {path("datasets/dataset2 facility_b.csv"), 1};
}

Path_ID_Map retrieve_relative_path2() {
  return {path("datasets/dataset3_facility_c.csv"), 2};
}

void display_benchmarks(int assigned_id) {
  auto elapsed = duration_cast<microseconds>(all_ends[assigned_id] -
                                             all_starts[assigned_id]);
  cout << "-> Dataset " << assigned_id
       << " Bubble Sorting took: " << elapsed.count() << " us\n";
  cout << "  -> Total tracking operations run: "
       << all_execution_cycles[assigned_id] << "\n";
  cout << "  -> Aggregated Linear Search duration: "
       << all_linear_durations[assigned_id] << " us\n";
  if (all_execution_cycles[assigned_id] > 0) {
    cout << "  -> Average latency per scanned data point: "
         << (double)all_linear_durations[assigned_id] /
                all_execution_cycles[assigned_id]
         << " us\n\n";
  }
}

inline steady_clock::time_point return_ends(int dataset_index) {
  return all_ends[dataset_index] = steady_clock::now();
}

inline long long return_durations(int dataset_index,
                                  long long linear_duration) {
  return all_linear_durations[dataset_index] = linear_duration;
}

inline int return_cycles(int dataset_index, int cycles) {
  return all_execution_cycles[dataset_index] = cycles;
}

inline void
benchmarking_calculations(int dataset_index,
                          const steady_clock::time_point &loop_checkpoint_a,
                          long long &linear_duration, int &cycles) {
  auto loop_checkpoint_b = steady_clock::now();
  linear_duration +=
      duration_cast<microseconds>(loop_checkpoint_b - loop_checkpoint_a)
          .count();
  cycles++;

  return_ends(dataset_index);
  return_durations(dataset_index, linear_duration);
  return_cycles(dataset_index, cycles);
}

inline void bubble_sort_and_linear_search_csv(LinkedList &current_values,
                                              const Node *heap_node,
                                              long long &linear_duration,
                                              int &cycles, int dataset_index) {
  current_values.bubble_sort(AGE);
  current_values.bubble_sort(BASE_COST_PER_HOUR);

  auto loop_checkpoint_a = steady_clock::now();

  LinkedList linear = current_values.search(AGE, heap_node->age);

  benchmarking_calculations(dataset_index, loop_checkpoint_a, linear_duration,
                            cycles);
}

LinkedList csv_reader(const Path_ID_Map &config) {
  LinkedList current_values;
  const path &current_dataset = config.file_path;
  int assigned_id = config.assigned_id;

  ifstream file(current_dataset);
  if (!file.is_open()) {
    cerr << "Error: This file cannot be opened due to '" << strerror(errno)
         << "' Reason\n";
    return current_values;
  }
  getline(file, csv_row_data);

  all_starts[assigned_id] = steady_clock::now();
  long long total_linear_duration_us = 0;
  int execution_cycles = 0;

  do {
    getline(file, csv_row_data);
    if (file.good()) {
      size_t start = 0;
      size_t end = 0;
      string fields[6];

      for (int j = 0; j < 6; j++) {
        if (j == 5) {
          fields[j] = csv_row_data.substr(start);
          while (fields[j].length() > 0 &&
                 (fields[j][fields[j].length() - 1] == '\r' ||
                  fields[j][fields[j].length() - 1] == '\n')) {
            fields[j].resize(fields[j].length() - 1);
          }
        } else {
          end = csv_row_data.find(',', start);
          fields[j] = csv_row_data.substr(start, end - start);
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

      bubble_sort_and_linear_search_csv(current_values, heap_node,
                                        total_linear_duration_us,
                                        execution_cycles, assigned_id);

      delete heap_node;
    }
  } while (file.good()  ? true
           : file.eof() ? ([&]() { return false; })()
                        : false);
  file.close();

  display_benchmarks(assigned_id);

  return current_values;
}

/** int main() {
  LinkedList values_0 = csv_reader(retrieve_relative_path0());
  LinkedList values_1 = csv_reader(retrieve_relative_path1());
  LinkedList values_2 = csv_reader(retrieve_relative_path2());

  return 0;
}**
***/
