#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC 50
#define MAX_PID 1000

#define READY 0
#define RUNNING 1
#define WAITING 2
#define TERMINATED 3
#define KILLED 4

typedef struct {
    char pname[40];
    int pid;
    int cpuTime;
    int ioAt;
    int ioTime;
    int cpuDone;
    int cpuLeft;
    int ioLeft;
    int endTime;
    int killedAt;
    int state;
} Process;

typedef struct {
    int data[200];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int val) {
    q->data[q->rear++] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    return q->data[q->front++];
}

void loadProcesses(Process proc[], int count, int pidIndex[]) {
    for (int i = 0; i < count; i++) {
        char x[10], y[10];
        scanf("%s %d %d %s %s",
              proc[i].pname,
              &proc[i].pid,
              &proc[i].cpuTime,
              x, y);

        proc[i].ioAt = strcmp(x, "-") == 0 ? -1 : atoi(x);
        proc[i].ioTime = strcmp(y, "-") == 0 ? 0 : atoi(y);

        proc[i].cpuDone = 0;
        proc[i].cpuLeft = proc[i].cpuTime;
        proc[i].ioLeft = 0;
        proc[i].endTime = -1;
        proc[i].killedAt = -1;
        proc[i].state = READY;

        pidIndex[proc[i].pid] = i;
    }
}

void sortKillEvents(int pid[], int time[], int k) {
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (time[j] < time[i]) {
                int t = time[i]; time[i] = time[j]; time[j] = t;
                int p = pid[i]; pid[i] = pid[j]; pid[j] = p;
            }
        }
    }
}

void applyKillEvents(Process proc[], int pidIndex[], int currentTime,
                     int killPid[], int killTime[],
                     int *killPtr, int totalKills,
                     int *runningIdx, int *doneCount) {

    while (*killPtr < totalKills && killTime[*killPtr] == currentTime) {
        int idx = pidIndex[killPid[*killPtr]];
        if (idx != -1 && proc[idx].state < TERMINATED) {
            proc[idx].state = KILLED;
            proc[idx].killedAt = currentTime;
            proc[idx].endTime = currentTime;
            (*doneCount)++;
            if (*runningIdx == idx)
                *runningIdx = -1;
        }
        (*killPtr)++;
    }
}

void runCPU(Process proc[], Queue *readyQ, Queue *waitQ,
            int *runningIdx, int currentTime, int *doneCount) {

    if (*runningIdx == -1 && !isEmpty(readyQ)) {
        *runningIdx = dequeue(readyQ);
        proc[*runningIdx].state = RUNNING;
    }

    if (*runningIdx != -1) {
        proc[*runningIdx].cpuDone++;
        proc[*runningIdx].cpuLeft--;

        if (proc[*runningIdx].cpuLeft == 0) {
            proc[*runningIdx].state = TERMINATED;
            proc[*runningIdx].endTime = currentTime + 1;
            (*doneCount)++;
            *runningIdx = -1;
        }
        else if (proc[*runningIdx].ioAt >= 0 &&
                 proc[*runningIdx].cpuDone == proc[*runningIdx].ioAt &&
                 proc[*runningIdx].ioTime > 0) {

            proc[*runningIdx].state = WAITING;
            proc[*runningIdx].ioLeft = proc[*runningIdx].ioTime;
            enqueue(waitQ, *runningIdx);
            *runningIdx = -1;
        }
    }
}

void updateIO(Process proc[], Queue *readyQ, Queue *waitQ) {
    Queue tempQ;
    initQueue(&tempQ);

    while (!isEmpty(waitQ)) {
        int idx = dequeue(waitQ);
        if (proc[idx].state == KILLED) continue;

        proc[idx].ioLeft--;
        if (proc[idx].ioLeft == 0) {
            proc[idx].state = READY;
            enqueue(readyQ, idx);
        } else {
            enqueue(&tempQ, idx);
        }
    }
    *waitQ = tempQ;
}

void printOutput(Process proc[], int count) {
    for (int i = 0; i < count; i++) {
        if (proc[i].state == KILLED) {
            printf("%d %s %d %d KILLED at %d - -\n",
                   proc[i].pid,
                   proc[i].pname,
                   proc[i].cpuTime,
                   proc[i].ioTime,
                   proc[i].killedAt);
        } else {
            int tat = proc[i].endTime;
            int wt = tat - proc[i].cpuTime - proc[i].ioTime;
            printf("%d %s %d %d %d %d\n",
                   proc[i].pid,
                   proc[i].pname,
                   proc[i].cpuTime,
                   proc[i].ioTime,
                   tat, wt);
        }
    }
}

int main() {
    Process proc[MAX_PROC];
    int pidIndex[MAX_PID];
    memset(pidIndex, -1, sizeof(pidIndex));

    int n;
    scanf("%d", &n);
    loadProcesses(proc, n, pidIndex);

    int k;
    scanf("%d", &k);

    int killPid[50], killTime[50];
    for (int i = 0; i < k; i++)
        scanf("%d %d", &killPid[i], &killTime[i]);

    sortKillEvents(killPid, killTime, k);

    Queue readyQ, waitQ;
    initQueue(&readyQ);
    initQueue(&waitQ);

    for (int i = 0; i < n; i++)
        enqueue(&readyQ, i);

    int currentTime = 0;
    int doneCount = 0;
    int runningIdx = -1;
    int killPtr = 0;

    while (doneCount < n) {
        applyKillEvents(proc, pidIndex, currentTime,
                        killPid, killTime,
                        &killPtr, k,
                        &runningIdx, &doneCount);

        runCPU(proc, &readyQ, &waitQ,
               &runningIdx, currentTime, &doneCount);

        updateIO(proc, &readyQ, &waitQ);

        currentTime++;
    }

    printOutput(proc, n);
    return 0;
}
