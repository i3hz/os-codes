#include <stdio.h>   
#include <stdlib.h>  // for functions like abs and qsort

#define MAX 100  // Define a constant for maximum number of requests

// Function prototypes for disk scheduling algorithms
void fcfs(int requests[], int n, int head);
void sstf(int requests[], int n, int head);
void scan(int requests[], int n, int head, int disk_size);
void c_scan(int requests[], int n, int head, int disk_size);

int main() {
    int n, i, head, disk_size, choice;  // Variables for number of requests, head position, disk size, and user choice
    int requests[MAX];  // Array to hold disk requests

    // Prompt user for the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);  // Read number of requests

    // Prompt user for the disk requests
    printf("Enter the requests: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);  // Read each request into the array
    }

    // Prompt user for the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);  // Read initial head position

    // Prompt user for the disk size
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);  // Read the total size of the disk

    // Display available disk scheduling algorithms
    printf("Disk Scheduling Algorithms:\n");
    printf("1. FCFS\n");   // First-Come, First-Served
    printf("2. SSTF\n");   // Shortest Seek Time First
    printf("3. SCAN\n");   // SCAN
    printf("4. C-SCAN\n");  // Circular SCAN
    printf("5. Display all algorithms\n");  // option to display results of all algorithms
    printf("Choose an algorithm: ");
    scanf("%d", &choice);  // Read user's choice for algorithm

    // Switch case to select and run the chosen disk scheduling algorithm
    switch(choice) {
        case 1:
            fcfs(requests, n, head);  // Call FCFS function
            break;
        case 2:
            sstf(requests, n, head);  // Call SSTF function
            break;
        case 3:
            scan(requests, n, head, disk_size);  // Call SCAN function
            break;
        case 4:
            c_scan(requests, n, head, disk_size);  // Call C-SCAN function
            break;
        case 5:
            printf("\nRunning all algorithms:\n\n");
            printf("---- FCFS ----\n");
            fcfs(requests, n, head);  // Display result of FCFS
            printf("\n---- SSTF ----\n");
            sstf(requests, n, head);  // Display result of SSTF
            printf("\n---- SCAN ----\n");
            scan(requests, n, head, disk_size);  // Display result of SCAN
            printf("\n---- C-SCAN ----\n");
            c_scan(requests, n, head, disk_size);  // Display result of C-SCAN
            break;
        default:
            printf("Invalid choice!\n");  // Handle invalid choice
            break;
    }

    return 0;  // Return 0 to indicate successful execution
}

// FCFS Disk Scheduling Algorithm
void fcfs(int requests[], int n, int head) {
    int seek_count = 0, distance, cur_track;  // Initialize seek count, distance, and current track

    printf("FCFS Disk Scheduling:\n");

    // Process each request in the order they were received
    for (int i = 0; i < n; i++) {
        cur_track = requests[i];  // Get the current request track
        distance = abs(cur_track - head);  // Calculate distance from current head position to the track
        seek_count += distance;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, cur_track, distance);  // Print movement info
        head = cur_track;  // Update head position to the current track
    }

    printf("Total seek time: %d\n", seek_count);  // Print total seek time for FCFS
}

// SSTF Disk Scheduling Algorithm
void sstf(int requests[], int n, int head) {
    int seek_count = 0, distance, cur_track;  // Initialize seek count, distance, and current track
    int completed[MAX] = {0};  // Array to track which requests have been completed

    printf("SSTF Disk Scheduling:\n");

    // Process each request
    for (int i = 0; i < n; i++) {
        int min = MAX, index = -1;  // Initialize minimum distance and index for the next request

        // Find the closest request to the current head position
        for (int j = 0; j < n; j++) {
            if (!completed[j]) {  // Only consider uncompleted requests
                distance = abs(requests[j] - head);  // Calculate distance
                if (distance < min) {  // Check if this distance is the smallest found
                    min = distance;  // Update minimum distance
                    index = j;  // Update index of the closest request
                }
            }
        }

        completed[index] = 1;  // Mark the closest request as completed
        cur_track = requests[index];  // Get the current track from the closest request
        seek_count += min;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, cur_track, min);  // Print movement info
        head = cur_track;  // Update head position to the current track
    }

    printf("Total seek time: %d\n", seek_count);  // Print total seek time for SSTF
}

// SCAN Disk Scheduling Algorithm
void scan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, distance;  // Initialize seek count and distance
    int left[MAX], right[MAX], left_size = 0, right_size = 0;  // Arrays for left and right requests

    printf("SCAN Disk Scheduling:\n");

    // Divide requests into left and right based on the current head position
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {  // If request is on the left of the head
            left[left_size++] = requests[i];  // Add to left array
        } else {  // If request is on the right of the head
            right[right_size++] = requests[i];  // Add to right array
        }
    }

    left[left_size++] = 0;  // Add the start of the disk to the left requests
    right[right_size++] = disk_size - 1;  // Add the end of the disk to the right requests

    // Sort the left and right request arrays
    qsort(left, left_size, sizeof(int), (int (*)(const void *, const void *))abs);  // Sort left requests
    qsort(right, right_size, sizeof(int), (int (*)(const void *, const void *))abs);  // Sort right requests

    // First move towards the right
    for (int i = 0; i < right_size; i++) {
        distance = abs(right[i] - head);  // Calculate distance to the next right request
        seek_count += distance;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, right[i], distance);  // Print movement info
        head = right[i];  // Update head position to the current request
    }

    // Then move towards the left
    for (int i = left_size - 1; i >= 0; i--) {
        distance = abs(left[i] - head);  // Calculate distance to the next left request
        seek_count += distance;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, left[i], distance);  // Print movement info
        head = left[i];  // Update head position to the current request
    }

    printf("Total seek time: %d\n", seek_count);  // Print total seek time for SCAN
}

// C-SCAN Disk Scheduling Algorithm
void c_scan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, distance;  // Initialize seek count and distance
    int left[MAX], right[MAX], left_size = 0, right_size = 0;  // Arrays for left and right requests

    printf("C-SCAN Disk Scheduling:\n");

    // Divide requests into left and right based on the current head position
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {  // If request is on the left of the head
            left[left_size++] = requests[i];  // Add to left array
        } else {  // If request is on the right of the head
            right[right_size++] = requests[i];  // Add to right array
        }
    }

    left[left_size++] = 0;  // Add the start of the disk to the left requests
    right[right_size++] = disk_size - 1;  // Add the end of the disk to the right requests

    // Sort the left and right request arrays
    qsort(left, left_size, sizeof(int), (int (*)(const void *, const void *))abs);  // Sort left requests
    qsort(right, right_size, sizeof(int), (int (*)(const void *, const void *))abs);  // Sort right requests

    // First move towards the right
    for (int i = 0; i < right_size; i++) {
        distance = abs(right[i] - head);  // Calculate distance to the next right request
        seek_count += distance;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, right[i], distance);  // Print movement info
        head = right[i];  // Update head position to the current request
    }

    // Move from the end of the disk to the start
    head = 0;  // Reset head position to the start of the disk
    for (int i = 0; i < left_size; i++) {
        distance = abs(left[i] - head);  // Calculate distance to the next left request
        seek_count += distance;  // Update total seek count
        printf("Move from %d to %d with seek %d\n", head, left[i], distance);  // Print movement info
        head = left[i];  // Update head position to the current request
    }

    printf("Total seek time: %d\n", seek_count);  // Print total seek time for C-SCAN
}



/*
#include <stdio.h>
#include <stdlib.h>  // For abs function

void fcfs(int requests[], int n, int head) {
    int seek_count = 0, distance;

    printf("FCFS Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        distance = abs(requests[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with seek %d\n", head, requests[i], distance);
        head = requests[i];
    }
    printf("Total seek time: %d\n", seek_count);
}

int main() {
    int n = 8;  // Number of requests
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};  // Disk requests
    int head = 53;  // Initial head position

    fcfs(requests, n, head);

    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>  // For abs function

#define MAX 100

void sstf(int requests[], int n, int head) {
    int seek_count = 0, distance;
    int completed[MAX] = {0};

    printf("SSTF Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        int min = MAX, index = -1;
        for (int j = 0; j < n; j++) {
            if (!completed[j]) {
                distance = abs(requests[j] - head);
                if (distance < min) {
                    min = distance;
                    index = j;
                }
            }
        }
        completed[index] = 1;
        seek_count += min;
        printf("Move from %d to %d with seek %d\n", head, requests[index], min);
        head = requests[index];
    }
    printf("Total seek time: %d\n", seek_count);
}

int main() {
    int n = 8;
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;

    sstf(requests, n, head);

    return 0;
}

*/


/*
#include <stdio.h>
#include <stdlib.h>  // For abs and qsort functions

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void scan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, distance;
    int left[n], right[n], left_size = 0, right_size = 0;

    printf("SCAN Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_size++] = requests[i];
        else
            right[right_size++] = requests[i];
    }

    left[left_size++] = 0;
    right[right_size++] = disk_size - 1;

    qsort(left, left_size, sizeof(int), compare);
    qsort(right, right_size, sizeof(int), compare);

    for (int i = 0; i < right_size; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with seek %d\n", head, right[i], distance);
        head = right[i];
    }

    for (int i = left_size - 1; i >= 0; i--) {
        distance = abs(left[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with seek %d\n", head, left[i], distance);
        head = left[i];
    }
    printf("Total seek time: %d\n", seek_count);
}

int main() {
    int n = 8;
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int disk_size = 200;

    scan(requests, n, head, disk_size);

    return 0;
}

*/


/*
#include <stdio.h>
#include <stdlib.h>  // For abs and qsort functions

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void c_scan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, distance;
    int left[n], right[n], left_size = 0, right_size = 0;

    printf("C-SCAN Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_size++] = requests[i];
        else
            right[right_size++] = requests[i];
    }

    left[left_size++] = 0;
    right[right_size++] = disk_size - 1;

    qsort(left, left_size, sizeof(int), compare);
    qsort(right, right_size, sizeof(int), compare);

    for (int i = 0; i < right_size; i++) {
        distance = abs(right[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with seek %d\n", head, right[i], distance);
        head = right[i];
    }

    head = 0;
    for (int i = 0; i < left_size; i++) {
        distance = abs(left[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with seek %d\n", head, left[i], distance);
        head = left[i];
    }
    printf("Total seek time: %d\n", seek_count);
}

int main() {
    int n = 8;
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int disk_size = 200;

    c_scan(requests, n, head, disk_size);

    return 0;
}

*/