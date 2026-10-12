#include <windows.h>
// Windows Headers
#include <psapi.h>
// Windows Headers
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

#include "linked_list.cpp"

using namespace std;
using namespace std::chrono;

struct Path_ID_Map {
  string file_path;
  int assigned_id;
};

steady_clock::time_point all_starts[3];
steady_clock::time_point all_ends[3];
long long all_linear_durations[3];
int all_execution_cycles[3];

size_t mem_before_calculations[3] = {0, 0, 0};
size_t mem_after_calculations[3] = {0, 0, 0};

size_t getMemoryUsage();

string filePath[3] = {"datasets/dataset1 facility_a.csv",
                      "datasets/dataset2 facility_b.csv",
                      "datasets/dataset3_facility_c.csv"};

Path_ID_Map retrieve_relative_path0() { return {filePath[0], 0}; }

Path_ID_Map retrieve_relative_path1() { return {filePath[1], 1}; }

Path_ID_Map retrieve_relative_path2() { return {filePath[2], 2}; }

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

void linear_search(LinkedList &value_0, LinkedList &value_1,
                   LinkedList &value_2) {
  int post_sort_choice = 0;
  printf("All datasets processed. Enter 2 to Search Data or any other number "
         "to continue: ");
  if (scanf("%d", &post_sort_choice) != 1) {
    while (getchar() != '\n')
      ;
    printf("Invalid input. Continuing.\n");
    return;
  }
  printf("\n");
  if (post_sort_choice == 2) {
    int search_type = 0;
    printf("Searching data based on Age across all datasets\n");
    printf("Enter 1 for Exact Age or 2 for an Age Group window: ");
    if (scanf("%d", &search_type) != 1) {
      while (getchar() != '\n')
        ;
      printf("Invalid input. Continuing.\n");
      return;
    }
    printf("\n");
    if (search_type == 1) {
      int target_age = 0;
      printf("Give the Age to search: ");
      if (scanf("%d", &target_age) != 1) {
        while (getchar() != '\n')
          ;
        printf("Invalid input. Continuing.\n");
        return;
      }
      printf("\n");
      size_t searchMemBefore = getMemoryUsage();
      auto searchStart = steady_clock::now();
      LinkedList search_res0 = value_0.search(AGE, target_age);
      LinkedList search_res1 = value_1.search(AGE, target_age);
      LinkedList search_res2 = value_2.search(AGE, target_age);
      auto searchEnd = steady_clock::now();
      size_t searchMemAfter = getMemoryUsage();
      table_format_2(search_res0, all_execution_cycles[0], 0);
      table_format_2(search_res1, all_execution_cycles[1], 1);
      table_format_2(search_res2, all_execution_cycles[2], 2);
      auto searchDuration =
          duration_cast<duration<double, milli>>(searchEnd - searchStart);
      long long searchDeltaBytes = static_cast<long long>(searchMemAfter) -
                                   static_cast<long long>(searchMemBefore);
      printf("==================================================\n");
      printf("-> LINEAR SEARCH DIAGNOSTICS\n");
      printf("==================================================\n");
      printf("  -> Linear Search execution latency: %f ms\n",
             searchDuration.count());
      printf("  -> Dynamic Tracking Memory Delta: %lld KB\n\n",
             searchDeltaBytes / 1024);
    } else if (search_type == 2) {
      int min_age = 0, max_age = 0;
      printf("Give the Age group limits:\n");
      printf("First Age Boundary (Minimum): ");
      if (scanf("%d", &min_age) != 1) {
        while (getchar() != '\n')
          ;
        printf("Invalid input. Continuing.\n");
        return;
      }
      printf("Second Age Boundary (Maximum): ");
      if (scanf("%d", &max_age) != 1) {
        while (getchar() != '\n')
          ;
        printf("Invalid input. Continuing.\n");
        return;
      }
      printf("\n");
      size_t searchMemBefore = getMemoryUsage();
      auto searchStart = steady_clock::now();
      LinkedList search_res0;
      for (Node *curr = value_0.first_node; curr != nullptr;
           curr = curr->next) {
        if (curr->age >= min_age && curr->age <= max_age) {
          Node copyNode = *curr;
          copyNode.next = nullptr;
          search_res0.push(copyNode);
        }
      }
      LinkedList search_res1;
      for (Node *curr = value_1.first_node; curr != nullptr;
           curr = curr->next) {
        if (curr->age >= min_age && curr->age <= max_age) {
          Node copyNode = *curr;
          copyNode.next = nullptr;
          search_res1.push(copyNode);
        }
      }
      LinkedList search_res2;
      for (Node *curr = value_2.first_node; curr != nullptr;
           curr = curr->next) {
        if (curr->age >= min_age && curr->age <= max_age) {
          Node copyNode = *curr;
          copyNode.next = nullptr;
          search_res2.push(copyNode);
        }
      }
      auto searchEnd = steady_clock::now();
      size_t searchMemAfter = getMemoryUsage();
      table_format_2(search_res0, all_execution_cycles[0], 0);
      table_format_2(search_res1, all_execution_cycles[1], 1);
      table_format_2(search_res2, all_execution_cycles[2], 2);
      auto searchDuration =
          duration_cast<duration<double, milli>>(searchEnd - searchStart);
      long long searchDeltaBytes = static_cast<long long>(searchMemAfter) -
                                   static_cast<long long>(searchMemBefore);
      printf("==================================================\n");
      printf("-> LINEAR SEARCH DIAGNOSTICS\n");
      printf("==================================================\n");
      printf("  -> Linear Search Range execution latency: %f ms\n",
             searchDuration.count());
      printf("  -> Dynamic Tracking Memory Delta: %lld KB\n\n",
             searchDeltaBytes / 1024);
    }
  }
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
                      int sub_selection) {
  char csv_row_data[70];
  LinkedList current_values;
  const string &current_dataset = config.file_path;
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
  switch (output_mode) {
  case 1:
    table_format(current_values, all_execution_cycles[assigned_id],
                 assigned_id);
    if (assigned_id == 2) {
      linear_search(current_values, current_values, current_values);
    }
    break;
  case 2:
    table_format_2(current_values, all_execution_cycles[assigned_id],
                   assigned_id);
    display_benchmarks(assigned_id);
    if (assigned_id == 2) {
      linear_search(current_values, current_values, current_values);
    }
    break;
  case 3:
    analyses(current_values, sub_selection, assigned_id);
    display_benchmarks(assigned_id);
    if (assigned_id == 2) {
      linear_search(current_values, current_values, current_values);
    }
    break;
  }
  return current_values;
}
