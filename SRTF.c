#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void swap(Process *x, Process *y)
{
    Process temp = *x;
    *x = *y;
    *y = temp;
}

int cmprArrivalTime(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrivalTime - p2->arrivalTime;
}

void minHeapify(Process* minHeap, int* size, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < *size && minHeap[left].remainingTime < minHeap[smallest].remainingTime)
        smallest = left;

    if (right < *size && minHeap[right].remainingTime < minHeap[smallest].remainingTime)
        smallest = right;

    if (smallest != idx)
    {
        swap(&minHeap[smallest], &minHeap[idx]);
        minHeapify(minHeap, size, smallest);
    }
}

void insertMinHeap(Process* minHeap, int* size, Process process) {
    (*size)++;
    int i = (*size) - 1;
    minHeap[i] = process;

    while (i != 0 && minHeap[(i - 1) / 2].remainingTime > minHeap[i].remainingTime)
    {
        swap(&minHeap[i], &minHeap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Process extractMin(Process* minHeap, int* size)
{
    if ((*size) == 1)
    {
        (*size)--;
        return minHeap[0];
    }

    Process root = minHeap[0];
    minHeap[0] = minHeap[(*size) - 1];
    (*size)--;
    minHeapify(minHeap, size, 0);

    return root;
}

void SRTF(Process* processes, int n) {
    Process* minHeap = (Process*)calloc(n, sizeof(Process));
    int size = 0;
    
    int completed = 0;
    int totalTime = 0;
    int index = 0;
    
    qsort(processes, n, sizeof(Process), cmprArrivalTime);
    
    Process current = processes[index++];
    totalTime = current.arrivalTime;

    while (completed != n)
    {
        while (index < n && processes[index].arrivalTime <= totalTime)
            insertMinHeap(minHeap, &size, processes[index++]);

        if (size != 0 && minHeap[0].remainingTime < current.remainingTime)
        {
            insertMinHeap(minHeap, &size, current);
            current = extractMin(minHeap, &size);
        }

        current.remainingTime--;
        totalTime++;

        if (current.remainingTime == 0)
        {
            current.turnaroundTime = totalTime - current.arrivalTime;
            current.waitingTime = current.turnaroundTime - current.burstTime;
            processes[current.processID - 1] = current;
            completed++;

            if (size != 0)
                current = extractMin(minHeap, &size);
            else if (index < n)
            {
                current = processes[index++];
                totalTime = current.arrivalTime;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process P%d : ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    SRTF(processes, n);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\t\n", processes[i].processID, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);

    int swt = 0;
    int stt = 0;
    for (int i = 0; i < n; i++)
    {
        swt += processes[i].waitingTime;
        stt += processes[i].turnaroundTime;
    }

    printf("Average Waiting Time : %.2f\n", (float)swt / n);
    printf("Average Turnaround Time : %.2f\n", (float)stt / n);
}
