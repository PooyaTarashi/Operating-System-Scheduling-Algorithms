#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processID;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
} Process;

int compareBurstTime(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burstTime - p2->burstTime;
}

int main() {
    int n; // number of processes
    printf("Enter number of processes : ");
    scanf("%d", &n);

    Process* processes = (Process*)calloc(n, sizeof(Process));
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    qsort(processes, n, sizeof(Process), compareBurstTime);

    processes[0].waitingTime = 0;
    for (int i = 1; i < n; i++)
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;

    for (int i = 0; i < n; i++)
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime, processes[i].waitingTime, processes[i].turnAroundTime);

    int sumWaitingTime = 0, sumTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        sumWaitingTime += processes[i].waitingTime;
        sumTurnAroundTime += processes[i].turnAroundTime;
    }
    printf("Average Waiting Time : %.2f\n", (float)sumWaitingTime / n);
    printf("Average Turnaround Time : %.2f\n", (float)sumTurnAroundTime / n);
}
