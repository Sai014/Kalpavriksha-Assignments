#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAX_PID 1000

#define READY 0
#define RUNNING 1
#define WAITING 2
#define TERMINATED 3
#define KILLED 4

typedef struct {
    char name[40];
    int pid;
    int cpuBurst, ioStart, ioDuration;
    int executedCpu, remainingCpu, ioLeft;
    int finishTime, killedTime;
    int state;
} Process;

typedef struct {
    int q[200];
    int f, r;
} Queue;

void initQ(Queue *q) { q->f = q->r = 0; }
int empty(Queue *q) { return q->f == q->r; }
void push(Queue *q, int x) { q->q[q->r++] = x; }
int pop(Queue *q) { return empty(q) ? -1 : q->q[q->f++]; }

int main() {
    Process p[MAX];
    int pidMap[MAX_PID];
    memset(pidMap, -1, sizeof(pidMap));

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char a[10], b[10];
        scanf("%s %d %d %s %s",
              p[i].name, &p[i].pid, &p[i].cpuBurst, a, b);

        p[i].ioStart = strcmp(a, "-") == 0 ? -1 : atoi(a);
        p[i].ioDuration = strcmp(b, "-") == 0 ? 0 : atoi(b);

        p[i].executedCpu = 0;
        p[i].remainingCpu = p[i].cpuBurst;
        p[i].ioLeft = 0;
        p[i].finishTime = -1;
        p[i].killedTime = -1;
        p[i].state = READY;

        pidMap[p[i].pid] = i;
    }

    int k;
    scanf("%d", &k);

    int killPid[50], killTime[50];
    for (int i = 0; i < k; i++)
        scanf("%d %d", &killPid[i], &killTime[i]);

    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
            if (killTime[j] < killTime[i]) {
                int t = killTime[i]; killTime[i] = killTime[j]; killTime[j] = t;
                int x = killPid[i]; killPid[i] = killPid[j]; killPid[j] = x;
            }

    Queue ready, waiting;
    initQ(&ready);
    initQ(&waiting);

    for (int i = 0; i < n; i++)
        push(&ready, i);

    int time = 0, finished = 0;
    int running = -1, killIdx = 0;

    while (finished < n) {

        while (killIdx < k && killTime[killIdx] == time) {
            int idx = pidMap[killPid[killIdx]];
            if (idx != -1 && p[idx].state < TERMINATED) {
                p[idx].state = KILLED;
                p[idx].killedTime = time;
                p[idx].finishTime = time;
                finished++;
                if (running == idx) running = -1;
            }
            killIdx++;
        }

        if (running == -1 && !empty(&ready)) {
            running = pop(&ready);
            p[running].state = RUNNING;
        }

        if (running != -1) {
            p[running].executedCpu++;
            p[running].remainingCpu--;

            if (p[running].remainingCpu == 0) {
                p[running].state = TERMINATED;
                p[running].finishTime = time + 1;
                finished++;
                running = -1;
            }
            else if (p[running].ioStart >= 0 &&
                     p[running].executedCpu == p[running].ioStart &&
                     p[running].ioDuration > 0) {
                p[running].state = WAITING;
                p[running].ioLeft = p[running].ioDuration;
                push(&waiting, running);
                running = -1;
            }
        }

        Queue nextWait;
        initQ(&nextWait);
        while (!empty(&waiting)) {
            int idx = pop(&waiting);
            if (p[idx].state == KILLED) continue;
            p[idx].ioLeft--;
            if (p[idx].ioLeft == 0) {
                p[idx].state = READY;
                push(&ready, idx);
            } else {
                push(&nextWait, idx);
            }
        }
        waiting = nextWait;

        time++;
    }

    for (int i = 0; i < n; i++) {
        if (p[i].state == KILLED) {
            printf("%d %s %d %d KILLED at %d - -\n",
                   p[i].pid, p[i].name,
                   p[i].cpuBurst, p[i].ioDuration,
                   p[i].killedTime);
        } else {
            int tat = p[i].finishTime;
            int wt = tat - p[i].cpuBurst - p[i].ioDuration;
            printf("%d %s %d %d %d %d\n",
                   p[i].pid, p[i].name,
                   p[i].cpuBurst, p[i].ioDuration,
                   tat, wt);
        }
    }

    return 0;
}
