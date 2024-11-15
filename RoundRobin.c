#include <stdio.h>  

int main() {
    int n, i, quantum, time = 0, remain;  // Declare variables for number of processes, index, time quantum, current time, and remaining processes
    printf("Enter number of processes: ");
    scanf("%d", &n);  // Read the number of processes

    // Arrays to hold burst times, remaining burst times, waiting times, and turnaround times for each process
    int burst[n], remain_burst[n], wait[n], turnaround[n];
    int total_wait = 0, total_tat = 0;  // Variables to hold total waiting time and total turnaround time
    int gantt_chart[100], gantt_time[100];  // Arrays to store the Gantt chart processes and time

    // Input burst time for each process
    for(i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);  // Read burst time for each process
        remain_burst[i] = burst[i];  // Initialize remaining burst time to the burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);  // Read the time quantum
    remain = n;  // Initialize remaining processes to the total number of processes

    // Process scheduling loop
    int gantt_index = 0;  // To keep track of the index in the Gantt chart
    while(remain != 0) {  // Continue until all processes are completed
        for(i = 0; i < n; i++) {  // Iterate through each process
            if(remain_burst[i] > 0) {  // Check if the current process has remaining burst time
                if(remain_burst[i] <= quantum) {  // If remaining burst time is less than or equal to quantum
                    gantt_chart[gantt_index] = i + 1;  // Add process to Gantt chart
                    gantt_time[gantt_index] = time;  // Store the time before this process runs for quantum
                    time += remain_burst[i];  // Increment time by the remaining burst time
                    gantt_index++;
                    wait[i] = time - burst[i];  // Calculate waiting time for the process
                    turnaround[i] = time;  // Calculate turnaround time for the process
                    total_wait += wait[i];  // Accumulate total waiting time
                    total_tat += turnaround[i];  // Accumulate total turnaround time
                    remain_burst[i] = 0;  // Mark the process as completed
                    remain--;  // Decrement the count of remaining processes
                } else {  // If remaining burst time is greater than quantum
                    gantt_chart[gantt_index] = i + 1;  // Add process to Gantt chart
                    gantt_time[gantt_index] = time;  // Store the time before this process runs for quantum
                    time += quantum;  // Increment time by the quantum value
                    gantt_index++;
                    remain_burst[i] -= quantum;  // Decrease remaining burst time by the quantum
                }
            }
        }
    }

    // Output the results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {  // Display information for each process
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst[i], wait[i], turnaround[i]);
    }

    // Calculate and display average waiting time and average turnaround time
    printf("\nAverage Waiting Time = %.2f", (float)total_wait / n);  // Calculate and print average waiting time
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);  // Calculate and print average turnaround time

    // Printing Gantt chart
    printf("\nGantt Chart:\n");
    printf("   ");
    for(i = 0; i < gantt_index; i++) {
        printf("----");
    }
    printf("\n   ");
    for(i = 0; i < gantt_index; i++) {
        printf("| P%d ", gantt_chart[i]);
    }
    printf("|\n   ");
    for(i = 0; i < gantt_index; i++) {
        printf("----");
    }
    printf("\n   ");
    for(i = 0; i < gantt_index; i++) {
        printf("%-4d", gantt_time[i]);
    }
    // Print the final time (after last process completion)
    printf("%-4d", time);
    printf("\n");

    return 0;  // Return 0 to indicate successful execution
}
