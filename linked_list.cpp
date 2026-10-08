#include <cstdlib>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

enum Base {
  AGE,
  LENGTH_OF_STAY,
  BASE_COST_PER_HOUR,
  DAYS_VISITS_PER_YEAR,
  TOTAL_MEDICAL_COST,

};

struct Node {
  string patientID, careType;
  int age, lengthOfStay, baseCostPerHour, daysVisitsPerYear;

  Node *next;

  string display() {
    return format(
        "[Care type={}, ID={}, Age={}, Length of stay={}, Base cost "
        "per hour={}, Days visits per year={}, Total medical cost={}]",
        careType, patientID, age, lengthOfStay, baseCostPerHour,
        daysVisitsPerYear, get_total_medical_cost());
  }
  int get_total_medical_cost() {
    return (baseCostPerHour * lengthOfStay) * daysVisitsPerYear;
  };
};
struct LinkedList {
  int length;
  Node *first_node;

  LinkedList() {
    length = 0;
    first_node = nullptr;
  }
  void push(Node node) {
    Node *new_node = new Node{node.patientID,
                              node.careType,
                              node.age,
                              node.lengthOfStay,
                              node.baseCostPerHour,
                              node.daysVisitsPerYear,
                              nullptr};
    length += 1;
    if (!first_node) {
      first_node = new_node;
      return;
    }
    Node *temp = first_node;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = new_node;
  }
  void append(int item, int i) {}

  void pop() {
    if (!first_node) {
      return;
    }
    Node *temp = first_node;
    Node *after_temp = first_node;
    while (temp->next) {
      after_temp = temp->next;
      if (!after_temp->next) {
        free(after_temp);
        temp->next = nullptr;
        length -= 1;
        return;
      }
      temp = temp->next;
    }
  }

  void display_all() {
    Node *temp = first_node;
    while (temp) {
      cout << temp->display() << " ";
      temp = temp->next;
    }
    cout << endl;
  }

  Node *get(int i) {
    if (i >= length || i < 0) {
      return nullptr;
    }
    int b = 0;
    Node *temp = first_node;

    while (b != i) {
      temp = temp->next;
      b += 1;
    }
    return temp;
  }
  Node *get_by_id(string id) {
    Node *temp = first_node;

    while (true) {
      if (temp->patientID == id) {
        return temp;
      }
      if (temp->next) {

        temp = temp->next;
      } else {
        throw invalid_argument("invalid ID.");
      }
    }
  }

  void delete_by_id(string id) {
    Node *temp = first_node;
    Node *after_temp = first_node;
    while (temp->next) {
      if (after_temp->patientID == id) {
        if (after_temp == first_node) {
          first_node = first_node->next;

        } else {
          temp->next = after_temp->next;
        }
        free(after_temp);
        return;
      }
      if (after_temp != first_node) {
        temp = temp->next;
      }
      after_temp = temp->next;
    }
    throw invalid_argument("invalid ID.");
  }

  void swap(int node1_i, int node2_i) {
    /// swaping two nodes
    if (node1_i > node2_i) {
      int temp = node1_i;
      node1_i = node2_i;
      node2_i = temp;
    }
    Node *node1 = get(node1_i);
    Node *node2 = get(node2_i);

    Node *before_node1 = get(node1_i - 1);
    Node *after_node1 = get(node1_i + 1);
    Node *before_node2 = get(node2_i - 1);
    Node *after_node2 = get(node2_i + 1);
    if (get(node2_i - 1) == node1 && node2_i > node1_i) {
      node2->next = node1;
      node1->next = after_node2;
      if (node1_i != 0) {
        before_node1->next = node2;
      } else {
        first_node = node2;
      }
    } else {
      before_node2->next = node1;
      node1->next = after_node2;
      node2->next = after_node1;
    }
    if (node1_i != 0) {
      before_node1->next = node2;
    } else {
      first_node = node2;
    }
  }

  void bubble_sort(Base sorting_base) {
    /// Sorting the list using Bubble Sort
    for (int i = 0; i < length; i++) {
      Node *temp = get(i);
      for (int b = 0; b < length; b++) {
        Node *temp2 = get(b);
        switch (sorting_base) {
        case AGE:
          if (temp->age < temp2->age) {
            swap(i, b);
          }
          break;
        case LENGTH_OF_STAY:
          if (temp->lengthOfStay < temp2->lengthOfStay) {
            swap(i, b);
          }
          break;
        case BASE_COST_PER_HOUR:
          if (temp->baseCostPerHour < temp2->baseCostPerHour) {
            swap(i, b);
          }
          break;

        case DAYS_VISITS_PER_YEAR:
          if (temp->daysVisitsPerYear < temp2->daysVisitsPerYear) {
            swap(i, b);
          }
          break;
        case TOTAL_MEDICAL_COST:
          if (temp->get_total_medical_cost() <
              temp2->get_total_medical_cost()) {
            swap(i, b);
          }
          break;
        }
      }
    }
  }

  void merge_sort(Base sorting_base) {
    /// Sorting the list using Merge Sort
  }

  LinkedList search(Base searching_base, int value) {
    /// Searching age, lengthOfStay, baseCostPerHour, daysVisitsPerYear,
    /// TotalMedicalCost using Linear search
    LinkedList *results = new LinkedList;
    Node *temp = first_node;
    while (true) {
      switch (searching_base) {
      case AGE:
        if (value == temp->age) {
          results->push(*temp);
        }
        break;
      case LENGTH_OF_STAY:
        if (value == temp->lengthOfStay) {
          results->push(*temp);
        }
        break;
      case BASE_COST_PER_HOUR:
        if (value == temp->baseCostPerHour) {
          results->push(*temp);
        }
        break;
      case DAYS_VISITS_PER_YEAR:
        if (value == temp->daysVisitsPerYear) {
          results->push(*temp);
        }
        break;
      case TOTAL_MEDICAL_COST:
        if (value == temp->get_total_medical_cost()) {
          results->push(*temp);
        }
        break;
      }
      if (temp->next) {

        temp = temp->next;
      } else {
        break;
      }
    }
    return *results;
  }
  Node *search_id(string value) {
    /// Searching id using Linear search
    Node *temp = first_node;
    while (true) {
      if (value == temp->patientID) {
        break;
      }
      if (temp->next) {

        temp = temp->next;
      } else {
        break;
      }
    }
    return temp;
  }
  LinkedList *search_caretype(string value) {
    /// Searching caretype using Linear search
    LinkedList *results = new LinkedList;
    Node *temp = first_node;
    while (true) {
      if (value == temp->careType) {
        results->push(*temp);
      }
      if (temp->next) {

        temp = temp->next;
      } else {
        break;
      }
    }
    return results;
  }
};

