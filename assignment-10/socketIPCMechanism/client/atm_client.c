#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    int choice, amount;
    char buffer[100];

    WSAStartup(MAKEWORD(2,2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("1.Withdraw\n2.Deposit\n3.Display Balance\n");
    scanf("%d", &choice);
    send(sock, (char *)&choice, sizeof(int), 0);

    if (choice == 1 || choice == 2) {
        scanf("%d", &amount);
        send(sock, (char *)&amount, sizeof(int), 0);
    }

    recv(sock, buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);

    closesocket(sock);
    WSACleanup();
    return 0;
}
