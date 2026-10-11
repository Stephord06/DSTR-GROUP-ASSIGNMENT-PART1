#include "linked_list.cpp"
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;
using namespace std::chrono;

struct Path_ID_Map {
  path file_path;
  int assigned_id;
};

steady_clock::time_point all_starts[3];
steady_clock::time_point all_ends[3];
long long all_linear_durations[3];
int all_execution_cycles[3];

extern "C" {
int atoi(const char *str);
int printf(const char *format, ...);
}

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
  printf("-> Dataset %d Bubble Sorting took: %ld us\n", assigned_id,
         elapsed.count());
  printf("  -> Total tracking operations run: %d\n",
         all_execution_cycles[assigned_id]);
  printf("  -> Aggregated Linear Search duration: %lld us\n",
         all_linear_durations[assigned_id]);
  if (all_execution_cycles[assigned_id] > 0) {
    printf("  -> Average latency per scanned data point: %f us\n\n",
           (double)all_linear_durations[assigned_id] /
               all_execution_cycles[assigned_id]);
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
  current_values.bubble_sort(TOTAL_MEDICAL_COST);

  auto loop_checkpoint_a = steady_clock::now();

  LinkedList linear = current_values.search(AGE, heap_node->age);

  benchmarking_calculations(dataset_index, loop_checkpoint_a, linear_duration,
                            cycles);
}

LinkedList csv_reader(const Path_ID_Map &config) {
  char csv_row_data[70];
  LinkedList current_values;
  const path &current_dataset = config.file_path;
  int assigned_id = config.assigned_id;

  ifstream file(current_dataset);
  if (!file.is_open()) {
    return current_values;
  }

  file.getline(csv_row_data, sizeof(csv_row_data));

  all_starts[assigned_id] = steady_clock::now();
  long long total_linear_duration_us = 0;
  int execution_cycles = 0;

  do {
    file.getline(csv_row_data, sizeof(csv_row_data));

    if (file.good()) {
      char *p = csv_row_data;
      char *fields[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
      int field_idx = 0;

      fields[field_idx++] = p;

      while (*p != '\0') {
        if (*p == '\r' || *p == '\n') {
          *p = '\0';
          break;
        }
        if (*p == '\t') {
          *p = '\0';
        }
        if (*p == ',') {
          *p = '\0';
          if (field_idx < 6) {
            fields[field_idx++] = p + 1;
          }
        }
        p++;
      }

      if (fields[0] == nullptr || fields[1] == nullptr ||
          fields[2] == nullptr || fields[3] == nullptr ||
          fields[4] == nullptr || fields[5] == nullptr) {
        continue;
      }

      Node *heap_node = new Node;
      heap_node->patientID = fields[0];
      heap_node->careType = fields[2];
      heap_node->age = atoi(fields[1]);
      heap_node->lengthOfStay = atoi(fields[3]);
      heap_node->baseCostPerHour = atoi(fields[4]);
      heap_node->daysVisitsPerYear = atoi(fields[5]);
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

/**int main() {
  LinkedList values_0 = csv_reader(retrieve_relative_path0());
  LinkedList values_1 = csv_reader(retrieve_relative_path1());
  LinkedList values_2 = csv_reader(retrieve_relative_path2());
  return 0;
}**/
