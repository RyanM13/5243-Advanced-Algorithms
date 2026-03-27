#!/bin/bash

workloads=("A" "B" "C" "D")
sizes=(1000 5000 10000 20000)

mkdir -p results

for w in "${workloads[@]}"; do
  for n in "${sizes[@]}"; do
    workload="workLoads/workLoad_${w}_${n}.json"

    echo "Running BST on $workload"
    ./bstRunner $workload results/bst_${w}_${n}.json

    echo "Running HashTable on $workload"
    ./htRunner $workload results/ht_${w}_${n}.json

    echo "Running LinkedList on $workload"
    ./LlRunner $workload results/ll_${w}_${n}.json

    echo "Running SortedArray on $workload"
    ./SArrayRunner $workload results/sa_${w}_${n}.json
  done

done
