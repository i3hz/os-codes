// next fit  
#include <stdio.h> 

// Function to perform Next Fit memory allocation
void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store the block ID allocated to each process
    int j = 0; // Keeps track of the last allocated block

    // Initialize all allocations to -1 (indicating no block is allocated initially)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Pick each process and find the next fit block
    for (int i = 0; i < n; i++) {
        // Continue searching for a block starting from the last allocation point
        while (j < m) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to the current process
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // Reduce the block size by the allocated process size
                j = (j + 1) % m; // Move to the next block in a circular manner
                break;
            }
            j = (j + 1) % m; // Move to the next block, wrapping around if necessary
        }
    }

    // Print the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]); // Print the process number and its size
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // If allocated, print the block number (1-indexed for readability)
        else
            printf("Not Allocated\n"); // If not allocated, indicate that
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600}; // Array of block sizes available
    int processSize[] = {212, 417, 112, 426};    // Array of process sizes
    int m = sizeof(blockSize) / sizeof(blockSize[0]); // Calculate number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]); // Calculate number of processes

    // Call the nextFit function to perform memory allocation
    nextFit(blockSize, m, processSize, n);

    return 0; // Indicate successful execution
}

