#include <cstdlib>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct Node {
  int patientID;
  int age, lengthOfStay, baseCostPerHour, daysVisitsPerYear;
  string careType;

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
  void push(int id, int age, string careType, int lengthOfStay,
            int baseCostPerHour, int daysVisitsPerYear) {
    Node *new_node = new Node{
        id,       age,    lengthOfStay, baseCostPerHour, daysVisitsPerYear,
        careType, nullptr};
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

  Node *get_by_id(int id) {
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

  void delete_by_id(int id) {
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
};

