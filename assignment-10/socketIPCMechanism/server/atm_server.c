#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

CRITICAL_SECTION cs;

DWORD WINAPI handleClient(void *arg) {
    SOCKET client = *(SOCKET *)arg;
    int choice, amount, balance;
    FILE *fp;
    char msg[100];

    recv(client, (char *)&choice, sizeof(int), 0);

    EnterCriticalSection(&cs);
    fp = fopen("accountDB.txt", "r+");
    fscanf(fp, "%d", &balance);

    if (choice == 1) {
        recv(client, (char *)&amount, sizeof(int), 0);
        if (amount > balance)
            strcpy(msg, "Insufficient Balance");
        else {
            balance -= amount;
            rewind(fp);
            fprintf(fp, "%d", balance);
            strcpy(msg, "Withdrawal Successful");
        }
    } else if (choice == 2) {
        recv(client, (char *)&amount, sizeof(int), 0);
        balance += amount;
        rewind(fp);
        fprintf(fp, "%d", balance);
        strcpy(msg, "Deposit Successful");
    } else {
        sprintf(msg, "Current Balance: %d", balance);
    }

    fclose(fp);
    LeaveCriticalSection(&cs);

    send(client, msg, strlen(msg), 0);
    closesocket(client);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in addr;
    int size = sizeof(addr);

    WSAStartup(MAKEWORD(2,2), &wsa);
    InitializeCriticalSection(&cs);

    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr *)&addr, sizeof(addr));
    listen(server, 5);

    printf("ATM Server Running...\n");

    while (1) {
        client = accept(server, (struct sockaddr *)&addr, &size);
        CreateThread(NULL, 0, handleClient, &client, 0, NULL);
    }
}
