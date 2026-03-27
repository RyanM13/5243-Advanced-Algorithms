#!/bin/bash

workloads=("A" "B" "C" "D")
sizes=(1000 5000 10000 20000)

for w in "${workloads[@]}"; do
  for n in "${sizes[@]}"; do
    ./workload_generator --workload $w --size $n --save workLoads/workLoad_${w}_${n}.json
  done
done
