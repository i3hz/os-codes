// shortest remaining time first
#include <stdio.h>

int main() {
    int n, i, time = 0, smallest;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], remain[n], wait[n], turnaround[n], arrival[n];
    int total_wait = 0, total_tat = 0;
    int gantt_chart[100][2], gantt_chart_proc[100];
    int gantt_index = 0;

    for (i = 0; i < n; i++) {
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
        remain[i] = burst[i];
    }

    int completed = 0;
    int min_time = 9999;
    smallest = -1;

    for (time = 0; completed != n; time++) {
        smallest = -1;
        min_time = 9999;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remain[i] > 0 && remain[i] < min_time) {
                min_time = remain[i];
                smallest = i;
            }
        }

        if (smallest == -1) {
            continue;
        }

        remain[smallest]--;

        // Track the Gantt chart entries
        if (gantt_index == 0 || gantt_chart_proc[gantt_index - 1] != smallest + 1) {
            gantt_chart[gantt_index][0] = time;
            gantt_chart_proc[gantt_index] = smallest + 1;
            gantt_index++;
        }
        gantt_chart[gantt_index - 1][1] = time + 1;

        if (remain[smallest] == 0) {
            completed++;
            int completion_time = time + 1;
            wait[smallest] = completion_time - arrival[smallest] - burst[smallest];
            if (wait[smallest] < 0) wait[smallest] = 0;
            turnaround[smallest] = completion_time - arrival[smallest];
            total_wait += wait[smallest];
            total_tat += turnaround[smallest];
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], wait[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    // Print the Gantt chart in the desired format
    printf("\nGantt Chart:\n");
    printf("  ");
    for (i = 0; i < gantt_index; i++) {
        printf(" ---------------- ");
    }
    printf("\n |");
    for (i = 0; i < gantt_index; i++) {
        printf("      P%d       |", gantt_chart_proc[i]);
    }
    printf("\n  ");
    for (i = 0; i < gantt_index; i++) {
        printf(" ---------------- ");
    }
    printf("\n");

    printf("%-2d", gantt_chart[0][0]);
    for (i = 0; i < gantt_index; i++) {
        printf("              %-2d", gantt_chart[i][1]);
    }
    printf("\n");

    return 0;
}