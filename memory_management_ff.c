// first fit
#include <stdio.h> 

// Function to perform First Fit memory allocation
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store the block ID allocated to each process
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // Initialize all allocations to -1 (indicating no initial allocation)
    }

    // Pick each process and find the first fit block
    for (int i = 0; i < n; i++) {
        // Traverse through each block to find the first suitable one
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) { // If block can fit the process
                allocation[i] = j; // Allocate block j to process i
                blockSize[j] -= processSize[i]; // Reduce block size by the process size
                break; // Move to the next process once allocated
            }
        }
    }

    // Display the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // Print the block number (1-indexed for readability)
        else
            printf("Not Allocated\n"); // Indicate if no suitable block was found
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600}; // Array of available block sizes
    int processSize[] = {212, 417, 112, 426};    // Array of process sizes
    int m = sizeof(blockSize) / sizeof(blockSize[0]); // Calculate the number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]); // Calculate the number of processes

    // Call the firstFit function to perform memory allocation
    firstFit(blockSize, m, processSize, n);

    return 0; // Indicate successful execution
}

