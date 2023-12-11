#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
} Process;

int main() {
    int n, currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process proc[MAX], temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for process #%d: ", i+1);
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].pid = i+1;
        proc[i].remaining_time = proc[i].burst_time;
    }

    while(completed != n) {
        // Find the process with highest priority at the current time
        int idx = -1;
        int min = 10000000; // Initialize min with a large number
        for(int i = 0; i < n; i++) {
            if(proc[i].arrival_time <= currentTime && proc[i].remaining_time > 0) {
                if(proc[i].priority < min) {
                    min = proc[i].priority;
                    idx = i;
                }
                // If priority match, pick the one with lowest arrival time
                if(proc[i].priority == min) {
                    if(idx == -1 || proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(proc[idx].remaining_time == proc[idx].burst_time) {
                proc[idx].start_time = currentTime;
            }
            // Execute the process for 1 unit of time
            proc[idx].remaining_time--;
            currentTime++;

            // Check if the process is completed
            if(proc[idx].remaining_time == 0) {
                proc[idx].completion_time = currentTime;
                proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
                proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
                
                totalWaitingTime += proc[idx].waiting_time;
                totalTurnaroundTime += proc[idx].turnaround_time;
                
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    // Display the details
    printf("\nPId\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].priority, proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Turnaround Time = %.2f\n", totalTurnaroundTime/n);
    printf("Average Waiting Time = %.2f\n", totalWaitingTime/n);

    return 0;
}

