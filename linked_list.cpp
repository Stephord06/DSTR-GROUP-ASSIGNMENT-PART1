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
  DAYS_VISITS_PER_YEAR

};

struct Node {
  string patientID, careType;
  int age, lengthOfStay, baseCostPerHour, daysVisitsPerYear;

  Node *next;

  string display() {
    return format("[Care type={}, ID={}, Age={}, Length of stay={}, Base cost "
                  "per hour={}, Days visits per year={}]",
                  careType, patientID, age, lengthOfStay, baseCostPerHour,
                  daysVisitsPerYear);
  }
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
    if (i >= length) {
      throw invalid_argument("index out of bounds.");
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

  LinkedList search(Base searching_base, int value) {
    /// Searching age, lengthOfStay, baseCostPerHour, daysVisitsPerYear using
    /// Linear search
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

