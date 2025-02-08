# Operating System Scheduling Algorithms

This repository contains solutions to the third series of exercises for the Operating Systems course. The exercises focus on implementing various CPU scheduling algorithms. Below is a list of the algorithms implemented in this repository:

## Algorithms Implemented

1. **Shortest Job First (SJF)**
   - A non-preemptive scheduling algorithm that selects the process with the smallest burst time to execute next.
   - [View Code](SJF.c/)

2. **Shortest Remaining Time First (SRTF)**
   - A preemptive version of SJF where the process with the smallest remaining burst time is executed next.
   - [View Code](SRTF.c/)

3. **Highest Response Ratio Next (HRRN)**
   - A non-preemptive scheduling algorithm that selects the process with the highest response ratio (RR) to execute next.
   - [View Code](HRRN.c/)

4. **Round Robin (RR) with Priority Scheduling**
   - A preemptive scheduling algorithm that uses a time quantum and priority to schedule processes.
   - [View Code](RR_Priority.c/)

5. **Multilevel Feedback Queue (MLFQ)**
   - A scheduling algorithm that uses multiple queues with different time quanta and priorities to schedule processes.
   - [View Code](MLFQ.c/)
