#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int pid,at,bt,ct,tat,wt;
}process;

void completionTime(process p[],int s){
    p[0].ct = p[0].bt;
    for(int i = 0 ; i<s ; i++){
        p[i].ct = p[i-1].ct+p[i].bt;
    }
}
void turnAroundTime(process p[],int s){
    for(int i = 0 ; i<s ; i++){
        p[i].tat = p[i].ct-p[i].at;
    }
}
void waitingTime(process p[],int s){
    for(int i  = 0 ; i<s ; i++){
        p[i].wt= p[i].tat-p[i].bt;
    }
}
void averageTime(process p[],int s){
    completionTime(p,s);
    turnAroundTime(p,s);
    waitingTime(p,s);
    int total_tat = 0 ,total_wt = 0;
    printf("Process ID\tArrival Time\t Burst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for(int i = 0 ; i<s ;i++){
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
               printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Average tat = %f\n", (float)total_tat / s);
    printf("Average wt = %f\n", (float)total_wt / s);
}
void main(){
    process p[] = {{1,2,4},{2,4,7},{3,5,8}};
    int s = sizeof(p)/sizeof(p[0]);
    averageTime(p,s);
}



