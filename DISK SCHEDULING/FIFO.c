#include<stdio.h>
#include<stdlib.h>
void fcfs(int requests[],int n ,int head){
    int total=0;
    int current = head;
    int alloted[n+1];
    alloted[0]=head;
    for(int i = 0 ; i<n ; i++){
        total+=abs(current-requests[i]);
        current=requests[i];
        alloted[i+1]=requests[i];
    }
    printf("Head movements:");
    for(int i = 0 ; i<n ; i++){
        printf("%d->",alloted[i]);
    }
    printf("Total head movements:%d",total);
}
void main(){
    int n , head;
    printf("Enter the no requests:");
    scanf("%d",&n);
    int requests[n];
    printf("enter the requests:");
    for(int i = 0; i<n ; i++){
        scanf("%d",&requests[i]);
    }
    printf("Enter the disk head");
    scanf("%d",&head);
    fcfs(requests,n,head);
}
