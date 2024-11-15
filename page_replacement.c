#include <stdio.h>
#include <stdbool.h>

// Function for FIFO Page Replacement
void fifo(int pages[], int n, int capacity) {
    int frames[capacity], front = 0, faults = 0; // Initialize frames, front pointer, and fault counter

    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int found = 0; // Flag to check if page is found in frames

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) { // Page found
                found = 1; // Set found flag
                break; // No need to check further
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            frames[front] = pages[i]; // Replace the page in the current frame
            front = (front + 1) % capacity; // Move front pointer circularly
            faults++; // Increment page fault counter
        }
    }

    // Print the total number of page faults
    printf("FIFO Total Page Faults = %d\n", faults);
}

// Function for Optimal Page Replacement
void optimal(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0; // Initialize frames and fault counter

    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int found = 0; // Flag to check if page is found in frames

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) { // Page found
                found = 1; // Set found flag
                break; // No need to check further
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            int farthest = i, replace = -1; // Initialize farthest usage index and replace index
            // Find the frame to replace
            for (int j = 0; j < capacity; j++) {
                int k;
                // Check future references to find the farthest used frame
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) { // If page is found in future
                        if (k > farthest) { // Check if it's the farthest one
                            farthest = k; // Update farthest usage
                            replace = j; // Update frame to replace
                        }
                        break; // Stop checking further
                    }
                }
                // If page not found in future references
                if (k == n) {
                    replace = j; // This frame can be replaced
                    break; // No need to check further
                }
            }
            // If no frame was found to replace, replace the first one
            if (replace == -1)
                replace = 0;
            frames[replace] = pages[i]; // Replace the page in the selected frame
            faults++; // Increment page fault counter
        }
    }

    // Print the total number of page faults
    printf("Optimal Total Page Faults = %d\n", faults);
}

// Function for LRU Page Replacement
void lru(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0; // Initialize frames and fault counter
    int time[capacity]; // To track the time of last use for each frame

    // Initialize all frames to -1 (indicating they are empty)
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int found = 0; // Flag to check if page is found in frames

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) { // Page found
                found = 1; // Set found flag
                time[j] = i; // Update the last use time
                break; // No need to check further
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            int leastUsed = 0; // Assume the first frame is the least recently used
            // Find the least recently used frame
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[leastUsed]) // If this frame was used less recently
                    leastUsed = j; // Update least used frame
            }
            frames[leastUsed] = pages[i]; // Replace the least recently used page
            time[leastUsed] = i; // Update the time of use
            faults++; // Increment page fault counter
        }
    }

    // Print the total number of page faults
    printf("LRU Total Page Faults = %d\n", faults);
}

// Function for Clock Page Replacement
void clock_algo(int pages[], int n, int capacity) {
    int frames[capacity], use[capacity], pointer = 0, faults = 0; // Initialize frames, use bits, pointer, and fault counter

    // Initialize all frames to -1 and use bits to 0
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Set frames to empty
        use[i] = 0; // Set use bits to 0
    }

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int found = 0; // Flag to check if page is found in frames

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) { // Page found
                found = 1; // Set found flag
                use[j] = 1; // Set the use bit
                break; // No need to check further
            }
        }

        // If the page is not found, a page fault occurs
        if (!found) {
            // Look for a page to replace
            while (use[pointer] == 1) { // While the use bit is set
                use[pointer] = 0; // Clear the use bit
                pointer = (pointer + 1) % capacity; // Move to the next frame circularly
            }
            frames[pointer] = pages[i]; // Replace the page in the selected frame
            use[pointer] = 1; // Set the use bit for the replaced frame
            pointer = (pointer + 1) % capacity; // Move pointer to the next frame
            faults++; // Increment page fault counter
        }
    }

    // Print the total number of page faults
    printf("Clock Total Page Faults = %d\n", faults);
}

int main() {
    int n, capacity, choice; // Variables for number of pages, frame capacity, and user choice

    // Prompt user for number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n); // Read number of pages

    int pages[n]; // Array to hold page references
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]); // Read page references into the array
    }

    // Prompt user for number of frames
    printf("Enter number of frames: ");
    scanf("%d", &capacity); // Read the capacity of frames

    // Display options for page replacement algorithms
    printf("Page Replacement Algorithms:\n");
    printf("1. FIFO\n2. Optimal\n3. LRU\n4. Clock\n5. Display all algorithms\n");
    printf("Choose an algorithm (1-5): ");
    scanf("%d", &choice); // Read user's choice

    // Switch case to select and run the chosen page replacement algorithm
    switch (choice) {
        case 1:
            fifo(pages, n, capacity); // Call FIFO function
            break;
        case 2:
            optimal(pages, n, capacity); // Call Optimal function
            break;
        case 3:
            lru(pages, n, capacity); // Call LRU function
            break;
        case 4:
            clock_algo(pages, n, capacity); // Call Clock function
            break;
        case 5:
            // Run all algorithms sequentially
            printf("Running FIFO...\n");
            fifo(pages, n, capacity);
            printf("Running Optimal...\n");
            optimal(pages, n, capacity);
            printf("Running LRU...\n");
            lru(pages, n, capacity);
            printf("Running Clock...\n");
            clock_algo(pages, n, capacity);
            break;
        default:
            printf("Invalid choice!\n"); // Handle invalid choice
            break;
    }

    return 0; // Return 0 to indicate successful execution
}

/*
#include <stdio.h>

void fifo(int pages[], int n, int capacity) {
    int frames[capacity], front = 0, faults = 0;

    // Initialize frames to -1
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    // Process each page
    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % capacity;
            faults++;
        }
    }

    printf("FIFO Total Page Faults = %d\n", faults);
}

int main() {
    int pages[] = {7,1,0,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1}; // Example page references
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo(pages, n, capacity);
    return 0;
}

*/


/*
#include <stdio.h>

void optimal(int pages[], int n, int capacity) {
    int frames[capacity], faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int farthest = i, replace = -1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replace = j;
                    break;
                }
            }
            if (replace == -1)
                replace = 0;

            frames[replace] = pages[i];
            faults++;
        }
    }

    printf("Optimal Total Page Faults = %d\n", faults);
}

int main() {
    int pages[] = {7,1,0,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    optimal(pages, n, capacity);
    return 0;
}
*/


/*
#include <stdio.h>

void lru(int pages[], int n, int capacity) {
    int frames[capacity], time[capacity], faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if (!found) {
            int leastUsed = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[leastUsed])
                    leastUsed = j;
            }
            frames[leastUsed] = pages[i];
            time[leastUsed] = i;
            faults++;
        }
    }

    printf("LRU Total Page Faults = %d\n", faults);
}

int main() {
    int pages[] = {7,1,0,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    lru(pages, n, capacity);
    return 0;
}
*/


/*
#include <stdio.h>

void clock_algo(int pages[], int n, int capacity) {
    int frames[capacity], use[capacity], pointer = 0, faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        use[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                use[j] = 1;
                break;
            }
        }

        if (!found) {
            while (use[pointer] == 1) {
                use[pointer] = 0;
                pointer = (pointer + 1) % capacity;
            }
            frames[pointer] = pages[i];
            use[pointer] = 1;
            pointer = (pointer + 1) % capacity;
            faults++;
        }
    }

    printf("Clock Total Page Faults = %d\n", faults);
}

int main() {
    int pages[] = {7,1,0,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    clock_algo(pages, n, capacity);
    return 0;
}
*/
