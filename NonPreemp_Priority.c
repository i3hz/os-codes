#include <stdio.h>


int main() {
    int n, i, j; // Declare variables: n (number of processes), i and j (loop counters)
   
    // Prompt user to enter the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n); // Read number of processes


    // Declare arrays for burst time, priority, waiting time, turnaround time, and process numbers
    int burst[n], priority[n], wait[n], turnaround[n], proc[n], total_wait = 0, total_tat = 0;


    // Input burst times and priorities for each process
    for(i = 0; i < n; i++) {
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &burst[i], &priority[i]); // Read burst time and priority for each process
        proc[i] = i + 1;  // Store process numbers for output (1-indexed for readability)
    }


    // Sorting based on priority (Non-Preemptive) - Lower value means higher priority
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            // If priority[i] > priority[j], swap to arrange in ascending order
            if(priority[i] > priority[j]) {
                // Swap priority
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;


                // Swap burst times
                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;


                // Swap process numbers
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }


    // Waiting time for the first process is 0
    wait[0] = 0;


    // Calculate waiting time for each process
    for(i = 1; i < n; i++) {
        wait[i] = wait[i - 1] + burst[i - 1]; // Waiting time = waiting time of previous process + burst time of previous process
        total_wait += wait[i]; // Add to total waiting time
    }


    // Calculate turnaround time for each process
    for(i = 0; i < n; i++) {
        turnaround[i] = wait[i] + burst[i]; // Turnaround time = waiting time + burst time
        total_tat += turnaround[i]; // Add to total turnaround time
    }


    // Display the results in a table format
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i], burst[i], priority[i], wait[i], turnaround[i]);
    }


    // Calculate and display average waiting time and turnaround time
    printf("\nAverage Waiting Time = %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);


    return 0; // End of the program
}



