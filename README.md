# Efficient Map Analysis for Connected Galactic Colonies

This project implements a map analysis engine for the BLG 336E - Analysis of Algorithms II course at ITU. It explores galactic colonies using circular maps, focusing on the identification and ranking of top-k largest colonies by resource type. The system utilizes Depth-First Search (DFS) and Breadth-First Search (BFS) for efficient graph traversal and analysis.

## Overview

The engine models a galactic sector as a circular map, where each cell represents a planet with specific natural resources. Adjacent planets with the same resource type form colonies. The program efficiently identifies the largest colonies, evaluates their sizes, and ranks them based on their resource types.

### Key Features

1. DFS and BFS traversal methods to explore colonies.
2. Circular map implementation to handle edge wrapping.
3. Identification and ranking of the top-k largest colonies.

### Input Files

1. `map1.txt`: A sample map with diverse resources.
2. `map2.txt`: A smaller map for testing edge cases.

## How to Run

### Prerequisites

- **Compiler**: Requires `g++` for compilation.
- **Environment**: Developed and tested on Ubuntu.

### Compilation

  ```bash
g++ main.cpp -o map_analysis
  ```

### Execution

- **Use DFS to analyze the map**:
  ```bash
  ./map_analysis 1 <k> <map_file>
  ```

- **Use BFS to analyze the map**:
  ```bash
  ./map_analysis 0 <k> <map_file>
  ```

### Example Commands
  ```bash
./map_analysis 1 5 map1.txt  
./map_analysis 0 3 map2.txt
  ```

## Technologies Used

- **C++**: For implementation.
- **Algorithms**: DFS and BFS for colony exploration.
- **Data Structures**: Circular maps, stacks, and queues.

## Project Highlights

- Demonstrates efficient exploration of spatial data on circular maps.
- Handles edge wrapping and adjacency efficiently.
- Optimized for large-scale galactic maps.

## Privacy Note

This repository is anonymized to comply with academic integrity policies.
This project was personally developed by EonTechie as a project for the BLG 336E - Analysis of Algorithms II course at ITU. It demonstrates individual effort in applying graph algorithms and data structures to analyze galactic maps.
