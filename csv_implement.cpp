#include "linked_list.cpp"
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <psapi.h>
#include <windows.h>

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

size_t mem_before_calculations[3] = {0, 0, 0};
size_t mem_after_calculations[3] = {0, 0, 0};

extern "C" {
int atoi(const char *str);
int printf(const char *format, ...);
}

size_t getMemoryUsage() {
  PROCESS_MEMORY_COUNTERS pmc;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
    return pmc.PagefileUsage;
  }
  return 0;
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
  if (cycles == 0) {
    mem_before_calculations[dataset_index] = getMemoryUsage();
  }

  auto loop_checkpoint_b = steady_clock::now();
  linear_duration +=
      duration_cast<milliseconds>(loop_checkpoint_b - loop_checkpoint_a)
          .count();
  cycles++;

  return_ends(dataset_index);
  return_durations(dataset_index, linear_duration);
  return_cycles(dataset_index, cycles);

  mem_after_calculations[dataset_index] = getMemoryUsage();
}

void display_benchmarks(int assigned_id) {
  auto elapsed = duration_cast<milliseconds>(all_ends[assigned_id] -
                                             all_starts[assigned_id]);
  printf("-> Dataset %d Bubble Sorting took: %ld ms\n", assigned_id,
         elapsed.count());
  printf("  -> Total tracking operations run: %d\n",
         all_execution_cycles[assigned_id]);
  printf("  -> Aggregated Linear Search duration: %lld ms\n",
         all_linear_durations[assigned_id]);
  if (all_execution_cycles[assigned_id] > 0) {
    printf("  -> Average latency per scanned data point: %f ms\n",
           (double)all_linear_durations[assigned_id] /
               all_execution_cycles[assigned_id]);
  }

  long long deltaBytes =
      static_cast<long long>(mem_after_calculations[assigned_id]) -
      static_cast<long long>(mem_before_calculations[assigned_id]);
  printf("  -> Memory Gap: %lld KB\n\n", deltaBytes / 1024);
}

void table_format(const LinkedList &dataset, int record_count,
                  int assigned_id) {
  auto current_time = steady_clock::now();
  auto parse_duration =
      duration_cast<milliseconds>(current_time - all_starts[assigned_id]);

  printf("Load Total Valid Records: %d\n", record_count);
  printf("Processing Time: %ld ms\n\n", parse_duration.count());

  printf("====================================================================="
         "===============================\n");
  printf("%-10s | %-4s | %-16s | %-12s | %-16s | %-18s |\n", "PatientID", "Age",
         "CareType", "LengthOfStay", "BaseCostPerHour", "DaysVisitsPerYear");
  printf("====================================================================="
         "===============================\n");

  Node *current = dataset.first_node;
  while (current != nullptr) {
    printf("%-10s | %-4d | %-16s | %-12d | %-16d | %-18d |\n",
           current->patientID.c_str(), current->age, current->careType.c_str(),
           current->lengthOfStay, current->baseCostPerHour,
           current->daysVisitsPerYear);
    current = current->next;
  }
  printf("\n");
}

void table_format_2(const LinkedList &dataset, int record_count,
                    int assigned_id) {
  printf("Sorted Display for Dataset %d \n", assigned_id);
  printf("====================================================================="
         "===============================\n");
  printf("%-10s | %-4s | %-16s | %-12s | %-16s | %-18s |\n", "PatientID", "Age",
         "CareType", "LengthOfStay", "BaseCostPerHour", "DaysVisitsPerYear");
  printf("====================================================================="
         "===============================\n");

  Node *current = dataset.first_node;
  while (current != nullptr) {
    printf("%-10s | %-4d | %-16s | %-12d | %-16d | %-18d |\n",
           current->patientID.c_str(), current->age, current->careType.c_str(),
           current->lengthOfStay, current->baseCostPerHour,
           current->daysVisitsPerYear);
    current = current->next;
  }
  printf("\nTotal Output Records: %d\n\n", record_count);
}

long long analyses(const LinkedList &dataset, int sub_selection,
                   int assigned_id) {
  int target_min_ages[5] = {0, 18, 26, 41, 61};
  int target_max_ages[5] = {17, 25, 40, 60, 100};
  const char *target_labels[5] = {
      "0-17 (Children & Adolescents)",
      "18-25 (Young Adults / University Students)", "26-40 (Adults)",
      "41-60 (Middle-Aged Adults)", "61-100 (Seniors / Elderly)"};

  printf("\n==================================================================="
         "======================\n");
  printf("  HEALTHCARE EXPENDITURE & SERVICE ANALYSIS REPORT FOR DATASET %d\n",
         assigned_id);
  printf("====================================================================="
         "====================\n");

  for (int mode = 0; mode < 5; ++mode) {
    if (sub_selection == 1 || sub_selection == (mode + 2)) {
      int min_age = target_min_ages[mode];
      int max_age = target_max_ages[mode];

      string unique_care_types[20];
      int unique_types_count = 0;

      Node *current = dataset.first_node;
      while (current != nullptr) {
        if (current->age >= min_age && current->age <= max_age) {
          bool exists = false;
          for (int i = 0; i < unique_types_count; i++) {
            if (unique_care_types[i] == current->careType) {
              exists = true;
              break;
            }
          }
          if (!exists && unique_types_count < 20) {
            unique_care_types[unique_types_count++] = current->careType;
          }
        }
        current = current->next;
      }

      printf("Age Group: %s\n", target_labels[mode]);
      printf("-----------------------------------------------------------------"
             "------------------------\n");
      printf("%-18s | %-13s | %-15s | %-28s\n", "Care Type", "Patient Count",
             "Total Cost ($)", "Average Cost per Patient ($)");
      printf("-----------------------------------------------------------------"
             "------------------------\n");

      double total_billing_age_group = 0.0;

      for (int i = 0; i < unique_types_count; i++) {
        int patient_count = 0;
        double total_cost = 0.0;

        current = dataset.first_node;
        while (current != nullptr) {
          if (current->age >= min_age && current->age <= max_age &&
              current->careType == unique_care_types[i]) {
            patient_count++;
            total_cost += current->get_total_medical_cost();
          }
          current = current->next;
        }

        double avg_cost =
            (patient_count > 0) ? (total_cost / patient_count) : 0.0;
        printf("%-18s | %-13d | %-15.2f | %-28.2f\n",
               unique_care_types[i].c_str(), patient_count, total_cost,
               avg_cost);
        total_billing_age_group += total_cost;
      }

      printf("-----------------------------------------------------------------"
             "------------------------\n");
      printf("Total Billing for Age Group: $%.2f\n", total_billing_age_group);
      printf("-----------------------------------------------------------------"
             "------------------------\n\n");
    }
  }
  return 0;
}

inline void bubble_sort_and_linear_search_csv(LinkedList &current_values,
                                              const Node *heap_node,
                                              long long &linear_duration,
                                              int &cycles, int dataset_index,
                                              int output_mode) {
  switch (output_mode) {
  case 2:
    current_values.bubble_sort(AGE);
    break;
  case 3:
    current_values.bubble_sort(AGE);
    current_values.bubble_sort(TOTAL_MEDICAL_COST);
    break;
  }
  auto loop_checkpoint_a = steady_clock::now();

  LinkedList linear = current_values.search(AGE, heap_node->age);

  benchmarking_calculations(dataset_index, loop_checkpoint_a, linear_duration,
                            cycles);
}

LinkedList csv_reader(const Path_ID_Map &config, int output_mode,
                      int sub_selection = 1) {
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

      if (output_mode == 2 || output_mode == 3) {
        bubble_sort_and_linear_search_csv(
            current_values, heap_node, total_linear_duration_us,
            all_execution_cycles[assigned_id], assigned_id, output_mode);
      } else {
        all_execution_cycles[assigned_id]++;
      }

      delete heap_node;
    }
  } while (file.good()  ? true
           : file.eof() ? ([&]() { return false; })()
                        : false);

  file.close();
  all_ends[assigned_id] = steady_clock::now();

  if (output_mode == 1) {
    table_format(current_values, all_execution_cycles[assigned_id],
                 assigned_id);
  } else if (output_mode == 2) {
    table_format_2(current_values, all_execution_cycles[assigned_id],
                   assigned_id);
    display_benchmarks(assigned_id);
  } else if (output_mode == 3) {
    analyses(current_values, sub_selection, assigned_id);
    display_benchmarks(assigned_id);
  }

  return current_values;
}
