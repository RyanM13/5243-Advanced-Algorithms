#include "linkedList.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Error: You need a filename!" << endl;
    return 1;
  }
  LinkedList list;
  list.runJobFile(argv[1]);
  cout << list.getCounters();

  list.save(argv[2], true);
  return 0;
}
