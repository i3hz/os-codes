#include <stdio.h>

typedef struct {
    int pid;            // Process ID
    int burst_time;     // Burst time
    int waiting_time;   // Waiting time
    int turnaround_time; // Turnaround time
} Process;

void print_gantt_chart(Process p[], int n) {
    int i, j; // Loop variables

    // Sort processes by burst time in ascending order (for SJF scheduling)
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) { // If the current burst time is greater than the next, swap them
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Print the top bar of the Gantt chart
    printf(" ");
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--"); // Print dashes based on burst time
        printf(" ");
    }
    printf("\n|");

    // Print process IDs inside the Gantt chart
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" "); // Print spaces for alignment
        printf("P%d", p[i].pid); // Print process ID
        for (j = 0; j < p[i].burst_time - 1; j++)
            printf(" "); // Print spaces for alignment
        printf("|"); // Print separator for each process
    }
    printf("\n ");

    // Print the bottom bar of the Gantt chart
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("--"); // Print dashes based on burst time
        printf(" ");
    }
    printf("\n");

    // Print the timeline below the Gantt chart
    printf("0"); // Start time
    int currentTime = 0;
    for (i = 0; i < n; i++) {
        currentTime += p[i].burst_time;
        for (j = 0; j < p[i].burst_time; j++)
            printf("  "); // Print spaces for alignment
        printf("%d", currentTime); // Print turnaround time (end time) for each process
    }
    printf("\n");
}

int main() {
    int n, i, j; // Variables for number of processes and loop indices

    // Ask the user for the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], wait[n], turnaround[n], total_wait = 0, total_tat = 0; // Arrays for burst, waiting, and turnaround times, and total waiting and turnaround time counters
    int proc[n], temp; // Array to store process IDs and a temporary variable for sorting
    Process p[n]; // Array of processes

    // Get burst time for each process
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]); // Store burst time in burst array
        proc[i] = i + 1; // Assign process ID
        p[i].pid = proc[i];
        p[i].burst_time = burst[i];
    }

    // Sorting processes by burst time in ascending order (for SJF scheduling)
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) { // If the current burst time is greater than the next, swap them
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Initialize waiting time for the first process to 0
    wait[0] = 0;

    // Calculate waiting time for each process
    for (i = 1; i < n; i++) {
        wait[i] = wait[i - 1] + p[i - 1].burst_time; // Waiting time of current process is the waiting time of the previous process plus its burst time
        total_wait += wait[i]; // Add waiting time to total waiting time
    }

    // Calculate turnaround time for each process
    for (i = 0; i < n; i++) {
        turnaround[i] = wait[i] + p[i].burst_time; // Turnaround time is waiting time + burst time
        total_tat += turnaround[i]; // Add turnaround time to total turnaround time
        p[i].waiting_time = wait[i];
        p[i].turnaround_time = turnaround[i];
    }

    // Print the results in a table format
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time); // Display process ID, burst time, waiting time, and turnaround time
    }

    // Calculate and display average waiting time and average turnaround time
    printf("\nAverage Waiting Time = %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    print_gantt_chart(p, n);

    return 0; // Indicate successful execution
}


