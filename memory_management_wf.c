// worst fit
#include <stdio.h> 

// Function to perform Worst Fit memory allocation
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Array to store the index of the block allocated to each process

    // Initialize all allocations to -1 (indicating no block is allocated initially)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Loop through each process to find the worst-fit block
    for (int i = 0; i < n; i++) {
        int worstIdx = -1; // Initialize worstIdx to -1, indicating no block selected yet

        // Iterate through each memory block to find the worst fit for the current process
        for (int j = 0; j < m; j++) {
            // Check if the current block can accommodate the process
            if (blockSize[j] >= processSize[i]) {
                // If no block has been selected yet or the current block is larger than the previously selected block
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) {
                    worstIdx = j; // Update worstIdx to the index of the current block
                }
            }
        }

        // If a suitable block was found, allocate it to the process
        if (worstIdx != -1) {
            allocation[i] = worstIdx; // Assign the block index to the process
            blockSize[worstIdx] -= processSize[i]; // Reduce the available size of the selected block by the size of the process
        }
    }

    // Print the allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]); // Print the process number and its size
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // If allocated, print the block number (1-indexed)
        else
            printf("Not Allocated\n"); // If not allocated, indicate that
    }
}

int main() {
    // Define the sizes of memory blocks available
    int blockSize[] = {100, 500, 200, 300, 600};
    // Define the sizes of processes to be allocated
    int processSize[] = {212, 417, 112, 426};
    
    // Calculate the number of blocks (m) and the number of processes (n)
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    // Call the worstFit function to perform memory allocation
    worstFit(blockSize, m, processSize, n);

    return 0; // Indicate successful execution of the program
}

