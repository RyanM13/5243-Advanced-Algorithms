#include "counters.hpp"
#include <iostream>

class LinkedList {
private:
  struct Node {
    int data;
    Node *next;

    Node(int v) : data(v), next(nullptr) {}
  };

  Counters c{};

  Node *head;

public:
  LinkedList() : head(nullptr) {}

  ~LinkedList() {
    Node *curr = head;

    // Lookups?
    while (curr) {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    }
  }

  bool insert(int value) {

    c.inserts++;
    if (contains(value))
      return false;

    c.structural_ops++;
    Node *n = new Node(value);

    n->next = head;
    head = n;

    return true;
  }

  bool contains(int value) const {
    c.lookups++;
    Node *curr = head;

    while (curr) {
      c.comparisons++;
      if (curr->data == value)
        return true;

      curr = curr->next;
    }

    return false;
  }

  bool erase(int value) {
    c.deletes++;
    Node *curr = head;
    Node *prev = nullptr;

    while (curr) {
      c.comparisons++;
      if (curr->data == value) {

        if (prev)
          prev->next = curr->next;
        else
          head = curr->next;
        c.structural_ops++;
        delete curr;
        return true;
      }

      prev = curr;
      curr = curr->next;
    }

    return false;
  }

  Counters getCounters() { return c; }

  void reset() { c = {}; }

  void save(string filename, bool dict = true) {
    c.saveCounters(filename, dict);
  }

  void runJobFile(std::string fname) {
    std::ifstream f(fname);
    json j = json::parse(f);
    // std::cout<<j<<std::endl;

    // iterate over json object and print out each operation with value
    // replace the print with actual operations, to process entire file.
    for (auto &element : j) {
      string op = element["op"];
      int val = element["value"];

      if (op == "insert")
        insert(val);
      else if (op == "contains")
        contains(val);
      else if (op == "delete")
        erase(val);
    }
  }

  void print() const {

    Node *curr = head;

    while (curr) {
      std::cout << curr->data << " ";
      curr = curr->next;
    }

    std::cout << "\n";
  }
};
