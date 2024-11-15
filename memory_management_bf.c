// best fit
#include <stdio.h> 

// Function to allocate memory to processes using the Best Fit algorithm
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store the index of the block allocated to each process
    
    // Initialize all allocations to -1 (indicating no block is allocated initially)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process to find a suitable block
    for (int i = 0; i < n; i++) {
        int bestIdx = -1; // Initialize bestIdx to -1, indicating no block selected yet

        // Find the best-fit block for the current process
        for (int j = 0; j < m; j++) {
            // Check if blockSize[j] can accommodate processSize[i]
            if (blockSize[j] >= processSize[i]) {
                // If bestIdx is -1 or the current block is a tighter fit, update bestIdx
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block was found, allocate it to the process
        if (bestIdx != -1) {
            allocation[i] = bestIdx; // Assign bestIdx as the block for the current process
            blockSize[bestIdx] -= processSize[i]; // Reduce available block size by the allocated amount
        }
    }

    // Print results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        // If a block was allocated, print the block number (1-indexed); otherwise, indicate "Not Allocated"
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600}; // Block sizes available
    int processSize[] = {212, 417, 112, 426};     // Sizes of processes to allocate
    int m = sizeof(blockSize) / sizeof(blockSize[0]); // Number of blocks
    int n = sizeof(processSize) / sizeof(processSize[0]); // Number of processes

    bestFit(blockSize, m, processSize, n); // Call the bestFit function to allocate memory

    return 0; // End of program
}

