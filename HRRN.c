#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int* arrival = (int*)calloc(n, sizeof(int));
    int* s = (int*)calloc(n, sizeof(int));
    int* done = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival[i]);
        scanf("%d", &s[i]);
    }

    int currTime = 0;
    int doneJob = 0;
    int awt = 0;
    while (doneJob < n)
    {
        int maxRRIDX = 0;
        float maxRR = 0;
        for (int i = 0; i < n; i++)
        {
            if (done[i] == 0 && arrival[i] <= currTime)
            {
                int rr = (float)((currTime - arrival[i]) + s[i]) / s[i];
                if (rr > maxRR)
                {
                    maxRR = rr;
                    maxRRIDX = i;
                }
                
            }
        }

        printf("process %d is executed at %d\n", maxRRIDX, currTime);

        awt += (currTime - arrival[maxRRIDX]);
        done[maxRRIDX] = 1;
        currTime += s[maxRRIDX];
        doneJob++;
        
    }

    printf("average waiting time: %.3f\n", (float)awt / n);   
    
}