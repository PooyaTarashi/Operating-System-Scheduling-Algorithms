#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int burstTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int lastExecTime;
} Process;

int compareByPriority(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processB->priority - processA->priority;
}

int currTime = 0;
Process heap[MAX_PROCESSES];
Process done[MAX_PROCESSES];
int doneIdx = 0;
int heapSize = 0;

void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void siftUp(int index)
{
    while (index > 0 && (heap[(index - 1) / 2].priority < heap[index].priority
                        || heap[(index - 1) / 2].priority == heap[index].priority && heap[(index - 1) / 2].lastExecTime > heap[index].lastExecTime
                        || heap[(index - 1) / 2].priority == heap[index].priority && heap[(index - 1) / 2].lastExecTime == heap[index].lastExecTime && heap[(index - 1) / 2].id > heap[index].id))
    {
        swap(&heap[index], &heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void siftDown(int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && (heap[left].priority > heap[largest].priority 
                        || heap[left].priority == heap[largest].priority && heap[left].lastExecTime < heap[largest].lastExecTime
                        || heap[left].priority == heap[largest].priority && heap[left].lastExecTime == heap[largest].lastExecTime && heap[left].id < heap[largest].id))
        largest = left;
        
    if (right < heapSize && (heap[right].priority > heap[largest].priority 
                        || heap[right].priority == heap[largest].priority && heap[right].lastExecTime < heap[largest].lastExecTime
                        || heap[right].priority == heap[largest].priority && heap[right].lastExecTime == heap[largest].lastExecTime && heap[right].id < heap[largest].id))
        largest = right;
    
    if (largest != index)
    {
        swap(&heap[index], &heap[largest]);
        siftDown(largest);
    }
}

Process extractMax()
{
    Process maxProcess = heap[0];
    heap[0] = heap[--heapSize];
    siftDown(0);
    return maxProcess;
}

void insertProcess(Process p)
{
    heap[heapSize] = p;
    siftUp(heapSize);
    heapSize++;
}

void simulateRoundRobinPriority(int q)
{
    while (heapSize > 0)
    {
        Process currTask = extractMax();

        printf("P%d ", currTask.id + 1);

        if (currTask.remainingTime == currTask.burstTime)
            currTask.waitingTime = currTime;
        else
            currTask.waitingTime += (currTime - currTask.lastExecTime);
// todo: waiting time ro dorost hesab nemikone wait haye jadid ro dar nazar nemigire // done

        if (currTask.remainingTime <= q)
        {
            currTime += currTask.remainingTime;
            currTask.remainingTime = 0;
            currTask.turnaroundTime = currTime;
            done[doneIdx++] = currTask;
        }
        else 
        {
            currTask.remainingTime -= q;
            currTime += q;
            currTask.lastExecTime = currTime;
            insertProcess(currTask);
        }
    }
}

int main()
{
    int n, q;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i;
        printf("Enter burst time for process P%d : ", i + 1);
        scanf("%d", &p.burstTime);
        p.remainingTime = p.burstTime;

        printf("Enter priority for process P%d : ", i + 1);
        scanf("%d", &p.priority);

        p.waitingTime = 0;
        p.turnaroundTime = 0;
        p.lastExecTime = 0;

        insertProcess(p);
    }

    printf("Enter time quantum : ");
    scanf("%d", &q);

    simulateRoundRobinPriority(q);

    qsort(done, doneIdx, sizeof(Process), compareByPriority);

    int wt = 0;
    int tt = 0;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < doneIdx; i++)
    {
        wt += done[i].waitingTime;
        tt += done[i].turnaroundTime;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", done[i].id + 1, done[i].burstTime, done[i].priority, done[i].waitingTime, done[i].turnaroundTime);
    }

    printf("Average Waiting Time : %.2f\n", (float)wt / doneIdx);
    printf("Average Turnaround Time : %.2f\n", (float)tt / doneIdx);
}
