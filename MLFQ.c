#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int* arrival = (int*)calloc(n, sizeof(int));
    int* burst = (int*)calloc(n, sizeof(int));
    int* queue1 = (int*)calloc(n, sizeof(int));
    int* queue2 = (int*)calloc(n, sizeof(int));
    // int* queue3 = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival[i]);
        scanf("%d", &burst[i]);
    }
    


    int doneProcesses = 0;
    int currTime = 0;
    int previouslyRunning = -1;
    int currQueue = -1;
    while (doneProcesses < n)
    {
        int flg = 0;

        if (currTime == 23)
        {
            int gjntobintr = 0;
            gjntobintr = 1;
        }
        

        // Selecting Task for Queue 1
        int foundProcForQ1 = -1;
        int arrTimeQ1 = 99999;
        int selectedIDX = -1;
        for (int i = 0; i < n; i++)
        {
            if (burst[i] > 0 && arrival[i] <= currTime && queue1[i] < 8)
            {
                foundProcForQ1 = 1;
                if (arrival[i] < arrTimeQ1)
                {
                    selectedIDX = i;
                    arrTimeQ1 = arrival[i];
                }
                
            }
        }

        if (foundProcForQ1 == 1)
        {
            int i = selectedIDX;
            queue1[i]++;
            flg = 1;

            if (previouslyRunning != i || currQueue != 1)
                printf("Process %d is running in queue 1 at %d.\n", i, currTime);

            previouslyRunning = i;
            currQueue = 1;

            if (--burst[i] == 0)
                doneProcesses++;
        }





        // Select Item for Queue 2
        if (flg == 0)
        {
            int foundProcForQ2 = -1;
            int arrTimeQ2 = 99999;
            int selectedIDX = -1;
            for (int i = 0; i < n; i++)
            {
                if (burst[i] > 0 && arrival[i] <= currTime && queue2[i] < 16)
                {
                    foundProcForQ2 = 1;
                    if (arrival[i] < arrTimeQ2)
                    {
                        selectedIDX = i;
                        arrTimeQ2 = arrival[i];
                    }
                }
            }
            if (foundProcForQ2 == 1)
            {
                int i = selectedIDX;
                queue2[i]++;
                flg = 1;

                if (previouslyRunning != i || currQueue != 2)
                    printf("Process %d is running in queue 2 at %d.\n", i, currTime);

                currQueue = 2;
                previouslyRunning = i;

                if (--burst[i] == 0)
                    doneProcesses++;
            }
            
        }




        if (flg == 0)
        {
            int foundProcForQ3 = -1;
            int arrTimeQ3 = 99999;
            int selectedIDX = -1;
            for (int i = 0; i < n; i++)
            {
                if (burst[i] > 0 && arrival[i] <= currTime && queue1[i] >= 8 && queue2[i] >= 16)
                {
                    foundProcForQ3 = 1;
                    if (arrival[i] < arrTimeQ3)
                    {
                        selectedIDX = i;
                        arrTimeQ3 = arrival[i];
                    }
                }
            }
                
                
            if (foundProcForQ3)
            {
                int i = selectedIDX;
                if (previouslyRunning != i || currQueue != 3)
                    printf("Process %d is running in queue 3 at %d.\n", i, currTime);

                previouslyRunning = i;
                currQueue = 3;


                if (--burst[i] == 0)
                    doneProcesses++;
            }
        }
        
        
        currTime++;
    }
    
}