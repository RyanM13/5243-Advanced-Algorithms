#include "sortedArraySet.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Error: You need a filename!" << endl;
    return 1;
  }

  SortedArraySet set;
  set.runJobFile(argv[1]);
  cout << set.getCounters();

  set.save(argv[2], true);
  return 0;
}
