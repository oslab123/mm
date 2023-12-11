#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process *processes = (Process *)malloc(n * sizeof(Process));
    
    for(int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process #%d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    int current_time = 0; 
    int completed = 0;
    int prev = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    while(completed != n) {
        int idx = -1;
        int minimum = 10000000; // You can also use INT_MAX from limits.h
        
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if(processes[i].remaining_time < minimum) {
                    minimum = processes[i].remaining_time;
                    idx = i;
                }
                if(processes[i].remaining_time == minimum) {
                    if(processes[i].arrival_time < processes[idx].arrival_time) {
                        minimum = processes[i].remaining_time;
                        idx = i;
                    }
                }
            }
        }
        
        if(idx != -1) {
            if(prev != processes[idx].pid) {
                printf("At time %d: Process #%d started\n", current_time, processes[idx].pid);
            }
            processes[idx].remaining_time -= 1;
            current_time++;
            prev = processes[idx].pid;
            
            if(processes[idx].remaining_time == 0) {
                completed++;
                
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                
                total_waiting_time += processes[idx].waiting_time;
                total_turnaround_time += processes[idx].turnaround_time;
                
                printf("At time %d: Process #%d completed\n", current_time, processes[idx].pid);
            }
        } else {
             current_time++;
        }
    }
    
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time = %.2f\n", (float)total_waiting_time / n);

    free(processes);
    
    return 0;
}

