# Critical Path Method (CPM) Implementation in C++

## Overview
This project implements the **Critical Path Method (CPM)**, a project management technique for identifying the sequence of critical tasks in a project. The program calculates:
- Earliest and latest start/finish times for tasks.
- The **Critical Path**, which represents the sequence of tasks that cannot be delayed without impacting the project timeline.

---

## Features
- Accepts interactive input for tasks, durations, and dependencies.
- Computes:
    - Earliest Start (ES) and Earliest Finish (EF) times.
    - Latest Start (LS) and Latest Finish (LF) times.
- Identifies the critical path using calculated timings.

---

## Input Format
Tasks are entered in the format:
```
Activity, Predecessors, Duration
```
- **Activity**: Name of the task.
- **Predecessors**: Comma-separated names of tasks that must finish before the current task can start (leave blank if none).
- **Duration**: Time taken to complete the task.

### Example Input
```
a,,1 // Task 'a' has no predecessors and takes 1 unit of time.
b,,2 // Task 'b' has no predecessors and takes 2 units of time.
c,a b,3 // Task 'c' depends on 'a' and 'b' and takes 3 units of time.
e,c,2 // Task 'e' depends on 'c' and takes 2 units of time. done // Finish input.
```
---

## Output Format
1. A table displaying each task's:
    - Duration
    - Earliest Start (ES) and Earliest Finish (EF)
    - Latest Start (LS) and Latest Finish (LF)
2. The **Critical Path**, displayed as a sequence of task names.

### Example Output
For the input:
```
a,,1
b,,2
c,a b,3
e,c,2
done
```
The output will be:
```
Task Duration ES EF LS LF
 a   1        0  1   0 1
 b   2        0  2   1 3 
 c   3        2  5   2 5 
 e   2        5  7   5 7

Critical Path: a -> c -> e

```
                     
   
---

## How It Works
### Algorithm
1. **Topological Sorting**:
   - Tasks are processed in dependency order using Kahn's Algorithm.
2. **Forward Pass**:
   - Computes **Earliest Start (ES)** and **Earliest Finish (EF)** by processing tasks in topological order.
3. **Backward Pass**:
   - Computes **Latest Start (LS)** and **Latest Finish (LF)** by processing tasks in reverse topological order.
4. **Critical Path Identification**:
   - Tasks where `ES == LS` are part of the critical path.

---

## How to Use

### Compilation and Execution
```bash
g++ -std=c++17 -o main main.cpp ./main
```             

### Running the Program
1. Input tasks interactively in the specified format.
2. Type done to finish input.
3. View the calculated timings and the critical path.



## Project Structure
```
.
├── main.cpp     // Main source code
└── README.md           // Documentation
```


## Code Overview
### ``struct Task``
Represents a project task with:

- ``name:`` Task name.
- ``duration:`` Task duration.
- ``earliestStart (ES):`` Earliest start time.
- ``earliestFinish (EF):`` Earliest finish time.
- ``latestStart (LS):`` Latest start time.
- ``latestFinish (LF):`` Latest finish time.
### ``class CPM``
Encapsulates the CPM logic with:

- ``addTask:`` Adds a task and its dependencies.
- ``calculate:`` Computes earliest and latest timings.
- ``getCriticalPath:`` Returns the critical path.
- ``displayTasks:`` Prints task details in a table.
- ``topologicalSort:`` Generates a valid execution order of tasks.

---
## References
- [Critical Path Method - Wikipedia](https://en.wikipedia.org/wiki/Critical_path_method)

[//]: # (---)

[//]: # ()
[//]: # (## Author)

[//]: # (- []&#40;&#41;)
