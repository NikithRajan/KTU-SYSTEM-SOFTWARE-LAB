#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int at, bt, ct, tat, wt;
} Process;

void completiontime(Process p[], int s) {
    p[0].ct = p[0].at + p[0].bt;
    for (int i = 1; i < s; i++) {
        if (p[i].at > p[i-1].ct) {
            p[i].ct = p[i].at + p[i].bt;
        } else {
            p[i].ct = p[i-1].ct + p[i].bt;
        }
    }
}

void turnAroundTime(Process p[], int s) {
    for (int i = 0; i < s; i++) {
        p[i].tat = p[i].ct - p[i].at;
    }
}

void WaitingTime(Process p[], int s) {
    for (int i = 0; i < s; i++) {
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void fcfs(Process p[], int s) {
    completiontime(p, s);
    turnAroundTime(p, s);
    WaitingTime(p, s);

    int ttat = 0, ttwt = 0;
    printf("Process id\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for (int i = 0; i < s; i++) {
        ttat += p[i].tat;
        ttwt += p[i].wt;
        printf("\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("The average waiting time is: %.2f\n", (float)ttwt / s);
    printf("The average Turn Around Time is: %.2f\n", (float)ttat / s);
}

int main() {
    Process p[] = {{0, 8, 0, 0, 0}, {1, 1, 0, 0, 0}, {2, 3, 0, 0, 0}, {3, 2, 0, 0, 0}, {4, 6, 0, 0, 0}};
    int s = sizeof(p) / sizeof(p[0]);
    fcfs(p, s);
    return 0;
}
