#pragma once

#include "counters.hpp"
#include <cstddef>
#include <vector>

class HashTable {
private:
  std::vector<std::vector<int>> table;
  std::size_t capacity;
  Counters c{};

  // Integer hash function
  std::size_t hash(int key) const {
    return static_cast<std::size_t>(key) * 2654435761u;
  }

  // Compress hash value into a valid bucket index
  std::size_t indexFor(int key) const { return hash(key) % capacity; }

public:
  explicit HashTable(std::size_t cap = 7) : table(cap), capacity(cap) {}

  bool insert(int key) {
    c.inserts++;
    std::size_t idx = indexFor(key);
    auto &bucket = table[idx];

    // Ignore duplicates
    for (int value : bucket) {
      c.comparisons++;
      if (value == key) {
        return false;
      }
    }

    c.structural_ops++;
    bucket.push_back(key);
    return true;
  }

  Counters getCounters() { return c; }

  void reset() { c = {}; }

  void save(string filename, bool dict = true) {
    c.saveCounters(filename, dict);
  }

  bool contains(int key) const {
    c.lookups++;
    std::size_t idx = indexFor(key);
    const auto &bucket = table[idx];

    for (int value : bucket) {
      c.comparisons++;
      if (value == key) {
        return true;
      }
    }

    return false;
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

  bool erase(int key) {
    c.deletes++;
    std::size_t idx = indexFor(key);
    auto &bucket = table[idx];

    for (std::size_t i = 0; i < bucket.size(); i++) {
      c.comparisons++;
      if (bucket[i] == key) {
        c.structural_ops++;
        // swap-pop delete: fast, order not preserved
        bucket[i] = bucket.back();
        bucket.pop_back();
        return true;
      }
    }

    return false;
  }
};
