// First Come First Serve
#include <stdio.h>  
#include <stdlib.h> 

#define MAX 100 // Define a maximum limit for the number of processes

// Structure to represent each process
typedef struct {
    int pid;             // Process ID
    int burst_time;      // Burst time of the process
    int waiting_time;    // Waiting time for the process
    int turnaround_time; // Turnaround time for the process
} Process;
// Function declaration to print the Gantt chart
void print_gantt_chart(Process p[], int n);

int main() {
    Process p[MAX]; // Array to store information of processes
    int i, n; // Loop variable i, and n to store the number of processes
    int sum_waiting_time = 0, sum_turnaround_time = 0; // Sum of waiting times and turnaround times
    float avgwt = 0; // Variable to store average waiting time
    float avgtt = 0; // Variable to store average turnaround time

    // Get the total number of processes from the user
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    // Get the burst time for each process from the user
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1; // Assign process ID (P1, P2, etc.)
        printf("P[%d] : ", i + 1); // Prompt for burst time of process P[i+1]
        scanf("%d", &p[i].burst_time); // Read burst time
        p[i].waiting_time = p[i].turnaround_time = 0; // Initialize waiting and turnaround times to 0
    }

    // First process has no waiting time, so its turnaround time equals its burst time
    p[0].turnaround_time = p[0].burst_time;

    // Calculate waiting and turnaround times for each process
    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time; // Waiting time of current process
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time; // Turnaround time of current process
    }

    // Calculate total waiting and turnaround times
    for (i = 0; i < n; i++) {
        sum_waiting_time += p[i].waiting_time; // Add waiting time of each process
        sum_turnaround_time += p[i].turnaround_time; // Add turnaround time of each process
    }

    // Calculate average waiting and turnaround times
    avgwt = (float)sum_waiting_time / n;
    avgtt = (float)sum_turnaround_time / n;

    // Display average waiting time and average turnaround time
    printf("Average Waiting Time : %.2f \n", avgwt);
    printf("Average Turnaround Time : %.2f \n", avgtt);
    printf("          GANTT CHART          \n");
    printf("          ***          \n");

    // Call function to print the Gantt chart for the given processes
    print_gantt_chart(p, n);

    return 0; // Indicate successful execution
}

// Function to print the Gantt chart for the FCFS scheduling
void print_gantt_chart(Process p[], int n) {
    int i, j; // Loop variables

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
    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].burst_time; j++)
            printf("  "); // Print spaces for alignment
        printf("%d", p[i].turnaround_time); // Print turnaround time as the end time for each process
    }
    printf("\n");
}
