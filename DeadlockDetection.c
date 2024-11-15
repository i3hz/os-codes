#include <stdio.h>

int main() {
    int n = 5;                         // Number of processes  
    int m = 3;                         // Number of resources (3 resources: A, B, C)

    // Allocation matrix (Alloc[i][j] indicates number of instances of resource j allocated to process i)
    int alloc[5][3] = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}   // P4
    };

    // Request matrix (Request[i][j] indicates number of instances of resource j requested by process i)
    int request[5][3] = {
        {0, 0, 0},  // P0
        {2, 0, 2},  // P1
        {0, 0, 0},  // P2
        {1, 0, 0},  // P3
        {0, 0, 2}   // P4
    };

    // Total instances of resources
    int total[3] = {7, 2, 6};   // Total resources: A=10, B=5, C=7

    // Available Resources as given in the question (A=3, B=3, C=2)
    int avail[3] = {0, 0, 0};    // Available resources for A, B, C

    // Calculate the need matrix (Need[i][j] = Request[i][j] - Alloc[i][j])
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = request[i][j] - alloc[i][j];
        }
    }

    // Check for deadlock
    int f[n], deadlock_detected = 1;  
    int safe_count = 0;  // To track if processes can be completed safely

    // Initially, set all processes as not finished
    for (int i = 0; i < n; i++) {
        f[i] = 0;  // f[i] = 0 means process i is not finished
    }

    // Loop to detect deadlock
    while (safe_count < n) {
        int progress_made = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // If process i is not finished
                int can_allocate = 1;
                for (int j = 0; j < m; j++) {
                    // Check if request for each resource is less than or equal to available resources
                    if (need[i][j] > avail[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                // If resources can be allocated, mark process as finished
                if (can_allocate) {
                    f[i] = 1;
                    safe_count++;
                    // Release resources back to available pool
                    for (int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    progress_made = 1;
                    break; // Break out of the loop to check again if progress was made
                }
            }
        }

        // If no progress was made, it means we are in a deadlock state
        if (!progress_made) {
            deadlock_detected = 0;
            break;
        }
    }

    // Output the result
    if (deadlock_detected) {
        printf("No deadlock detected. System is in a safe state.\n");
    } else {
        printf("Deadlock detected in the system.\n");
    }

    return 0;
}