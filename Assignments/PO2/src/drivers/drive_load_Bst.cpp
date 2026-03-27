#include "bst.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Error: You need a filename!" << endl;
    cout << "Usage: ./dbst ../work_files/workload_A_1000.json" << endl;
    return 1;
  }

  Bst tree;
  tree.runJobFile(argv[1]);
  cout << tree.getCounters();
  tree.save(argv[2], true);

  return 0;

  // for(int i=0;i<100;i++){
  //     tree.insert(rand());
  //     if (i%10==0){
  //         cout<<tree.getCounters();
  //     }
  // }
  //
  // tree.reset();
  //
  // for(int i=0;i<100;i++){
  //     tree.insert(rand());
  //     if (i%10==0){
  //         cout<<tree.getCounters();
  //     }
  // }
  //
  //
  //
  // cout<<tree.getCounters();
  //
  // tree.save("yourfilename",false);
  //
}
