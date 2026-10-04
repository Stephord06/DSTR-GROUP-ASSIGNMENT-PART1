#include <cstdlib>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct Node {
  // intial values and should be changed later
  int patientID;
  string name;
  Node *next;

  string display() { return format("[{}, {}]", patientID, name); }
};

struct LinkedList {
  int length;
  Node *first_node;

  LinkedList() {
    length = 0;
    first_node = nullptr;
  }
  void push(int id, string name) {
    Node *new_node = new Node{id, name, nullptr};
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
  // broken implementation for now
  void pop() {
    Node *temp = first_node;
    int i = 0;
    while (i < length) {
      temp = temp->next;
      i += 1;
    }
    free(temp);
    length -= 1;
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
      throw invalid_argument("index out of bounds");
    }
    int b = 0;
    Node *temp = first_node;

    while (b != i) {
      temp = temp->next;
      b += 1;
    }
    return temp;
  }
}

;

