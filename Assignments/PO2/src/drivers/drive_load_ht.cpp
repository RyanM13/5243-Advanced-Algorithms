#include "hashTable.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Error: You need a filename!" << endl;
    return 1;
  }
  HashTable table;
  table.runJobFile(argv[1]);
  cout << table.getCounters();

  table.save(argv[2], true);
  return 0;
}
