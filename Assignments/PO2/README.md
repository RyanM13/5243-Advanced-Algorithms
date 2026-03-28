## P02 - Comparisons of Data Structures
### Ryan Mathews
### Description:

This project is to compare different data structures under different stress tests. The goal is to generate workload files and then run them using the main drivers for the data structures. After that analyze the comparisons between the files using the heat maps.

## Files
| # | File | Description |
|---|------|-------------|
| 1 | [Drivers](https://github.com/RyanM13/5243-Advanced-Algorithms/tree/main/Assignments/PO2/src/drivers) | Main drivers that fuel the comparisons |
| 2 | [Structures](https://github.com/RyanM13/5243-Advanced-Algorithms/tree/main/Assignments/PO2/src/include)| Data structures for the drivers to compare |
| 3 | [Workload Generator](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/workload_generator.cpp) | Generates random operations based on type (A, B, C, D) |
| 4 | [makework.sh](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/makework.sh) | Bash file to generate all workload files at once |
| 5 | [runner.sh](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/runner.sh) | Bash file to run all drivers and generate results |
| 6 | [Workloads](https://github.com/RyanM13/5243-Advanced-Algorithms/tree/main/Assignments/PO2/src/workLoads) | Workload JSON files |
| 7 | [Results](https://github.com/RyanM13/5243-Advanced-Algorithms/tree/main/Assignments/PO2/src/results) | Counter results for each structure/workload combination |
| 8 | [charts](https://github.com/RyanM13/5243-Advanced-Algorithms/tree/main/Assignments/PO2/src/charts/heatmap)| Generated heat maps and charts |
| 9 | [map.py](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/map.py) | Creates the heatmaps using the files from Results|
### Instructions

### Step 1 - Compile the Workload Generator
```bash
g++ -std=c++20 -Iinclude workload_generator.cpp -o wg
```

### Step 2 - Generate Workloads
```bash
chmod +x makework.sh
./makework.sh
```

### Step 3 - Compile the Drivers
```bash
g++ -std=c++20 -Iinclude drivers/drive_load_Bst.cpp -o bstRunner
g++ -std=c++20 -Iinclude drivers/drive_load_HashTable.cpp -o htRunner
g++ -std=c++20 -Iinclude drivers/drive_load_LinkedList.cpp -o llRunner
g++ -std=c++20 -Iinclude drivers/drive_load_SortedArraySet.cpp -o saRunner
```

### Step 4 - Run All Experiments
```bash
chmod +x runner.sh
./runner.sh
```

### Step 5 - Generate Heat Maps
```bash
python3 map.py
```

## Workload Types
| Type | Description |
|------|-------------|
| A | Random inserts followed by random lookups |
| B | Sorted inserts followed by random lookups |
| C | Mixed — 50% lookups, 25% inserts, 25% deletes |
| D | n inserts followed by 5n lookups (read heavy) |

## Comparison Data

### I decided to represent the comparisons using Heat Maps as I feel as though they are efficient and visually easily to understand. I split these into 4 different maps: Comparisons, Deletes, Lookups, and Structural Operations.

# Comparisons

[Comparison](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/charts/heatmap/comparisons_heatmap.png?raw=true)<img width="1800" height="500" alt="image" src="https://github.com/user-attachments/assets/6a9a2007-0472-4807-b2d7-bf9ae0fa7767" />

## Discovery

- BST performed relatively well on all workloads other than B (sorted, implied skewd tree)
- Hash table gave a pretty even reading, with its worst workload being D (read heavy) 
- Linked list performed the worst through all of the different structures and workloads
- Sorted Array gave the best performance possibly because of the O(log n) binary search algorithm


# Deletes 

[Delete](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/charts/heatmap/deletes_heatmap.png?raw=true)<img width="1800" height="500" alt="image" src="https://github.com/user-attachments/assets/ac588a15-5b9c-431f-b764-5017923792b4" />

## Discovery 
- All data structures processed the same file hence the identical deletes. 

## Lookups

[Lookup](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/charts/heatmap/lookups_heatmap.png?raw=true)<img width="1800" height="500" alt="image" src="https://github.com/user-attachments/assets/2199b3f6-6f5e-4c49-ad81-a435c9843123" />

## Discovery 

- Shows even numbers between 3 of the data structures since they share similar properties
- Linked list is shown to be the worst data structure by far for lookups, which makes sense based on no direct access like the others

## Structural Operations

[Structural Op](https://github.com/RyanM13/5243-Advanced-Algorithms/blob/main/Assignments/PO2/src/charts/heatmap/structural_ops_heatmap.png?raw=true)<img width="1800" height="500" alt="image" src="https://github.com/user-attachments/assets/517f45ef-2084-41ef-869c-1db749d04d12" />

## Discovery 

- Shows cleary that sorted arrays are bad for inserting due to static space.
- Shows the other data structures allow for easier insertion and structural operation
